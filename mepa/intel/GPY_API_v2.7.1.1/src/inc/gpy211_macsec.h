/******************************************************************************
         Copyright 2020 - 2021 MaxLinear Inc.
         Copyright 2016 - 2020 Intel Corporation
         Copyright 2015 - 2016 Lantiq Beteiligungs-GmbH & Co. KG
         Copyright 2012 - 2014 Lantiq Deutschland GmbH

  SPDX-License-Identifier: (BSD-3-Clause OR GPL-2.0-only)

******************************************************************************/

#ifndef _GPY211_MACSEC_H_
#define _GPY211_MACSEC_H_

/** \section MACsec APIs

    \section intro_sec_macsec Introduction

    The GPY212 device supports MACsec. The variables those are commented with (-i), (-e) and (-crypto)
    are meant for applicable MACSec direction:
    An ingress-only configuration (-i), only intended for the MACsec ingress transform.
	An egress-only configuration (-e), only intended for the MACsec egress transform.
	Crypt-authenticate (-crypto). The basic cryptographic operations are applied to the packet.
	Direction (encryption or decryption) and mode is determined by the transform record.

	MACsec ingress and MACsec egress processing of performing the MACsec transformation.
*/

/** \defgroup GPY212_MACSEC_API GPY212 MACsec APIs
	\brief This chapter describes the functional APIs for MACsec.
	Note: Not supported on GPHY flavours (i.e part numbers): GPY211
	*/
/**@{*/

/** \defgroup GPY211_MACSEC_SECINIT Initialization APIs
	\brief Group of functional APIs for MACsec initialization and cleanup.
*/

/** \defgroup GPY211_MACSEC_SECTR Transform Record config APIs
	\brief Group of functional APIs for configuring transform record.
*/

/** \defgroup GPY211_MACSEC_SECSAM Secure Association Matching (SAM) rule params config APIs
	\brief Group of functional APIs for configuring SA matching rule params.
*/

/** \defgroup GPY211_MACSEC_SECFCA Secure Association Matching (SAM) Flow Control Action (FCA) config APIs
	\brief Group of functional APIs for configuring SAM flow control action.
*/

/** \defgroup GPY211_MACSEC_SECNMFCA Secure Association Matching (SAM) Non-Match Flow Control Action (FCA) config APIs
	\brief Group of functional APIs for configuring SAM Non-Match flow control action.
*/

/** \defgroup GPY211_MACSEC_SECEEX Secure Association Matching (SAM) Entry Enable config APIs
	\brief Group of functional APIs for configuring SAM entry enable flags.
*/

/** \defgroup GPY211_MACSEC_SECEEC Secure Association Matching (SAM) Entry Enable Control config APIs
	\brief Group of functional APIs for configuring SAM entry enable control.
*/

/** \defgroup GPY211_MACSEC_SECICC Ingress Consistency Check (ICC) config APIs
	\brief Group of functional APIs for configuring ingress consistency check.
*/

/** \defgroup GPY211_MACSEC_SECSTATS Statistics get APIs
	\brief Group of functional APIs for getting statistics.
*/

/** \defgroup GPY211_MACSEC_SECCCTRL Counters Control config APIs
	\brief Group of functional APIs for controlling counters.
*/

/** \defgroup GPY211_MACSEC_SECMCTRL Miscellaneous Control config APIs
	\brief Group of functional APIs for configuring misc controls.
*/

/** \defgroup GPY211_MACSEC_SECNMCTRL Secure Association Matching (SAM) No-Match Control config APIs
	\brief Group of functional APIs for configuring SAM Non-Match pkt action.
*/

/** \defgroup GPY211_MACSEC_SECSASUMM Secure Association (SA) Expiry Summary config APIs
	\brief Group of functional APIs for configuring SA expiry summary.
*/

/** \defgroup GPY211_MACSEC_SECCPC Control Packet config APIs
	\brief Group of functional APIs for control packet classification.
*/

/** \defgroup GPY211_MACSEC_OP_PROC Output Post Processor config
	\brief Group of structures for Output Post Processor config storage.
*/

/** \defgroup GPY211_MACSEC_CRYPTO Crypto Core config
	\brief Group of structures for Crypto Core config storage.
*/

/** \defgroup GPY211_MACSEC_AIC Interrupt Controller config
	\brief Group of structures for Interrupt Controller config storage.
*/

/**@}*/ /* GPY212_MACSEC_API */

/**********************
	Constant
 **********************/

/** \cond INTERNAL */
// Max number of sync retry
#define IN_FLIGHT_BUSY_RETRY 10

/** \brief Ethertype for MACSec frames */
#define ETH_PROTO_MACSEC 0x88E5
/** \brief Ethertype for MACSec frames - byte swapped of ETH_PROTO_MACSEC */
#define BYTE_SWAP_16BIT(A) ((((A) & 0xFF00) >> 8) | (((A) & 0x00FF) << 8))
#define ETH_PROTO_MACSEC_BYTE_SWAPPED BYTE_SWAP_16BIT(ETH_PROTO_MACSEC)

/** \brief EIP-160 Signature */
#define EIP160_NR_CNR 0x5FA0u
/** \brief EIP-62 Signature */
#define EIP62_NR_CNR 0xC13Eu
/** \brief Secure Channel Id size */
#define MACSEC_SCI_LEN_BYTE 8
/** \brief Secure Channel Id size */
#define MACSEC_SCI_LEN_WORD 2

/** \brief Key size for 128-bit CA type */
#define MACSEC_CA128_KEY_LEN_BYTE 16
/** \brief Key size for 256-bit CA type */
#define MACSEC_CA256_KEY_LEN_BYTE 32
/** \brief Key size for 128-bit CA type */
#define MACSEC_CA128_KEY_LEN_WORD 4
/** \brief Key size for 256-bit CA type */
#define MACSEC_CA256_KEY_LEN_WORD 8
/** \brief Max Key size among all CA types */
#define MACSEC_KEY_LEN_BYTE 32

/** \brief H-Key size */
#define MACSEC_HKEY_LEN_BYTE 16
/** \brief H-Key size */
#define MACSEC_HKEY_LEN_WORD 4
/** \brief Context Salt size */
#define MACSEC_CSALT_LEN_WORD 3

/** \brief Secure Channel ID size */
#define MACSEC_SCI_LEN_BYTE 8
/** \brief Short SCI size */
#define MACSEC_SSCI_LEN_BYTE 4
/** \brief Context Salt size */
#define MACSEC_SALT_LEN_BYTE 12

/** \brief Max number of SA rules supported */
#define MACSEC_MAX_SA_RULES 32

/** \brief Base Address of EIP_160S_IG_TR_PAGE0 */
#define EIP_160S_IG_TR_PAGE0_BASE 0x00B00000u
/** \brief Offest Address of EIP_160S_IG_TR_PAGE0 */
#define EIP_160S_IG_TR_PAGE0_OFFSET 0x00000000u
/** \brief Offest Address of EIP_160S_IG_SAM_RULES_PAGE0 */
#define EIP_160S_IG_SAM_RULES_PAGE0_OFFSET 0x00004000u


/** \brief Base Address of EIP_160S_EG_TR_PAGE0 */
#define EIP_160S_EG_TR_PAGE0_BASE 0x00B20000u
/** \brief Offest Address of EIP_160S_EG_TR_PAGE0 */
#define EIP_160S_EG_TR_PAGE0_OFFSET 0x00000000u
/** \brief Offest Address of EIP_160S_EG_SAM_RULES_PAGE0 */
#define EIP_160S_EG_SAM_RULES_PAGE0_OFFSET 0x00004000u

/** \brief Association Number */
#define MACSEC_MAX_AN 4
/** \brief CCW Fields */
/** \brief Field SN - Sequence Number */
#define CCW_EIPX_TR_CCW_SN_POS 28
/** \brief Field SN - Sequence Number */
#define CCW_EIPX_TR_CCW_SN_MASK 0x03000000u
/** \brief Field AN - Association Number */
#define CCW_EIPX_TR_CCW_AN_POS 26
/** \brief Field AN - Association Number */
#define CCW_EIPX_TR_CCW_AN_MASK 0x0C000000u
/** \brief Field CA - Crypto algorithm */
#define CCW_EIPX_TR_CCW_CA_POS 17
/** \brief Field CA - Crypto algorithm */
#define CCW_EIPX_TR_CCW_CA_MASK 0x000E0000u

/** \brief SA Update Control Fields */
/** \brief Field AN - Index of the next SA.  */
#define SA_UPDATE_SA_INDEX_POS 0
/** \brief Field AN - Index of the next SA */
#define SA_UPDATE_SA_INDEX_MASK 0x00003FFFu
/** \brief Field AN - SA expired summary register */
#define SA_UPDATE_SA_EXPIRED_IRQ_POS 14
/** \brief Field AN - SA expired summary register */
#define SA_UPDATE_SA_EXPIRED_IRQ_MASK 0x00004000u
/** \brief Field AN - Next SA index valid */
#define SA_UPDATE_SA_INDEX_VALID_POS 15
/** \brief Field AN - Next SA index valid */
#define SA_UPDATE_SA_INDEX_VALID_MASK 0x00008000u
/** \brief Field AN - Index of the flow control that holds the current SA */
#define SA_UPDATE_FLOW_INDEX_POS 16
/** \brief Field AN - Index of the flow control that holds the current SA */
#define SA_UPDATE_FLOW_INDEX_MASK 0x7FFF0000u
/** \brief Field AN - SA index update enable */
#define SA_UPDATE_SA_INDEX_UPDATE_EN_POS 31
/** \brief Field AN - SA index update enable */
#define SA_UPDATE_SA_INDEX_UPDATE_EN_MASK 0x80000000u

/** \brief TR context_size in words */
#define ING_MAX_TR_SIZE_WORDS 20
/** \brief TR context_size in bytes */
#define ING_MAX_TR_SIZE_BYTES (ING_MAX_TR_SIZE_WORDS * 4)

/** \brief TR context_size in words */
#define EGR_MAX_TR_SIZE_WORDS 24
/** \brief TR context_size in bytes */
#define EGR_MAX_TR_SIZE_BYTES (EGR_MAX_TR_SIZE_WORDS * 4)

/** \brief SAM params size in words */
#define IE_MAX_SAM_SIZE_WORDS 16
/** \brief SAM params size in bytes */
#define IE_MAX_SAM_SIZE_BYTES (IE_MAX_SAM_SIZE_WORDS * 4)

/** \brief Ingress Consistency Check params size in words */
#define ICC_MAX_MATCH_SIZE_WORDS 4
/** \brief Ingress Consistency Check params size in bytes */
#define ICC_MAX_MATCH_SIZE_BYTES (ICC_MAX_MATCH_SIZE_WORDS * 4)

/** \brief CPC params size in bytes */
#define IE_MAX_CPC_SIZE_BYTES 16
/** \brief CPC rule for DA + EHT size in bytes */
#define IE_CPC_DA_ETH_SIZE_BYTES 8
/** \brief CPC rule for EHT size in bytes */
#define IE_CPC_ETH_SIZE_BYTES 4

/** \brief SAM FCA size in bytes */
#define IE_MAX_SAM_FCA_BYTES 4

/** \brief SA statistic size in words */
#define MAX_SA_STATS_SIZE_WORDS 32
/** \brief SA statistic size in bytes */
#define MAX_SA_STATS_SIZE_BYTES (MAX_SA_STATS_SIZE_WORDS * 4)
/** \brief SA statistic size in words */
#define MAX_VLAN_COUNT_SUMM_WORDS 3
/** \brief Max Ingress SA counters */
#define MAX_ING_SA_COUNTERS 11
/** \brief Max Egress SA counters */
#define MAX_EGR_SA_COUNTERS 4
/** \brief Max VLAN counters for both Ingress & Egress */
#define MAX_VLAN_COUNTERS 5
/** \brief Max Ingress GLOBAL counters */
#define MAX_ING_GLOBAL_COUNTERS 14
/** \brief Max Egress GLOBAL counters */
#define MAX_EGR_GLOBAL_COUNTERS 5
/** \brief Max VLAN user priorities */
#define MAX_VLAN_USER_PRIORITIES 8

/** \brief Max Counter sync retry count */
#define EIP160_MAX_SYNC_RETRY_COUNT 100

/** \brief Ingress default CCW word for 32-bit PN & 128-bit AES type */
#define ING_32BPN_128KEY_DEF_CCW 0xD24BE06F
/** \brief Ingress default CCW word for 32-bit PN & 256-bit AES type */
#define ING_32BPN_256KEY_DEF_CCW 0xD24FE06F
/** \brief Ingress default CCW word for 64-bit PN & 128-bit AES type */
#define ING_64BPN_128KEY_DEF_CCW 0xE24BA0EF
/** \brief Ingress default CCW word for 64-bit PN & 256-bit AES type */
#define ING_64BPN_256KEY_DEF_CCW 0xE24FA0EF

/** \brief AN is variable field and should be inserted */
/** \brief Egress default CCW word for 32-bit PN & 128-bit AES type */
#define EGR_32BPN_128KEY_DEF_CCW 0x924BE066
/** \brief Egress default CCW word for 32-bit PN & 256-bit AES type */
#define EGR_32BPN_256KEY_DEF_CCW 0x924FE066
/** \brief Egress default CCW word for 64-bit PN & 128-bit AES type */
#define EGR_64BPN_128KEY_DEF_CCW 0xA24BE066
/** \brief Egress default CCW word for 64-bit PN & 256-bit AES type */
#define EGR_64BPN_256KEY_DEF_CCW 0xA24FE066

/** \brief Typedefs */
#ifdef __KERNEL__
typedef u64 __bitwise sci_t;
#else
typedef u64 sci_t;
#endif

/** \brief Default register values */
/** \brief Default value of SAM_NM_PARAMS reg */
#define DEF_SAM_NM_PARAMS 0xE588007F
/** \endcond */

/** \addtogroup GPY211_MACSEC_SECINIT */
/**@{*/
/** \brief MACsec direction */
enum msec_dir {
	/** \brief Ingress (Decryption) direction */
	INGRESS_DIR = 0,
	/** \brief Egress (Encryption) direction */
	EGRESS_DIR = 1,
};

/** \brief MACSEC HW version information */
struct eip160_version {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief EIP number signature */
			u32 eip_nr: 8;
			/** \brief Complement EIP-number signature */
			u32 eip_nr_complement: 8;
			/** \brief Patch level for module hardware */
			u32 patch_level: 4;
			/** \brief Minor version of module hardware */
			u32 minor_version: 4;
			/** \brief Major version of module hardware */
			u32 major_version: 4;
			/** \brief Write with zero and ignore on read */
			u32 reserved: 4;
#elif defined(__BIG_ENDIAN)
			/** \brief Write with zero and ignore on read */
			u32 reserved: 4;
			/** \brief Major version of module hardware */
			u32 major_version: 4;
			/** \brief Minor version of module hardware */
			u32 minor_version: 4;
			/** \brief Patch level for module hardware */
			u32 patch_level: 4;
			/** \brief Complement EIP-number signature */
			u32 eip_nr_complement: 8;
			/** \brief EIP number signature */
			u32 eip_nr: 8;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief MACSEC HW version information */
		u32 raw_eip160_ver;
	};
};

/** \brief MACSEC HW configuration information */
struct eip160_config {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief The max number of SA match sets supported */
			u32 nr_of_sas: 8;
			/** \brief (-i) The max number of consistency check sets supported */
			u32 consist_checks: 8;
			/** \brief (-i)Enable SCI matching */
			u32 match_sci: 1;
			/** \brief Write with zero and ignore on read */
			u32 reserved: 15;
#elif defined(__BIG_ENDIAN)
			/** \brief Write with zero and ignore on read */
			u32 reserved: 15;
			/** \brief (-i)Enable SCI matching */
			u32 match_sci: 1;
			/** \brief (-i) The max number of consistency check sets supported */
			u32 consist_checks: 8;
			/** \brief The max number of SA match sets supported */
			u32 nr_of_sas: 8;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief IP160 HW configuration (raw) information */
		u32 raw_eip160_cfg;
	};
} ;

/** \brief MACSEC HW configuration extn information */
struct eip160_config2 {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Number of statistics counters per SA */
			u32 sa_counters: 4;
			/** \brief Number of statistics counters per VLAN User Priority */
			u32 vl_counters: 4;
			/** \brief Number of global statistics counters */
			u32 global_counters: 6;
			/** \brief Programmable locking of counters at maximum value */
			u32 saturate_cntrs: 1;
			/** \brief Programmable enabling of statistics counters reset on read */
			u32 auto_cntr_reset: 1;
			/** \brief Number of octet counters per SA */
			u32 sa_octet_ctrs: 2;
			/** \brief Number of octet counters per VLAN User Priority */
			u32 vl_octet_ctrs: 2;
			/** \brief Number of global octet counters */
			u32 glob_octet_ctrs: 4;
			/** \brief Specialize the engine for ingress  & counters only */
			u32 ingress_only: 1;
			/** \brief Specialize the engine for egress & counters only */
			u32 egress_only: 1;
			/** \brief Write with zero and ignore on read */
			u32 reserved: 1;
			/** \brief Bypassing VLAN tags before SecTAG is supported */
			u32 tag_bypass: 1;
			/** \brief Write with zero and ignore on read */
			u32 reserved2: 4;
#elif defined(__BIG_ENDIAN)
			/** \brief Write with zero and ignore on read */
			u32	reserved2: 4;
			/** \brief Bypassing VLAN tags before SecTAG is supported */
			u32	tag_bypass: 1;
			/** \brief Write with zero and ignore on read */
			u32	reserved: 1;
			/** \brief Specialize the engine for egress & counters only */
			u32	egress_only: 1;
			/** \brief Specialize the engine for ingress  & counters only */
			u32	ingress_only: 1;
			/** \brief Number of global octet counters */
			u32	glob_octet_ctrs: 4;
			/** \brief Number of octet counters per VLAN User Priority */
			u32	vl_octet_ctrs: 2;
			/** \brief Number of octet counters per SA */
			u32	sa_octet_ctrs: 2;
			/** \brief Programmable enabling of statistics counters reset on read */
			u32	auto_cntr_reset: 1;
			/** \brief Programmable locking of counters at maximum value */
			u32	saturate_cntrs: 1;
			/** \brief Number of global statistics counters */
			u32	global_counters: 6;
			/** \brief Number of statistics counters per VLAN User Priority */
			u32	vl_counters: 4;
			/** \brief Number of statistics counters per SA */
			u32	sa_counters: 4;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief MACSEC HW configuration extn (raw) information */
		u32 raw_eip160_cfg2;
	};
};

/** \brief AIC (Advanced Interrupt Controller) module configuration data */
struct aic_options {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Direct indication of the number of interrupt inputs */
			u32 number_of_inputs: 6;
			/** \brief Write with zero and ignore on read */
			u32 reserved: 26;
#elif defined(__BIG_ENDIAN)
			/** \brief Write with zero and ignore on read */
			u32 reserved: 26;
			/** \brief Direct indication of the number of interrupt inputs */
			u32 number_of_inputs: 6;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief MACSEC HW version information */
		u32 raw_aic_opt;
	};
};

/** \brief AIC (Advanced Interrupt Controller) module version information */
struct aic_version {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief EIP number signature */
			u32 eip_nr: 8;
			/** \brief Complement EIP-number signature */
			u32 eip_nr_complement: 8;
			/** \brief Patch level for module hardware */
			u32 patch_level: 4;
			/** \brief Minor version of module hardware */
			u32 minor_version: 4;
			/** \brief Major version of module hardware */
			u32 major_version: 4;
			/** \brief Write with zero and ignore on read */
			u32 reserved: 4;
#elif defined(__BIG_ENDIAN)
			/** \brief Write with zero and ignore on read */
			u32 reserved: 4;
			/** \brief Major version of module hardware */
			u32 major_version: 4;
			/** \brief Minor version of module hardware */
			u32 minor_version: 4;
			/** \brief Patch level for module hardware */
			u32 patch_level: 4;
			/** \brief Complement EIP-number signature */
			u32 eip_nr_complement: 8;
			/** \brief EIP number signature */
			u32 eip_nr: 8;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief MACSEC HW version information */
		u32 raw_aic_ver;
	};
};

/** \brief MACSEC HW capabilities information */
struct eip160_hwcap {
	/** \brief MACSEC HW version information */
	struct eip160_version eip_ver;
	/** \brief MACSEC HW configuration information */
	struct eip160_config eip_cfg;
	/** \brief MACSEC HW configuration extn information */
	struct eip160_config2 eip_cfg2;
	/** \brief AIC Module Configuration information */
	struct aic_options aic_opt;
	/** \brief AIC Module Version information */
	struct aic_version aic_ver;
};
/**@}*/ /* GPY211_SECINIT */

/** \addtogroup GPY211_MACSEC_SECTR */
/**@{*/
/** \brief Crypto Algorithm for data encryption  */
enum crypto_algorithm {
	/** \brief AES-CTR-128 */
	CA_AES_CTR_128 = 5,
	/** \brief AES-CTR-192
	Not supported for GPY2xx */
	CA_AES_CTR_192 = 6,
	/** \brief AES-CTR-256 */
	CA_AES_CTR_256 = 7,
};

/** \brief Sequence Number type */
enum seq_type {
	/** \brief 32-bit sequence number */
	SN_32_BIT = 1,
	/** \brief 64-bit sequence number */
	SN_64_BIT = 2,
};

/** \brief Context Control word */
struct ctx_ctrl_word {
	/** \brief Crypto algorithm type.
	Valid values are defined in \ref crypto_algorithm enum */
	enum crypto_algorithm ca_type;
	/** \brief (-e)Association Number inserted into the SecTag for egress */
	u8 an;
	/** \brief Sequence number type.
	Valid values are defined in \ref seq_type enum */
	enum seq_type sn_type;
};

/** \brief Context Salt (applicable only for 64-bit PN) */
struct ctx_salt {
	/** \brief The Salt */
	u8 salt[MACSEC_SALT_LEN_BYTE];
	/** \brief Short-SCI to xor-ed with Salt-0 */
	u8 s_sci[MACSEC_SSCI_LEN_BYTE];
};

/** \brief Cryptographic parameters */
struct crypto_params {
	/** \brief AES encryption/decryption key for given MACsec SA */
	u8 key[MACSEC_KEY_LEN_BYTE];
	/** \brief Hash key for authentication operation (derived from key) */
	u8 hkey[MACSEC_HKEY_LEN_BYTE];
	union {
		/** \brief The SCI that belongs to the specific MACsec SA
		(NA for 64-bit PN Ingress case) */
		u8 sci[MACSEC_SCI_LEN_BYTE];
		/** \brief The SCI that belongs to the specific MACsec SA
		(NA for 64-bit PN Ingress case) */
		sci_t scid;
	};
	/** \brief Context Salt \ref ctx_salt */
	struct ctx_salt c_salt;
};

/** \brief Packet Numbering and Replay check */
struct pn_replay_check {
	union {
		struct {
			/** \brief Sequence Number-0 for 32/64-bit packet number */
			u32 seq0;
			/** \brief Sequence Number-1 for 64-bit packet number (MSW) */
			u32 seq1;
		};
		/** \brief Sequence Number for 32/64-bit packet number */
		u64 seq_num;
	};
	/** \brief Replay Window size for ingress sequence number checking
			   Value 0 is enforced for strict ordering */
	u32 mask;
};

/** \brief Current Packet Number in Transform Record */
struct sa_current_pn {
	/** \brief Transform Record entry index */
	u8 sa_index;
	/** \brief Current Sequence Number */
	u64 curr_pn;
};

/** \brief SA Update Control word */
struct sa_update_ctrl {
	/** \brief Index of the next SA */
	u16 sa_index;
	/** \brief To annotation in the SA expired summary register */
	u8 sa_expired_irq;
	/** \brief Next SA index valid */
	u8 sa_index_valid;
	/** \brief Index of the flow control register that holds the current SA */
	u16 flow_index;
	/** \brief SA index update enable */
	u8 sa_ind_update_en;
};

/** \brief Input Transform Record structure */
struct transform_rec {
	union {
		/** \brief Transform Record entry index */
		u8 sa_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	/** \brief Context control word \ref ctx_ctrl_word */
	struct ctx_ctrl_word ccw;
	/** \brief Cryptographic parameters \ref crypto_params */
	struct crypto_params cp;
	/** \brief Packet numbering and replay check \ref pn_replay_check */
	struct pn_replay_check pn_rc;
	/** \brief SA update control word \ref sa_update_ctrl */
	struct sa_update_ctrl sa_update;
};

/** \brief Output Transform Record */
struct raw_trans_rec {
	union {
		/** \brief Transform Record entry index */
		u8 sa_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	/** \brief Max TR size to hold both Ing & Egr */
	u32 raw_trans_rec[EGR_MAX_TR_SIZE_WORDS];
};
/**@}*/ /* GPY211_SECTR */

/** \cond INTERNAL */
/** \brief HW Transform Record for CA type of GCM-AES-128 */
struct ing_tr_32bpn_128bak {
	/** \brief Context control word */
	u32 ccw;
	/** \brief A unique identifier for each context */
	u32 ctx_id;
	/** \brief AES encryption/decryption key */
	u32 key[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Hash key for authentication operation */
	u32 hkey[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Seq0 for 32-bit packet number */
	u32 seq;
	/** \brief Replay Window size for ingress SN checking
			   Value 0 is enforced for strict ordering */
	u32 mask;
	/** \brief IV0 (SCI placed at the word-0) */
	u32 iv0;
	/** \brief IV1 (SCI placed at the word-1) */
	u32 iv1;
	/** \brief Write with zero and ignore on read */
	u32 res0[6];
};

/** \brief HW Transform Record for CA type of GCM-AES-256 */
struct ing_tr_32bpn_256bak {
	/** \brief Context control word */
	u32 ccw;
	/** \brief A unique identifier for each context */
	u32 ctx_id;
	/** \brief AES encryption/decryption key */
	u32 key[MACSEC_CA256_KEY_LEN_WORD];
	/** \brief Hash key for authentication operation */
	u32 hkey[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Seq0 for 32-bit packet number */
	u32 seq;
	/** \brief Window size for ingress SN checking
			   Value 0 is enforced for strict ordering */
	u32 mask;
	/** \brief IV0 (SCI placed at the word-0) */
	u32 iv0;
	/** \brief IV1 (SCI placed at the word-1) */
	u32 iv1;
	/** \brief Write with zero and ignore on read */
	u32 res0[2];
};

/** \brief HW Transform Record for CA type of GCM-AES-XPN-128 */
struct ing_tr_64bpn_128bak {
	/** \brief Context control word */
	u32 ccw;
	/** \brief A unique identifier for each context */
	u32 ctx_id;
	/** \brief AES encryption/decryption key */
	u32 key[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Hash key for authentication operation */
	u32 hkey[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Seq0 for 64-bit packet number */
	u32 seq0;
	/** \brief Seq1 for 64-bit packet number (MSW) */
	u32 seq1;
	/** \brief Window size for ingress SN checking
			   Value 0 is enforced for strict ordering */
	u32 mask;
	/** \brief IV0 (Context Salt placed at word-0) */
	u32 iv0;
	/** \brief IV1 (Context Salt placed at word-1) */
	u32 iv1;
	/** \brief IV1 (Context Salt placed at word-2) */
	u32 iv2;
	/** \brief Write with zero and ignore on read */
	u32 res[4];
};

/** \brief HW Transform Record for CA type of GCM-AES-XPN-256 */
struct ing_tr_64bpn_256bak {
	/** \brief Context control word */
	u32 ccw;
	/** \brief A unique identifier for each context */
	u32 ctx_id;
	/** \brief AES encryption/decryption key */
	u32 key[MACSEC_CA256_KEY_LEN_WORD];
	/** \brief Hash key for authentication operation */
	u32 hkey[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Seq0 for 64-bit packet number */
	u32 seq0;
	/** \brief Seq1 for 64-bit packet number (MSW) */
	u32 seq1;
	/** \brief Window size for ingress SN checking
			   Value 0 is enforced for strict ordering */
	u32 mask;
	/** \brief IV0 (Context Salt placed at word-0) */
	u32 iv0;
	/** \brief IV1 (Context Salt placed at word-1) */
	u32 iv1;
	/** \brief IV1 (Context Salt placed at word-2) */
	u32 iv2;
};

/** \brief HW Transform Record for CA type of GCM-AES-128 */
struct egr_tr_32bpn_128bak {
	/** \brief Context control word */
	u32 ccw;
	/** \brief A unique identifier for each context */
	u32 ctx_id;
	/** \brief AES encryption/decryption key */
	u32 key[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Hash key for authentication operation */
	u32 hkey[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Seq0 for 32-bit packet number */
	u32 seq;
	/** \brief IV0 (SCI placed at the word-0) */
	u32 iv0;
	/** \brief IV1 (SCI placed at the word-1) */
	u32 iv1;
	/** \brief Write with zero and ignore on read */
	u32 res0[2];
	/** \brief SA Update Control \ref sa_update_ctrl */
	u32 sa_upd_ctrl;
	/** \brief Write with zero and ignore on read */
	u32 res1[8];
};

/** \brief HW Transform Record for CA type of GCM-AES-256 */
struct egr_tr_32bpn_256bak {
	/** \brief Context control word */
	u32 ccw;
	/** \brief A unique identifier for each context */
	u32 ctx_id;
	/** \brief AES encryption/decryption key */
	u32 key[MACSEC_CA256_KEY_LEN_WORD];
	/** \brief Hash key for authentication operation */
	u32 hkey[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Seq0 for 32-bit packet number */
	u32 seq;
	/** \brief IV0 (SCI placed at the word-0) */
	u32 iv0;
	/** \brief IV1 (SCI placed at the word-1) */
	u32 iv1;
	/** \brief Write with zero and ignore on read */
	u32 res0[2];
	/** \brief SA Update Control \ref sa_update_ctrl */
	u32 sa_upd_ctrl;
	/** \brief Write with zero and ignore on read */
	u32 res1[4];
};

/** \brief HW Transform Record for CA type of GCM-AES-XPN-128 */
struct egr_tr_64bpn_128bak {
	/** \brief Context control word */
	u32 ccw;
	/** \brief A unique identifier for each context */
	u32 ctx_id;
	/** \brief AES encryption/decryption key */
	u32 key[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Hash key for authentication operation */
	u32 hkey[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Seq0 for 64-bit packet number */
	u32 seq0;
	/** \brief Seq1 for 64-bit packet number (MSW) */
	u32 seq1;
	/** \brief Write with zero and ignore on read */
	u32 res0;
	/** \brief IS0 (Context Salt placed at word-0) */
	u32 is0;
	/** \brief IS1 (Context Salt placed at word-1) */
	u32 is1;
	/** \brief IS1 (Context Salt placed at word-2) */
	u32 is2;
	/** \brief IV0 (SCI placed at the word-0) */
	u32 iv0;
	/** \brief IV1 (SCI placed at the word-1) */
	u32 iv1;
	/** \brief Write with zero and ignore on read */
	u32 res1;
	/** \brief SA Update Control \ref sa_update_ctrl */
	u32 sa_upd_ctrl;
	/** \brief Write with zero and ignore on read */
	u32 res2[4];
};

/** \brief HW Transform Record for CA type of GCM-AES-XPN-256 */
struct egr_tr_64bpn_256bak {
	/** \brief Context control word */
	u32 ccw;
	/** \brief A unique identifier for each context */
	u32 ctx_id;
	/** \brief AES encryption/decryption key */
	u32 key[MACSEC_CA256_KEY_LEN_WORD];
	/** \brief Hash key for authentication operation */
	u32 hkey[MACSEC_CA128_KEY_LEN_WORD];
	/** \brief Seq0 for 64-bit packet number */
	u32 seq0;
	/** \brief Seq1 for 64-bit packet number (MSW) */
	u32 seq1;
	/** \brief Write with zero and ignore on read */
	u32 res0;
	/** \brief IS0 (Context Salt placed at word-0) */
	u32 is0;
	/** \brief IS1 (Context Salt placed at word-1) */
	u32 is1;
	/** \brief IS1 (Context Salt placed at word-2) */
	u32 is2;
	/** \brief IV0 (SCI placed at the word-0) */
	u32 iv0;
	/** \brief IV1 (SCI placed at the word-1) */
	u32 iv1;
	/** \brief Write with zero and ignore on read */
	u32 res1;
	/** \brief SA Update Control \ref sa_update_ctrl */
	u32 sa_upd_ctrl;
};
/** \endcond */

/** \addtogroup GPY211_MACSEC_SECEEX */
/**@{*/
/** \brief Secure Association Matching (SAM) Entry Enable feature type */
enum sam_eex_type {
	/** \brief Entry Enable flags for debugging purpose */
	SAM_ENTRY_ENABLE = 0,
	/** \brief  Entry Enable toggles the value of every enable flag */
	SAM_ENTRY_TOGGLE = 1,
	/** \brief  Entry Enable set */
	SAM_ENTRY_SET = 2,
	/** \brief  Entry Enable clear */
	SAM_ENTRY_CLEAR = 3,
};

/** \brief Output Secure Association Matching (SAM) Entry Enable flags */
struct raw_sam_ee {
#ifdef USE_WORD_READ // 32-bit word based read
	/** \brief 32-bit word number to be configured */
	u8 word_num: 3;
#endif
	/** \brief SAM Entry Enable feature type.
	Valid values are defined in \ref sam_eex_type enum */
	enum sam_eex_type eex_type;
	/** \brief Max SA Match rule flags size */
	u32 raw_sam_ee[MACSEC_MAX_SA_RULES / 32];
};
/**@}*/ /* GPY211_SECEEX */

/** \addtogroup GPY211_MACSEC_SECEEC */
/**@{*/
/** \brief Secure Association Matching (SAM) Entry Enable control */
struct sam_ee_ctrl {
	/** \brief Index of a SAM entry to enable when set_enable = 1b */
	u8 sam_index_set;
	/** \brief Enable the SAM entry with index sam_index_set */
	u8 set_enable;
	/** \brief Enable all entries */
	u8 set_all;
	/** \brief Index of a SAM entry to disable when set_clear = 1b */
	u8 sam_index_clear;
	/** \brief Disable the SAM entry with index sam_index_clear */
	u8 clear_enable;
	/** \brief Disable all entries */
	u8 clear_all;
};
/**@}*/ /* GPY211_SECEEC */

/** \addtogroup GPY211_MACSEC_SECSAM */
/**@{*/
/** \brief Output Secure Association Matching (SAM) rule params */
struct raw_sam_param {
	union {
		/** \brief SA rule num to be configured */
		u8 rule_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	/** \brief Max SA Match rule params size to hold both Ing & Egr */
	u32 raw_sam_param[IE_MAX_SAM_SIZE_WORDS];
};

/** \brief Secure Association Matching (SAM) Misc params */
struct sam_misc_param {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Parsed VLAN valid flag compare value */
			u32 vlan_valid: 1;
			/** \brief Parsed QinQ found flag compare value */
			u32 qinq_found: 1;
			/** \brief Parsed STAG valid flag compare value */
			u32 stag_valid: 1;
			/** \brief Parsed QTAG valid flag compare value */
			u32 qtag_valid1: 1;
			/** \brief Parsed VLAN User Priority compare value */
			u32 vlan_up: 3;
#else
			/** \brief Reserved */
			u32 reserved: 7;
#endif
			/** \brief Packet is control packet (as pre-decoded) compare value */
			u32 control_packet: 1;
			/** \brief Allow packets without a MACsec tag to match */
			u32 untagged: 1;
			/** \brief Allow packets with a standard and valid MACsec tag to match */
			u32 tagged: 1;
			/** \brief Allow packets with an invalid MACsec tag to match */
			u32 bad_tag: 1;
			/** \brief Allow packets with a MACsec tag indicating KaY handling to be
					   done to match */
			u32 kay_tag: 1;
			/** \brief Source port compare value \ref sam_fca_dpt */
			u32 source_port: 2;
			/** \brief Write with zero and ignore on read */
			u32 reserved1: 2;
			/** \brief Priority of this entry for determining the actual transform
					   used on a match when multiple entries match */
			u32 match_priority: 4;
			/** \brief Write with zero and ignore on read */
			u32 reserved2: 4;
			/** \brief MACsec TCI/AN byte compare value */
			u32 macsec_tci_an: 8;
#elif defined(__BIG_ENDIAN)
			/** \brief MACsec TCI/AN byte compare value */
			u32 macsec_tci_an: 8;
			/** \brief Write with zero and ignore on read */
			u32 reserved2: 4;
			/** \brief Priority of this entry for determining the actual transform
					   used on a match when multiple entries match */
			u32 match_priority: 4;
			/** \brief Write with zero and ignore on read */
			u32 reserved1: 2;
			/** \brief Source port compare value \ref sam_fca_dpt */
			u32 source_port: 2;
			/** \brief Allow packets with a MACsec tag indicating KaY handling to be
					   done to match */
			u32 kay_tag: 1;
			/** \brief Allow packets with an invalid MACsec tag to match */
			u32 bad_tag: 1;
			/** \brief Allow packets with a standard and valid MACsec tag to match */
			u32 tagged: 1;
			/** \brief Allow packets without a MACsec tag to match */
			u32 untagged: 1;
			/** \brief Packet is control packet (as pre-decoded) compare value */
			u32 control_packet: 1;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Parsed VLAN User Priority compare value */
			u32 vlan_up: 3;
			/** \brief Parsed QTAG valid flag compare value */
			u32 qtag_valid1: 1;
			/** \brief Parsed STAG valid flag compare value */
			u32 stag_valid: 1;
			/** \brief Parsed QinQ found flag compare value */
			u32 qinq_found: 1;
			/** \brief Parsed VLAN valid flag compare value */
			u32 vlan_valid: 1;
#else
			/** \brief Reserved */
			u32 reserved: 7;
#endif
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief Miscellaneous (raw) match */
		u32 misc;
	};
};

/** \brief Secure Association Matching (SAM) Mask params */
struct sam_mask_param {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Enable MAC_SA bits [7:0] */
			u32 mac_sa_0_mask: 1;
			/** \brief Enable MAC_SA bits [15:8] */
			u32 mac_sa_1_mask: 1;
			/** \brief Enable MAC_SA bits [23:16] */
			u32 mac_sa_2_mask: 1;
			/** \brief Enable MAC_SA bits [31:24] */
			u32 mac_sa_3_mask: 1;
			/** \brief Enable MAC_SA bits [39:32] */
			u32 mac_sa_4_mask: 1;
			/** \brief Enable MAC_SA bits [47:40] */
			u32 mac_sa_5_mask: 1;
			/** \brief Enable MAC_DA bits [7:0] */
			u32 mac_da_0_mask: 1;
			/** \brief Enable MAC_DA bits [15:8] */
			u32 mac_da_1_mask: 1;
			/** \brief Enable MAC_DA bits [23:16] */
			u32 mac_da_2_mask: 1;
			/** \brief Enable MAC_DA bits [31:24] */
			u32 mac_da_3_mask: 1;
			/** \brief Enable MAC_DA bits [39:32] */
			u32 mac_da_4_mask: 1;
			/** \brief Enable MAC_DA bits [47:40] */
			u32 mac_da_5_mask: 1;
			/** \brief Enable parsed Ether-type field */
			u32 mac_etype_mask: 1;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Enable parsed VLAN valid flag */
			u32 vlan_vld_mask: 1;
			/** \brief Enable parsed QinQ found flag */
			u32 qinq_found_mask: 1;
			/** \brief Enable parsed STAG valid flag */
			u32 stag_vld_mask: 1;
			/** \brief Enable parsed QTAG valid flag */
			u32 qtag_vld_mask: 1;
			/** \brief Enable parsed VLAN User Priority value */
			u32 vlan_up_mask: 1;
			/** \brief Enable parsed VLAN ID value */
			u32 vlan_id_mask: 1;
#else
			/** \brief Reserved */
			u32 reserved: 6;
#endif
			/** \brief Enable source port compare with source_port in the 'misc' reg */
			u32 source_port_mask: 1;
			/** \brief Enable control packet status compare with control_packet bit in
					   the 'misc' reg */
			u32 ctrl_packet_mask: 1;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Enable parsed inner VLAN User Priority value compare with
					   vlan_up_inner field in the 'misc' reg */
			u32 vlan_up_inner_mask: 1;
			/** \brief Enable parsed inner VLAN ID value compare with vlan_up_inner
					   field in the 'misc' reg */
			u32 vlan_id_inner_mask: 1;
#else
			/** \brief Reserved */
			u32 reserved2: 2;
#endif
			/** \brief Enable MACsec header SCI value compare with 64 bits SCI value
					   in the 'misc' reg */
			u32 macsec_sci_mask: 1;
			/** \brief Separate compare enable bits for the macsec_tci_an field in
					   the 'misc' reg */
			u32 tci_an_mask: 8;
#elif defined(__BIG_ENDIAN)
			/** \brief Separate compare enable bits for the macsec_tci_an field in
					   the 'misc' reg */
			u32	tci_an_mask: 8;
			/** \brief Enable MACsec header SCI value compare with 64 bits SCI value
					   in the 'misc' reg */
			u32	macsec_sci_mask: 1;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Enable parsed inner VLAN ID value compare with vlan_up_inner
					   field in the 'misc' reg */
			u32	vlan_id_inner_mask: 1;
			/** \brief Enable parsed inner VLAN User Priority value compare with
					   vlan_up_inner field in the 'misc' reg */
			u32	vlan_up_inner_mask: 1;
#else
			/** \brief Reserved */
			u32 reserved2: 2;
#endif
			/** \brief Enable control packet status compare with control_packet bit in
					   the 'misc' reg */
			u32	ctrl_packet_mask: 1;
			/** \brief Enable source port compare with source_port in the 'misc' reg */
			u32	source_port_mask: 1;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Enable parsed VLAN ID value */
			u32	vlan_id_mask: 1;
			/** \brief Enable parsed VLAN User Priority value */
			u32	vlan_up_mask: 1;
			/** \brief Enable parsed QTAG valid flag */
			u32	qtag_vld_mask: 1;
			/** \brief Enable parsed STAG valid flag */
			u32	stag_vld_mask: 1;
			/** \brief Enable parsed QinQ found flag */
			u32	qinq_found_mask: 1;
			/** \brief Enable parsed VLAN valid flag */
			u32	vlan_vld_mask: 1;
#else
			/** \brief Reserved */
			u32 reserved: 6;
#endif
			/** \brief Enable parsed Ether-type field */
			u32	mac_etype_mask: 1;
			/** \brief Enable MAC_DA bits [47:40] */
			u32	mac_da_5_mask: 1;
			/** \brief Enable MAC_DA bits [39:32] */
			u32	mac_da_4_mask: 1;
			/** \brief Enable MAC_DA bits [31:24] */
			u32	mac_da_3_mask: 1;
			/** \brief Enable MAC_DA bits [23:16] */
			u32	mac_da_2_mask: 1;
			/** \brief Enable MAC_DA bits [15:8] */
			u32	mac_da_1_mask: 1;
			/** \brief Enable MAC_DA bits [7:0] */
			u32	mac_da_0_mask: 1;
			/** \brief Enable MAC_SA bits [47:40] */
			u32	mac_sa_5_mask: 1;
			/** \brief Enable MAC_SA bits [39:32] */
			u32	mac_sa_4_mask: 1;
			/** \brief Enable MAC_SA bits [31:24] */
			u32	mac_sa_3_mask: 1;
			/** \brief Enable MAC_SA bits [23:16] */
			u32	mac_sa_2_mask: 1;
			/** \brief Enable MAC_SA bits [15:8] */
			u32	mac_sa_1_mask: 1;
			/** \brief Enable MAC_SA bits [7:0] */
			u32	mac_sa_0_mask: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM Mask (raw) */
		u32 mask;
	};
};

/** \brief Secure Association Matching (SAM) extended params */
struct sam_extn_param {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Parsed inner VLAN ID compare value */
			u32 vlan_id_inner: 12;
			/** \brief Parsed inner VLAN Up compare value */
			u32 vlan_up_inner: 3;
			/** \brief Write with zero and ignore on read */
			u32 reserved1: 1;
#else
			/** \brief Reserved */
			u32 reserved: 16;
#endif
			/** \brief Index of the flow control register that defines an action for
					   the corresponding SA matching rule */
			u32 flow_index: 8;
			/** \brief Write with zero and ignore on read */
			u32 reserved2: 8;
#elif defined(__BIG_ENDIAN)
			/** \brief Write with zero and ignore on read */
			u32	reserved2: 8;
			/** \brief Index of the flow control register that defines an action for
					   the corresponding SA matching rule */
			u32	flow_index: 8;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Write with zero and ignore on read */
			u32	reserved1: 1;
			/** \brief Parsed inner VLAN Up compare value */
			u32	vlan_up_inner: 3;
			/** \brief Parsed inner VLAN ID compare value */
			u32	vlan_id_inner: 12;
#else
			/** \brief Reserved */
			u32 reserved: 16;
#endif
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM Extended (raw) params */
		u32 extn;
	};
};

/** \brief Secure Association Matching (SAM) rule params */
struct sa_match_param {
	union {
		/** \brief SA rule num to be configured */
		u8 rule_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	/** \brief Src MAC */
	u8 sa_mac[6];
	/** \brief Dst MAC */
	u8 da_mac[6];
	/** \brief Ether-type */
	u16 eth_type;
//#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	/** \brief VLAN ID */
	u16 vlan_id;
//#endif
	/** \brief Miscellaneous (bit-fields) match \ref sam_misc_param */
	struct sam_misc_param misc_par;
	union {
		struct {
			/** \brief (-i)The SCI */
			u8 sci[MACSEC_SCI_LEN_BYTE];
		};
		/** \brief (-i)The SCI */
		sci_t scid;
	};
	/** \brief SAM Mask (bit-fields) \ref sam_mask_param */
	struct sam_mask_param mask_par;
	/** \brief SAM Extended (bit-fields) params \ref sam_extn_param */
	struct sam_extn_param extn_par;
};

/** \brief Outer VLAN control */
struct sam_cp_tag {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Translation table to derive the user priority from the
					   PCP field in “802.1Q” tags. User priority for PCP-0 */
			u32 map_tbl_pcp_0: 3;
			/** \brief User priority for PCP-1 */
			u32 map_tbl_pcp_1: 3;
			/** \brief User priority for PCP-2 */
			u32 map_tbl_pcp_2: 3;
			/** \brief User priority for PCP-3 */
			u32 map_tbl_pcp_3: 3;
			/** \brief User priority for PCP-4 */
			u32 map_tbl_pcp_4: 3;
			/** \brief User priority for PCP-5 */
			u32 map_tbl_pcp_5: 3;
			/** \brief User priority for PCP-6 */
			u32 map_tbl_pcp_6: 3;
			/** \brief User priority for PCP-7 */
			u32 map_tbl_pcp_7: 3;
			/** \brief Default user priority, assigned to non-VLAN packets and
					   to VLAN packets for which the VLAN user priority
					   processing is disabled */
			u32 def_up: 3;
			/** \brief Enable user priority processing for “802.1s” packets */
			u32 stag_up_en: 1;
			/** \brief Enable user priority processing for “802.1Q” packets */
			u32 qtag_up_en: 1;
#else
			/** \brief Reserved */
			u32 reserved: 29;
#endif
			/** \brief Take care of packets with two VLAN tags */
			u32 parse_qinq: 1;
			/** \brief Take care of packets with an “802.1s” VLAN tag */
			u32 parse_stag: 1;
			/** \brief Take care of packets with an “802.1Q” VLAN tag */
			u32 parse_qtag: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief Take care of packets with an “802.1Q” VLAN tag */
			u32 parse_qtag: 1;
			/** \brief Take care of packets with an “802.1s” VLAN tag */
			u32 parse_stag: 1;
			/** \brief Take care of packets with two VLAN tags */
			u32 parse_qinq: 1;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Enable user priority processing for “802.1Q” packets */
			u32 qtag_up_en: 1;
			/** \brief Enable user priority processing for “802.1s” packets */
			u32 stag_up_en: 1;
			/** \brief Default user priority, assigned to non-VLAN packets and
					   to VLAN packets for which the VLAN user priority
					   processing is disabled */
			u32 def_up: 3;
			/** \brief User priority for PCP-7 */
			u32 map_tbl_pcp_7: 3;
			/** \brief User priority for PCP-6 */
			u32 map_tbl_pcp_6: 3;
			/** \brief User priority for PCP-5 */
			u32 map_tbl_pcp_5: 3;
			/** \brief User priority for PCP-4 */
			u32 map_tbl_pcp_4: 3;
			/** \brief User priority for PCP-3 */
			u32 map_tbl_pcp_3: 3;
			/** \brief User priority for PCP-2 */
			u32 map_tbl_pcp_2: 3;
			/** \brief User priority for PCP-1 */
			u32 map_tbl_pcp_1: 3;
			/** \brief Translation table to derive the user priority from the
					   PCP field in “802.1Q” tags. User priority for PCP-0 */
			u32 map_tbl_pcp_0: 3;
#else
			/** \brief Reserved */
			u32 reserved: 29;
#endif
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief Outer VLAN control - raw */
		u32 raw_ocp_tag;
	};
};

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
/** \brief VLAN ether-type control */
struct sam_pp_tags {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Ether-type value used for “802.1Q” tag type */
			u32 qtag_value: 16;
			/** \brief Ether-type value used for “802.1s” tag type */
			u32 stag_value: 16;
#elif defined(__BIG_ENDIAN)
			/** \brief Ether-type value used for “802.1s” tag type */
			u32 stag_value: 16;
			/** \brief Ether-type value used for “802.1Q” tag type */
			u32 qtag_value: 16;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM Extended (raw) params */
		u32 raw_pp_tags;
	};
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Secondary ether-type value used for “802.1s” tag type */
			u32 stag_value2: 16;
			/** \brief Tertiary ether-type value used for “802.1s” tag type */
			u32 stag_value3: 16;
#elif defined(__BIG_ENDIAN)
			/** \brief Tertiary ether-type value used for “802.1s” tag type */
			u32 stag_value3: 16;
			/** \brief Secondary ether-type value used for “802.1s” tag type */
			u32 stag_value2: 16;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM Extended (raw) params */
		u32 raw_pp_tags2;
	};
};

/** \brief Inner VLAN control */
struct sam_cp_tag2 {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Translation table to derive the user priority from the
					   PCP field in “802.1Q” tags. User priority for PCP-0 */
			u32 map_tbl2_pcp_0: 3;
			/** \brief User priority for PCP-1 */
			u32 map_tbl2_pcp_1: 3;
			/** \brief User priority for PCP-2 */
			u32 map_tbl2_pcp_2: 3;
			/** \brief User priority for PCP-3 */
			u32 map_tbl2_pcp_3: 3;
			/** \brief User priority for PCP-4 */
			u32 map_tbl2_pcp_4: 3;
			/** \brief User priority for PCP-5 */
			u32 map_tbl2_pcp_5: 3;
			/** \brief User priority for PCP-6 */
			u32 map_tbl2_pcp_6: 3;
			/** \brief User priority for PCP-7 */
			u32 map_tbl2_pcp_7: 3;
			/** \brief Reserved */
			u32 reserved: 8;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved: 8;
			/** \brief User priority for PCP-7 */
			u32 map_tbl2_pcp_7: 3;
			/** \brief User priority for PCP-6 */
			u32 map_tbl2_pcp_6: 3;
			/** \brief User priority for PCP-5 */
			u32 map_tbl2_pcp_5: 3;
			/** \brief User priority for PCP-4 */
			u32 map_tbl2_pcp_4: 3;
			/** \brief User priority for PCP-3 */
			u32 map_tbl2_pcp_3: 3;
			/** \brief User priority for PCP-2 */
			u32 map_tbl2_pcp_2: 3;
			/** \brief User priority for PCP-1 */
			u32 map_tbl2_pcp_1: 3;
			/** \brief Translation table to derive the user priority from the
					   PCP field in “802.1Q” tags. User priority for PCP-0 */
			u32 map_tbl2_pcp_0: 3;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM Extended (raw) params */
		u32 raw_icp_tag;
	};
};
#endif

/** \brief Secure Association Matching (SAM) VLAN tag parsing algorithm parameters */
struct sam_vlan_parse {
	/** \brief VLAN control */
	struct sam_cp_tag outer_tag;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	/** \brief VLAN ether-type control */
	struct sam_pp_tags pp_tags;
	/** \brief Inner VLAN control */
	struct sam_cp_tag2 inner_tag;
#endif
};
/**@}*/ /* GPY211_SECSAM */

/** \addtogroup GPY211_MACSEC_SECFCA */
/**@{*/
/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) flow type */
enum sam_fca_ft {
	/** \brief Bypass */
	SAM_FCA_FLOW_BYPASS = 0,
	/** \brief Drop */
	SAM_FCA_FLOW_DROP = 1,
	/** \brief MACsec ingress */
	SAM_FCA_FLOW_INGRESS = 2,
	/** \brief MACsec egress */
	SAM_FCA_FLOW_EGRESS = 3,
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) dest-port type */
enum sam_fca_dpt {
	/** \brief Common port */
	SAM_FCA_DPT_COMMON = 0,
	/** \brief Reserved port */
	SAM_FCA_DPT_RES = 1,
	/** \brief Control port */
	SAM_FCA_DPT_CONTROL = 2,
	/** \brief Un-Control port */
	SAM_FCA_DPT_UNCONTROL = 3,
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) drop-action type */
enum sam_fca_dat {
	/** \brief Bypass with CRC corruption indicator */
	SAM_FCA_DROP_AS_CRC = 0,
	/** \brief Bypass with bad packet indicator */
	SAM_FCA_DROP_AS_BAD_PKT = 1,
	/** \brief Internal drop by crypto-core */
	SAM_FCA_DROP_AS_INTERNAL = 2,
	/** \brief do not drop (for debugging only) */
	SAM_FCA_NO_DROP = 3,
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) frame-validation type */
enum sam_fca_fvt {
	/** \brief Disabled */
	SAM_FCA_VALIDATE_DIS = 0,
	/** \brief Check */
	SAM_FCA_VALIDATE_CHECK = 1,
	/** \brief Strict */
	SAM_FCA_VALIDATE_STRICT = 2,
	/** \brief Reserved */
	SAM_FCA_VALIDATE_RES = 3,
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) IV type */
enum sam_fca_iv {
	/** \brief IV is loaded via the transform record */
	SAM_FCA_LOAD_IV_VIA_TR = 0,
	/** \brief IV is loaded via the input frame located in front of the frame */
	SAM_FCA_LOAD_IV_VIA_START_INFRAME = 1,
	/** \brief IV is loaded via the input frame located at end of the frame */
	SAM_FCA_LOAD_IV_VIA_END_INFRAME = 2,
	/** \brief First three IV words are loaded via the input frame */
	SAM_FCA_LOAD_IV3_VIA_INFRAME = 3,
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) Drop/Bypass/Ing/Egr action params */
struct sa_match_fca {
	union {
		/** \brief Flow control action index to be configured */
		u8 flow_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	/** \brief Flow type (action type).
	Valid values are defined in \ref sam_fca_ft enum */
	enum sam_fca_ft flow_type;
	/** \brief Destination port.
	Valid values are defined in \ref sam_fca_dpt enum */
	enum sam_fca_dpt dest_port;
	/** \brief (-i)Perform 'drop_action' if packet is not from reserved port */
	u8 drop_non_reserved;
	/** \brief Enables basic crypt-authenticate mode */
	u8 flow_crypt_auth;
	/** \brief Drop operation type.
	Valid values are defined in \ref sam_fca_dat enum */
	enum sam_fca_dat drop_action;
	/** \brief Index of the associated transform record (SA) */
	u8 sa_index;
	union {
		/** \brief (-i)Enable replay protection */
		u8 replay_protect;
		/** \brief (-e)Enable frame  protection */
		u8 protect_frame;
	};
	/** \brief (-crypto)IV load type
	Valid values are defined in \ref sam_fca_iv enum */
	enum sam_fca_iv iv;
	/** \brief MACsec SA inUse for the looked-up SA */
	u8 sa_in_use;
	/** \brief (-e)Include explicit SCI in packet */
	u8 include_sci;
	/** \brief (-i)Frame validation level. This value is used for 802.1AE
	compliant processing when MACsec secure channel is found.
	Valid values are defined in \ref sam_fca_fvt enum */
	enum sam_fca_fvt validate_frames;
	union {
		/** \brief (-e)ES (End Station) bit in TCI field */
		u8 use_es;
		/** \brief (-e)(-crypto)Append the calculated ICV */
		u8 icv_append;
	};
	union {
		/** \brief (-e)SCB (Single Copy Broadcast) bit in TCI field */
		u8 use_scb;
		/** \brief (-i)(-crypto)Retrieve and verify the ICV against the
				calculated internally */
		u8 icv_verify;
	};
	/** \brief (-e)The number of 4-byte tags to be bypassed */
	u8 tag_bypass_size;
	/** \brief (-e)Control bit for ''sa_in_use' flag */
	u8 sa_index_update;
	/** \brief The number of bytes (in the range of 0-127) */
	u8 conf_offset;
	/** \brief (-e)Enable confidentiality protection */
	u8 conf_protect;
	/** \brief (-crypto)Specifies length (in bytes) of the bypass data */
	u8 crypt_auth_bypass_len;
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) for decryption/encryption actions */
struct sam_fca_macsec {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Flow type (action type).
			Valid values are defined in \ref sam_fca_ft enum */
			u32 flow_type: 2;
			/** \brief Destination port.
			Valid values are defined in \ref sam_fca_dpt enum */
			u32 dest_port: 2;
			/** \brief (-i)Perform 'drop_action' if packet is not from reserved port */
			u32 drop_non_reserved: 1;
			/** \brief Enables basic crypt-authenticate mode */
			u32 flow_crypt_auth: 1;
			/** \brief Drop operation type.
			Valid values are defined in \ref sam_fca_dat enum */
			u32 drop_action: 2;
			/** \brief Index of the associated transform record (SA) */
			u32 sa_index: 8;
//			union {
			/** \brief (-i)Enable replay protection */
//				u32 replay_protect: 1;
			/** \brief (-e)Enable frame  protection */
//				u32 protect_frame: 1;
//			};
			/** \brief (-i)Enable replay protection
					   (-e)Enable frame  protection */
			u32 rep_prot_fr: 1;
			/** \brief MACsec SA inUse for the looked-up SA */
			u32 sa_in_use: 1;
			/** \brief (-e)Include explicit SCI in packet */
			u32 include_sci: 1;
//			union {
//				struct {
			/** \brief (-e)ES (End Station) bit in TCI field */
//					u32 use_es: 1;
			/** \brief (-e)SCB (Single Copy Broadcast) bit in TCI field */
//					u32 use_scb: 1;
//				};
			/** \brief (-i)Frame validation level. This value is used for 802.1AE
			compliant processing when MACsec secure channel is found.
			Valid values are defined in \ref sam_fca_fvt enum */
//				u32  validate_frames: 2;
//			};
			/** \brief (-i)Frame validation level. This value is used for 802.1AE
			compliant processing when MACsec secure channel is found.
			Valid values are \ref sam_fca_fvt.
			           (-e)ES (End Station) bit in TCI field
			           (-e)SCB (Single Copy Broadcast) bit in TCI field*/
			u32  vlevel_es_scb: 2;
			/** \brief (-e)The number of 4-byte tags to be bypassed */
			u32 tag_bypass_size: 2;
			/** \brief (-e)Control bit for ''sa_in_use' flag */
			u32 sa_index_update: 1;
			/** \brief The number of bytes (in the range of 0-127) */
			u32 conf_offset: 7;
			/** \brief (-e)Enable confidentiality protection */
			u32 conf_protect: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief (-e)Enable confidentiality protection */
			u32 conf_protect: 1;
			/** \brief The number of bytes (in the range of 0-127) */
			u32 conf_offset: 7;
			/** \brief (-e)Control bit for ''sa_in_use' flag */
			u32 sa_index_update: 1;
			/** \brief (-e)The number of 4-byte tags to be bypassed */
			u32 tag_bypass_size: 2;
			/** \brief (-i)Frame validation level. This value is used for 802.1AE
			compliant processing when MACsec secure channel is found.
			Valid values are \ref sam_fca_fvt.
			           (-e)ES (End Station) bit in TCI field
			           (-e)SCB (Single Copy Broadcast) bit in TCI field*/
			u32  vlevel_es_scb: 2;
			/** \brief (-e)Include explicit SCI in packet */
			u32 include_sci: 1;
			/** \brief MACsec SA inUse for the looked-up SA */
			u32 sa_in_use: 1;
			/** \brief (-i)Enable replay protection
					   (-e)Enable frame  protection */
			u32 rep_prot_fr: 1;
			/** \brief Index of the associated transform record (SA) */
			u32 sa_index: 8;
			/** \brief Drop operation type.
			Valid values are defined in \ref sam_fca_dat enum */
			u32 drop_action: 2;
			/** \brief Enables basic crypt-authenticate mode */
			u32 flow_crypt_auth: 1;
			/** \brief (-i)Perform 'drop_action' if packet is not from reserved port */
			u32 drop_non_reserved: 1;
			/** \brief Destination port.
			Valid values are defined in \ref sam_fca_dpt enum */
			u32 dest_port: 2;
			/** \brief Flow type (action type).
			Valid values are defined in \ref sam_fca_ft enum */
			u32 flow_type: 2;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM FCA for ingress/egress action (raw) params */
		u32 raw_fca_macsec;
	};
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) for bypass/drop actions */
struct sam_fca_bpd {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Flow type (action type).
			Valid values are defined in \ref sam_fca_ft enum */
			u32 flow_type: 2;
			/** \brief Destination port.
			Valid values are defined in \ref sam_fca_dpt enum */
			u32 dest_port: 2;
			/** \brief (-i)Perform 'drop_action' if packet is not from reserved port */
			u32 drop_non_reserved: 1;
			/** \brief Enables basic crypt-authenticate mode */
			u32 flow_crypt_auth: 1;
			/** \brief Drop operation type.
			Valid values are defined in \ref sam_fca_dat enum */
			u32 drop_action: 2;
			/** \brief Index of the associated transform record (SA) */
			u32 sa_index: 8;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief MACsec SA inUse for the looked-up SA */
			u32 sa_in_use: 1;
			/** \brief Reserved */
			u32 reserved2: 14;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved2: 14;
			/** \brief MACsec SA inUse for the looked-up SA */
			u32 sa_in_use: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Index of the associated transform record (SA) */
			u32 sa_index: 8;
			/** \brief Drop operation type
			Valid values are defined in defined in \ref sam_fca_dat enum */
			u32 drop_action: 2;
			/** \brief Enables basic crypt-authenticate mode */
			u32 flow_crypt_auth: 1;
			/** \brief (-i)Perform 'drop_action' if packet is not from reserved port */
			u32 drop_non_reserved: 1;
			/** \brief Destination port
			Valid values are defined in \ref sam_fca_dpt enum */
			u32 dest_port: 2;
			/** \brief Flow type (action type)
			Valid values are defined in \ref sam_fca_ft enum */
			u32 flow_type: 2;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM FCA for bypass/drop action (raw) params */
		u32 raw_fca_bpd;
	};
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) for crypt-authenticate operations */
struct sam_fca_crypt {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Reserved */
			u32 reserved: 2;
			/** \brief Destination port.
			Valid values are defined in \ref sam_fca_dpt enum */
			u32 dest_port: 2;
			/** \brief (-i)Perform 'drop_action' if packet is not from reserved port */
			u32 drop_non_reserved: 1;
			/** \brief Enables basic crypt-authenticate mode */
			u32 flow_crypt_auth: 1;
			/** \brief Drop operation type.
			Valid values are defined in \ref sam_fca_dat enum */
			u32 drop_action: 2;
			/** \brief Index of the associated transform record (SA) */
			u32 sa_index: 8;
			/** \brief Defines IV loading mode */
			u32 iv: 2;
			/** \brief (-crypto)Bit 7 of the AAD length for AES-GCM operations */
			u32 conf_offset_7: 1;
			/** \brief (-e)(-crypto)Append the calculated ICV */
			u32 icv_append: 1;
			/** \brief (-i)(-crypto)Retrieve and verify the ICV against the
					calculated internally */
			u32 icv_verify: 1;
			/** \brief Reserved */
			u32 reserved2: 3;
			/** \brief The number of bytes (in the range of 0-127) */
			u32 conf_offset: 7;
			/** \brief (-e)Enable confidentiality protection */
			u32 conf_protect: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief (-e)Enable confidentiality protection */
			u32 conf_protect: 1;
			/** \brief The number of bytes (in the range of 0-127) */
			u32 conf_offset: 7;
			/** \brief Reserved */
			u32 reserved2: 3;
			/** \brief (-i)(-crypto)Retrieve and verify the ICV against the
					calculated internally */
			u32 icv_verify: 1;
			/** \brief (-e)(-crypto)Append the calculated ICV */
			u32 icv_append: 1;
			/** \brief (-crypto)Bit 7 of the AAD length for AES-GCM operations */
			u32 conf_offset_7: 1;
			/** \brief Defines IV loading mode */
			u32 iv: 2;
			/** \brief Index of the associated transform record (SA) */
			u32 sa_index: 8;
			/** \brief Drop operation type
			Valid values are defined in \ref sam_fca_dat enum */
			u32 drop_action: 2;
			/** \brief Enables basic crypt-authenticate mode */
			u32 flow_crypt_auth: 1;
			/** \brief (-i)Perform 'drop_action' if packet is not from reserved port */
			u32 drop_non_reserved: 1;
			/** \brief Destination port
			Valid values are defined in \ref sam_fca_dpt enum */
			u32 dest_port: 2;
			/** \brief Reserved */
			u32 reserved: 2;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM FCA for bypass/drop action (raw) params */
		u32 raw_fca_crypt;
	};
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) for crypt-authenticate control */
struct sam_fca_cac {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief The length (in bytes) of the bypass data during
			crypt-authenticate operation */
			u32 crypt_auth_bypass_len: 8;
			/** \brief Reserved */
			u32 reserved: 24;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved: 24;
			/** \brief The length (in bytes) of the bypass data during
			crypt-authenticate operation */
			u32 crypt_auth_bypass_len: 8;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief SAM FCA for bypass/drop action (raw) params */
		u32 raw_fca_cac;
	};
};

/** \brief Secure Association Matching (SAM) Flow Control Action (FCA) over packets that matched one of the SA */
struct sam_pkt_fca {
	union {
		/** \brief Flow control action index to be configured */
		u8 flow_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	union {
		/** \brief SAM FCA for bypass/drop actions */
		struct sam_fca_bpd bypass_drop;
		/** \brief SAM FCA for decryption/encryption actions */
		struct sam_fca_macsec dec_enc;
		/** \brief SAM FCA for crypt-authenticate operations */
		struct sam_fca_crypt crypt_auth;
	};
	/** \brief SAM FCA for crypt-authenticate control */
	struct sam_fca_cac cabp_len;
};
/**@}*/ /* GPY211_SECFCA */

/** \addtogroup GPY211_MACSEC_SECSTATS */
/**@{*/
/** \brief Ingress - Per-SA statistics */
struct ing_sa_stats {
	union {
		/** \brief SA stats index to read */
		u8 rule_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	union {
		/** \brief Total input octets decrypted */
		u64 InOctetsDecrypted;
		/** \brief Total input octets validated */
		u64 InOctetsValidated;
	};
	union {
		/** \brief Total input octets decrypted (extended) */
		u64 InOctetsDecrypted2;
		/** \brief Total input octets validated (extended) */
		u64 InOctetsValidated2;
	};
	union {
		/** \brief Total input packets Unchecked */
		u64 InPktsUnchecked;
		/** \brief Total input packets HitDrop */
		u64 InPktsHitDrop;
	};
	/** \brief Total input packets Delayed */
	u64 InPktsDelayed;
	/** \brief Total input packets Late */
	u64 InPktsLate;
	/** \brief Total input packets decrypted */
	u64 InPktsOK;
	/** \brief Total input packets Invalid */
	u64 InPktsInvalid;
	/** \brief Total input packets NotValid */
	u64 InPktsNotValid;
	/** \brief Total input packets NotUsingSA */
	u64 InPktsNotUsingSA;
	/** \brief Total input packets UnusedSA */
	u64 InPktsUnusedSA;
	/** \brief Total input packets those are not MACsec tagged */
	u64 InPktsUntaggedHit;
};

/** \brief Egress - Per-SA statistics */
struct egr_sa_stats {
	union {
		/** \brief SA stats index to read */
		u8 rule_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	union {
		/** \brief Total output octets encrypted */
		u64 OutOctetsEncrypted;
		/** \brief Total output octets protected */
		u64 OutOctetsProtected;
	};
	union {
		/** \brief Total output octets encrypted (extended) */
		u64 OutOctetsEncrypted2;
		/** \brief Total output octets protected (extended) */
		u64 OutOctetsProtected2;
	};
	union {
		/** \brief Total output packets encrypted */
		u64 OutPktsEncrypted;
		/** \brief Total output packets protected */
		u64 OutPktsProtected;
		/** \brief Total output packets HitDrop */
		u64 OutPktsHitDrop;
	};
	/** \brief Total output packets those exceed MTU size after encrypted */
	u64 OutPktsTooLong;
};

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
/** @cond INTERNAL */
/** \brief Ingress - Per-VLAN-UP statistics */
struct ing_vlan_stats {
	/** \brief VLAN User Priority (CoS) */
	u8 vlan_up;
	/** \brief Total octets before decryption */
	u64 InOctetsVL;
	/** \brief Total octets before decryption (extended) */
	u64 InOctetsVL2;
	/** \brief Total packets decrypted */
	u64 InPktsVL;
	/** \brief Total packets Dropped */
	u64 InDroppedPktsVL;
	/** \brief Total packets OverSize */
	u64 InOverSizePktsVL;
};

/** \brief Egress - Per-VLAN-UP statistics */
struct egr_vlan_stats {
	/** \brief VLAN User Priority (CoS) */
	u8 vlan_up;
	/** \brief Total octets after encryption */
	u64 OutOctetsVL;
	/** \brief Total octets after encryption (extended) */
	u64 OutOctetsVL2;
	/** \brief Total packets encrypted */
	u64 OutPktsVL;
	/** \brief Total packets Dropped */
	u64 OutDroppedPktsVL;
	/** \brief Total packets OverSize */
	u64 OutOverSizePktsVL;
};
/** @endcond */
#endif

/** \brief Ingress - Global statistics */
struct ing_global_stats {
	/** \brief Total transform errors */
	u64 TransformErrorPkts;
	/** \brief Total input control frames */
	u64 InPktsCtrl;
	/** \brief Total input 'Strict' validated non MACsec tagged frames  */
	u64 InPktsNoTag;
	/** \brief Total input non 'Strict' validated non MACsec tagged frames */
	u64 InPktsUntagged;
	/** \brief Total input MACsec tagged frames */
	u64 InPktsTagged;
	/** \brief Total input (non MACsec tagged) bad-tagged frames */
	u64 InPktsBadTag;
	/** \brief Total input (non MACsec tagged) SA not found frames */
	u64 InPktsUntaggedMiss;
	/** \brief Total input (MACsec tagged) but without SCI frames */
	u64 InPktsNoSCI;
	/** \brief Total input (MACsec tagged) but with unknown SCI frames */
	u64 InPktsUnknownSCI;
	/** \brief Total input Ingress CC failed Control frames */
	u64 InConsistCheckControlledNotPass;
	/** \brief Total input Ingress CC failed Uncontrol frames */
	u64 InConsistCheckUncontrolledNotPass;
	/** \brief Total input Ingress CC passed Control frames */
	u64 InConsistCheckControlledPass;
	/** \brief Total input Ingress CC passed Uncontrol frames */
	u64 InConsistCheckUncontrolledPass;
	/** \brief Total input non-VLAN frames decrypted */
	u64 InOverSizePkts;
};

/** \brief Egress - Global statistics */
struct egr_global_stats {
	/** \brief Total transform errors	*/
	u64 TransformErrorPkts;
	/** \brief Total output control frames */
	u64 OutPktsCtrl;
	/** \brief Total output frames for those SA not found */
	u64 OutPktsUnknownSA;
	/** \brief Total output frames without protection */
	u64 OutPktsUntagged;
	/** \brief Total output non-VLAN frames encrypted */
	u64 OutOverSizePkts;
};

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
/** \brief Counters debug registers-1 */
struct count_debug1 {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief SA counters that were incremented for the last packet */
			u32 sa_inc_mask: 15;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief SA octet counters that were incremented for the last packet */
			u32 sa_octet_inc: 15;
			/** \brief Reserved */
			u32 reserved2: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved2: 1;
			/** \brief SA octet counters that were incremented for the last packet */
			u32 sa_octet_inc: 15;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief SA counters that were incremented for the last packet */
			u32 sa_inc_mask: 15;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief Counters debug registers - Raw */
		u32 raw_cdb1;
	};
};

/** \brief Counters debug registers-2 */
struct count_debug2 {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief SA counters that were incremented for the last packet */
			u32 vlan_inc_mask: 15;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Reserved */
			u32 vlan_octet_inc: 15;
			/** \brief Reserved */
			u32 reserved2: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved2: 1;
			/** \brief Reserved */
			u32 vlan_octet_inc: 15;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief SA counters that were incremented for the last packet */
			u32 vlan_inc_mask: 15;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief Counters debug registers - Raw */
		u32 raw_cdb2;
	};
};

/** \brief Counters debug registers-4 */
struct count_debug4 {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief COUNT_DEBUG1 register has been written with test data */
			u32 sa_test: 1;
			/** \brief COUNT_DEBUG2 register has been written with test data */
			u32 vlan_test: 1;
			/** \brief COUNT_DEBUG3 register has been written with test data */
			u32 global_test: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief SA counters that were incremented for the last packet */
			u32 sa_nr: 8;
			/** \brief VLAN counters that were incremented for the last packet */
			u32 vlan_up: 3;
			/** \brief Reserved */
			u32 reserved2: 1;
			/** \brief Global octet counters that were incremented for the last packet */
			u32 global_octet_inc: 15;
			/** \brief Reserved */
			u32 reserved3: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved3: 1;
			/** \brief Global octet counters that were incremented for the last packet */
			u32 global_octet_inc: 15;
			/** \brief Reserved */
			u32 reserved2: 1;
			/** \brief VLAN counters that were incremented for the last packet */
			u32 vlan_up: 3;
			/** \brief SA counters that were incremented for the last packet */
			u32 sa_nr: 8;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief COUNT_DEBUG3 register has been written with test data */
			u32 global_test: 1;
			/** \brief COUNT_DEBUG2 register has been written with test data */
			u32 vlan_test: 1;
			/** \brief COUNT_DEBUG1 register has been written with test data */
			u32 sa_test: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief Counters debug registers - Raw */
		u32 raw_cdb4;
	};
};

/** \brief Statistics counters module debug registers */
struct stats_debug_regs {
	/** \brief Counters debug registers -Bitfield */
	struct count_debug1 cdb1;
	/** \brief Counters debug registers -Bitfield */
	struct count_debug2 cdb2;
	/** Global counters that were incremented for the last packet */
	u32 global_inc_mask;
	/** \brief Counters debug registers -Bitfield */
	struct count_debug4 cdb4;
};
#endif

/** \brief Thresholds for the frame or octet counters */
struct frame_octet_thr {
	/** Frame threshold */
	u64 frame_threshold;
	/** Octet threshold */
	u64 octet_threshold;
};

/** \brief Per-SA stats get type */
enum psa_input {
	/** \brief Get all Per SA statistics summary flags */
	PSA_SUMM_GET_ALL = 0,
	/** \brief Get Per SA statistics summary flags for given SA num */
	PSA_SUMM_GET_GIVEN = 1,
};

/** \brief Counters memory map: Ingress - Per-SA statistics */
struct ing_psa_bmap {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Total input octets decrypted (aka validated) */
			u32 InOctetsDecryptedValidated: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Total input packets Unchecked (aks HitDropReserved) */
			u32 InPktsUncheckedHitDropReserved: 1;
			/** \brief Total input packets Delayed */
			u32 InPktsDelayed: 1;
			/** \brief Total input packets Late */
			u32 InPktsLate: 1;
			/** \brief Total input packets decrypted */
			u32 InPktsOK: 1;
			/** \brief Total input packets Invalid */
			u32 InPktsInvalid: 1;
			/** \brief Total input packets NotValid */
			u32 InPktsNotValid: 1;
			/** \brief Total input packets NotUsingSA */
			u32 InPktsNotUsingSA: 1;
			/** \brief Total input packets UnusedSA */
			u32 InPktsUnusedSA: 1;
			/** \brief Total input packets those are not MACsec tagged */
			u32 InPktsUntaggedHit: 1;
			/** \brief Reserved */
			u32 reserved2: 21;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved2: 21;
			/** \brief Total input packets those are not MACsec tagged */
			u32 InPktsUntaggedHit: 1;
			/** \brief Total input packets UnusedSA */
			u32 InPktsUnusedSA: 1;
			/** \brief Total input packets NotUsingSA */
			u32 InPktsNotUsingSA: 1;
			/** \brief Total input packets NotValid */
			u32 InPktsNotValid: 1;
			/** \brief Total input packets Invalid */
			u32 InPktsInvalid: 1;
			/** \brief Total input packets decrypted */
			u32 InPktsOK: 1;
			/** \brief Total input packets Late */
			u32 InPktsLate: 1;
			/** \brief Total input packets Delayed */
			u32 InPktsDelayed: 1;
			/** \brief Total input packets Unchecked (aks HitDropReserved) */
			u32 InPktsUncheckedHitDropReserved: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Total input octets decrypted (aka validated) */
			u32 InOctetsDecryptedValidated: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Counters memory map: Ingress - Per-SA statistics - raw */
		u32 raw_psa_bmap;
	};
};

/** \brief Counters memory map: Egress - Per-SA statistics */
struct egr_psa_bmap {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Total output octets encrypted (aka protected) */
			u32 OutOctetsEncryptedProtected: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Total output packets encrypted (aks HitDropReserved) */
			u32 OutPktsEncryptedProtectedHitDropReserved: 1;
			/** \brief Total output packets those exceed MTU size after encrypted */
			u32 OutPktsTooLong: 1;
			/** \brief Reserved */
			u32 reserved2: 28;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved2: 28;
			/** \brief Total output packets those exceed MTU size after encrypted */
			u32 OutPktsTooLong: 1;
			/** \brief Total output packets encrypted (aks HitDropReserved) */
			u32 OutPktsEncryptedProtectedHitDropReserved: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Total output octets encrypted (aka protected) */
			u32 OutOctetsEncryptedProtected: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Counters memory map: Egress - Per-SA statistics - raw */
		u32 raw_psa_bmap;
	};
};

/** \brief Per SA statistics summary flags */
struct psa_summary {
	union {
		/** \brief SA stats index to read / clear */
		u8 rule_index;
		/** \brief (Deprecated) Do not use this param */
		u8 sarule_num;
	};
	/** \brief Per-SA stats get type.
	Valid values are defined in \ref psa_input enum */
	enum psa_input psa_type;
	/** \brief Per-SA statistics summary \ref ing_psa_bmap or egr_psa_bmap */
	u32 count_summ_psa[MACSEC_MAX_SA_RULES];
};
/**@}*/ /* GPY211_SECSTATS */

/** \addtogroup GPY211_MACSEC_SECCCTRL */
/**@{*/
/** \brief Counters control params */
struct count_control {
	/** \brief Reset all statistics counters to zero also clears all statistics
			   summary registers */
	u8 reset_all;
	/** \brief Enable normal read/write access to the counter memory for dbg */
	u8 debug_access;
	/** \brief Saturate or wrap back */
	u8 saturate_cntrs;
	/** \brief Counters cleared on a read */
	u8 auto_cntr_reset;
	/** \brief Resets all statistics threshold summary registers */
	u8 reset_summary;
};

/** \brief Counters increment enable registers */
struct count_incen {
	/** \brief SA counters is allowed to be incremented */
	u16 sa_inc_en;
	/** \brief VLAN counters is allowed to be incremented */
	u16 vlan_inc_en;
	/** \brief Global counters is allowed to be incremented */
	u16 global_inc_en;
};

/** \brief A packet for which a security failure is declared */
struct count_secfail1 {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief SA-related counter increments are regarded a security fail */
			u32 sa_secfail_mask: 15;
			/** \brief If to update any VLAN counters for a non-VLAN packet */
			u32 vlan_cntr_update: 1;
			/** \brief If to use result of consistency checking module */
			u32 gate_cons_check: 1;
			/** \brief Mask for MACsec crypto-core first result token word */
			u32 error_mask: 15;
#elif defined(__BIG_ENDIAN)
			/** \brief Mask for MACsec crypto-core first result token word */
			u32 error_mask: 15;
			/** \brief If to use result of consistency checking module */
			u32 gate_cons_check: 1;
			/** \brief If to update any VLAN counters for a non-VLAN packet */
			u32 vlan_cntr_update: 1;
			/** \brief SA-related counter increments are regarded a security fail */
			u32 sa_secfail_mask: 15;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** A packet for which a security failure is declared - raw */
		u32 raw_secfail1;
	};
};

/** \brief A packet for which a security failure is declared */
struct count_secfail {
	/** \brief A packet for which a security failure is declared */
	struct count_secfail1 secfail_1;
	/** \brief Which global counter increments are regarded a security fail event */
	u32 global_secfaill_mask;
};
/**@}*/ /* GPY211_SECCCTRL */

/** \addtogroup GPY211_MACSEC_SECMCTRL */
/**@{*/
/** \brief Misc control params */
struct misc_control {
	/** \brief Fixed latency forcing value */
	u16 mc_latency_fix;
	/** \brief Debug feature */
	u8 static_bypass;
	/** \brief 802.1AE compliant processing */
	u8 nm_macsec_en;
	/** \brief Global frame validation level. This value is used for 802.1AE
	compliant processing when no MACsec secure channel is found.
	Valid values are defined in \ref sam_fca_fvt enum */
	enum sam_fca_fvt validate_frames;
	/** \brief Resets all statistics threshold summary registers */
	u8 sectag_after_vlan;
};
/**@}*/ /* GPY211_SECMCTRL */

/** \addtogroup GPY211_MACSEC_SECNMCTRL */
/**@{*/
/** \brief SN non-match control params */
struct sa_nm_params {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Compare Ether-type against 0x88E5 */
			u32 comp_etype: 1;
			/** \brief Check V (Version) */
			u32 check_v: 1;
			/** \brief Check if KaY packet */
			u32 check_kay: 1;
			/** \brief Check illegal C == 1 & E == 0 flags combination */
			u32 check_c_e: 1;
			/** \brief Check illegal SC/ES/SCB bit combinations */
			u32 check_sc: 1;
			/** \brief Check SL (Short Length) field contents out-of-range */
			u32 check_sl: 1;
			/** \brief Check PN (Only for 32-bit PN) */
			u32 check_pn: 1;
			/** Reserved */
			u32 reserved: 9;
			/** Reserved */
			u32 msec_tag_value: 16;
			/** SA no-match classifier control - raw */
#elif defined(__BIG_ENDIAN)
			/** Ether-type value used for MACsec tag type comparison */
			u32	msec_tag_value: 16;
			/** Reserved */
			u32	reserved: 9;
			/** \brief Check PN (Only for 32-bit PN) */
			u32	check_pn: 1;
			/** \brief Check SL (Short Length) field contents out-of-range */
			u32	check_sl: 1;
			/** \brief Check illegal SC/ES/SCB bit combinations */
			u32	check_sc: 1;
			/** \brief Check illegal C == 1 & E == 0 flags combination */
			u32	check_c_e: 1;
			/** \brief Check if KaY packet */
			u32	check_kay: 1;
			/** \brief Check V (Version) */
			u32	check_v: 1;
			/** \brief Compare Ether-type against 0x88E5 */
			u32	comp_etype: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** SA no-match classifier control - raw */
		u32 raw_sanm_ctrl;
	};
};
/**@}*/ /* GPY211_SECNMCTRL */

/** \addtogroup GPY211_MACSEC_SECNMFCA */
/**@{*/
/** \brief SA non-match SecY packet type */
enum sa_nm_secy_pt {
	/** \brief Non-MACsec tag */
	SA_NM_SECY_UNTAGGED = 0,
	/** \brief Valid MACsec tagged */
	SA_NM_SECY_TAGGED = 1,
	/** \brief Invalid MACsec tagged */
	SA_NM_SECY_BAD_TAGGED = 2,
	/** \brief Valid MACsec tagged handled by KaY */
	SA_NM_SECY_KAY_TAGGED = 3,
	/** \brief Same action for all above types of frames */
	SA_NM_SECY_ALL_TAGGED = 4,
};

/** \brief SA non-match FCA flow type */
enum sa_nm_fca_ft {
	/** \brief Bypass */
	SA_NM_FCA_FLOW_BYPASS = 0,
	/** \brief Drop */
	SA_NM_FCA_FLOW_DROP = 1,
};

/** \brief SA non-match FCA dest-port type */
enum sa_nm_fca_dpt {
	/** \brief Common port */
	SA_NM_FCA_DPT_COMMON = 0,
	/** \brief Reserved port */
	SA_NM_FCA_DPT_RES = 1,
	/** \brief Control port */
	SA_NM_FCA_DPT_CONTROL = 2,
	/** \brief Un-Control port */
	SA_NM_FCA_DPT_UNCONTROL = 3,
};

/** \brief SA non-match FCA drop-action type */
enum sa_nm_fca_dat {
	/** \brief Bypass with CRC corruption indicator */
	SA_NM_FCA_DROP_AS_CRC = 0,
	/** \brief Bypass with bad packet indicator */
	SA_NM_FCA_DROP_AS_BAD_PKT = 1,
	/** \brief Internal drop by crypto-core */
	SA_NM_FCA_DROP_AS_INTERNAL = 2,
	/** \brief Do not drop (for debugging only) */
	SA_NM_FCA_NO_DROP = 3,
};

/** \brief SN non-match flow control action */
struct sa_nonmatch_fca {
	/** \brief SecY packet type.
	Valid values are defined in \ref sa_nm_secy_pt enum */
	enum sa_nm_secy_pt pkt_type;
	/** \brief Flow type
	Valid values are defined in \ref sa_nm_fca_ft enum */
	enum sa_nm_fca_ft flow_type;
	/** \brief Destination port
	Valid values are defined in \ref sa_nm_fca_dpt enum */
	enum sa_nm_fca_dpt dest_port;
	/** \brief (-i)Perform drop_action */
	u8 drop_non_reserved;
	/** \brief Drop action
	Valid values are defined in \ref sa_nm_fca_dat enum */
	enum sa_nm_fca_dat drop_action;
};
/**@}*/ /* GPY211_SECNMFCA */

/** \addtogroup GPY211_MACSEC_SECSASUMM */
/**@{*/
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
/** \brief Counters memory map: Ingress - Per-VLAN-UP statistics */
struct ing_vlan_bmap {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Total octets before decryption */
			u32 InOctetsVL: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Total packets decrypted */
			u32 InPktsVL: 1;
			/** \brief Total packets Dropped */
			u32 InDroppedPktsVL: 1;
			/** \brief Total packets OverSize */
			u32 InOverSizePktsVL: 1;
			/** \brief Reserved */
			u32 reserved2: 27;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved2: 27;
			/** \brief Total packets OverSize */
			u32 InOverSizePktsVL: 1;
			/** \brief Total packets Dropped */
			u32 InDroppedPktsVL: 1;
			/** \brief Total packets decrypted */
			u32 InPktsVL: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Total octets before decryption */
			u32 InOctetsVL: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Counters memory map: Ingress - Per-VLAN-UP statistics - raw */
		u32 raw_vlan_bmap;
	};
};

/** \brief Counters memory map: Egress - Per-VLAN-UP statistics */
struct egr_vlan_bmap {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Total octets after encryption */
			u32 OutOctetsVL: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Total packets encrypted */
			u32 OutPktsVL: 1;
			/** \brief Total packets Dropped */
			u32 OutDroppedPktsVL: 1;
			/** \brief Total packets OverSize */
			u32 OutOverSizePktsVL: 1;
			/** \brief Reserved */
			u32 reserved2: 27;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved2: 27;
			/** \brief Total packets OverSize */
			u32 OutOverSizePktsVL: 1;
			/** \brief Total packets Dropped */
			u32 OutDroppedPktsVL: 1;
			/** \brief Total packets encrypted */
			u32 OutPktsVL: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Total octets after encryption */
			u32 OutOctetsVL: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Counters memory map: Ingress - Per-VLAN-UP statistics - raw */
		u32 raw_vlan_bmap;
	};
};
#endif

/** \brief Counters memory map: Ingress - Global statistics */
struct ing_global_bmap {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Total transform errors */
			u32 TransformErrorPkts: 1;
			/** \brief Total input control frames */
			u32 InPktsCtrl: 1;
			/** \brief Total input 'Strict' validated non MACsec tagged frames  */
			u32 InPktsNoTag: 1;
			/** \brief Total input non 'Strict' validated non MACsec tagged frames */
			u32 InPktsUntagged: 1;
			/** \brief Total input MACsec tagged frames */
			u32 InPktsTagged: 1;
			/** \brief Total input (non MACsec tagged) bad-tagged frames */
			u32 InPktsBadTag: 1;
			/** \brief Total input (non MACsec tagged) SA not found frames */
			u32 InPktsUntaggedMiss: 1;
			/** \brief Total input (MACsec tagged) but without SCI frames */
			u32 InPktsNoSCI: 1;
			/** \brief Total input (MACsec tagged) but with unknown SCI frames */
			u32 InPktsUnknownSCI: 1;
			/** \brief Total input Ingress CC failed Controlled frames */
			u32 InConsistCheckControlledNotPass: 1;
			/** \brief Total input Ingress CC failed Uncontrolled frames */
			u32 InConsistCheckUncontrolledNotPass: 1;
			/** \brief Total input Ingress CC passed Controlled frames */
			u32 InConsistCheckControlledPass: 1;
			/** \brief Total input Ingress CC passed Uncontrolled frames */
			u32 InConsistCheckUncontrolledPass: 1;
			/** \brief Total input non-VLAN frames decrypted */
			u32 InOverSizePkts: 1;
			/** \brief Reserved */
			u32 reserved: 18;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved: 18;
			/** \brief Total input non-VLAN frames decrypted */
			u32 InOverSizePkts: 1;
			/** \brief Total input Ingress CC passed Uncontrolled frames */
			u32 InConsistCheckUncontrolledPass: 1;
			/** \brief Total input Ingress CC passed Controlled frames */
			u32 InConsistCheckControlledPass: 1;
			/** \brief Total input Ingress CC failed Uncontrolled frames */
			u32 InConsistCheckUncontrolledNotPass: 1;
			/** \brief Total input Ingress CC failed Controlled frames */
			u32 InConsistCheckControlledNotPass: 1;
			/** \brief Total input (MACsec tagged) but with unknown SCI frames */
			u32 InPktsUnknownSCI: 1;
			/** \brief Total input (MACsec tagged) but without SCI frames */
			u32 InPktsNoSCI: 1;
			/** \brief Total input (non MACsec tagged) SA not found frames */
			u32 InPktsUntaggedMiss: 1;
			/** \brief Total input (non MACsec tagged) bad-tagged frames */
			u32 InPktsBadTag: 1;
			/** \brief Total input MACsec tagged frames */
			u32 InPktsTagged: 1;
			/** \brief Total input non 'Strict' validated non MACsec tagged frames */
			u32 InPktsUntagged: 1;
			/** \brief Total input 'Strict' validated non MACsec tagged frames	*/
			u32 InPktsNoTag: 1;
			/** \brief Total input control frames */
			u32 InPktsCtrl: 1;
			/** \brief Total transform errors */
			u32 TransformErrorPkts: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Counters memory map: Ingress - Global statistics - raw */
		u32 raw_global_bmap;
	};
};

/** \brief Counters memory map: Egress - Global statistics */
struct egr_global_bmap {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Total transform errors	*/
			u32 TransformErrorPkts: 1;
			/** \brief Total output control frames */
			u32 OutPktsCtrl: 1;
			/** \brief Total output frames for those SA not found */
			u32 OutPktsUnknownSA: 1;
			/** \brief Total output frames without protection */
			u32 OutPktsUntagged: 1;
			/** \brief Total output non-VLAN frames encrypted */
			u32 OutOverSizePkts: 1;
			/** \brief Reserved */
			u32 reserved: 27;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved: 27;
			/** \brief Total output non-VLAN frames encrypted */
			u32 OutOverSizePkts: 1;
			/** \brief Total output frames without protection */
			u32 OutPktsUntagged: 1;
			/** \brief Total output frames for those SA not found */
			u32 OutPktsUnknownSA: 1;
			/** \brief Total output control frames */
			u32 OutPktsCtrl: 1;
			/** \brief Total transform errors	*/
			u32 TransformErrorPkts: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Counters memory map: Ingress - Global statistics - raw */
		u32 raw_global_bmap;
	};
};

/** \brief SA expired/pn-thr/psa summary */
struct stats_summary {
#ifdef USE_WORD_READ // 32-bit word based read
	/** \brief 32-bit word number to be configured */
	u8 word_num: 3;
#endif
	/** \brief Per-SA statistics summary */
	u32 psa_sum_word[MACSEC_MAX_SA_RULES / 32];
	/** \brief Global statistics summary \ref ing_global_bmap or egr_global_bmap*/
	u32 glb_summ_word;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	/** \brief VLAN statistics summary \ref ing_vlan_bmap or egr_vlan_bmap*/
	u32 vlan_summ_word[MAX_VLAN_COUNT_SUMM_WORDS];
#endif
};
/**@}*/ /* GPY211_SECSASUMM */

/** \addtogroup GPY211_MACSEC_SECCPC */
/**@{*/
/** \brief Control Packet Classification entry type */
enum cpc_entry_type {
	/** \brief Entries 0 - 9 for rule matching on DA + ET */
	CPC_ENTRY_DA_ETH = 0,
	/** \brief DA range compare with lower and upper bound values */
	CPC_ENTRY_DA_RANGE = 1,
	/** \brief Enable MAC_DA compare against programmable 44 bits “constant” */
	CPC_ENTRY_DA_CONST44 = 2,
	/** \brief Enable MAC_DA compare against programmable 48 bits “constant” */
	CPC_ENTRY_DA_CONST48 = 3,
	/** \brief Entries 10 - 17 for rule matching on ET or Vlan id + Vlan up*/
	CPC_ENTRY_ETH = 4,
};

/** \brief Control packet match mode register */
struct cp_match_mode {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up
					   When vlan_sel_x is set, the corresponding etype_sel_x and
					   etype_sel_10+x are ignored.*/
			u32 vlan_sel_0: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32 vlan_sel_1: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32 vlan_sel_2: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32 vlan_sel_3: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32 vlan_sel_4: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32 vlan_sel_5: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32 vlan_sel_6: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32 vlan_sel_7: 1;
#else
			/** \brief Reserved */
			u32 reserved3: 8;
#endif
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_0: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_1: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_2: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_3: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_4: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_5: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_6: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_7: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_8: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_9: 1;
			/** \brief Write zeroes and ignore on reading */
			u32 reserved: 3;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_10: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_11: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_12: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_13: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_14: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_15: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_16: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32 e_type_sel_17: 1;
			/** \brief Write zeroes and ignore on reading */
			u32 reserved2: 3;
#elif defined(__BIG_ENDIAN)
			/** \brief Write zeroes and ignore on reading */
			u32	reserved2: 3;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_17: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_16: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_15: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_14: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_13: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_12: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_11: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_10: 1;
			/** \brief Write zeroes and ignore on reading */
			u32	reserved: 3;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_9: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_8: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_7: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_6: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_5: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_4: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_3: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_2: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_1: 1;
			/** \brief Enable matching on parsed (=1) or packet (=0) Ethertype */
			u32	e_type_sel_0: 1;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32	vlan_sel_7: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32	vlan_sel_6: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32	vlan_sel_5: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32	vlan_sel_4: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32	vlan_sel_3: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32	vlan_sel_2: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up */
			u32	vlan_sel_1: 1;
			/** \brief Enable matching on DA + ET + Vlan id + Vlan up
					   When vlan_sel_x is set, the corresponding etype_sel_x and
					   etype_sel_10+x are ignored.*/
			u32	vlan_sel_0: 1;
#else
			/** \brief Reserved */
			u32 reserved3: 8;
#endif
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief Control packet match mask (raw) */
		u32 cp_match_mask;
	};
};

/** \brief Control packet match enable register */
struct cp_match_enable {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Enable MAC_DA compare */
			u32 mac_da_0: 1;
			/** \brief Enable MAC_DA compare */
			u32 mac_da_1: 1;
			/** \brief Enable MAC_DA compare */
			u32 mac_da_2: 1;
			/** \brief Enable MAC_DA compare */
			u32 mac_da_3: 1;
			/** \brief Enable MAC_DA compare */
			u32 mac_da_4: 1;
			/** \brief Enable MAC_DA compare */
			u32 mac_da_5: 1;
			/** \brief Enable MAC_DA compare */
			u32 mac_da_6: 1;
			/** \brief Enable MAC_DA compare */
			u32 mac_da_7: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_0: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_1: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_2: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_3: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_4: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_5: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_6: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_7: 1;
			/** \brief Enable combined MAC_DA/Ether-type compare */
			u32 comb_8: 1;
			/** \brief Enable combined MAC_DA/Ether-type compare */
			u32 comb_9: 1;
			/** \brief Enable MAC_DA range compare */
			u32 range: 1;
			/** \brief Enable MAC_DA compare against given 44 bits “constant” */
			u32 const_44: 1;
			/** \brief Enable MAC_DA compare against given 48 bits “constant” */
			u32 const_48: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_10: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_11: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_12: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_13: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_14: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_15: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_16: 1;
			/** \brief Enable Ether-type compare */
			u32 e_type_17: 1;
			/** \brief Write zeroes and ignore on reading */
			u32 reserved: 3;
#elif defined(__BIG_ENDIAN)
			/** \brief Write zeroes and ignore on reading */
			u32	reserved: 3;
			/** \brief Enable Ether-type compare */
			u32	e_type_17: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_16: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_15: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_14: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_13: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_12: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_11: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_10: 1;
			/** \brief Enable MAC_DA compare against given 48 bits “constant” */
			u32	const_48: 1;
			/** \brief Enable MAC_DA compare against given 44 bits “constant” */
			u32	const_44: 1;
			/** \brief Enable MAC_DA range compare */
			u32	range: 1;
			/** \brief Enable combined MAC_DA/Ether-type compare */
			u32	comb_9: 1;
			/** \brief Enable combined MAC_DA/Ether-type compare */
			u32	comb_8: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_7: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_6: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_5: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_4: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_3: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_2: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_1: 1;
			/** \brief Enable Ether-type compare */
			u32	e_type_0: 1;
			/** \brief Enable MAC_DA compare */
			u32	mac_da_7: 1;
			/** \brief Enable MAC_DA compare */
			u32	mac_da_6: 1;
			/** \brief Enable MAC_DA compare */
			u32	mac_da_5: 1;
			/** \brief Enable MAC_DA compare */
			u32	mac_da_4: 1;
			/** \brief Enable MAC_DA compare */
			u32	mac_da_3: 1;
			/** \brief Enable MAC_DA compare */
			u32	mac_da_2: 1;
			/** \brief Enable MAC_DA compare */
			u32	mac_da_1: 1;
			/** \brief Enable MAC_DA compare */
			u32	mac_da_0: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief  */
		u32 cp_match_en;
	};
};

/** \brief Control Packet match rule params */
struct cp_class_param {
	/** \brief DA or ET entry number */
	u8 cpc_index;
	/** \brief CPC entry type to program */
	enum cpc_entry_type cpc_type;
	union {
		/** \brief Individual Dst MAC */
		u8 mac_da[6];
		/** \brief Range: Start Dst MAC */
		u8 mac_da_start[6];
		/** \brief MAC_DA 44 bits “constant” */
		u8 mac_da_const44[6];
		/** \brief MAC_DA 48 bits “constant” */
		u8 mac_da_const48[6];
	};
	/** \brief Range: End Dst MAC */
	u8 mac_da_end[6];
	union {
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief One VLAN Id compare value for the first VLAN TAG */
			u16 vlan_id: 12;
			/** \brief One VLAN Up compare value for the first VLAN TAG */
			u16 vlan_up: 3;
			/** \brief When set, compare of VLAN up (PCP) is disabled */
			u16 disable_up: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief When set, compare of VLAN up (PCP) is disabled */
			u16 disable_up: 1;
			/** \brief One VLAN Up compare value for the first VLAN TAG */
			u16 vlan_up: 3;
			/** \brief One VLAN Id compare value for the first VLAN TAG */
			u16 vlan_id: 12;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief VLAN information (raw) */
		u16 vlan_info;
#endif
		/** \brief Ether-type */
		u16 ether_type;
	};
	/** \brief Control packet match mask \ref cp_match_mode */
	struct cp_match_mode cpm_mode;
	/** \brief Control packet match enable \ref cp_match_enable */
	struct cp_match_enable cpm_enable;
};
/**@}*/ /* GPY211_SECCPC */

/** \addtogroup GPY211_MACSEC_SECICC */
/**@{*/
/** \brief Ingress Consistency Check control */
struct ing_cc_ctrl {
	/** \brief No match action for 'Normal' packets */
	u8 nm_act;
	/** \brief No match action for 'Control' packets */
	u8 nm_ctrl_act;
	/** \brief Ether-type field compare value for the etype_valid comparison */
	u16 cp_etype_max_len;
};

/** \brief Ingress Consistency Check entry word-0 */
struct icc_match_ovl_eth {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN

			/** \brief Outer VLAN Id compare value */
			u32 vlan_id: 12;
			/** \brief Reserved */
			u32 reserved: 4;
#else
			/** \brief Reserved */
			u32 reserved: 16;
#endif
			/** \brief Ether-type compare value against actual Ether-type field */
			u32 payload_e_type: 16;
#elif defined(__BIG_ENDIAN)
			/** \brief Ether-type compare value against actual Ether-type field */
			u32 payload_e_type: 16;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
			/** \brief Reserved */
			u32 reserved: 4;
			/** \brief One VLAN Id compare value */
			u32 vlan_id: 12;
#else
			/** \brief Reserved */
			u32 reserved: 16;
#endif
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief ICC entry word-0 (raw) */
		u32 raw_iccm_vleth;
	};
};

/** \brief Ingress Consistency Check entry word-1 */
struct icc_match_misc {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief SA entry matched for this packet */
			u32 sai_hit: 1;
			/** \brief Packet is tagged as 802.1Q or 802.1s VLAN packet */
			u32 vlan_valid: 1;
			/** \brief First Ether-type in packet > cp_etype_max_len */
			u32 etype_valid: 1;
			/** \brief Packet was classified as control packet */
			u32 ctrl_packet: 1;
			/** \brief Enable sai_hit field compare */
			u32 sa_hit_mask: 1;
			/** \brief Enable sa_or_rule_nr field compare with SA entry number
					   (the rule_nr_mask must be 0b) */
			u32 sa_nr_mask: 1;
			/** \brief Enable vlan_valid field compare */
			u32 vlan_valid_mask: 1;
			/** \brief Enable vlan_id field compare (do not set to 1b if no
					   VLAN packet is expected here) */
			u32 vlan_id_mask: 1;
			/** \brief Enable etype_valid field compare */
			u32 etype_valid_mask: 1;
			/** \brief Enable payload_e_type field compare */
			u32 payl_etype_mask: 1;
			/** \brief Enable ctrl_packet field compare */
			u32 ctrl_packet_mask: 1;
			/** \brief Enable sa_or_rule_nr field compare with SA matching rule
					   number (the sa_nr_mask must be 0b) */
			u32 rule_nr_mask: 1;
			/** \brief Priority of this entry for determining the match action
					   on a match, 0 = lowest, 7 = highest */
			u32 match_priority: 3;
			/** \brief Packet match action, 0b = drop, 1b = pass */
			u32 match_action: 1;
			/** \brief Compare value for SA matching rule number or SA entry
					   number, depending on which flag is set (rule_nr_mask or
					   sa_nr_mask) */
			u32 sa_or_rule_nr: 8;
			/** \brief Enable parsed inner VLAN User Priority value compare with
					   vlan_up_inner field */
			u32 vlan_up_inner_mask: 1;
			/** \brief Enable parsed inner VLAN ID value compare with
					   vlan_up_inner field */
			u32 vlan_id_inner_mask: 1;
			/** \brief SA matching rule matched for this packet */
			u32 rule_hit: 1;
			/** \brief Enable rule_hit field compare */
			u32 rule_hit_mask: 1;
			/** \brief SA matching rule matched for this packet */
			u32 reserved: 4;
#elif defined(__BIG_ENDIAN)
			/** \brief SA matching rule matched for this packet */
			u32 reserved: 4;
			/** \brief Enable rule_hit field compare */
			u32 rule_hit_mask: 1;
			/** \brief SA matching rule matched for this packet */
			u32 rule_hit: 1;
			/** \brief Enable parsed inner VLAN ID value compare with
					   vlan_up_inner field */
			u32 vlan_id_inner_mask: 1;
			/** \brief Enable parsed inner VLAN User Priority value compare with
					   vlan_up_inner field */
			u32 vlan_up_inner_mask: 1;
			/** \brief Compare value for SA matching rule number or SA entry
					   number, depending on which flag is set (rule_nr_mask or
					   sa_nr_mask) */
			u32 sa_or_rule_nr: 8;
			/** \brief Packet match action, 0b = drop, 1b = pass */
			u32 match_action: 1;
			/** \brief Priority of this entry for determining the match action
					   on a match, 0 = lowest, 7 = highest */
			u32 match_priority: 3;
			/** \brief Enable sa_or_rule_nr field compare with SA matching rule
					   number (the sa_nr_mask must be 0b) */
			u32 rule_nr_mask: 1;
			/** \brief Enable ctrl_packet field compare */
			u32 ctrl_packet_mask: 1;
			/** \brief Enable payload_e_type field compare */
			u32 payl_etype_mask: 1;
			/** \brief Enable etype_valid field compare */
			u32 etype_valid_mask: 1;
			/** \brief Enable vlan_id field compare (do not set to 1b if no
					   VLAN packet is expected here) */
			u32 vlan_id_mask: 1;
			/** \brief Enable vlan_valid field compare */
			u32 vlan_valid_mask: 1;
			/** \brief Enable sa_or_rule_nr field compare with SA entry number
					   (the rule_nr_mask must be 0b) */
			u32 sa_nr_mask: 1;
			/** \brief Enable sai_hit field compare */
			u32 sa_hit_mask: 1;
			/** \brief Packet was classified as control packet */
			u32 ctrl_packet: 1;
			/** \brief First Ether-type in packet > cp_etype_max_len */
			u32 etype_valid: 1;
			/** \brief Packet is tagged as 802.1Q or 802.1s VLAN packet */
			u32 vlan_valid: 1;
			/** \brief SA entry matched for this packet */
			u32 sai_hit: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief ICC entry word-1 (raw) */
		u32 raw_iccm_misc;
	};
};

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
/** \brief Ingress Consistency Check entry word-2 */
struct icc_match_ivl {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Parsed inner VLAN Id compare value */
			u32 vlan_id_inner: 12;
			/** \brief Parsed inner VLAN Up compare value */
			u32 vlan_up_inner: 3;
			/** \brief Reserved */
			u32 reserved: 17;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved: 17;
			/** \brief Parsed inner VLAN Up compare value */
			u32 vlan_up_inner: 3;
			/** \brief Parsed inner VLAN Id compare value */
			u32 vlan_id_inner: 12;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief ICC entry word-2 (raw) */
		u32 raw_iccm_ivl;
	};
};
#endif

/** \brief Ingress Consistency Check parameters */
struct icc_match_param {
	/** ICC index to configure */
	u8 icc_index;
	/** ICC entry lower word-0 */
	struct icc_match_ovl_eth vlan_eth;
	/** ICC entry high word */
	struct icc_match_misc icc_misc;
#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
	/** ICC entry high word */
	struct icc_match_ivl icc_ivl;
#endif
};
/** \brief In/Out ICC Entry Enable flags */
struct raw_icc_ee {
#ifdef USE_WORD_READ // 32-bit word based read
	/** \brief 32-bit word number to be configured */
	u8 word_num: 3;
#endif
	/** \brief Max ICC Match rule flags size */
	u32 raw_icc_ee[MACSEC_MAX_SA_RULES / 32];
};

/** \brief Ingress Consistency Check Entry Enable control */
struct icc_ee_ctrl {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Index of a CC entry to enable when set_enable = 1b */
			u32 cc_index_set: 8;
			/** \brief Reserved */
			u32 reserved: 6;
			/** \brief Enable the CC entry with index cc_index_set */
			u32 set_enable: 1;
			/** \brief Enable all entries */
			u32 set_all: 1;
			/** \brief Index of a CC entry to disable when set_clear = 1b */
			u32 cc_index_clear: 8;
			/** \brief Reserved */
			u32 reserved2: 6;
			/** \brief Disable the CC entry with index cc_index_clear */
			u32 clear_enable: 1;
			/** \brief Disable all entries */
			u32 clear_all: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief Disable all entries */
			u32 clear_all: 1;
			/** \brief Disable the CC entry with index cc_index_clear */
			u32 clear_enable: 1;
			/** \brief Reserved */
			u32 reserved2: 6;
			/** \brief Index of a CC entry to disable when set_clear = 1b */
			u32 cc_index_clear: 8;
			/** \brief Enable all entries */
			u32 set_all: 1;
			/** \brief Enable the CC entry with index cc_index_set */
			u32 set_enable: 1;
			/** \brief Reserved */
			u32 reserved: 6;
			/** \brief Index of a CC entry to enable when set_enable = 1b */
			u32 cc_index_set: 8;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** \brief ICC EE Control (raw) */
		u32 raw_icc_eec;
	};
};

/**@}*/ /* GPY211_SECICC */

/** \addtogroup GPY211_MACSEC_OP_PROC */
/**@{*/
/** \brief OPP's Packet number threshold summary */
struct sa_pn_thr_summ {
#ifdef USE_WORD_READ // 32-bit word based read
	/** \brief 32-bit word number to be configured */
	u8 word_num: 3;
#endif
	/** \brief (-e)Packet number threshold summary */
	u32 pnthr_sum_word[MACSEC_MAX_SA_RULES / 32];
};

/** \brief SA expired summary */
struct sa_exp_summ {
#ifdef USE_WORD_READ // 32-bit word based read
	/** \brief 32-bit word number to be configured */
	u8 word_num: 3;
#endif
	/** \brief (-e)SA expired summary word */
	u32 sa_expsum_word[MACSEC_MAX_SA_RULES / 32];
};
/**@}*/ /* GPY211_OP_PROC */

/** \addtogroup GPY211_MACSEC_CRYPTO */
/**@{*/
#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
/** \brief Context Control/Status */
struct eip62_ctx_stat {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Frame length error */
			u32 e0: 1;
			/** \brief Token error */
			u32 e1: 1;
			/** \brief Frame input length error */
			u32 e2: 1;
			/** \brief Counter overflow */
			u32 e3: 1;
			/** \brief Token configuration error */
			u32 e4: 1;
			/** \brief Invalid command/algorithm/mode/combination */
			u32 e5: 1;
			/** \brief Prohibited algorithm */
			u32 e6: 1;
			/** \brief (-i)Packet number is zero */
			u32 e7: 1;
			/** \brief Sequence number threshold overflow */
			u32 e8: 1;
			/** \brief Authentication failed */
			u32 e9: 1;
			/** \brief (-i)Sequence number check failed.
						(-e)Sequence number rollover detected */
			u32 e10: 1;
			/** \brief Reserved */
			u32 reserved: 4;
			/** \brief Low-level state information - ??? */
			u32 debug_state: 17;
#elif defined(__BIG_ENDIAN)
			/** \brief Low-level state information - ??? */
			u32 debug_state: 17;
			/** \brief Reserved */
			u32 reserved: 4;
			/** \brief (-i)Sequence number check failed.
						(-e)Sequence number rollover detected */
			u32 e10: 1;
			/** \brief Authentication failed */
			u32 e9: 1;
			/** \brief Sequence number threshold overflow */
			u32 e8: 1;
			/** \brief (-i)Packet number is zero */
			u32 e7: 1;
			/** \brief Prohibited algorithm */
			u32 e6: 1;
			/** \brief Invalid command/algorithm/mode/combination */
			u32 e5: 1;
			/** \brief Token configuration error */
			u32 e4: 1;
			/** \brief Counter overflow */
			u32 e3: 1;
			/** \brief Frame input length error */
			u32 e2: 1;
			/** \brief Token error */
			u32 e1: 1;
			/** \brief Frame length error */
			u32 e0: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Context Status - raw */
		u32 raw_ctx_stat;
	};
};
#endif

/** \brief Interrupt Control/Status */
struct eip62_int_stat {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Input data does not properly receive all data (e2) */
			u32 input_error: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief An error occurred while processing the frame or parsing
					   the token. Combination of errors e0, e1, e3 and e4 */
			u32 processing_error: 1;
			/** \brief An invalid context has been fetched. Combination of
					   errors e5 and e6 */
			u32 context_error: 1;
			/** \brief If a sequence number exceeds the programmed sequence
					   number threshold (refer to 0) due to an outbound sequence
					   number increment this interrupt is triggered (e8) */
			u32 seq_threshold: 1;
			/** \brief If a sequence number roll-over (increment from maximum to
					   zero) due to an outbound sequence number increment this
					   interrupt is triggered (e10 egress only) */
			u32 seq_rollover: 1;
			/** \brief Reserved */
			u32 reserved2: 9;
			/** \brief Actual value of the output pin, read-only */
			u32 interrupt_pin: 1;
			/** \brief Enable the input_error interrupt */
			u32 input_error_en: 1;
			/** \brief Enable the output_error interrupt */
			u32 output_error_en: 1;
			/** \brief Enable the processing_error interrupt */
			u32 processing_error_en: 1;
			/** \brief Enable the context_error interrupt */
			u32 context_error_en: 1;
			/** \brief Enable the seq_threshold interrupt */
			u32 seq_threshold_en: 1;
			/** \brief Enable the seq_rollover interrupt */
			u32 seq_rollover_en: 1;
			/** \brief Reserved */
			u32 reserved3: 8;
			/** \brief Enable the fatal_error interrupt */
			u32 fatal_error_en: 1;
			/** \brief Set to 1b if the interrupt signal must appear on the
					   EIP-62 IRQ output */
			u32 interrupt_pin_en: 1;
#elif defined(__BIG_ENDIAN)
			/** \brief Set to 1b if the interrupt signal must appear on the
					   EIP-62 IRQ output */
			u32 interrupt_pin_en: 1;
			/** \brief Enable the fatal_error interrupt */
			u32 fatal_error_en: 1;
			/** \brief Reserved */
			u32 reserved3: 8;
			/** \brief Enable the seq_rollover interrupt */
			u32 seq_rollover_en: 1;
			/** \brief Enable the seq_threshold interrupt */
			u32 seq_threshold_en: 1;
			/** \brief Enable the context_error interrupt */
			u32 context_error_en: 1;
			/** \brief Enable the processing_error interrupt */
			u32 processing_error_en: 1;
			/** \brief Enable the output_error interrupt */
			u32 output_error_en: 1;
			/** \brief Enable the input_error interrupt */
			u32 input_error_en: 1;
			/** \brief Actual value of the output pin, read-only */
			u32 interrupt_pin: 1;
			/** \brief Reserved */
			u32 reserved2: 9;
			/** \brief If a sequence number roll-over (increment from maximum to
					   zero) due to an outbound sequence number increment this
					   interrupt is triggered (e10 egress only) */
			u32 seq_rollover: 1;
			/** \brief If a sequence number exceeds the programmed sequence
					   number threshold (refer to 0) due to an outbound sequence
					   number increment this interrupt is triggered (e8) */
			u32 seq_threshold: 1;
			/** \brief An invalid context has been fetched. Combination of
					   errors e5 and e6 */
			u32 context_error: 1;
			/** \brief An error occurred while processing the frame or parsing
					   the token. Combination of errors e0, e1, e3 and e4 */
			u32 processing_error: 1;
			/** \brief Reserved */
			u32 reserved: 1;
			/** \brief Input data does not properly receive all data (e2) */
			u32 input_error: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Context Status - raw */
		u32 raw_int_stat;
	};
};

/** \brief MACsec crypto-core control/status registers */
struct crypto_core_stat {
	/** \brief Interrupt Control/Status */
	struct eip62_int_stat int_stat;
#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
	/** \brief Context Control/Status */
	struct eip62_ctx_stat ctx_stat;
	/** Software Interrupt */
	u32 sw_interrupt;
#endif
};

/** \brief Sequence number threshold */
struct seq_num_thr {
	/** \brief Sequence number type.
	Valid values are defined in \ref seq_type enum */
	enum seq_type sn_type;
	/** SN threshold */
	u64 sn_threshold;
};
/**@}*/ /* GPY211_CRYPTO */

/** \addtogroup GPY211_MACSEC_AIC */
/**@{*/
/** \brief Interrupt bit assignments in Advanced Interrupt Controller (EIP201) */
struct aic_bit_assign {
	union {
		struct {
#if defined(__LITTLE_ENDIAN)
			/** \brief Packet drop pulse from classification logic */
			u32 drop_class: 1;
			/** \brief Packet drop pulse from post-processor logic */
			u32 drop_pp: 1;
			/** \brief Packet drop pulse from MTU checking logic */
			u32 drop_mtu: 1;
			/** \brief Interrupt pulse from EIP-62 MACsec crypto-engine core */
			u32 eng_irq: 1;
			/** \brief Interrupt pulse from statistics module (SA statistics) */
			u32 stat_sa_thr: 1;
			/** \brief Interrupt pulse from statistics module (global statistics) */
			u32 stat_global_thr: 1;
			/** \brief Interrupt pulse from statistics module (VLAN statistics) */
			u32 stat_vlan_thr: 1;
			/** \brief (-i)Packet drop pulse from consistency checking logic */
			u32 drop_cc: 1;
			/** \brief (-e)Pulse from post processor */
			u32 sa_pn_thr: 1;
			/** \brief (-e)Pulse from classifier */
			u32 sa_expired: 1;
			/** \brief Reserved */
			u32 reserved: 22;
#elif defined(__BIG_ENDIAN)
			/** \brief Reserved */
			u32 reserved: 22;
			/** \brief (-e)Pulse from classifier */
			u32 sa_expired: 1;
			/** \brief (-e)Pulse from post processor */
			u32 sa_pn_thr: 1;
			/** \brief (-i)Packet drop pulse from consistency checking logic */
			u32 drop_cc: 1;
			/** \brief Interrupt pulse from statistics module (VLAN statistics) */
			u32 stat_vlan_thr: 1;
			/** \brief Interrupt pulse from statistics module (global statistics) */
			u32 stat_global_thr: 1;
			/** \brief Interrupt pulse from statistics module (SA statistics) */
			u32 stat_sa_thr: 1;
			/** \brief Interrupt pulse from EIP-62 MACsec crypto-engine core */
			u32 eng_irq: 1;
			/** \brief Packet drop pulse from MTU checking logic */
			u32 drop_mtu: 1;
			/** \brief Packet drop pulse from post-processor logic */
			u32 drop_pp: 1;
			/** \brief Packet drop pulse from classification logic */
			u32 drop_class: 1;
#else
#error "__LITTLE_ENDIAN or __BIG_ENDIAN must be defined"
#endif
		};
		/** Interrupt bit assignments - raw */
		u32 raw_aic_bits;
	};
};

/** \brief AIC Control & Status */
struct aic_control_stat {
	/** AIC Input Polarity Control */
	struct aic_bit_assign pol_ctrl;
	/** AIC Input Type Control */
	struct aic_bit_assign type_ctrl;
	/** AIC Raw Interrupt Pending Status */
	struct aic_bit_assign raw_stat;
	/** AIC Masked Interrupt Pending Status */
	struct aic_bit_assign enabled_stat;

	/** AIC Interrupt Enable Control */
	struct aic_bit_assign enable_ctrl;

	/** AIC Interrupt Enable */
	struct aic_bit_assign enable_set;
	/** AIC Interrupt Acknowledge */
	struct aic_bit_assign ack;
	/** AIC Interrupt Disable */
	struct aic_bit_assign enable_clr;
};
/**@}*/ /* GPY211_AIC */


/**********************
	APIs
 **********************/

/** \addtogroup GPY211_MACSEC_SECINIT */
/**@{*/
/**
	\brief This API initializes the one time settings before configuring rules
		   for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_init_ing_dev(struct gpy211_device *phy);

/**
	\brief This API initializes the one time settings before configuring rules
		   for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_init_egr_dev(struct gpy211_device *phy);

/**
	\brief This API gets the MACSec hardware capabilities for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param hw_cap Pointer to HW cap (\ref eip160_hwcap).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_cap(struct gpy211_device *phy,
			    struct eip160_hwcap *hw_cap);

/**
	\brief This API gets the MACSec hardware capabilities for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param hw_cap Pointer to HW cap (\ref eip160_hwcap).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_cap(struct gpy211_device *phy,
			    struct eip160_hwcap *hw_cap);
/**@}*/ /* GPY211_SECINIT */

/** \addtogroup GPY211_MACSEC_SECTR */
/**@{*/
/**
	\brief This API configures the transform record, which contains parameters such as
		   Crypto Algorithm type, AN, Seq type, SA Key, SCI, Replay Window size,
		   Context Salt and Short SCI for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_tr Pointer to TR config (\ref transform_rec).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_tr(struct gpy211_device *phy,
			      struct transform_rec *in_tr);

/**
	\brief This API configures the transform record, which contains parameters such as
		   Crypto Algorithm type, AN, Seq type, SA Key, SCI, Seq num,
		   Context Salt, Short SCI, Next SA index, SA exp IRQ event, Flow index
		   and SA index update enable fields for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_tr Pointer to TR config (\ref transform_rec).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_tr(struct gpy211_device *phy,
			      struct transform_rec *in_tr);

/**
	\brief This API updates the context control word, which contains parameters such as
		   Crypto Algorithm type, Seq type, Next SA index, SA exp IRQ event,
		   Flow index and SA index update enable fields for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_tr Pointer to SA Update Control config (\ref sa_update_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_update_egr_sa_cw(struct gpy211_device *phy,
				 struct transform_rec *in_tr);

/**
	\brief This API gets the transform record, which contains parameters such as
		   Crypto Algorithm type, AN, Seq type, SA Key, SCI, Replay Window size,
		   Context Salt and Short SCI for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param out_tr Pointer to TR config (\ref raw_trans_rec).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_tr(struct gpy211_device *phy,
			   struct raw_trans_rec *out_tr);

/**
	\brief This API gets the transform record, which contains parameters such as
		   Crypto Algorithm type, AN, Seq type, SA Key, SCI, Seq num,
		   Context Salt, Short SCI, Next SA index, SA exp IRQ event, Flow index
		   and SA index update enable fields for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param out_tr Pointer to TR config (\ref raw_trans_rec).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_tr(struct gpy211_device *phy,
			   struct raw_trans_rec *out_tr);

/**
	\brief This API gets the current sequence number from the transform record for
	the Ingress device. This is used to check the PN exhaustion and extend the
	current flow's life.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param curr_pn Pointer to TR config (\ref sa_current_pn).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_pn(struct gpy211_device *phy,
			   struct sa_current_pn *curr_pn);

/**
	\brief This API gets current the sequence number from the transform record for
	the Egress device. This is used to check the PN exhaustion and extend the
	current flow's life.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param curr_pn Pointer to TR config (\ref sa_current_pn).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_pn(struct gpy211_device *phy,
			   struct sa_current_pn *curr_pn);

/**
	\brief This API clears the transform record, which contains parameters such as
		   Crypto Algorithm type, AN, Seq type, SA Key, SCI, Replay Window size,
		   Context Salt and Short SCI for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_tr Pointer to TR config (\ref transform_rec).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_ing_tr(struct gpy211_device *phy,
			     const struct transform_rec *in_tr);

/**
	\brief This API clears the transform record, which contains parameters such as
		   Crypto Algorithm type, AN, Seq type, SA Key, SCI, Replay Window size,
		   Context Salt and Short SCI for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_tr Pointer to TR config (\ref transform_rec).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_egr_tr(struct gpy211_device *phy,
			     const struct transform_rec *in_tr);

/**@}*/ /* GPY211_SECTR */

/** \addtogroup GPY211_MACSEC_SECSAM */
/**@{*/
/**
	\brief This API configures the SA matching rule, which contains parameters such as
		   Src MAC, Dst MAC, Ether type, Misc Match (\ref sam_misc_param),
		   SCI, Match Mask (\ref sam_mask_param) and Flow Index for the Ingress
		   device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_sam Pointer to SA matching rule config (\ref sa_match_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_sam_rule(struct gpy211_device *phy,
				    const struct sa_match_param *in_sam);

/**
	\brief This API configures the SA matching rule, which contains parameters such as
		   Src MAC, Dst MAC, Ether type, Misc Match (\ref sam_misc_param),
		   SCI, Match Mask (\ref sam_mask_param) and Flow Index for the Egress
		   device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_sam Pointer to SA matching rule config (\ref sa_match_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_sam_rule(struct gpy211_device *phy,
				    const struct sa_match_param *in_sam);

/**
	\brief This API gets the SA matching rule, which contains parameters such as
		   Src MAC, Dst MAC, Ether type, Misc Match (\ref sam_misc_param),
		   SCI, Match Mask (\ref sam_mask_param) and Flow Index for the Ingress
		   device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param out_sam Pointer to SA matching rule config (\ref sa_match_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_sam_rule(struct gpy211_device *phy,
				 struct raw_sam_param *out_sam);

/**
	\brief This API gets the SA matching rule, which contains parameters such as
		   Src MAC, Dst MAC, Ether type, Misc Match (\ref sam_misc_param),
		   SCI, Match Mask (\ref sam_mask_param) and Flow Index for the Egress
		   device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param out_sam Pointer to SA matching rule config (\ref sa_match_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_sam_rule(struct gpy211_device *phy,
				 struct raw_sam_param *out_sam);

/**
	\brief This API clears the SA matching rule, which contains parameters such as
		   Src MAC, Dst MAC, Ether type, Misc Match (\ref sam_misc_param),
		   SCI, Match Mask (\ref sam_mask_param) and Flow Index for the Ingress
		   device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_sam Pointer to SA matching rule config (\ref sa_match_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_ing_sam_rule(struct gpy211_device *phy,
				   const struct sa_match_param *in_sam);

/**
	\brief This API clears the SA matching rule, which contains parameters such as
		   Src MAC, Dst MAC, Ether type, Misc Match (\ref sam_misc_param),
		   SCI, Match Mask (\ref sam_mask_param) and Flow Index for the Egress
		   device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_sam Pointer to SA matching rule config (\ref sa_match_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_egr_sam_rule(struct gpy211_device *phy,
				   const struct sa_match_param *in_sam);

/**
	\brief This API configures VLAN parsing logic for the Ingress device.

	It delivers a number of “parsed” parameters to the main SA matching logic to determine which SA to use.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param parse_vlan Pointer to VLAN config (\ref sam_vlan_parse).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_vlan_parse(struct gpy211_device *phy,
				      const struct sam_vlan_parse *parse_vlan);

/**
	\brief This API configures VLAN parsing logic for the Egress device.

	It delivers a number of “parsed” parameters to the main SA matching logic to determine which SA to use.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param parse_vlan Pointer to VLAN config (\ref sam_vlan_parse).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_vlan_parse(struct gpy211_device *phy,
				      const struct sam_vlan_parse *parse_vlan);

/**@}*/ /* GPY211_SECSAM */

/** \addtogroup GPY211_MACSEC_SECFCA */
/**@{*/
/**
	\brief This API configures the SA matching flow control action, which contains
		   parameters such as flow type (\ref sam_fca_ft), destination port type
		   (\ref sam_fca_dpt), drop non-reserved, cryptographic authentication,
		   drop type (\ref sam_fca_dat), SA index, replay protection, validation
		   level, confidentiality offset, IV load type (\ref sam_fca_iv),
		   bit 7 of the AAD length, append ICV, and verify ICV for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sam_fca Pointer to SA matching flow control action (\ref sa_match_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_sam_fca(struct gpy211_device *phy,
				   const struct sa_match_fca *sam_fca);

/**
	\brief This API configures the SA matching flow control action, which contains
		   parameters such as flow type (\ref sam_fca_ft), destination port type
		   (\ref sam_fca_dpt), cryptographic authentication, drop type
		   (\ref sam_fca_dat), SA index, frame protection, include SCI,
		   confidentiality offset, IV load type (\ref sam_fca_iv),
		   bit 7 of the AAD length, append ICV, verify ICV, end station
		   & single copy broadcast flags, tag bypass size, SA index update flag, and
		   confidentiality protection flag for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sam_fca Pointer to SA Matching Flow Control action (\ref sa_match_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_sam_fca(struct gpy211_device *phy,
				   const struct sa_match_fca *sam_fca);

/**
	\brief This API gets the SA matching flow control action, which contains
		   parameters such as flow type (\ref sam_fca_ft), destination port type
		   (\ref sam_fca_dpt), drop non-reserved, cryptographic authentication,
		   drop type (\ref sam_fca_dat), SA index, replay protection, validation
		   level, confidentiality offset, IV load type (\ref sam_fca_iv),
		   bit 7 of the AAD length, append ICV, and verify ICV for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sam_fca Pointer to SA matching flow control action (\ref sam_pkt_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_sam_fca(struct gpy211_device *phy,
				struct sam_pkt_fca *sam_fca);

/**
	\brief This API gets the SA matching flow control action, which contains
		   parameters such as flow type (\ref sam_fca_ft), destination port type
		   (\ref sam_fca_dpt), cryptographic authentication, drop type
		   (\ref sam_fca_dat), SA index, frame protection, include SCI,
		   confidentiality offset, IV load type (\ref sam_fca_iv),
		   bit 7 of the AAD length, append ICV, verify ICV, end station
		   & single copy broadcast flags, tag bypass size, SA index update flag, and
		   confidentiality protection flag for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sam_fca Pointer to SA matching flow control action (\ref sam_pkt_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_sam_fca(struct gpy211_device *phy,
				struct sam_pkt_fca *sam_fca);

/**
	\brief This API clears the SA matching flow control action, which contains
		   parameters such as flow type (\ref sam_fca_ft), destination port type
		   (\ref sam_fca_dpt), drop non-reserved, cryptographic authentication,
		   drop type (\ref sam_fca_dat), SA index, replay protection, validation
		   level, confidentiality offset, IV load type (\ref sam_fca_iv),
		   bit 7 of the AAD length, append ICV, and verify ICV for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sam_fca Pointer to SA matching flow control action (\ref sa_match_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_ing_sam_fca(struct gpy211_device *phy,
				  const struct sa_match_fca *sam_fca);

/**
	\brief This API clears the SA matching flow control action, which contains
		   parameters such as flow type (\ref sam_fca_ft), destination port type
		   (\ref sam_fca_dpt), cryptographic authentication, drop type
		   (\ref sam_fca_dat), SA index, frame protection, include SCI,
		   confidentiality offset, IV load type (\ref sam_fca_iv),
		   bit 7 of the AAD length, append ICV, verify ICV, end station
		   & single copy broadcast flags, tag bypass size, SA index update flag, and
		   confidentiality protection flag for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sam_fca Pointer to SA matching flow control action (\ref sa_match_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_egr_sam_fca(struct gpy211_device *phy,
				  const struct sa_match_fca *sam_fca);
/**@}*/ /* GPY211_SECFCA */

/** \addtogroup GPY211_MACSEC_SECEEX */
/**@{*/
/**
	\brief This API configures the SAM entry enable feature for the Ingress device.
		   This provides control over the enabling and disabling of SA matching
		   entries (rules). The following functionality is available to reduce
		   or fully eliminate the need for read/modify/write cycles:

	a) Setting and clearing the enable bits with a single write action.
	b) Clearing all or setting all enable bits with a single write action.
	c) Setting one and clearing another enable bit with a single write action.
	d) Toggling of enable bits (multiple write actions might be needed).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_ee Pointer to SAM EE flags (\ref raw_sam_ee).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_sam_eex(struct gpy211_device *phy,
				   const struct raw_sam_ee *in_ee);

/**
	\brief This API configures the SAM entry enable feature for the Egress device.
		   This provides control over the enabling and disabling of SA matching
		   entries (rules). The following functionality is available to reduce
		   or fully eliminate the need for read/modify/write cycles:

	a) Setting and clearing the enable bits with a single write action.
	b) Clearing all or setting all enable bits with a single write action.
	c) Setting one and clearing another enable bit with a single write action.
	d) Toggling of enable bits (multiple write actions might be needed).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_ee Pointer to SAM EE flags (\ref raw_sam_ee).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_sam_eex(struct gpy211_device *phy,
				   const struct raw_sam_ee *in_ee);

/**
	\brief This API gets the SAM entry enable feature settings for the Ingress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param out_ee Pointer to SAM EE flags (\ref raw_sam_ee).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_sam_eef(struct gpy211_device *phy,
				struct raw_sam_ee *out_ee);

/**
	\brief This API gets the SAM entry enable feature settings for the Egress device.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param out_ee Pointer to SAM EE flags (\ref raw_sam_ee).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_sam_eef(struct gpy211_device *phy,
				struct raw_sam_ee *out_ee);
/**@}*/ /* GPY211_SECEEX */

/** \addtogroup GPY211_MACSEC_SECEEC */
/**@{*/
/**
	\brief This API configures the SAM entry enable control for the Ingress device.
		   This offers combined functionality to be performed with a single write action:

	a) Enabling or disabling an entry.
	b) Enabling one and disabling another entry at the same time.
	c) Enabling or disabling all entries.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param ee_ctrl Pointer to SAM EE Control (\ref sam_ee_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_sam_eec(struct gpy211_device *phy,
				   const struct sam_ee_ctrl *ee_ctrl);

/**
	\brief This API configures the SAM entry enable control for the Egress device.
		   This offers combined functionality to be performed with a single write action:

	a) Enabling or disabling an entry.
	b) Enabling one and disabling another entry at the same time.
	c) Enabling or disabling all entries.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param ee_ctrl Pointer to SAM EE Control (\ref sam_ee_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_sam_eec(struct gpy211_device *phy,
				   const struct sam_ee_ctrl *ee_ctrl);
/**@}*/ /* GPY211_SECEEC */

/** \addtogroup GPY211_MACSEC_SECICC */
/**@{*/
/**
	\brief This API configures the consistency check matching rule for the Ingress device.
		   In the Ingress data path, packets are partially re-inspected after
		   leaving the MACsec engine core for a consistency check.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_cc Pointer to consistency check rule param (\ref icc_match_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_cc_rule(struct gpy211_device *phy,
				   const struct icc_match_param *in_cc);

/**
	\brief This API gets the consistency check matching rule for the Ingress device.
		   In the Ingress data path, packets are partially re-inspected after
		   leaving the MACsec engine core for a consistency check.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_cc Pointer to consistency check rule param (\ref icc_match_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_cc_rule(struct gpy211_device *phy,
				struct icc_match_param *in_cc);

/**
	\brief This API configures the consistency check entry enable flags for the Ingress
		   device. In the Ingress data path, packets are partially re-inspected
		   after leaving the MACsec engine core for a consistency check.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_cc Pointer to consistency check rule param (\ref raw_icc_ee).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_cc_eef(struct gpy211_device *phy,
				  const struct raw_icc_ee *in_cc);

/**
	\brief This API gets the consistency check entry enable flags for the Ingress
		   device. In the Ingress data path, packets are partially re-inspected
		   after leaving the MACsec engine core for a consistency check.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_cc Pointer to consistency check rule param (\ref raw_icc_ee).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_cc_eef(struct gpy211_device *phy,
			       struct raw_icc_ee *in_cc);

/**
	\brief This API configures the consistency check control for the Ingress device.
		   This offers functionality to configure what action (drop/pass) is to be taken
		   when non-matching control & non-control frames are received.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_ccc Pointer to consistency check control (\ref ing_cc_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_cc_ctrl(struct gpy211_device *phy,
				   const struct ing_cc_ctrl *in_ccc);

/**
	\brief This API configures the consistency check entry enable control for
		   the Ingress device. In the Ingress data path, packets are partially
		   re-inspected after leaving the MACsec engine core for a consistency
		   check.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param ee_ctrl Pointer to consistency check rule param (\ref icc_ee_ctrl).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_cc_eec(struct gpy211_device *phy,
				  const struct icc_ee_ctrl *ee_ctrl);
/**@}*/ /* GPY211_SECICC */

/** \addtogroup GPY211_MACSEC_SECSTATS */
/**@{*/
/**
	\brief This API gets the Per-SA statistics for the Ingress device.
		   The statistics counters are maintained in RAM to reduce the size
		   of the engine.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sa_stats Pointer to Per-SA counters (\ref ing_sa_stats).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_sa_stats(struct gpy211_device *phy,
				 struct ing_sa_stats *sa_stats);

/**
	\brief This API gets the Per-SA statistics for the Egress device.
		   The statistics counters are maintained in RAM to reduce the size
		   of the engine.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sa_stats Pointer to Per-SA counters (\ref egr_sa_stats).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_sa_stats(struct gpy211_device *phy,
				 struct egr_sa_stats *sa_stats);

/**
	\brief This API gets the global statistics for the Ingress device.
		   The statistics counters are maintained in RAM to reduce the size
		   of the engine.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param glob_stats Pointer to global counters (\ref ing_global_stats).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_global_stats(struct gpy211_device *phy,
				     struct ing_global_stats *glob_stats);

/**
	\brief This API gets the global statistics for the Egress device.
		   The statistics counters are maintained in RAM to reduce the size
		   of the engine.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param glob_stats Pointer to global counters (\ref egr_global_stats).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_global_stats(struct gpy211_device *phy,
				     struct egr_global_stats *glob_stats);

#if defined(SUPPORT_MACSEC_VLAN) && SUPPORT_MACSEC_VLAN
/** @cond INTERNAL */
/**
	\brief This API gets the per-VLAN user priority statistics for the Ingress device.
		   The statistics counters are maintained in RAM to reduce the size
		   of the engine.

		   This API is not applicable for GPY2xx.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param vlan_stats Pointer to per-VLAN UP counters (\ref ing_vlan_stats).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_vlan_stats(struct gpy211_device *phy,
				   struct ing_vlan_stats *vlan_stats);

/**
	\brief This API gets the per-VLAN User Priority statistics for the Egress device.
		   The statistics counters are maintained in RAM to reduce the size
		   of the engine.

		   This API is not applicable for GPY2xx.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param vlan_stats Pointer to per-VLAN UP counters (\ref egr_vlan_stats).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_vlan_stats(struct gpy211_device *phy,
				   struct egr_vlan_stats *vlan_stats);
/** @endcond */
#endif

#if defined(EN_MSEC_DEBUG_ACCESS) && EN_MSEC_DEBUG_ACCESS
/**
	\brief This API gets the debug statistics for the Ingress device.
		   The statistics counters are maintained in RAM to reduce the size
		   of the engine.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param dbg_stats Pointer to debug counters (\ref stats_debug_regs).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_debug_stats(struct gpy211_device *phy,
				    struct stats_debug_regs *dbg_stats);

/**
	\brief This API gets the debug statistics for the Egress device.
		   The statistics counters are maintained in RAM to reduce the size
		   of the engine.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param dbg_stats Pointer to Debug Counters (\ref stats_debug_regs).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_debug_stats(struct gpy211_device *phy,
				    struct stats_debug_regs *dbg_stats);
#endif

/**@}*/ /* GPY211_SECSTATS */

/** \addtogroup GPY211_MACSEC_SECCCTRL */
/**@{*/
/**
	\brief This API controls the behavior of the counters for the Ingress device.
		   The counters can be made to saturate, and/or to clear on read:
	a) Saturating means that the counter remains at its maximum value of
	   0xFFFF_FFFF_FFFF_FFFF when it overflows and does not wrap around to zero.
	b) Clear on read means that the counter is cleared to zero when its data is
	   read. Reading and clearing is an atomic operation performed by hardware;
	   no counted events are lost between obtaining the value and clearing the
	   counter.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_ctrl Pointer to counter control (\ref count_control).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_count_ctrl(struct gpy211_device *phy,
				      const struct count_control *cnt_ctrl);

/**
	\brief This API controls the behavior of the counters for the Egress device.
		   The counters can be made to saturate, and/or to clear on read:
	a) Saturating means that the counter remains at its maximum value of
	   0xFFFF_FFFF_FFFF_FFFF when it overflows and does not wrap around to zero.
	b) Clear on read means that the counter is cleared to zero when its data is
	   read. Reading and clearing is an atomic operation performed by hardware;
	   no counted events are lost between obtaining the value and clearing the
	   counter.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_ctrl Pointer to counter control (\ref count_control).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_count_ctrl(struct gpy211_device *phy,
				      const struct count_control *cnt_ctrl);

/**
	\brief This API controls the counter increment enable for the Ingress device.
		   This provides control over which counters are allowed to be
		   incremented. It is recommended to disable counters that are not
		   strictly necessary for MACsec compliance. After reset, all counters
		   are enabled.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_incen Pointer to counter increment enable (\ref count_incen).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_count_incen(struct gpy211_device *phy,
				       const struct count_incen *cnt_incen);

/**
	\brief This API controls the counter increment enable for the Egress device.
		   This provides control over which counters are allowed to be
		   incremented. It is recommended to disable counters that are not
		   strictly necessary for MACsec compliance. After reset, all counters
		   are enabled.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_incen Pointer to counter increment enable (\ref count_incen).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_count_incen(struct gpy211_device *phy,
				       const struct count_incen *cnt_incen);

/**
	\brief This API controls the programmable thresholds for the Ingress device.

	The frame threshold is used for the frame counters. The octet threshold is used for the octet counters.

	Note: Setting the threshold registers to zero will only cause summary
	events (Global statistics summary, Per-SA statistics summary and All SA counters statistics summary)
	in the case of counter overflow (rollover from maximum value to zero).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_thr Pointer to counter thresholds (\ref frame_octet_thr).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_count_thresh(struct gpy211_device *phy,
					const struct frame_octet_thr *cnt_thr);

/**
	\brief This API gets the programmable thresholds for the Ingress device.

	The frame threshold is used for the frame counters. The octet threshold is used for the octet counters.

	Note: Setting the threshold registers to zero will only cause summary
	events in the case of counter overflow (roll-over from maximum value to zero).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_thr Pointer to counter thresholds (\ref frame_octet_thr).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_count_thresh(struct gpy211_device *phy,
				     struct frame_octet_thr *cnt_thr);

/**
	\brief This API controls the programmable thresholds for the Egress device.

	The frame threshold is used for the frame counters. The octet threshold is used for the octet counters.

	Note: Setting the threshold registers to zero will only cause summary
	events in the case of counter overflow (roll-over from maximum value to zero).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_thr Pointer to counter thresholds (\ref frame_octet_thr).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_count_thresh(struct gpy211_device *phy,
					const struct frame_octet_thr *cnt_thr);

/**
	\brief This API gets the programmable thresholds for the Egress device.

	The frame threshold is used for the frame counters. The octet threshold is used for the octet counters.

	Note: Setting the threshold registers to zero will only cause summary
	events in the case of counter overflow (roll-over from maximum value to zero).

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_thr Pointer to counter thresholds (\ref frame_octet_thr).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_count_thresh(struct gpy211_device *phy,
				     struct frame_octet_thr *cnt_thr);

/**
	\brief This API configures the security fail and error mask for the Ingress device.

	A packet for which a security failure is declared (using the secfail_mask
	fields in these registers) is tagged to be transmitted with a CRC error.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_secfail Pointer to SEC fail events (\ref count_secfail).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_count_secfail(struct gpy211_device *phy,
		const struct count_secfail *cnt_secfail);

/**
	\brief This API configures the security fail and error mask for the Egress device.

	A packet for which a security failure is declared (using the secfail_mask
	fields in these registers) is tagged to be transmitted with a CRC error.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cnt_secfail Pointer to SEC fail events (\ref count_secfail).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_count_secfail(struct gpy211_device *phy,
		const struct count_secfail *cnt_secfail);

/**@}*/ /* GPY211_SECCCTRL */

/** \addtogroup GPY211_MACSEC_SECMCTRL */
/**@{*/
/**
	\brief This API controls the following for the Ingress device:

	a) Enabling static bypass mode.
	b) Controlling the latency equalization function.
	c) Allowing MACsec-compliant handling of MACsec packets for which no MACsec
	   SA is available.
	d) Controlling the maximum size of the transform record.
	e) Global frame validation level.
	f) Enabling detection of the MACsec SecTAG after VLAN tags.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param misc_ctrl Pointer to misc control (\ref misc_control).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_misc_ctrl(struct gpy211_device *phy,
				     const struct misc_control *misc_ctrl);

/**
	\brief This API controls the following for the Ingress device:

	a) Enabling static bypass mode.
	b) Controlling the latency equalization function.
	c) Allowing MACsec-compliant handling of MACsec packets for which no MACsec
	   SA is available.
	d) Controlling the maximum size of the transform record.
	e) Global frame validation level.
	f) Enabling detection of the MACsec SecTAG after VLAN tags.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param misc_ctrl Pointer to misc control (\ref misc_control).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_misc_ctrl(struct gpy211_device *phy,
				     const struct misc_control *misc_ctrl);
/**@}*/ /* GPY211_SECMCTRL */

/** \addtogroup GPY211_MACSEC_SECNMCTRL */
/**@{*/
/**
	\brief This API sets the no-match classifier control action.
		   The parameters in the API are used to perform a MACsec tag classification
		   algorithm, which is executed before the SA matching rule look-up and
		   the corresponding flow is determined. This algorithm parses the
		   Ether-type and MACsec SecTAG and produces a result that is used by
		   SA matching flows and to select the SA non-matching flow.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param nm_ctrl Pointer to SA No-Match control (\ref sa_nm_params).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_sa_nm_ctrl(struct gpy211_device *phy,
				      const struct sa_nm_params *nm_ctrl);

/**
	\brief This API sets the no-match classifier control action.
		   The parameters in the API are used to perform a MACsec tag classification
		   algorithm, which is executed before the SA matching rule look-up and
		   the corresponding flow is determined. This algorithm parses the
		   Ether-type and MACsec SecTAG and produces a result that is used by
		   SA matching flows and to select the SA non-matching flow.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param nm_ctrl Pointer to SA No-Match control (\ref sa_nm_params).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_sa_nm_ctrl(struct gpy211_device *phy,
				      const struct sa_nm_params *nm_ctrl);
/**@}*/ /* GPY211_SECNMCTRL */

/** \addtogroup GPY211_MACSEC_SECNMFCA */
/**@{*/
/**
	\brief This API controls how packets that do not match any of the SA
		   matching rules are handled if the received packet is not a control frame.
		   If the input classification of the EIP-160 is used, the non-matching
		   flows are subdivided into eight packet type categories, split by
		   whether or not the packet was classified as a control packet and the
		   output of a separate MACsec tag classification function.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param nm_ncp Pointer to SA No-Match flow ctrl action (\ref sa_nonmatch_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_sa_nm_ncp(struct gpy211_device *phy,
				     const struct sa_nonmatch_fca *nm_ncp);

/**
	\brief This API controls how packets that do not match any of the SA
		   matching rules are handled if the transmitted packet is not a control frame.
		   If the input classification of the EIP-160 is used, the non-matching
		   flows are subdivided into eight packet type categories, split by
		   whether or not the packet was classified as a control packet and the
		   output of a separate MACsec tag classification function.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param nm_ncp Pointer to SA No-Match flow ctrl action (\ref sa_nonmatch_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_sa_nm_ncp(struct gpy211_device *phy,
				     const struct sa_nonmatch_fca *nm_ncp);

/**
	\brief This API controls how packets that do not match any of the SA
		   matching rules are handled if the received packet is a control frame.
		   If the input classification of the EIP-160 is used, the non-matching
		   flows are subdivided into eight packet type categories, split by
		   whether or not the packet was classified as a control packet and the
		   output of a separate MACsec tag classification function.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param nm_cp Pointer to SA No-Match flow ctrl action (\ref sa_nonmatch_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_sa_nm_cp(struct gpy211_device *phy,
				    const struct sa_nonmatch_fca *nm_cp);

/**
	\brief This API controls how packets that do not match any of the SA
		   matching rules are handled if the transmitted packet is a control frame.
		   If the input classification of the EIP-160 is used, the non-matching
		   flows are subdivided into eight packet type categories, split by
		   whether or not the packet was classified as a control packet and the
		   output of a separate MACsec tag classification function.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param nm_cp Pointer to SA No-Match flow ctrl action (\ref sa_nonmatch_fca).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_sa_nm_cp(struct gpy211_device *phy,
				    const struct sa_nonmatch_fca *nm_cp);

/**@}*/ /* GPY211_SECNMFCA */

/** \addtogroup GPY211_MACSEC_SECSASUMM */
/**@{*/
/**
	\brief This API clears the per-SA statistics summary, global statistics
		   summary and per-VLAN-UP statistics summary for the Ingress device.

	The counter summary registers hold a summary of which statistics
	counters have crossed the programmable threshold. The frame threshold is used for the frame counters.
	The octet threshold is used for the octet counters. The following summary flags are available:

	a) One for each global statistics counter.
	b) One for each VLAN statistics counter.
	c) One for each SA statistics block when one of the counters in the SA
	   statistics crossed the corresponding (frame or octet) programmable
	   threshold.
	d) One for each counter of each SA.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param xxx_sum Pointer to statistics summary (\ref stats_summary).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_ing_stats_summ(struct gpy211_device *phy,
				     const struct stats_summary *xxx_sum);

/**
	\brief This API clears the per-SA statistics summary, global statistics
		   summary and per-VLAN-UP statistics summary for the Egress device.

	The counter summary registers hold a summary of which statistics
	counters have crossed the programmable threshold. The frame threshold is used for the frame counters.
	The octet threshold is used for the octet counters. The following summary flags are available:

	a) One for each global statistics counter.
	b) One for each VLAN statistics counter.
	c) One for each SA statistics block when one of the counters in the SA
	   statistics crossed the corresponding (frame or octet) programmable
	   threshold.
	d) One for each counter of each SA.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param xxx_sum Pointer to statistics summary (\ref stats_summary).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_egr_stats_summ(struct gpy211_device *phy,
				     const struct stats_summary *xxx_sum);

/**
	\brief This API gets the per-SA statistics summary, global statistics
		   summary and per-VLAN-UP statistics summary for the Ingress device.

	The counter summary registers hold a summary of which statistics
	counters have crossed the programmable threshold. The frame threshold is used for the frame counters.
	The octet threshold is used for the octet counters. The following summary flags are available:

	a) One for each global statistics counter.
	b) One for each VLAN statistics counter.
	c) One for each SA statistics block when one of the counters in the SA
	   statistics crossed the corresponding (frame or octet) programmable
	   threshold.
	d) One for each counter of each SA.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param xxx_sum Pointer to statistics summary (\ref stats_summary).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_stats_summ(struct gpy211_device *phy,
				   struct stats_summary *xxx_sum);

/**
	\brief This API gets the per-SA statistics summary, global statistics
		   summary and per-VLAN-UP statistics summary for the Egress device.

	The counter summary registers hold a summary of which statistics
	counters have crossed the programmable threshold. The frame threshold is used for the frame counters.
	The octet threshold is used for the octet counters. The following summary flags are available:

	a) One for each global statistics counter.
	b) One for each VLAN statistics counter.
	c) One for each SA statistics block when one of the counters in the SA
	   statistics crossed the corresponding (frame or octet) programmable
	   threshold.
	d) One for each counter of each SA.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param xxx_sum Pointer to Statistics summary (\ref stats_summary).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_stats_summ(struct gpy211_device *phy,
				   struct stats_summary *xxx_sum);

/**
	\brief This API clears the statistics summary flags for each counter of each SA
	for the Ingress device.

	This summary register is a vector with one flag per SA to indicate that any
	counter within the corresponding SA statistics group crossed the programmed
	threshold (there can be multiple at the same time).

	The event of setting a flag in the SA summary register is used to set the
	flag for the corresponding SA in the per-SA summary register and
	consequently to generate the interrupt event.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param psa_sum Pointer to all SA statistics summary (\ref psa_summary).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_ing_psa_stats_summ(struct gpy211_device *phy,
		const struct psa_summary *psa_sum);

/**
	\brief This API gets the statistics summary flags for each counter of each SA
	for the Ingress device.

	This summary register is a vector with one flag per SA to indicate that any
	counter within the corresponding SA statistics group crossed the programmed
	threshold (there can be multiple at the same time).

	The event of setting a flag in the SA summary register is used to set the
	flag for the corresponding SA in the per-SA summary register and
	consequently to generate the interrupt event.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param psa_sum Pointer to all SA statistics summary (\ref psa_summary).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_psa_stats_summ(struct gpy211_device *phy,
				       struct psa_summary *psa_sum);

/**
	\brief This API clears the statistics summary flags for each counter of each SA
	for the Egress device.

	This summary register is a vector with one flag per SA to indicate that any
	counter within the corresponding SA statistics group crossed the programmed
	threshold (there can be multiple at the same time).

	The event of setting a flag in the SA summary register is used to set the
	flag for the corresponding SA in the per-SA summary register and
	consequently to generate the interrupt event.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param psa_sum Pointer to all SA statistics summary (\ref psa_summary).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_egr_psa_stats_summ(struct gpy211_device *phy,
		const struct psa_summary *psa_sum);

/**
	\brief This API gets the statistics summary flags for each counter of each SA
	for the Egress device.

	This summary register is a vector with one flag per SA to indicate that any
	counter within the corresponding SA statistics group crossed the programmed
	threshold (there can be multiple at the same time).

	The event of setting a flag in the SA summary register is used to set the
	flag for the corresponding SA in the per-SA summary register and
	consequently to generate the interrupt event.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param psa_sum Pointer to all SA statistics summary (\ref psa_summary).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_psa_stats_summ(struct gpy211_device *phy,
				       struct psa_summary *psa_sum);

/**@}*/ /* GPY211_SECSASUMM */

/** \addtogroup GPY211_MACSEC_SECCPC */
/**@{*/
/**
	\brief This API configures the the control packet classification rules for
		   the Ingress device.

	One of the first parallel operations of the packet classification is to
	determine whether or not this is a control packet. The MAC_DA and
	Ether-type fields of the packet are compared to several values (individually
	and in combination). If one of these comparisons returns a match, the packet
	is tagged as a control packet. Each of the comparisons can be enabled
	individually.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_cpc Pointer to CPC rule (\ref cp_class_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_cp_rule(struct gpy211_device *phy,
				   const struct cp_class_param *in_cpc);

/**
	\brief This API configures the control packet classification rules for
		   the Egress device.

	One of the first parallel operations of the packet classification is to
	determine whether or not this is a control packet. The MAC_DA and
	Ether-type fields of the packet are compared to several values (individually
	and in combination). If one of these comparisons returns a match, the packet
	is tagged as a control packet. Each of the comparisons can be enabled
	individually.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param in_cpc Pointer to CPC rule (\ref cp_class_param).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_cp_rule(struct gpy211_device *phy,
				   const struct cp_class_param *in_cpc);
/**@}*/ /* GPY211_SECCPC */

/** \addtogroup GPY211_MACSEC_OP_PROC */
/**@{*/
/**
	\brief This API clears the SA packet number threshold summary for the Egress
		   device.

	The packet number threshold summary register indicates any MACsec egress SA for which the packet number will expire imminently
	such that the host must initiate retrieval of a new (next) key.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param pnthr_sum Pointer to threshold summary (\ref sa_pn_thr_summ).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_sa_pn_thr_summ(struct gpy211_device *phy,
				     const struct sa_pn_thr_summ *pnthr_sum);

/**
	\brief This API gets the SA packet number threshold summary for the Egress device.

	The packet number threshold summary register indicates any MACsec egress SA for which the packet number will expire imminently
	such that the host must initiate retrieval of a new (next) key.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param pnthr_sum Pointer to threshold summary (\ref sa_pn_thr_summ).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_sa_pn_thr_summ(struct gpy211_device *phy,
				   struct sa_pn_thr_summ *pnthr_sum);

/**
	\brief This API clears the the SA expired summary for the Egress device.

	The SA expired summary register indicates which MACsec Egress
	SA has expired due to the packet number reaching the maximum allowed value and no
	valid next SA being installed.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param saexp_sum Pointer to SA expired summary (\ref sa_exp_summ).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_egr_sa_exp_summ(struct gpy211_device *phy,
				      const struct sa_exp_summ *saexp_sum);

/**
	\brief This API gets the SA expired summary for the Egress device.

	The SA expired summary register indicates which MACsec Egress
	SA expired due to the packet number reaching the maximum allowed value and no
	valid next SA being installed.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param saexp_sum Pointer to SA expired summary (\ref sa_exp_summ).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_sa_exp_summ(struct gpy211_device *phy,
				    struct sa_exp_summ *saexp_sum);

/**@}*/ /* GPY211_OP_PROC */

/** \addtogroup GPY211_MACSEC_CRYPTO */
/**@{*/
/**
	\brief This API clears the interrupt status for the Ingress device.

	This API clears the context, HW & SW interrupt status, of the currently active
	frame.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cc_stat Pointer to CC interrupts (\ref crypto_core_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_ing_cc_int_stat(struct gpy211_device *phy,
				      const struct crypto_core_stat *cc_stat);

/**
	\brief This API gets the interrupt status for the Ingress device.

	This API gets the context, HW & SW interrupt status, of the currently active
	frame.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cc_stat Pointer to CC interrupts (\ref crypto_core_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_cc_int_stat(struct gpy211_device *phy,
				    struct crypto_core_stat *cc_stat);

/**
	\brief This API clears the interrupt status for the Egress device.

	This API clears the context, HW & SW interrupt status, of the currently active
	frame.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cc_stat Pointer to CC interrupts (\ref crypto_core_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_clear_egr_cc_int_stat(struct gpy211_device *phy,
				      const struct crypto_core_stat *cc_stat);

/**
	\brief This API gets the interrupt status for the Egress device.

	This API gets the context, HW & SW interrupt status, of the currently active
	frame.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param cc_stat Pointer to CC interrupts (\ref crypto_core_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_cc_int_stat(struct gpy211_device *phy,
				    struct crypto_core_stat *cc_stat);

/**
	\brief This API configures the sequence number threshold for the Ingress device.

	The EIP-62 provides the possibility of setting a separate threshold for cipher
	suites with 32-bit and 64-bit packet numbering.

	These registers can be configured to trigger an informative error e8
	indicating that the inbound sequence number equals the programmed value in this
	register, which can trigger an interrupt. With this interrupt, the system
	has time to start a re-key before the rollover error fires. If the next
	(incremented) sequence number is equal to or greater than this value
	(selectable in EIP62_CONTEXT_CTRL register, see section 3.3.19.1),
	the sequence number threshold overflow bit e8 in the result token is set.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sn_thr Pointer to SN threshold (\ref seq_num_thr).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_sn_thresh(struct gpy211_device *phy,
				     const struct seq_num_thr *sn_thr);

/**
	\brief This API gets the sequence number threshold for the Ingress device.

	The EIP-62 provides the possibility of setting a separate threshold for cipher
	suites with 32-bit and 64-bit packet numbering.

	These registers can be configured to trigger an informative error e8
	indicating that the outbound sequence number equals the programmed value in this
	register, which can trigger an interrupt. With this interrupt, the system
	has time to start a re-key before the rollover error fires. If the next
	(incremented) sequence number is equal to or greater than this value
	(selectable in EIP62_CONTEXT_CTRL register, see section 3.3.19.1),
	the sequence number threshold overflow bit e8 in the result token is set.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sn_thr Pointer to SN threshold (\ref seq_num_thr).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_sn_thresh(struct gpy211_device *phy,
				  struct seq_num_thr *sn_thr);

/**
	\brief This API configures the sequence number threshold for the Egress device.

	The EIP-62 provides the possibility of setting a separate threshold for cipher
	suites with 32-bit and 64-bit packet numbering.

	These registers can be configured to trigger an informative error e8
	indicating that the outbound sequence number equals the programmed value in this
	register, which can trigger an interrupt. With this interrupt, the system
	has time to start a re-key before the rollover error fires. If the next
	(incremented) sequence number is equal to or greater than this value
	(selectable in EIP62_CONTEXT_CTRL register, see section 3.3.19.1),
	the sequence number threshold overflow bit e8 in the result token is set.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sn_thr Pointer to SN threshold (\ref seq_num_thr).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_sn_thresh(struct gpy211_device *phy,
				     const struct seq_num_thr *sn_thr);

/**
	\brief This API gets the sequence number threshold for the Egress device.

	The EIP-62 provides the possibility of setting a separate threshold for cipher
	suites with 32-bit and 64-bit packet numbering.

	These registers can be configured to trigger an informative error e8
	indicating that the outbound sequence number equals the programmed value in this
	register, which can trigger an interrupt. With this interrupt, the system
	has time to start a re-key before the rollover error fires. If the next
	(incremented) sequence number is equal to or greater than this value
	(selectable in EIP62_CONTEXT_CTRL register, see section 3.3.19.1),
	the sequence number threshold overflow bit e8 in the result token is set.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param sn_thr Pointer to SN threshold (\ref seq_num_thr).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_sn_thresh(struct gpy211_device *phy,
				  struct seq_num_thr *sn_thr);

/**@}*/ /* GPY211_CRYPTO */

/** \addtogroup GPY211_MACSEC_AIC */
/**@{*/
/**
	\brief This API configures the Ingress Advanced Interrupt Controller device.

	The AIC combines all internal interrupts in a single interrupt output,
	providing edge detection of the interrupt pulses and masking.

	This API configures the AIC properties, such as input polarity/type control, interrupt
	pending status, masked interrupt pending status and interrupt enable
	control.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param aic_csr Pointer to AIC config (\ref aic_control_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_ing_aic_csr(struct gpy211_device *phy,
				   const struct aic_control_stat *aic_csr);

/**
	\brief This API gets the configuration of the Ingress Advanced Interrupt Controller.

	The AIC combines all internal interrupts in a single interrupt output,
	providing edge detection of the interrupt pulses and masking.

	This API gets the AIC properties, such as interrupt enable control, interrupt
	enable/disable and interrupt acknowledge.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param aic_csr Pointer to AIC config (\ref aic_control_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_ing_aic_csr(struct gpy211_device *phy,
				struct aic_control_stat *aic_csr);

/**
	\brief This API configures the Egress Advanced Interrupt Controller device.

	The AIC combines all internal interrupts in a single interrupt output,
	providing edge detection of the interrupt pulses and masking.

	This API configures the AIC properties, such as input polarity/type control, interrupt
	pending status, masked interrupt pending status and interrupt enable
	control.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param aic_csr Pointer to AIC config (\ref aic_control_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_config_egr_aic_csr(struct gpy211_device *phy,
				   const struct aic_control_stat *aic_csr);

/**
	\brief This API gets the configuration of the Egress Advanced Interrupt Controller.

	The AIC combines all internal interrupts in a single interrupt output,
	providing edge detection of the interrupt pulses and masking.

	This API gets the AIC properties, such as interrupt enable control, interrupt
	enable/disable and interrupt acknowledge.

	\param phy Pointer to GPHY data (\ref gpy211_device).
	\param aic_csr Pointer to AIC config (\ref aic_control_stat).

	\return
	- =0: successful
	- <0: error code
*/
int gpy2xx_msec_get_egr_aic_csr(struct gpy211_device *phy,
				struct aic_control_stat *aic_csr);

/**@}*/ /* GPY211_AIC */

#endif /** \brief _GPY211_MACSEC_H_ */
