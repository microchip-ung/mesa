// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PHY_COMMON_H_
#define _VTSS_PHY_COMMON_H_

#define MAX_SPI_DATA  50
#define MAX_VENICE_SPI_STREAM 7
#define MAX_CFG_PADDING_BYTES 3
#define MAX_VIPER_SPI_STREAM  7 + MAX_CFG_PADDING_BYTES
#define MACSEC_INGR              0x0000
#define MACSEC_EGR               0x8000
#define FC_BUFFER                0xF000
#define HOST_MAC                 0xF100
#define LINE_MAC                 0xF200
#define PROC_ID_0                0x9000
#define PROC_ID_2                0x9200

#include "vtss_phy_api.h"
#include "../src/common/vtss_phy_state.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PHY_BASE_PORT(p) (base_port(vtss_state, p))

#if defined(VTSS_CHIP_10G_PHY) || defined(VTSS_FEATURE_MACSEC)
ioreg_blk *_ioreg(ioreg_blk *io, u16 dev, BOOL is32, u32 addr);

#define CSR_RD(p, io_reg, value)     \
    {   \
       vtss_rc __rc = _csr_rd(vtss_state, p, io_reg, value); \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    }

#define CSR_WR(p, io_reg, value)                 \
    {\
      vtss_rc __rc = _csr_wr(vtss_state, p, io_reg, value); \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    }

#define CSR_WRM(p, io_reg, value, mask) \
    { \
        vtss_rc __rc = _csr_wrm(vtss_state, p, io_reg, value, mask); \
        if (__rc != VTSS_RC_OK)                  \
            return __rc;                         \
    }

vtss_rc csr_rd(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 mmd, BOOL is32, u32 addr, u32 *value);

vtss_rc csr_wr(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 mmd, BOOL is32, u32 addr, u32 value);

vtss_rc csr_wrm(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 mmd, BOOL is32, u32 addr, u32 value, u32 mask);

vtss_rc _csr_rd(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *io, u32 *value);

vtss_rc _csr_wr(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *io, u32 value);

vtss_rc _csr_wrm(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *io, u32 value, u32 mask);

vtss_rc _csr_rd_64(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *reg_low, ioreg_blk *reg_up, u64 *value);

vtss_rc _csr_wr_64(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *reg_low, ioreg_blk *reg_up, u64 value);

vtss_rc csr_rd_64(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 mmd, BOOL is32, u32 addr1, u32 addr2, u64 *value);

vtss_rc csr_wr_64(vtss_state_t *vtss_state, vtss_port_no_t port_no, u16 mmd, BOOL is32, u32 addr1, u32 addr2, u64 value);

vtss_rc _csr_warm_wrm(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *io, u32 value,u32 mask, u32 chk_mask, const char *function, const u16 line);
vtss_rc _csr_warm_wr(vtss_state_t *vtss_state, vtss_port_no_t port_no, ioreg_blk *io, u32 value, const char *function, const u16 line);
#define CSR_WARM_WRM(p, io_reg, value, mask) \
    { \
        vtss_rc __rc = _csr_warm_wrm(vtss_state, p, io_reg, value, mask, 0xFFFFFFFF, __FUNCTION__, __LINE__); \
        if (__rc != VTSS_RC_OK)                  \
            return __rc;                         \
    }
#define CSR_WARM_WR(p, io_reg, value)                 \
    {\
        vtss_rc __rc = _csr_warm_wr(vtss_state, p, io_reg, value, __FUNCTION__, __LINE__); \
        if (__rc != VTSS_RC_OK)           \
            return __rc;                  \
    }

#define CSR_COLD_WR(p, io_reg, value)                 \
    {\
    vtss_rc __rc;\
      if (!vtss_state->sync_calling_private) {\
          __rc = _csr_wr(vtss_state, p, io_reg, value); \
          if (__rc != VTSS_RC_OK)                                 \
            return __rc;                  \
      } \
    }
#define CSR_COLD_WRM(p, io_reg, value, mask) \
    { \
        vtss_rc __rc;\
      if (!vtss_state->sync_calling_private) {\
         __rc = _csr_wrm(vtss_state, p, io_reg, value, mask); \
        if (__rc != VTSS_RC_OK)                  \
            return __rc;                         \
      } \
    }
#endif
vtss_rc get_base_adr(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 dev, u32 addr, u32 *phy10g_base, u32 *target_id, u32 *offset, BOOL *use_base_port);
vtss_rc phy_type_get(vtss_state_t *vtss_state,
                     const vtss_port_no_t port_no, BOOL *const clause45);

/** \brief PHY Packet Counters */
typedef struct vtss_statistic_t_ {
#if defined(VTSS_CHIP_CU_PHY)
    vtss_phy_statistic_t counters_1g;           /**< 1G PHY counters */
#endif
#if defined(VTSS_CHIP_10G_PHY)
    vtss_phy_10g_pkt_mon_conf_t counters_10g;   /**< 10G PHY fifo_bist:MON counters */
#endif
} vtss_statistic_t;

/**
 * \brief debug function for getting phy statistics for both 1G & 10G
 *
 * \param inst [IN]     Target instance reference.
 * \param port_no [IN]  Any phy port with the chip
 * \param stats         Pointer to where to put the statistics.
 *
 * \return VTSS_RC_OK - Statistics is valid else statistics is invalid
 **/

vtss_rc vtss_statistics_get(const vtss_inst_t inst,
                             const vtss_port_no_t  port_no,
                              vtss_statistic_t *stats);

#if defined(VTSS_CHIP_10G_PHY)
/* SPI callout function for 10G Phys */
vtss_rc vtss_phy_10g_spi_read_write(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL read, u8 dev, u16 reg_num, u32 *const data);
vtss_port_no_t base_port(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_port_no_t pma_port_no(vtss_state_t *vtss_state, vtss_port_no_t port_no);
BOOL use_alternate_port(const u16 mmd, const u32 addr);
u32 get_front_port_from_channel_id(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no, const u16 ch_id, const u16 chip_no);

#endif /* #if defined(VTSS_CHIP_10G_PHY) */

/* SPI callout function for 1G Phys */
vtss_rc vtss_phy_1g_spi_read_write(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 rng_sel, BOOL read, u8 target_id, u16 offset, u32 *const data);

/* Enable or Disable MAC block */
vtss_rc phy_10g_mac_conf(vtss_state_t *vtss_state, vtss_port_no_t port_no,BOOL enable, BOOL macsec_ena);
vtss_rc phy_mac_fc_buffer_reset(vtss_state_t *vtss_state, vtss_port_no_t port_no);

/* Enable or Disable macsec clock */
vtss_rc phy_10g_macsec_clk_en(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL enable);

#if defined(VTSS_FEATURE_MACSEC)
/* Set FC Buffer frame gap compensation */
vtss_rc vtss_fc_buffer_frm_gap_set(vtss_state_t *vtss_state, vtss_port_no_t port_no, u8 frm_gap);
#endif


vtss_rc vtss_phy_callout_set(const vtss_inst_t inst,
                             const vtss_port_no_t  port_no,
                             const mepa_callout_t    *co,
                             struct mepa_callout_ctx *c);


#ifdef __cplusplus
}
#endif

#endif /* _VTSS_PHY_COMMON_H_ */
