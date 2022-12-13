// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <microchip/ethernet/switch/api.h>
#include "microchip/ethernet/board/api.h"
#include <json-c/json.h>

extern meba_inst_t meba_global_inst;

typedef struct {
    int         idx;
    mesa_bool_t error;
    char        *ptr;
    char        buf[1024];
    json_object *params;
    json_object *result;
} json_rpc_req_t;

typedef mesa_rc (* json_rpc_cb_t)(json_rpc_req_t *req);

typedef struct {
    const char    *name;
    json_rpc_cb_t cb;
} json_rpc_method_t;

extern json_rpc_method_t json_rpc_table[];

#define MESA_RC(expr) { mesa_rc _rc = (expr); if (_rc != MESA_RC_OK) { req->error = 1; return _rc; } }

mesa_rc json_rpc_call(json_rpc_req_t *req, mesa_rc rc);

// Any object
mesa_rc json_rpc_get_idx_json_object(json_rpc_req_t *req, json_object *obj, int *idx, json_object **obj_value);
mesa_rc json_rpc_get_name_json_object(json_rpc_req_t *req, json_object *obj, const char *name, json_object **obj_value);

// Object
mesa_rc json_rpc_new(json_rpc_req_t *req, json_object **obj);
mesa_rc json_rpc_add_name_json_object(json_rpc_req_t *req, json_object *obj, const char *name, json_object *obj_value);

// Array
mesa_rc json_rpc_array_new(json_rpc_req_t *req, json_object **obj);
mesa_rc json_rpc_add_json_array(json_rpc_req_t *req, json_object *obj, json_object *obj_value);

// NULL
mesa_rc json_rpc_add_json_null(json_rpc_req_t *req, json_object *obj);

// String
mesa_rc json_rpc_get_idx_json_string(json_rpc_req_t *req, json_object *obj, int *idx, const char **value);
mesa_rc json_rpc_get_name_json_string(json_rpc_req_t *req, json_object *obj, const char *name, const char **value);
mesa_rc json_rpc_add_json_string(json_rpc_req_t *req, json_object *obj, const char *value);
mesa_rc json_rpc_add_name_json_string(json_rpc_req_t *req, json_object *obj, const char *name, const char *value);

// Integer
mesa_rc json_rpc_get_idx_uint8_t(json_rpc_req_t *req, json_object *obj, int *idx, uint8_t *value);
mesa_rc json_rpc_get_idx_int8_t(json_rpc_req_t *req, json_object *obj, int *idx, int8_t *value);
mesa_rc json_rpc_get_idx_uint16_t(json_rpc_req_t *req, json_object *obj, int *idx, uint16_t *value);
mesa_rc json_rpc_get_idx_int16_t(json_rpc_req_t *req, json_object *obj, int *idx, int16_t *value);
mesa_rc json_rpc_get_idx_uint32_t(json_rpc_req_t *req, json_object *obj, int *idx, uint32_t *value);
mesa_rc json_rpc_get_idx_int32_t(json_rpc_req_t *req, json_object *obj, int *idx, int32_t *value);
mesa_rc json_rpc_get_idx_uint64_t(json_rpc_req_t *req, json_object *obj, int *idx, uint64_t *value);
mesa_rc json_rpc_get_idx_int64_t(json_rpc_req_t *req, json_object *obj, int *idx, int64_t *value);
mesa_rc json_rpc_get_name_uint8_t(json_rpc_req_t *req, json_object *obj, const char *name, uint8_t *value);
mesa_rc json_rpc_get_name_int8_t(json_rpc_req_t *req, json_object *obj, const char *name, int8_t *value);
mesa_rc json_rpc_get_name_uint16_t(json_rpc_req_t *req, json_object *obj, const char *name, uint16_t *value);
mesa_rc json_rpc_get_name_int16_t(json_rpc_req_t *req, json_object *obj, const char *name, int16_t *value);
mesa_rc json_rpc_get_name_uint32_t(json_rpc_req_t *req, json_object *obj, const char *name, uint32_t *value);
mesa_rc json_rpc_get_name_int32_t(json_rpc_req_t *req, json_object *obj, const char *name, int32_t *value);
mesa_rc json_rpc_get_name_uint64_t(json_rpc_req_t *req, json_object *obj, const char *name, uint64_t *value);
mesa_rc json_rpc_get_name_int64_t(json_rpc_req_t *req, json_object *obj, const char *name, int64_t *value);
mesa_rc json_rpc_get_uint8_t(json_rpc_req_t *req, json_object *obj, uint8_t *value);
mesa_rc json_rpc_get_int8_t(json_rpc_req_t *req, json_object *obj, int8_t *value);
mesa_rc json_rpc_get_uint16_t(json_rpc_req_t *req, json_object *obj, uint16_t *value);
mesa_rc json_rpc_get_int16_t(json_rpc_req_t *req, json_object *obj, int16_t *value);
mesa_rc json_rpc_get_uint32_t(json_rpc_req_t *req, json_object *obj, uint32_t *value);
mesa_rc json_rpc_get_int32_t(json_rpc_req_t *req, json_object *obj, int32_t *value);
mesa_rc json_rpc_get_uint64_t(json_rpc_req_t *req, json_object *obj, uint64_t *value);
mesa_rc json_rpc_get_int64_t(json_rpc_req_t *req, json_object *obj, int64_t *value);
mesa_rc json_rpc_add_uint8_t(json_rpc_req_t *req, json_object *obj, uint8_t *value);
mesa_rc json_rpc_add_int8_t(json_rpc_req_t *req, json_object *obj, int8_t *value);
mesa_rc json_rpc_add_uint16_t(json_rpc_req_t *req, json_object *obj, uint16_t *value);
mesa_rc json_rpc_add_int16_t(json_rpc_req_t *req, json_object *obj, int16_t *value);
mesa_rc json_rpc_add_uint32_t(json_rpc_req_t *req, json_object *obj, uint32_t *value);
mesa_rc json_rpc_add_int32_t(json_rpc_req_t *req, json_object *obj, int32_t *value);
mesa_rc json_rpc_add_uint64_t(json_rpc_req_t *req, json_object *obj, uint64_t *value);
mesa_rc json_rpc_add_int64_t(json_rpc_req_t *req, json_object *obj, int64_t *value);
mesa_rc json_rpc_add_name_uint8_t(json_rpc_req_t *req, json_object *obj, const char *name, uint8_t *value);
mesa_rc json_rpc_add_name_int8_t(json_rpc_req_t *req, json_object *obj, const char *name, int8_t *value);
mesa_rc json_rpc_add_name_uint16_t(json_rpc_req_t *req, json_object *obj, const char *name, uint16_t *value);
mesa_rc json_rpc_add_name_int16_t(json_rpc_req_t *req, json_object *obj, const char *name, int16_t *value);
mesa_rc json_rpc_add_name_uint32_t(json_rpc_req_t *req, json_object *obj, const char *name, uint32_t *value);
mesa_rc json_rpc_add_name_int32_t(json_rpc_req_t *req, json_object *obj, const char *name, int32_t *value);
mesa_rc json_rpc_add_name_uint64_t(json_rpc_req_t *req, json_object *obj, const char *name, uint64_t *value);
mesa_rc json_rpc_add_name_int64_t(json_rpc_req_t *req, json_object *obj, const char *name, int64_t *value);

mesa_rc json_rpc_add_name_int(json_rpc_req_t *req, json_object *obj, const char *name, int *value);
mesa_rc json_rpc_add_int(json_rpc_req_t *req, json_object *obj, int *value);

mesa_rc json_rpc_get_idx_int(json_rpc_req_t *req, json_object *obj, int *idx, int *value);
mesa_rc json_rpc_get_name_int(json_rpc_req_t *req, json_object *obj, const char *name, int *value);
mesa_rc json_rpc_get_int(json_rpc_req_t *req, json_object *obj, int *value);

// Boolean
mesa_rc json_rpc_get_idx_mesa_bool_t(json_rpc_req_t *req, json_object *obj, int *idx, mesa_bool_t *value);
mesa_rc json_rpc_get_name_mesa_bool_t(json_rpc_req_t *req, json_object *obj, const char *name, mesa_bool_t *value);
mesa_rc json_rpc_add_mesa_bool_t(json_rpc_req_t *req, json_object *obj, mesa_bool_t *value);
mesa_rc json_rpc_add_name_mesa_bool_t(json_rpc_req_t *req, json_object *obj, const char *name, mesa_bool_t *value);

// Portlist
mesa_rc json_rpc_get_idx_mesa_port_list_t(json_rpc_req_t *req, json_object *obj, int *idx, mesa_port_list_t *port_list);
mesa_rc json_rpc_get_name_mesa_port_list_t(json_rpc_req_t *req, json_object *obj, const char *name, mesa_port_list_t *port_list);
mesa_rc json_rpc_add_mesa_port_list_t(json_rpc_req_t *req, json_object *obj, mesa_port_list_t *port_list);
mesa_rc json_rpc_add_name_mesa_port_list_t(json_rpc_req_t *req, json_object *obj, const char *name, mesa_port_list_t *port_list);

// Unions
mesa_rc json_rpc_get2_mesa_ace_t(json_rpc_req_t *req, json_object *obj, mesa_ace_t *parm);
mesa_rc json_rpc_add2_mesa_ace_t(json_rpc_req_t *req, json_object *obj, mesa_ace_t *parm);
mesa_rc json_rpc_get2_mesa_routing_entry_t(json_rpc_req_t *req, json_object *obj, mesa_routing_entry_t *parm);
mesa_rc json_rpc_add2_mesa_routing_entry_t(json_rpc_req_t *req, json_object *obj, mesa_routing_entry_t *parm);
mesa_rc json_rpc_get2_mesa_routing_mc_entry_t(json_rpc_req_t *req, json_object *obj, mesa_routing_mc_entry_t *parm);
mesa_rc json_rpc_add2_mesa_routing_mc_entry_t(json_rpc_req_t *req, json_object *obj, mesa_routing_mc_entry_t *parm);
mesa_rc json_rpc_get2_mesa_vce_key_t(json_rpc_req_t *req, json_object *obj, mesa_vce_key_t *parm);
mesa_rc json_rpc_add2_mesa_vce_key_t(json_rpc_req_t *req, json_object *obj, mesa_vce_key_t *parm);
mesa_rc json_rpc_get2_mesa_ip_addr_t(json_rpc_req_t *req, json_object *obj, mesa_ip_addr_t *parm);
mesa_rc json_rpc_add2_mesa_ip_addr_t(json_rpc_req_t *req, json_object *obj, mesa_ip_addr_t *parm);
mesa_rc json_rpc_get2_mesa_qce_key_t(json_rpc_req_t *req, json_object *obj, mesa_qce_key_t *parm);
mesa_rc json_rpc_add2_mesa_qce_key_t(json_rpc_req_t *req, json_object *obj, mesa_qce_key_t *parm);
mesa_rc json_rpc_get2_mesa_vcap_vr_t(json_rpc_req_t *req, json_object *obj, mesa_vcap_vr_t *parm);
mesa_rc json_rpc_add2_mesa_vcap_vr_t(json_rpc_req_t *req, json_object *obj, mesa_vcap_vr_t *parm);
mesa_rc json_rpc_get2_mesa_packet_tx_info_t(json_rpc_req_t *req, json_object *obj, mesa_packet_tx_info_t *parm);
mesa_rc json_rpc_add2_mesa_packet_tx_info_t(json_rpc_req_t *req, json_object *obj, mesa_packet_tx_info_t *parm);
mesa_rc json_rpc_get2_mesa_qos_ingress_map_t(json_rpc_req_t *req, json_object *obj, mesa_qos_ingress_map_t *parm);
mesa_rc json_rpc_add2_mesa_qos_ingress_map_t(json_rpc_req_t *req, json_object *obj, mesa_qos_ingress_map_t *parm);
mesa_rc json_rpc_get2_mesa_qos_egress_map_t(json_rpc_req_t *req, json_object *obj, mesa_qos_egress_map_t *parm);
mesa_rc json_rpc_add2_mesa_qos_egress_map_t(json_rpc_req_t *req, json_object *obj, mesa_qos_egress_map_t *parm);
