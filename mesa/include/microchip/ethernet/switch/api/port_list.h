// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_SWITCH_API_PORT_LIST_
#define _MICROCHIP_ETHERNET_SWITCH_API_PORT_LIST_

#include <string.h>
#include <microchip/ethernet/switch/api/types.h>

/** Size of the private array size. Max port count must be less than
 *  (MESA_PORT_LIST_ARRAY_SIZE * 8) for all configurations. */
#define MESA_PORT_LIST_ARRAY_SIZE 16

#ifdef __cplusplus
struct mesa_port_list_t;
struct mesa_port_list_ref {
  public:
    mesa_port_list_ref(const mesa_port_list_ref &) = delete;
    mesa_port_list_ref &operator=(const mesa_port_list_ref &rhs);
    mesa_port_list_ref(mesa_port_list_ref &&rhs)
        : parent_(rhs.parent_), bit_idx(rhs.bit_idx) {}

    mesa_port_list_ref(mesa_port_list_t *p, size_t i)
        : parent_(p), bit_idx(i) {}

    operator bool() const;
    mesa_port_list_ref &operator=(bool b);
    mesa_port_list_ref &operator&=(bool b);
    mesa_port_list_ref &operator|=(bool b);
    mesa_port_list_ref &operator^=(bool b);

  protected:
    mesa_port_list_t *parent_ = nullptr;
    size_t bit_idx = 0;
};

extern uint32_t mesa_port_cnt(mesa_inst_t inst);

/** \brief Port list */
struct mesa_port_list_t {
    size_t array_size() const { return MESA_PORT_LIST_ARRAY_SIZE; }
    size_t max_size() const { return MESA_PORT_LIST_ARRAY_SIZE * 8; }
    size_t size() const { return mesa_port_cnt(NULL); }

    bool get(size_t bit) const {
        size_t idx = bit / 8;
        size_t mod = bit % 8;
        return (_private[idx] >> mod) & 0x1;
    }

    void set(size_t bit, bool val = true) {
        size_t idx = bit / 8;
        size_t mod = bit % 8;
        uint8_t x = 1;
        x <<= mod;

        if (val) {
            _private[idx] |= x;
        } else {
            _private[idx] &= ~x;
        }
    }

    void clr(size_t bit) { set(bit, false); }

    void clear_all() {
        for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i) _private[i] = 0;
    }

    bool is_empty() const {
        for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i) {
            if (_private[i] != 0) return false;
        }

        return true;
    }

    void set_all() {
        for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i)
            _private[i] = 0xff;
    }

    mesa_port_list_t &operator|=(const mesa_port_list_t &rhs) {
        for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i)
            _private[i] |= rhs._private[i];

        return *this;
    }

    mesa_port_list_t &operator&=(const mesa_port_list_t &rhs) {
        for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i)
            _private[i] &= rhs._private[i];

        return *this;
    }

    mesa_port_list_t operator&(const mesa_port_list_t &rhs) const {
        mesa_port_list_t res(*this);
        for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i)
            res._private[i] &= rhs._private[i];

        return res;
    }

    mesa_port_list_t operator|(const mesa_port_list_t &rhs) const {
        mesa_port_list_t res(*this);
        for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i)
            res._private[i] |= rhs._private[i];

        return res;
    }

    mesa_port_list_t operator~() const {
        mesa_port_list_t res;
        for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i)
            res._private[i] = ~_private[i];

        return res;
    }

    mesa_port_list_ref operator[](size_t bit) {
        return static_cast<mesa_port_list_ref&&>(mesa_port_list_ref(this, bit));
    }

    const bool operator[](size_t bit) const { return get(bit); }

    uint8_t _private[MESA_PORT_LIST_ARRAY_SIZE] = { 0 };
};

inline bool operator==(const mesa_port_list_t &rhs,
                       const mesa_port_list_t &lhs) {
    for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i)
        if (rhs._private[i] != lhs._private[i])
            return false;
    return true;
}

inline bool operator!=(const mesa_port_list_t &rhs,
                       const mesa_port_list_t &lhs) {
    for (size_t i = 0; i < MESA_PORT_LIST_ARRAY_SIZE; ++i)
        if (rhs._private[i] != lhs._private[i])
            return true;
    return false;
}

inline mesa_port_list_ref::operator bool() const {
    return parent_->get(bit_idx);
}

inline mesa_port_list_ref &mesa_port_list_ref::operator=(
        const mesa_port_list_ref &rhs) {
    parent_->set(bit_idx, (bool)rhs);
    return *this;
}

inline mesa_port_list_ref &mesa_port_list_ref::operator=(bool b) {
    parent_->set(bit_idx, b);
    return *this;
}

inline mesa_port_list_ref &mesa_port_list_ref::operator&=(bool b) {
    bool p = parent_->get(bit_idx);
    bool n = p & b;
    parent_->set(bit_idx, n);
    return *this;
}

inline mesa_port_list_ref &mesa_port_list_ref::operator|=(bool b) {
    bool p = parent_->get(bit_idx);
    bool n = p | b;
    parent_->set(bit_idx, n);
    return *this;
}

inline mesa_port_list_ref &mesa_port_list_ref::operator^=(bool b) {
    bool p = parent_->get(bit_idx);
    bool n = p ^ b;
    parent_->set(bit_idx, n);
    return *this;
}

template <typename T, size_t size>
inline size_t MESA_ARRSZ(T(&)[size]) {
    return size;
}

// TODO
inline size_t MESA_ARRSZ(const mesa_port_list_t &t) { return 5; }

// hacks...
inline void memcpy(mesa_port_list_t &dst, const mesa_port_list_t &src, size_t) {
    dst = src;
}

void memcpy(void *dst, const mesa_port_list_t *src, size_t);
void memcpy(mesa_port_list_t *dst, const void *src, size_t);

inline int memcmp(const mesa_port_list_t &s1, const mesa_port_list_t &s2,
                  size_t) {
    return memcmp(s1._private, s2._private, sizeof(s1._private));
}

inline void memset(mesa_port_list_t &s, int c, size_t ) {
    if (c)
        s.set_all();
    else
        s.clear_all();
}


#else   // __cplusplus

typedef struct {
    uint8_t _private[MESA_PORT_LIST_ARRAY_SIZE];
} mesa_port_list_t;

static inline void mesa_port_list_clear(mesa_port_list_t *l)
{
    memset(l->_private, 0, sizeof(l->_private));
}

static inline void mesa_port_list_set(mesa_port_list_t *l, int bit, mesa_bool_t val)
{
    size_t idx = bit / 8;
    size_t mod = bit % 8;
    uint8_t x = 1;
    x <<= mod;

    if (val) {
        l->_private[idx] |= x;
    } else {
        l->_private[idx] &= ~x;
    }
}

static inline int mesa_port_list_get(const mesa_port_list_t *l, int bit)
{
        size_t idx = bit / 8;
        size_t mod = bit % 8;
        return (l->_private[idx] >> mod) & 0x1;
}


#endif  // __cplusplus
#endif  // _MICROCHIP_ETHERNET_SWITCH_API_PORT_LIST_
