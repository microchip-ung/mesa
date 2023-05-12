// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include <mesa-rpc.h>
#include "trace.h"
#include "main.h"
#include "port.h"
#include "cli.h"

static mscc_appl_trace_module_t trace_module = {
    .name = "json_rpc"
};

enum {
    TRACE_GROUP_DEFAULT,
    TRACE_GROUP_CNT
};

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

// Message format: 4 bytes length field followed by data
#define JSON_RPC_HDR_LEN 4

/* - Error handling ------------------------------------------------ */

mesa_rc json_rpc_call(json_rpc_req_t *req, mesa_rc rc)
{
    if (rc != MESA_RC_OK) {
        sprintf(req->ptr, "MESA call error");
    }
    return rc;
}

static mesa_rc json_rpc_obj_type_get(json_rpc_req_t *req, struct json_object *obj, const char *name, json_type type, json_object **obj_value)
{
    if (!json_object_object_get_ex(obj, name, obj_value)) {
        sprintf(req->ptr, "name '%s' not found", name);
        return MESA_RC_ERROR;
    } else if (!json_object_is_type(*obj_value, type)) {
        sprintf(req->ptr, "name '%s' type mismatch", name);
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
}

static mesa_rc json_rpc_array_type_get(json_rpc_req_t *req, json_object *obj, int *idx, json_type type, json_object **obj_value)
{
    *obj_value = json_object_array_get_idx(obj, *idx);
    if (*obj_value == NULL) {
        sprintf(req->ptr, "array index '%u' not found", *idx);
        return MESA_RC_ERROR;
    } else if (!json_object_is_type(*obj_value, type)) {
        sprintf(req->ptr, "array index '%u' type mismatch", *idx);
        return MESA_RC_ERROR;
    }
    (*idx)++;
    return MESA_RC_OK;
}

// Get any object from array
mesa_rc json_rpc_get_idx_json_object(json_rpc_req_t *req, json_object *obj, int *idx, json_object **obj_value)
{
    *obj_value = json_object_array_get_idx(obj, *idx);
    if (*obj_value == NULL) {
        sprintf(req->ptr, "array index '%u' not found", *idx);
        return MESA_RC_ERROR;
    }
    (*idx)++;
    return MESA_RC_OK;
}

// Get any object from object
mesa_rc json_rpc_get_name_json_object(json_rpc_req_t *req, json_object *obj, const char *name, json_object **obj_value)
{
    if (!json_object_object_get_ex(obj, name, obj_value)) {
        sprintf(req->ptr, "name '%s' not found", name);
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
}

/* - Object -------------------------------------------------------- */

mesa_rc json_rpc_new(json_rpc_req_t *req, json_object **obj)
{
    *obj = json_object_new_object();
    if (*obj == NULL) {
        sprintf(req->ptr, "new: out of memory");
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
}

// Add to object
mesa_rc json_rpc_add_name_json_object(json_rpc_req_t *req, json_object *obj, const char *name, json_object *obj_value)
{
    if (obj_value == NULL) {
        sprintf(req->ptr, "name '%s', out of memory", name);
        return MESA_RC_ERROR;
    }
    json_object_object_add(obj, name, obj_value);
    return MESA_RC_OK;
}

/* - Array --------------------------------------------------------- */

mesa_rc json_rpc_array_new(json_rpc_req_t *req, json_object **obj)
{
    *obj = json_object_new_array();
    if (*obj == NULL) {
        sprintf(req->ptr, "new: out of memory");
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
}

// Add to array
mesa_rc json_rpc_add_json_array(json_rpc_req_t *req, json_object *obj, json_object *obj_value)
{
    json_object_array_add(obj, obj_value);
    return MESA_RC_OK;
}

/* - NULL ---------------------------------------------------------- */

mesa_rc json_rpc_add_json_null(json_rpc_req_t *req, json_object *obj)
{
    json_object_array_add(obj, NULL);
    return MESA_RC_OK;
}

/* - String -------------------------------------------------------- */

// Get from array
mesa_rc json_rpc_get_idx_json_string(json_rpc_req_t *req, json_object *obj, int *idx, const char **value)
{
    json_object *obj_value;

    MESA_RC(json_rpc_array_type_get(req, obj, idx, json_type_string, &obj_value));
    *value = json_object_get_string(obj_value);
    return MESA_RC_OK;
}

// Get from object
mesa_rc json_rpc_get_name_json_string(json_rpc_req_t *req, json_object *obj, const char *name, const char **value)
{
    json_object *obj_value;

    MESA_RC(json_rpc_obj_type_get(req, obj, name, json_type_string, &obj_value));
    *value = json_object_get_string(obj_value);
    return MESA_RC_OK;
}

// Add to array
mesa_rc json_rpc_add_json_string(json_rpc_req_t *req, json_object *obj, const char *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_string(value));
}

// Add to object
mesa_rc json_rpc_add_name_json_string(json_rpc_req_t *req, json_object *obj, const char *name, const char *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_string(value));
}

/* - Integer ------------------------------------------------------- */

#define U8_MIN   0x00
#define U8_MAX   0xff
#define I8_MIN   0xffffffffffffff80   /* -127 */
#define I8_MAX   0x7f
#define U16_MIN  0x0000
#define U16_MAX  0xffff
#define I16_MIN  0xffffffffffff8000   /* -32768 */
#define I16_MAX  0x7fff
#define U32_MIN  0x00000000
#define U32_MAX  0xffffffff
#define I32_MIN  0xffffffff80000000   /* -2147483648 */
#define I32_MAX  0x7fffffff
#define U64_MIN  0x0000000000000000
#define U64_MAX  0x7fffffffffffffff
#define I64_MIN  0x8000000000000000   /* -9223372036854775808 */
#define I64_MAX  0x7fffffffffffffff

static mesa_rc json_rpc_int_range_check(json_rpc_req_t *req, const char *name, json_object *obj, int64_t *value, int64_t min, int64_t max)
{
    *value = json_object_get_int64(obj);
    if (*value < min || *value > max) {
        sprintf(req->ptr, "%s: illegal value: %" PRIi64 ", legal range: [%" PRIi64 " ; %" PRIi64 "]", name, *value, min, max);
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
}

static mesa_rc json_rpc_int_get(json_rpc_req_t *req, json_object *obj, int64_t *value, int64_t min, int64_t max)
{
    return json_rpc_int_range_check(req, "raw", obj, value, min, max);
}

static mesa_rc json_rpc_obj_int_get(json_rpc_req_t *req, json_object *obj, const char *name, int64_t *value, int64_t min, int64_t max)
{
    json_object *obj_value;

    MESA_RC(json_rpc_obj_type_get(req, obj, name, json_type_int, &obj_value));
    return json_rpc_int_range_check(req, name, obj_value, value, min, max);
}

static mesa_rc json_rpc_array_int_get(json_rpc_req_t *req, json_object *obj, int *idx, int64_t *value, int64_t min, int64_t max)
{
    json_object *obj_value;
    char        name[32];

    MESA_RC(json_rpc_array_type_get(req, obj, idx, json_type_int, &obj_value));
    sprintf(name, "array index %u", *idx);
    return json_rpc_int_range_check(req, name, obj_value, value, min, max);
}

// Get from array
mesa_rc json_rpc_get_idx_uint8_t(json_rpc_req_t *req, json_object *obj, int *idx, uint8_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, U8_MIN, U8_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_idx_int8_t(json_rpc_req_t *req, json_object *obj, int *idx, int8_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, I8_MIN, I8_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_idx_uint16_t(json_rpc_req_t *req, json_object *obj, int *idx, uint16_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, U16_MIN, U16_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_idx_int16_t(json_rpc_req_t *req, json_object *obj, int *idx, int16_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, I16_MIN, I16_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_idx_uint32_t(json_rpc_req_t *req, json_object *obj, int *idx, uint32_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, U32_MIN, U32_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_idx_int32_t(json_rpc_req_t *req, json_object *obj, int *idx, int32_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, I32_MIN, I32_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_add_name_int(json_rpc_req_t *req, json_object *obj, const char *name, int *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int(*value));
}

mesa_rc json_rpc_add_int(json_rpc_req_t *req, json_object *obj, int *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int(*value));
}

mesa_rc json_rpc_get_idx_int(json_rpc_req_t *req, json_object *obj, int *idx, int *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, I32_MIN, I32_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_int(json_rpc_req_t *req, json_object *obj, int *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, I32_MIN, I32_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_name_int(json_rpc_req_t *req, json_object *obj, const char *name, int *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, I32_MIN, I32_MAX));
    *value = val;
    return MESA_RC_OK;
}


mesa_rc json_rpc_get_idx_uint64_t(json_rpc_req_t *req, json_object *obj, int *idx, uint64_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, U64_MIN, U64_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_idx_int64_t(json_rpc_req_t *req, json_object *obj, int *idx, int64_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_array_int_get(req, obj, idx, &val, I64_MIN, I64_MAX));
    *value = val;
    return MESA_RC_OK;
}

// Get from object
mesa_rc json_rpc_get_name_uint8_t(json_rpc_req_t *req, json_object *obj, const char *name, uint8_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, U8_MIN, U8_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_name_int8_t(json_rpc_req_t *req, json_object *obj, const char *name, int8_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, I8_MIN, I8_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_name_uint16_t(json_rpc_req_t *req, json_object *obj, const char *name, uint16_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, U16_MIN, U16_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_name_int16_t(json_rpc_req_t *req, json_object *obj, const char *name, int16_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, I16_MIN, I16_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_name_uint32_t(json_rpc_req_t *req, json_object *obj, const char *name, uint32_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, U32_MIN, U32_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_name_int32_t(json_rpc_req_t *req, json_object *obj, const char *name, int32_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, I32_MIN, I32_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_name_uint64_t(json_rpc_req_t *req, json_object *obj, const char *name, uint64_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, U64_MIN, U64_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_name_int64_t(json_rpc_req_t *req, json_object *obj, const char *name, int64_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_obj_int_get(req, obj, name, &val, I64_MIN, I64_MAX));
    *value = val;
    return MESA_RC_OK;
}

// Get from raw object
mesa_rc json_rpc_get_uint8_t(json_rpc_req_t *req, json_object *obj, uint8_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, U8_MIN, U8_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_int8_t(json_rpc_req_t *req, json_object *obj, int8_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, I8_MIN, I8_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_uint16_t(json_rpc_req_t *req, json_object *obj, uint16_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, U16_MIN, U16_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_int16_t(json_rpc_req_t *req, json_object *obj, int16_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, I16_MIN, I16_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_uint32_t(json_rpc_req_t *req, json_object *obj, uint32_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, U32_MIN, U32_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_int32_t(json_rpc_req_t *req, json_object *obj, int32_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, I32_MIN, I32_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_uint64_t(json_rpc_req_t *req, json_object *obj, uint64_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, U64_MIN, U64_MAX));
    *value = val;
    return MESA_RC_OK;
}

mesa_rc json_rpc_get_int64_t(json_rpc_req_t *req, json_object *obj, int64_t *value)
{
    int64_t val;

    MESA_RC(json_rpc_int_get(req, obj, &val, I64_MIN, I64_MAX));
    *value = val;
    return MESA_RC_OK;
}

// Add to array
mesa_rc json_rpc_add_uint8_t(json_rpc_req_t *req, json_object *obj, uint8_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int(*value));
}

mesa_rc json_rpc_add_int8_t(json_rpc_req_t *req, json_object *obj, int8_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int(*value));
}

mesa_rc json_rpc_add_uint16_t(json_rpc_req_t *req, json_object *obj, uint16_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int(*value));
}

mesa_rc json_rpc_add_int16_t(json_rpc_req_t *req, json_object *obj, int16_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int(*value));
}

mesa_rc json_rpc_add_uint32_t(json_rpc_req_t *req, json_object *obj, uint32_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int64(*value));
}

mesa_rc json_rpc_add_int32_t(json_rpc_req_t *req, json_object *obj, int32_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int(*value));
}

mesa_rc json_rpc_add_uint64_t(json_rpc_req_t *req, json_object *obj, uint64_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int64(*value));
}

mesa_rc json_rpc_add_int64_t(json_rpc_req_t *req, json_object *obj, int64_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_int64(*value));
}

// Add to object
mesa_rc json_rpc_add_name_uint8_t(json_rpc_req_t *req, json_object *obj, const char *name, uint8_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int(*value));
}

mesa_rc json_rpc_add_name_int8_t(json_rpc_req_t *req, json_object *obj, const char *name, int8_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int(*value));
}

mesa_rc json_rpc_add_name_uint16_t(json_rpc_req_t *req, json_object *obj, const char *name, uint16_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int(*value));
}

mesa_rc json_rpc_add_name_int16_t(json_rpc_req_t *req, json_object *obj, const char *name, int16_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int(*value));
}

mesa_rc json_rpc_add_name_uint32_t(json_rpc_req_t *req, json_object *obj, const char *name, uint32_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int64(*value));
}

mesa_rc json_rpc_add_name_int32_t(json_rpc_req_t *req, json_object *obj, const char *name, int32_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int(*value));
}

mesa_rc json_rpc_add_name_uint64_t(json_rpc_req_t *req, json_object *obj, const char *name, uint64_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int64(*value));
}

mesa_rc json_rpc_add_name_int64_t(json_rpc_req_t *req, json_object *obj, const char *name, int64_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_int64(*value));
}


/* - Boolean ------------------------------------------------------- */

// Get from array
mesa_rc json_rpc_get_idx_mesa_bool_t(json_rpc_req_t *req, json_object *obj, int *idx, mesa_bool_t *value)
{
    json_object *obj_value;

    MESA_RC(json_rpc_array_type_get(req, obj, idx, json_type_boolean, &obj_value));
    *value = json_object_get_boolean(obj_value);
    return MESA_RC_OK;
}

// Get from object
mesa_rc json_rpc_get_name_mesa_bool_t(json_rpc_req_t *req, json_object *obj, const char *name, mesa_bool_t *value)
{
    json_object *obj_value;

    MESA_RC(json_rpc_obj_type_get(req, obj, name, json_type_boolean, &obj_value));
    *value = json_object_get_boolean(obj_value);
    return MESA_RC_OK;
}

// Add to array
mesa_rc json_rpc_add_mesa_bool_t(json_rpc_req_t *req, json_object *obj, mesa_bool_t *value)
{
    return json_rpc_add_json_array(req, obj, json_object_new_boolean(*value));
}

// Add to object
mesa_rc json_rpc_add_name_mesa_bool_t(json_rpc_req_t *req, json_object *obj, const char *name, mesa_bool_t *value)
{
    return json_rpc_add_name_json_object(req, obj, name, json_object_new_boolean(*value));
}

/* - Port list ----------------------------------------------------- */

static int json_rpc_str2portlist(const char *str, mesa_port_list_t *port_list)
{
    const char     *p;
    mesa_port_no_t port_no = 0;
    int            valid = 0, error = 0;

    mesa_port_list_clear(port_list);
    for (p = str; error == 0; p++) {
        if (isdigit(*p)) {
            port_no = (port_no * 10 + (*p - '0'));
            valid = 1;
        } else if (*p == ',' || *p == '\0') {
            if (valid) {
                if (port_no < (MESA_PORT_LIST_ARRAY_SIZE * 8)) {
                    mesa_port_list_set(port_list, port_no, 1);
                    port_no = 0;
                    valid = 0;
                } else {
                    error = 1;
                }
            } else if (*p == ',') {
                error = 1;
            }
            if (*p == '\0') {
                break;
            }
        } else {
            error = 1;
        }
    }
    return error;
}

// Get from array
mesa_rc json_rpc_get_idx_mesa_port_list_t(json_rpc_req_t *req, json_object *obj, int *idx, mesa_port_list_t *port_list)
{
    json_object *obj_value;
    const char  *str;

    MESA_RC(json_rpc_array_type_get(req, obj, idx, json_type_string, &obj_value));
    str = json_object_get_string(obj_value);
    if (json_rpc_str2portlist(str, port_list)) {
        sprintf(req->ptr, "array index '%u', illegal portlist '%s'", (*idx) - 1, str);
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
}

// Get from object
mesa_rc json_rpc_get_name_mesa_port_list_t(json_rpc_req_t *req, json_object *obj, const char *name, mesa_port_list_t *port_list)
{
    json_object *obj_value;
    const char  *str;

    MESA_RC(json_rpc_obj_type_get(req, obj, name, json_type_string, &obj_value));
    str = json_object_get_string(obj_value);
    if (json_rpc_str2portlist(str, port_list)) {
        sprintf(req->ptr, "name '%s', illegal portlist '%s'", name, str);
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
}

static char *json_rpc_portlist2str(mesa_port_list_t *port_list, char *str)
{
    mesa_port_no_t port_no;
    uint32_t       port_cnt = mesa_port_cnt(NULL);
    int            first = 1;
    char           *p = str;

    *p = 0;
    for (port_no = 0; port_no < port_cnt; port_no++) {
        if (mesa_port_list_get(port_list, port_no)) {
            p += sprintf(p, "%s%u", first ? "" : ",", port_no);
            first = 0;
        }
    }
    return str;
}

// Add to array
mesa_rc json_rpc_add_mesa_port_list_t(json_rpc_req_t *req, json_object *obj, mesa_port_list_t *port_list)
{
    char str[256];

    return json_rpc_add_json_string(req, obj, json_rpc_portlist2str(port_list, str));
}

// Add to object
mesa_rc json_rpc_add_name_mesa_port_list_t(json_rpc_req_t *req, json_object *obj, const char *name, mesa_port_list_t *port_list)
{
    char str[256];

    return json_rpc_add_name_json_string(req, obj, name, json_rpc_portlist2str(port_list, str));
}

/* - Unions -------------------------------------------------------- */

mesa_rc json_rpc_get2_mesa_ace_t(json_rpc_req_t *req, json_object *obj, mesa_ace_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "frame", &obj_value));
    switch (parm->type) {
    case MESA_ACE_TYPE_ANY:
        MESA_RC(json_rpc_get_name_mesa_ace_frame_any_t(req, obj_value, "any", &parm->frame.any));
        break;
    case MESA_ACE_TYPE_ETYPE:
        MESA_RC(json_rpc_get_name_mesa_ace_frame_etype_t(req, obj_value, "etype", &parm->frame.etype));
        break;
    case MESA_ACE_TYPE_LLC:
        MESA_RC(json_rpc_get_name_mesa_ace_frame_llc_t(req, obj_value, "llc", &parm->frame.llc));
        break;
    case MESA_ACE_TYPE_SNAP:
        MESA_RC(json_rpc_get_name_mesa_ace_frame_snap_t(req, obj_value, "snap", &parm->frame.snap));
        break;
    case MESA_ACE_TYPE_ARP:
        MESA_RC(json_rpc_get_name_mesa_ace_frame_arp_t(req, obj_value, "arp", &parm->frame.arp));
        break;
    case MESA_ACE_TYPE_IPV4:
        MESA_RC(json_rpc_get_name_mesa_ace_frame_ipv4_t(req, obj_value, "ipv4", &parm->frame.ipv4));
        break;
    case MESA_ACE_TYPE_IPV6:
        MESA_RC(json_rpc_get_name_mesa_ace_frame_ipv6_t(req, obj_value, "ipv6", &parm->frame.ipv6));
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_ace_t(json_rpc_req_t *req, json_object *obj, mesa_ace_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_new(req, &obj_value));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "frame", obj_value));
    switch (parm->type) {
    case MESA_ACE_TYPE_ANY:
        MESA_RC(json_rpc_add_name_mesa_ace_frame_any_t(req, obj_value, "any", &parm->frame.any));
        break;
    case MESA_ACE_TYPE_ETYPE:
        MESA_RC(json_rpc_add_name_mesa_ace_frame_etype_t(req, obj_value, "etype", &parm->frame.etype));
        break;
    case MESA_ACE_TYPE_LLC:
        MESA_RC(json_rpc_add_name_mesa_ace_frame_llc_t(req, obj_value, "llc", &parm->frame.llc));
        break;
    case MESA_ACE_TYPE_SNAP:
        MESA_RC(json_rpc_add_name_mesa_ace_frame_snap_t(req, obj_value, "snap", &parm->frame.snap));
        break;
    case MESA_ACE_TYPE_ARP:
        MESA_RC(json_rpc_add_name_mesa_ace_frame_arp_t(req, obj_value, "arp", &parm->frame.arp));
        break;
    case MESA_ACE_TYPE_IPV4:
        MESA_RC(json_rpc_add_name_mesa_ace_frame_ipv4_t(req, obj_value, "ipv4", &parm->frame.ipv4));
        break;
    case MESA_ACE_TYPE_IPV6:
        MESA_RC(json_rpc_add_name_mesa_ace_frame_ipv6_t(req, obj_value, "ipv6", &parm->frame.ipv6));
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_routing_entry_t(json_rpc_req_t *req, json_object *obj, mesa_routing_entry_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "route", &obj_value));
    switch (parm->type) {
    case MESA_ROUTING_ENTRY_TYPE_IPV4_UC:
        MESA_RC(json_rpc_get_name_mesa_ipv4_uc_t(req, obj_value, "ipv4_uc", &parm->route.ipv4_uc));
        break;
    case MESA_ROUTING_ENTRY_TYPE_IPV6_UC:
        MESA_RC(json_rpc_get_name_mesa_ipv6_uc_t(req, obj_value, "ipv6_uc", &parm->route.ipv6_uc));
        break;
    default:
        return MESA_RC_ERROR;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_routing_entry_t(json_rpc_req_t *req, json_object *obj, mesa_routing_entry_t *parm)
{
    json_object *obj_value;
    MESA_RC(json_rpc_new(req, &obj_value));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "route", obj_value));
    switch (parm->type) {
    case MESA_ROUTING_ENTRY_TYPE_IPV4_UC:
        MESA_RC(json_rpc_add_name_mesa_ipv4_uc_t(req, obj_value, "ipv4_uc", &parm->route.ipv4_uc));
        break;
    case MESA_ROUTING_ENTRY_TYPE_IPV6_UC:
        MESA_RC(json_rpc_add_name_mesa_ipv6_uc_t(req, obj_value, "ipv6_uc", &parm->route.ipv6_uc));
        break;
    case MESA_ROUTING_ENTRY_TYPE_INVALID:
    case MESA_ROUTING_ENTRY_TYPE_IPV4_MC:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_routing_mc_entry_t(json_rpc_req_t *req, json_object *obj, mesa_routing_mc_entry_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "route", &obj_value));
    if (parm->type == MESA_RT_TYPE_IPV4_MC) {
        MESA_RC(json_rpc_get_name_mesa_ipv4_mc_t(req, obj_value, "ipv4_mc", &parm->route.ipv4_mc));
    } else {
        MESA_RC(json_rpc_get_name_mesa_ipv6_mc_t(req, obj_value, "ipv6_mc", &parm->route.ipv6_mc));
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_routing_mc_entry_t(json_rpc_req_t *req, json_object *obj, mesa_routing_mc_entry_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_new(req, &obj_value));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "route", obj_value));
    if (parm->type == MESA_RT_TYPE_IPV4_MC) {
        MESA_RC(json_rpc_add_name_mesa_ipv4_mc_t(req, obj_value, "ipv4_mc", &parm->route.ipv4_mc));
    } else {
        MESA_RC(json_rpc_add_name_mesa_ipv6_mc_t(req, obj_value, "ipv6_mc", &parm->route.ipv6_mc));
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_vce_key_t(json_rpc_req_t *req, json_object *obj, mesa_vce_key_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "frame", &obj_value));
    switch (parm->type) {
    case MESA_VCE_TYPE_ETYPE:
        MESA_RC(json_rpc_get_name_mesa_vce_frame_etype_t(req, obj_value, "etype", &parm->frame.etype));
        break;
    case MESA_VCE_TYPE_LLC:
        MESA_RC(json_rpc_get_name_mesa_vce_frame_llc_t(req, obj_value, "llc", &parm->frame.llc));
        break;
    case MESA_VCE_TYPE_SNAP:
        MESA_RC(json_rpc_get_name_mesa_vce_frame_snap_t(req, obj_value, "snap", &parm->frame.snap));
        break;
    case MESA_VCE_TYPE_IPV4:
        MESA_RC(json_rpc_get_name_mesa_vce_frame_ipv4_t(req, obj_value, "ipv4", &parm->frame.ipv4));
        break;
    case MESA_VCE_TYPE_IPV6:
        MESA_RC(json_rpc_get_name_mesa_vce_frame_ipv6_t(req, obj_value, "ipv6", &parm->frame.ipv6));
        break;
    case MESA_VCE_TYPE_ANY:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_vce_key_t(json_rpc_req_t *req, json_object *obj, mesa_vce_key_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_new(req, &obj_value));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "frame", obj_value));
    switch (parm->type) {
    case MESA_VCE_TYPE_ETYPE:
        MESA_RC(json_rpc_add_name_mesa_vce_frame_etype_t(req, obj_value, "etype", &parm->frame.etype));
        break;
    case MESA_VCE_TYPE_LLC:
        MESA_RC(json_rpc_add_name_mesa_vce_frame_llc_t(req, obj_value, "llc", &parm->frame.llc));
        break;
    case MESA_VCE_TYPE_SNAP:
        MESA_RC(json_rpc_add_name_mesa_vce_frame_snap_t(req, obj_value, "snap", &parm->frame.snap));
        break;
    case MESA_VCE_TYPE_IPV4:
        MESA_RC(json_rpc_add_name_mesa_vce_frame_ipv4_t(req, obj_value, "ipv4", &parm->frame.ipv4));
        break;
    case MESA_VCE_TYPE_IPV6:
        MESA_RC(json_rpc_add_name_mesa_vce_frame_ipv6_t(req, obj_value, "ipv6", &parm->frame.ipv6));
        break;
    case MESA_VCE_TYPE_ANY:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_ip_addr_t(json_rpc_req_t *req, json_object *obj, mesa_ip_addr_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "addr", &obj_value));
    switch (parm->type) {
    case MESA_IP_TYPE_IPV4:
        MESA_RC(json_rpc_get_name_uint32_t(req, obj_value, "ipv4", &parm->addr.ipv4));
        break;
    case MESA_IP_TYPE_IPV6:
        MESA_RC(json_rpc_get_name_mesa_ipv6_t(req, obj_value, "ipv6", &parm->addr.ipv6));
        break;
    case MESA_IP_TYPE_NONE:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_ip_addr_t(json_rpc_req_t *req, json_object *obj, mesa_ip_addr_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_new(req, &obj_value));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "addr", obj_value));
    switch (parm->type) {
    case MESA_IP_TYPE_IPV4:
        MESA_RC(json_rpc_add_name_uint32_t(req, obj_value, "ipv4", &parm->addr.ipv4));
        break;
    case MESA_IP_TYPE_IPV6:
        MESA_RC(json_rpc_add_name_mesa_ipv6_t(req, obj_value, "ipv6", &parm->addr.ipv6));
        break;
    case MESA_IP_TYPE_NONE:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_qce_key_t(json_rpc_req_t *req, json_object *obj, mesa_qce_key_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "frame", &obj_value));
    switch (parm->type) {
    case MESA_QCE_TYPE_ETYPE:
        MESA_RC(json_rpc_get_name_mesa_qce_frame_etype_t(req, obj_value, "etype", &parm->frame.etype));
        break;
    case MESA_QCE_TYPE_LLC:
        MESA_RC(json_rpc_get_name_mesa_qce_frame_llc_t(req, obj_value, "llc", &parm->frame.llc));
        break;
    case MESA_QCE_TYPE_SNAP:
        MESA_RC(json_rpc_get_name_mesa_qce_frame_snap_t(req, obj_value, "snap", &parm->frame.snap));
        break;
    case MESA_QCE_TYPE_IPV4:
        MESA_RC(json_rpc_get_name_mesa_qce_frame_ipv4_t(req, obj_value, "ipv4", &parm->frame.ipv4));
        break;
    case MESA_QCE_TYPE_IPV6:
        MESA_RC(json_rpc_get_name_mesa_qce_frame_ipv6_t(req, obj_value, "ipv6", &parm->frame.ipv6));
        break;
    case MESA_QCE_TYPE_ANY:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_qce_key_t(json_rpc_req_t *req, json_object *obj, mesa_qce_key_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_new(req, &obj_value));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "frame", obj_value));
    switch (parm->type) {
    case MESA_QCE_TYPE_ETYPE:
        MESA_RC(json_rpc_add_name_mesa_qce_frame_etype_t(req, obj_value, "etype", &parm->frame.etype));
        break;
    case MESA_QCE_TYPE_LLC:
        MESA_RC(json_rpc_add_name_mesa_qce_frame_llc_t(req, obj_value, "llc", &parm->frame.llc));
        break;
    case MESA_QCE_TYPE_SNAP:
        MESA_RC(json_rpc_add_name_mesa_qce_frame_snap_t(req, obj_value, "snap", &parm->frame.snap));
        break;
    case MESA_QCE_TYPE_IPV4:
        MESA_RC(json_rpc_add_name_mesa_qce_frame_ipv4_t(req, obj_value, "ipv4", &parm->frame.ipv4));
        break;
    case MESA_QCE_TYPE_IPV6:
        MESA_RC(json_rpc_add_name_mesa_qce_frame_ipv6_t(req, obj_value, "ipv6", &parm->frame.ipv6));
        break;
    case MESA_QCE_TYPE_ANY:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_vcap_vr_t(json_rpc_req_t *req, json_object *obj, mesa_vcap_vr_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "vr", &obj_value));
    switch (parm->type) {
    case MESA_VCAP_VR_TYPE_VALUE_MASK:
        MESA_RC(json_rpc_get_name_mesa_vcap_vr_v_t(req, obj_value, "v", &parm->vr.v));
        break;
    default:
        MESA_RC(json_rpc_get_name_mesa_vcap_vr_r_t(req, obj_value, "r", &parm->vr.r));
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_vcap_vr_t(json_rpc_req_t *req, json_object *obj, mesa_vcap_vr_t *parm)
{
    json_object *obj_value;

    MESA_RC(json_rpc_new(req, &obj_value));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "vr", obj_value));
    switch (parm->type) {
    case MESA_VCAP_VR_TYPE_RANGE_INCLUSIVE:
    case MESA_VCAP_VR_TYPE_RANGE_EXCLUSIVE:
        MESA_RC(json_rpc_add_name_mesa_vcap_vr_r_t(req, obj_value, "r", &parm->vr.r));
        break;
    default:
        MESA_RC(json_rpc_add_name_mesa_vcap_vr_v_t(req, obj_value, "v", &parm->vr.v));
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_packet_tx_info_t(json_rpc_req_t *req, json_object *obj, mesa_packet_tx_info_t *parm)
{
    // The 'vstax' union is currently unused
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_packet_tx_info_t(json_rpc_req_t *req, json_object *obj, mesa_packet_tx_info_t *parm)
{
    // The 'vstax' union is currently unused
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_qos_ingress_map_t(json_rpc_req_t *req, json_object *obj, mesa_qos_ingress_map_t *parm)
{
    json_object *obj_value, *obj_maps, *obj_pcp_dei, *obj_dpd;
    int         i, j;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "maps", &obj_maps));
    switch (parm->key) {
    case MESA_QOS_INGRESS_MAP_KEY_PCP:
        MESA_RC(json_rpc_get_name_json_object(req, obj_maps, "pcp", &obj_value));
        for (i = 0; i < 8; ) {
            MESA_RC(json_rpc_get_idx_mesa_qos_ingress_map_values_t(req, obj_value, &i, &parm->maps.pcp[i]));
        }
        break;
    case MESA_QOS_INGRESS_MAP_KEY_PCP_DEI:
        MESA_RC(json_rpc_get_name_json_object(req, obj_maps, "pcp_dei", &obj_pcp_dei));
        for (i = 0; i < 8; ) {
            MESA_RC(json_rpc_get_idx_json_object(req, obj_pcp_dei, &i, &obj_value));
            for (j = 0; j < 2; ) {
                MESA_RC(json_rpc_get_idx_mesa_qos_ingress_map_values_t(req, obj_value, &j, &parm->maps.pcp_dei[i - 1][j]));
            }
        }
        break;
    case MESA_QOS_INGRESS_MAP_KEY_DSCP:
        MESA_RC(json_rpc_get_name_json_object(req, obj_maps, "dscp", &obj_value));
        for (i = 0; i < 64; ) {
            MESA_RC(json_rpc_get_idx_mesa_qos_ingress_map_values_t(req, obj_value, &i, &parm->maps.dscp[i]));
        }
        break;
    case MESA_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI:
        MESA_RC(json_rpc_get_name_json_object(req, obj_maps, "dpd", &obj_dpd));
        MESA_RC(json_rpc_get_name_json_object(req, obj_dpd, "dscp", &obj_value));
        for (i = 0; i < 64; ) {
            MESA_RC(json_rpc_get_idx_mesa_qos_ingress_map_values_t(req, obj_value, &i, &parm->maps.dpd.dscp[i]));
        }
        MESA_RC(json_rpc_get_name_json_object(req, obj_dpd, "pcp_dei", &obj_pcp_dei));
        for (i = 0; i < 8; ) {
            MESA_RC(json_rpc_get_idx_json_object(req, obj_pcp_dei, &i, &obj_value));
            for (j = 0; j < 2; ) {
                MESA_RC(json_rpc_get_idx_mesa_qos_ingress_map_values_t(req, obj_value, &j, &parm->maps.dpd.pcp_dei[i - 1][j]));
            }
        }
        break;
    default:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_qos_ingress_map_t(json_rpc_req_t *req, json_object *obj, mesa_qos_ingress_map_t *parm)
{
    json_object *obj_value, *obj_maps, *obj_pcp_dei, *obj_dpd;
    int         i, j;

    MESA_RC(json_rpc_new(req, &obj_maps));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "maps", obj_maps));
    switch (parm->key) {
    case MESA_QOS_INGRESS_MAP_KEY_PCP:
        MESA_RC(json_rpc_array_new(req, &obj_value));
        MESA_RC(json_rpc_add_name_json_object(req, obj_maps, "pcp", obj_value));
        for (i = 0; i < 8; i++) {
            MESA_RC(json_rpc_add_mesa_qos_ingress_map_values_t(req, obj_value, &parm->maps.pcp[i]));
        }
        break;
    case MESA_QOS_INGRESS_MAP_KEY_PCP_DEI:
        MESA_RC(json_rpc_array_new(req, &obj_pcp_dei));
        MESA_RC(json_rpc_add_name_json_object(req, obj_maps, "pcp_dei", obj_pcp_dei));
        for (i = 0; i < 8; i++) {
            MESA_RC(json_rpc_array_new(req, &obj_value));
            MESA_RC(json_rpc_add_json_array(req, obj_pcp_dei, obj_value));
            for (j = 0; j < 2; j++) {
                MESA_RC(json_rpc_add_mesa_qos_ingress_map_values_t(req, obj_value, &parm->maps.pcp_dei[i][j]));
            }
        }
        break;
    case MESA_QOS_INGRESS_MAP_KEY_DSCP:
        MESA_RC(json_rpc_array_new(req, &obj_value));
        MESA_RC(json_rpc_add_name_json_object(req, obj_maps, "dscp", obj_value));
        for (i = 0; i < 64; i++) {
            MESA_RC(json_rpc_add_mesa_qos_ingress_map_values_t(req, obj_value, &parm->maps.dscp[i]));
        }
        break;
    case MESA_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI:
        MESA_RC(json_rpc_new(req, &obj_dpd));
        MESA_RC(json_rpc_add_name_json_object(req, obj_dpd, "dpd", obj_maps));
        MESA_RC(json_rpc_array_new(req, &obj_value));
        MESA_RC(json_rpc_add_name_json_object(req, obj_dpd, "dscp", obj_value));
        for (i = 0; i < 64; i++) {
            MESA_RC(json_rpc_add_mesa_qos_ingress_map_values_t(req, obj_value, &parm->maps.dpd.dscp[i]));
        }
        MESA_RC(json_rpc_array_new(req, &obj_pcp_dei));
        MESA_RC(json_rpc_add_name_json_object(req, obj_dpd, "pcp_dei", obj_pcp_dei));
        for (i = 0; i < 8; i++) {
            MESA_RC(json_rpc_array_new(req, &obj_value));
            MESA_RC(json_rpc_add_json_array(req, obj_pcp_dei, obj_value));
            for (j = 0; j < 2; j++) {
                MESA_RC(json_rpc_add_mesa_qos_ingress_map_values_t(req, obj_value, &parm->maps.dpd.pcp_dei[i][j]));
            }
        }
        break;
    default:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_get2_mesa_qos_egress_map_t(json_rpc_req_t *req, json_object *obj, mesa_qos_egress_map_t *parm)
{
    json_object *obj_value, *obj_maps, *obj_cosid_dpl, *obj_dscp_dpl;
    int         i, j;

    MESA_RC(json_rpc_get_name_json_object(req, obj, "maps", &obj_maps));
    switch (parm->key) {
    case MESA_QOS_EGRESS_MAP_KEY_COSID:
        MESA_RC(json_rpc_get_name_json_object(req, obj_maps, "cosid", &obj_value));
        for (i = 0; i < 8; ) {
            MESA_RC(json_rpc_get_idx_mesa_qos_egress_map_values_t(req, obj_value, &i, &parm->maps.cosid[i]));
        }
        break;
    case MESA_QOS_EGRESS_MAP_KEY_COSID_DPL:
        MESA_RC(json_rpc_get_name_json_object(req, obj_maps, "cosid_dpl", &obj_cosid_dpl));
        for (i = 0; i < 8; ) {
            MESA_RC(json_rpc_get_idx_json_object(req, obj_cosid_dpl, &i, &obj_value));
            for (j = 0; j < 4; ) {
                MESA_RC(json_rpc_get_idx_mesa_qos_egress_map_values_t(req, obj_value, &j, &parm->maps.cosid_dpl[i - 1][j]));
            }
        }
        break;
    case MESA_QOS_EGRESS_MAP_KEY_DSCP:
        MESA_RC(json_rpc_get_name_json_object(req, obj_maps, "dscp", &obj_value));
        for (i = 0; i < 64; ) {
            MESA_RC(json_rpc_get_idx_mesa_qos_egress_map_values_t(req, obj_value, &i, &parm->maps.dscp[i]));
        }
        break;
    case MESA_QOS_EGRESS_MAP_KEY_DSCP_DPL:
        MESA_RC(json_rpc_get_name_json_object(req, obj_maps, "dscp_dpl", &obj_dscp_dpl));
        for (i = 0; i < 64; ) {
            MESA_RC(json_rpc_get_idx_json_object(req, obj_dscp_dpl, &i, &obj_value));
            for (j = 0; j < 4; ) {
                MESA_RC(json_rpc_get_idx_mesa_qos_egress_map_values_t(req, obj_value, &j, &parm->maps.dscp_dpl[i - 1][j]));
            }
        }
        break;
    default:
        break;
    }
    return MESA_RC_OK;
}

mesa_rc json_rpc_add2_mesa_qos_egress_map_t(json_rpc_req_t *req, json_object *obj, mesa_qos_egress_map_t *parm)
{
    json_object *obj_value, *obj_maps, *obj_cosid_dpl, *obj_dscp_dpl;
    int         i, j;

    MESA_RC(json_rpc_new(req, &obj_maps));
    MESA_RC(json_rpc_add_name_json_object(req, obj, "maps", obj_maps));
    switch (parm->key) {
    case MESA_QOS_EGRESS_MAP_KEY_COSID:
        MESA_RC(json_rpc_array_new(req, &obj_value));
        MESA_RC(json_rpc_add_name_json_object(req, obj_maps, "cosid", obj_value));
        for (i = 0; i < 8; i++) {
            MESA_RC(json_rpc_add_mesa_qos_egress_map_values_t(req, obj_value, &parm->maps.cosid[i]));
        }
        break;
    case MESA_QOS_EGRESS_MAP_KEY_COSID_DPL:
        MESA_RC(json_rpc_array_new(req, &obj_cosid_dpl));
        MESA_RC(json_rpc_add_name_json_object(req, obj_maps, "cosid_dpl", obj_cosid_dpl));
        for (i = 0; i < 8; i++) {
            MESA_RC(json_rpc_array_new(req, &obj_value));
            MESA_RC(json_rpc_add_json_array(req, obj_cosid_dpl, obj_value));
            for (j = 0; j < 4; j++) {
                MESA_RC(json_rpc_add_mesa_qos_egress_map_values_t(req, obj_value, &parm->maps.cosid_dpl[i][j]));
            }
        }
        break;
    case MESA_QOS_EGRESS_MAP_KEY_DSCP:
        MESA_RC(json_rpc_array_new(req, &obj_value));
        MESA_RC(json_rpc_add_name_json_object(req, obj_maps, "dscp", obj_value));
        for (i = 0; i < 64; i++) {
            MESA_RC(json_rpc_add_mesa_qos_egress_map_values_t(req, obj_value, &parm->maps.dscp[i]));
        }
        break;
    case MESA_QOS_EGRESS_MAP_KEY_DSCP_DPL:
        MESA_RC(json_rpc_array_new(req, &obj_dscp_dpl));
        MESA_RC(json_rpc_add_name_json_object(req, obj_maps, "dscp_dpl", obj_dscp_dpl));
        for (i = 0; i < 64; i++) {
            MESA_RC(json_rpc_array_new(req, &obj_value));
            MESA_RC(json_rpc_add_json_array(req, obj_dscp_dpl, obj_value));
            for (j = 0; j < 4; j++) {
                MESA_RC(json_rpc_add_mesa_qos_egress_map_values_t(req, obj_value, &parm->maps.dscp_dpl[i][j]));
            }
        }
        break;
    default:
        break;
    }
    return MESA_RC_OK;
}

/* - Static method table ------------------------------------------- */

// Maximum 64 DSCPs and 4 DPLs
#define DSCP_DPL_MAX (64 * 4)

static mesa_rc mesa_rpc_mesa_qos_dscp_dpl_conf_get(json_rpc_req_t *req)
{
    uint32_t                 dpl_cnt, dpl, dscp;
    mesa_qos_dscp_dpl_conf_t conf[DSCP_DPL_MAX];
    json_object              *obj_dscp, *obj_dpl;

    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &dpl_cnt));
    MESA_RC(json_rpc_call(req, mesa_qos_dscp_dpl_conf_get(NULL, dpl_cnt, conf)));
    MESA_RC(json_rpc_add_json_null(req, req->result));
    MESA_RC(json_rpc_array_new(req, &obj_dscp));
    MESA_RC(json_rpc_add_json_array(req, req->result, obj_dscp));
    for (dscp = 0; dscp < 64; dscp++) {
        MESA_RC(json_rpc_array_new(req, &obj_dpl));
        MESA_RC(json_rpc_add_json_array(req, obj_dscp, obj_dpl));
        for (dpl = 0; dpl < dpl_cnt; dpl++) {
            MESA_RC(json_rpc_add_mesa_qos_dscp_dpl_conf_t(req, obj_dpl, &conf[dscp * dpl_cnt + dpl]));
        }
    }
    return MESA_RC_OK;
}

static mesa_rc mesa_rpc_mesa_qos_dscp_dpl_conf_set(json_rpc_req_t *req)
{
    uint32_t                 dpl_cnt;
    int                      dpl, dscp;
    mesa_qos_dscp_dpl_conf_t conf[DSCP_DPL_MAX];
    json_object              *obj_dscp, *obj_dpl;

    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &dpl_cnt));
    MESA_RC(json_rpc_get_idx_json_object(req, req->params, &req->idx, &obj_dscp));
    for (dscp = 0; dscp < 64; ) {
        MESA_RC(json_rpc_get_idx_json_object(req, obj_dscp, &dscp, &obj_dpl));
        for (dpl = 0; dpl < dpl_cnt; ) {
            MESA_RC(json_rpc_get_idx_mesa_qos_dscp_dpl_conf_t(req, obj_dpl, &dpl, &conf[(dscp - 1) * dpl_cnt + dpl]));
        }
    }
    MESA_RC(json_rpc_call(req, mesa_qos_dscp_dpl_conf_set(NULL, dpl_cnt, conf)));
    MESA_RC(json_rpc_add_json_null(req, req->result));
    return MESA_RC_OK;
}

// Maximum is 4 DPLs and 3 groups
#define WRED_MAX 12

static mesa_rc mesa_rpc_mesa_qos_dpl_group_conf_get(json_rpc_req_t *req)
{
    uint32_t                  dpl_cnt, grp_cnt, dpl, grp;
    mesa_qos_dpl_group_conf_t conf[WRED_MAX];
    json_object               *obj_dpl, *obj_grp;

    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &dpl_cnt));
    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &grp_cnt));
    MESA_RC(json_rpc_call(req, mesa_qos_dpl_group_conf_get(NULL, dpl_cnt, grp_cnt, conf)));
    MESA_RC(json_rpc_add_json_null(req, req->result));
    MESA_RC(json_rpc_add_json_null(req, req->result));
    MESA_RC(json_rpc_array_new(req, &obj_dpl));
    MESA_RC(json_rpc_add_json_array(req, req->result, obj_dpl));
    for (dpl = 0; dpl < dpl_cnt; dpl++) {
        MESA_RC(json_rpc_array_new(req, &obj_grp));
        MESA_RC(json_rpc_add_json_array(req, obj_dpl, obj_grp));
        for (grp = 0; grp < grp_cnt; grp++) {
            MESA_RC(json_rpc_add_mesa_qos_dpl_group_conf_t(req, obj_grp, &conf[dpl * grp_cnt + grp]));
        }
    }
    return MESA_RC_OK;
}

static mesa_rc mesa_rpc_mesa_qos_dpl_group_conf_set(json_rpc_req_t *req)
{
    uint32_t                  dpl_cnt, grp_cnt;
    int                       dpl, grp;
    mesa_qos_dpl_group_conf_t conf[WRED_MAX];
    json_object               *obj_dpl, *obj_grp;

    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &dpl_cnt));
    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &grp_cnt));
    MESA_RC(json_rpc_get_idx_json_object(req, req->params, &req->idx, &obj_dpl));
    for (dpl = 0; dpl < dpl_cnt; ) {
        MESA_RC(json_rpc_get_idx_json_object(req, obj_dpl, &dpl, &obj_grp));
        for (grp = 0; grp < grp_cnt; ) {
            MESA_RC(json_rpc_get_idx_mesa_qos_dpl_group_conf_t(req, obj_grp, &grp, &conf[(dpl - 1) * grp_cnt + grp]));
        }
    }
    MESA_RC(json_rpc_call(req, mesa_qos_dpl_group_conf_set(NULL, dpl_cnt, grp_cnt, conf)));
    MESA_RC(json_rpc_add_json_null(req, req->result));
    MESA_RC(json_rpc_add_json_null(req, req->result));
    return MESA_RC_OK;
}

static struct {
    uint32_t dummy;
} ts_timestamp_alloc_cx;

static mesa_ts_timestamp_t ts_cb_ts;

static void ts_timestamp_alloc_cb(void                 *context,
                                  uint32_t             port_no,
                                  mesa_ts_timestamp_t  *ts)
{
    ts_cb_ts = *ts;
}

static mesa_rc tx_timestamp_get(json_rpc_req_t *req)
{
    MESA_RC(json_rpc_add_json_null(req, req->result));
    MESA_RC(json_rpc_add_mesa_ts_timestamp_t(req, req->result, &ts_cb_ts));

    return MESA_RC_OK;
}

static const char *string_mesa_core_clock_freq_t(mesa_core_clock_freq_t *parm)
{
    return (
            *parm == MESA_CORE_CLOCK_DEFAULT ? "MESA_CORE_CLOCK_DEFAULT" :
            *parm == MESA_CORE_CLOCK_250MHZ ? "MESA_CORE_CLOCK_250MHZ" :
            *parm == MESA_CORE_CLOCK_500MHZ ? "MESA_CORE_CLOCK_500MHZ" :
            *parm == MESA_CORE_CLOCK_625MHZ ? "MESA_CORE_CLOCK_625MHZ" :
            "MESA_CORE_CLOCK_DEFAULT");
}

static mesa_rc misc_get(json_rpc_req_t *req)
{
    mesa_init_conf_t  conf;
    json_object       *obj_value;

    MESA_RC(json_rpc_add_json_null(req, req->result));

    MESA_RC(json_rpc_call(req, mesa_init_conf_get(NULL, &conf)));

    MESA_RC(json_rpc_new(req, &obj_value));
    MESA_RC(json_rpc_add_name_json_string(req, obj_value, "core_clock_freq", string_mesa_core_clock_freq_t(&conf.core_clock.freq)));

    MESA_RC(json_rpc_add_json_array(req, req->result, obj_value));

    return MESA_RC_OK;
}

// Get struct
static mesa_rc json_rpc_get_mesa_ts_timestamp_alloc_t(json_rpc_req_t *req, json_object *obj, mesa_ts_timestamp_alloc_t *parm)
{
    MESA_RC(json_rpc_get_name_uint64_t(req, obj, "port_mask", &parm->port_mask));
    parm->context = &ts_timestamp_alloc_cx;
    parm->cb = ts_timestamp_alloc_cb;
    return MESA_RC_OK;
}

static mesa_rc mesa_rpc_mesa_tx_timestamp_idx_alloc(json_rpc_req_t *req)
{
    mesa_ts_timestamp_alloc_t conf;
    mesa_ts_id_t              ts_id;
    json_object               *obj_alloc;

    MESA_RC(json_rpc_get_idx_json_object(req, req->params, &req->idx, &obj_alloc));
    MESA_RC(json_rpc_get_mesa_ts_timestamp_alloc_t(req, obj_alloc, &conf));

    MESA_RC(json_rpc_call(req, mesa_tx_timestamp_idx_alloc(NULL, &conf, &ts_id)));
    MESA_RC(json_rpc_add_json_null(req, req->result));
    MESA_RC(json_rpc_add_mesa_ts_id_t(req, req->result, &ts_id));
    return MESA_RC_OK;
}

static mesa_rc appl_port_status_get(json_rpc_req_t *req)
{
    mesa_port_no_t      port_no;
    mesa_port_status_t  status;

    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &port_no));

    MESA_RC(json_rpc_call(req, mscc_appl_port_status_get(port_no, &status)));
    MESA_RC(json_rpc_add_json_null(req, req->result));
    MESA_RC(json_rpc_add_mesa_port_status_t(req, req->result, &status));
    return MESA_RC_OK;
}

static mesa_rc mesa_rpc_packet_tx_frame(json_rpc_req_t *req)
{
    mesa_packet_tx_info_t tx_info;
    uint8_t frame[1600];
    uint32_t length;
    json_object *obj;
    int i, len, max = sizeof(frame);

    MESA_RC(json_rpc_get_idx_mesa_packet_tx_info_t(req, req->params, &req->idx, &tx_info));
    MESA_RC(json_rpc_array_type_get(req, req->params, &req->idx, json_type_array, &obj));
    len = json_object_array_length(obj);
    if (len > max) {
        sprintf(req->ptr, "frame array length: %u, max: %u", len, max);
        MESA_RC(MESA_RC_ERROR);
    }
    for (i = 0; i < len; ) {
        MESA_RC(json_rpc_get_idx_uint8_t(req, obj, &i, &frame[i]));
    }
    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &length));
    MESA_RC(json_rpc_call(req, mesa_packet_tx_frame(NULL, &tx_info, frame, length)));
    json_object_array_add(req->result, NULL);
    json_object_array_add(req->result, NULL);
    json_object_array_add(req->result, NULL);
    return MESA_RC_OK;
}

mesa_rc intr_ev_get(const char *name, uint32_t idx, uint32_t *cnt);

/* Update the internal timestamp table, from HW */
static void test_ts_phy_fifo_read( const mepa_port_no_t           port_no,
                                   const mepa_timestamp_t     *const fifo_ts,
                                   const mepa_ts_fifo_sig_t   *const sig,
                                   const mepa_ts_fifo_status_t status)
{
    mepa_ts_fifo_sig_t sig_loc;
    memset(&sig_loc, 0, sizeof(sig_loc));
    memcpy(&sig_loc, sig, sizeof(mepa_ts_fifo_sig_t));
    T_D("PHY Fifo read: port_no %u, msg_type:  %d, type %d, domain %d, seq %d\n", port_no,
        sig->msg_type, sig->msg_type, sig->domain_num, sig->sequence_id);
    T_D("PHY Fifo read: tx time:  Sec_Hi:%d, Sec_Low:%u,  Nsec: %u, Nsec (hex) ns %x\n",
         fifo_ts->seconds.high, fifo_ts->seconds.low, fifo_ts->nanoseconds, fifo_ts->nanoseconds);
}

static mesa_rc event_get(json_rpc_req_t *req)
{
    const char *name;
    uint32_t   idx, cnt;

    MESA_RC(json_rpc_get_idx_json_string(req, req->params, &req->idx, &name));
    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &idx));
    MESA_RC(json_rpc_call(req, intr_ev_get(name, idx, &cnt)));
    MESA_RC(json_rpc_add_uint32_t(req, req->result, &cnt));
    return MESA_RC_OK;
}

static mesa_rc mesa_rpc_meba_phy_ts_fifo_read_install(json_rpc_req_t *req)
{
    mepa_port_no_t port_no;
    mepa_ts_fifo_read_t rd_cb = &test_ts_phy_fifo_read;

    MESA_RC(json_rpc_get_idx_uint32_t(req, req->params, &req->idx, &port_no));
    MESA_RC(json_rpc_call(req, meba_phy_ts_fifo_read_install(meba_global_inst, port_no, rd_cb)));
    json_object_array_add(req->result, NULL);
    json_object_array_add(req->result, NULL);

    return MESA_RC_OK;
}


static json_rpc_method_t json_rpc_static_table[] = {
    { "mesa_qos_dscp_dpl_conf_get", mesa_rpc_mesa_qos_dscp_dpl_conf_get },
    { "mesa_qos_dscp_dpl_conf_set", mesa_rpc_mesa_qos_dscp_dpl_conf_set },
    { "mesa_qos_dpl_group_conf_get", mesa_rpc_mesa_qos_dpl_group_conf_get },
    { "mesa_qos_dpl_group_conf_set", mesa_rpc_mesa_qos_dpl_group_conf_set },
    { "mesa_tx_timestamp_idx_alloc", mesa_rpc_mesa_tx_timestamp_idx_alloc },
    { "mesa_tx_timestamp_get", tx_timestamp_get },
    { "mscc_appl_port_status_get", appl_port_status_get },
    { "mesa_misc_get", misc_get },
    { "mesa_packet_tx_frame", mesa_rpc_packet_tx_frame },
    { "mesa_event_get", event_get },
    { NULL, NULL}
};

static json_rpc_method_t json_rpc_phy_static_table[] = {
    { "meba_phy_ts_fifo_read_install" , mesa_rpc_meba_phy_ts_fifo_read_install },
    { NULL , NULL }
};



/* - JSON-RPC parser ----------------------------------------------- */

static int find_and_call_method(const char *method_name, json_rpc_req_t *req)
{
    int                 found = 0;
    json_rpc_method_t   *method;

    for (method = json_rpc_table; method->cb != NULL && !found; method++) {
        if (!strcmp(method->name, method_name)) {
            found = 1;
            method->cb(req);
        }
    }
    for (method = json_rpc_static_table; method->cb != NULL && !found; method++) {
        if (!strcmp(method->name, method_name)) {
            found = 1;
            method->cb(req);
        }
    }
    for (method = json_rpc_phy_static_table; method->cb != NULL && !found; method++) {
        if (!strcmp(method->name, method_name)) {
            found = 1;
            method->cb(req);
        }
    }


    return (found);
}

static int json_cli(int argc, const char **argv)
{
    int found = 0;
    json_rpc_req_t req = {};
    const char *m_str = 0, *p_str = 0;
    json_object       *obj_result = 0;
    const char *reply;

    req.ptr = req.buf;

    obj_result = json_object_new_object();
    req.result = json_object_new_array();

    if (req.result == NULL || obj_result == NULL) {
        T_I("Alloc error");

        if (obj_result)
            json_object_put(obj_result);

        if (req.result)
            json_object_put(req.result);

        return -1;
    }

    if (argc != 3) {
        cli_printf("Usage: call <method> <params>");
        return -1;
    }

    m_str = argv[1];
    p_str = argv[2];

    req.params = json_tokener_parse(p_str);
    if (req.params == NULL) {
        snprintf(req.buf, 1024, "Could not parse parameters");
        req.error = 1;
        goto OUT;
    }

    found = find_and_call_method(m_str, &req);

    if (!found) {
        snprintf(req.buf, 1024, "Method not found");
        req.error = 1;
        goto OUT;
    }

OUT:
    if (req.error) {
        json_object_object_add(obj_result, "error",
                               json_object_new_string(req.buf));
        json_object_put(req.result);
        req.result = 0;
    } else {
        json_object_object_add(obj_result, "result", req.result);
        req.result = NULL;
    }

    reply = json_object_to_json_string(obj_result);

    cli_printf("%s\n", reply);

    json_object_put(obj_result);

    if (req.error) {
        return -1;
    } else {
        return 0;
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "call <method> <params>",
        "Call an API method using JSON syntax",
        0,
        0,
        json_cli,
    },
};

static int json_rpc_parse(int fd, char *msg)
{
    json_object       *obj_req, *obj_rep, *obj_result, *obj_error, *obj_method, *obj_id;
    const char        *method_name, *reply;
    json_rpc_req_t    req = {};
    int               send_reply = 0, found = 0;
    uint32_t          len, *p;
    char              hdr[JSON_RPC_HDR_LEN];

    T_N("request: %s", msg);

    req.idx = 0;
    req.result = NULL;
    sprintf(req.buf, "internal error");
    if ((obj_req = json_tokener_parse(msg)) == NULL) {
        T_I("json_tokener_parse failed");
    } else if (!json_object_object_get_ex(obj_req, "method", &obj_method)) {
        T_I("method object not found");
    } else if (json_object_get_type(obj_method) != json_type_string) {
        T_I("method object not string");
    } else if (!json_object_object_get_ex(obj_req, "params", &req.params)) {
        T_I("params object not found");
    } else if (json_object_get_type(req.params) != json_type_array) {
        T_I("params object not array");
    } else if (!json_object_object_get_ex(obj_req, "id", &obj_id)) {
        T_I("id object not found");
    } else if ((req.result = json_object_new_array()) == NULL) {
        T_I("alloc reply object failed");
    } else {
        // Lookup and call method
        send_reply = 1;
        method_name = json_object_get_string(obj_method);
        req.ptr = req.buf;
        req.ptr += sprintf(req.ptr, "method '%s': ", method_name);

        found = find_and_call_method(method_name, &req);

        if (!found) {
            sprintf(req.ptr, "not found");
            req.error = 1;
        }
    }
    
    if (send_reply && (obj_rep = json_object_new_object()) != NULL) {
        if (req.error) {
            obj_result = NULL;
            obj_error = json_object_new_string(req.buf);
        } else {
            obj_result = req.result;
            req.result = NULL; // Ownership transferred to obj_rep below
            obj_error = NULL;
        }
        json_object_object_add(obj_rep, "result", obj_result);
        json_object_object_add(obj_rep, "error", obj_error);
        json_object_object_add(obj_rep, "id", json_object_get(obj_id));
        reply = json_object_to_json_string(obj_rep);
        len = strlen(reply);
        p = (uint32_t *)hdr;
        *p = htonl(len);
        T_I("reply length: %u", len);
        T_D("reply: %s", reply);
        if (write(fd, hdr, sizeof(hdr)) != sizeof(hdr) || 
            write(fd, reply, len) != len) {
            T_E("write error");
        }
        json_object_put(obj_rep);
    }

    // Free objects (the call ignores NULL object)
    json_object_put(obj_req);
    json_object_put(req.result);

    return 0;
}

typedef struct {
    int                fd;
    struct sockaddr_in addr;
    uint32_t           len;
    uint32_t           rx_cnt;
    char               *msg;
} json_rpc_con_t;

#define FD_FREE (-1)
#define JSON_RPC_CON_MAX 4
static json_rpc_con_t json_rpc_con_table[JSON_RPC_CON_MAX];

static json_rpc_con_t *json_rpc_connection_lookup(int fd)
{
    int            i;
    json_rpc_con_t *con;

    for (i = 0; i < JSON_RPC_CON_MAX; i++) {
        con = &json_rpc_con_table[i];
        if (con->fd == fd) {
            return con;
        }
    }
    return NULL;
}

static void json_rpc_connection(int fd, void *ref)
{
    int            n, error = 1;
    uint32_t       len;
    json_rpc_con_t *con;
    char           hdr[JSON_RPC_HDR_LEN], *p = hdr;

    // Lookup connection
    if ((con = json_rpc_connection_lookup(fd)) == NULL) {
        T_E("connection not found");
        return;
    }

    if (con->len == 0) {
        // Read header
        if ((n = read(fd, hdr, sizeof(hdr))) < sizeof(hdr)) {
            T_I("header small");
        } else if ((len = ntohl(*(uint32_t *)p)) == 0 || len > (100 * 1024)) {
            T_E("illegal length: %u", len);
        } else if ((con->msg = (char *)malloc(len + 1)) == NULL) {
            T_E("msg malloc failed");
        } else {
            T_I("data length: %u", len);
            con->len = len;
            return;
        }
    } else if ((n = read(fd, con->msg + con->rx_cnt, con->len - con->rx_cnt)) <= 0) {
        // Read data failed
        T_I("no data");
    } else {
        // Read data success
        error = 0;
        con->rx_cnt += n;
        if (con->rx_cnt != con->len) {
            // Message not complete
            return;
        }
        con->msg[con->len] = 0;
        error = json_rpc_parse(fd, con->msg);
    }

    // Free message
    if (con->msg) {
        free(con->msg);
    }
    memset(con, 0, sizeof(*con));

    if (error) {
        T_I("closing connection");
        close(fd);
        if (fd_read_register(fd, NULL, NULL)) {
            T_E("Failed to un-rgister fd");
        }
        con->fd = FD_FREE;
    } else {
        // Preserve file descriptor
        con->fd = fd;
    }
}

static void json_rpc_accept(int fd, void *ref)
{
    json_rpc_con_t *con;
    socklen_t      len = sizeof(con->addr);
    
    // Lookup free connection
    if ((con = json_rpc_connection_lookup(FD_FREE)) == NULL) {
        T_E("no free connection");
    } else if ((fd = accept(fd, (struct sockaddr *)&con->addr, &len)) < 0) {
        T_E("accept() failed: %s", strerror(errno));
    } else if (fd_read_register(fd, json_rpc_connection, NULL) < 0) {
        T_E("fd_read_register() failed");
    } else {
        T_N("new connection accepted");
        con->fd = fd;
    }
}

static void json_rpc_init(void)
{
    int                i, fd;
    struct sockaddr_in addr;

    T_D("enter");
    for (i = 0; i < JSON_RPC_CON_MAX; i++) {
        json_rpc_con_table[i].fd = FD_FREE;
    }
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(1234);
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        T_E("socket failed: %s", strerror(errno));
    } else if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        T_E("bind failed: %s", strerror(errno));
        close(fd);
    } else if (listen(fd, 1) < 0) {
        T_E("listen failed: %s", strerror(errno));
        close(fd);
    } else if (fd_read_register(fd, json_rpc_accept, NULL) < 0) {
        T_E("fd_read_register() failed");
        close(fd);
    }
    T_D("exit");
}

void mscc_appl_json_rpc_init(mscc_appl_init_t *init)
{
    int i;

    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        json_rpc_init();

        for (i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
            mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
        }

        break;

    default:
        break;
    }
}
