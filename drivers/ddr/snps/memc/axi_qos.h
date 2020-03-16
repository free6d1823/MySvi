//------------------------------------------------------------------------------
//
// Copyright 2019 Synopsys, INC.
//
// This Synopsys IP and all associated documentation are proprietary to
// Synopsys, Inc. and may only be used pursuant to the terms and conditions of a
// written license agreement with Synopsys, Inc. All other use, reproduction,
// modification, or distribution of the Synopsys IP or the associated
// documentation is strictly prohibited.
//
// Component Name   : DWC_ddrctl
// Component Version: 1.00a-ea06
// Release Type     : EA
//------------------------------------------------------------------------------


#ifndef AXI_QOS_H
#define	AXI_QOS_H

#include <stdint.h>

//#include "fwd.h"

#ifdef	__cplusplus
extern "C" {
	#endif
	/*************************************************************************
	 * T Y P E D E F S    &    D E F I N E S
	 *************************************************************************/

	/**
	 * @brief AXI read QoS parameters.
	 */
	typedef struct tag_axiQoSReadConfig_t {
		uint32_t rqos_map_region[3];		//!< PCFGQOS0_n.rqos_map_region0,1,2
		uint32_t rqos_map_level[2];			//!< PCFGQOS0_n.rqos_map_level0,1
		uint32_t rqos_map_timeoutb;			//!< PCFGQOS1_n.rqos_map_timeoutb
		uint32_t rqos_map_timeoutr;			//!< PCFGQOS1_n.rqos_map_timeoutr
	} axiQoSReadConfig_t;

	/**
	 * @brief AXI write QoS parameters.
	 */
	typedef struct tag_axiQoSWriteConfig_t {
		uint32_t wqos_map_region[3];		//!< PCFGWQOS0_n.wqos_map_region0,1,2
		uint32_t wqos_map_level[2];			//!< PCFGWQOS0_n.wqos_map_level1,2
		uint32_t wqos_map_timeout[2];		//!< PCFGWQOS1_n.wqos_map_timeout1,2
	} axiQoSWriteConfig_t;

	/**
	 * @brief AXI port read parameters
	 */
	typedef struct tag_axiReadParams_t {
		uint32_t rdwr_ordered_en;				//!< PCFGR_n.rdwr_ordered_en
		uint32_t rd_port_pagematch_en;			//!< PCFGR_n.rd_port_pagematch_en
		uint32_t rd_port_urgent_en;				//!< PCFGR_n.rd_port_urgent_en
		uint32_t rd_port_aging_en;				//!< PCFGR_n.rd_port_aging_en
		uint32_t read_reorder_bypass_en;		//!< PCFGR_n.read_reorder_bypass_en
		uint32_t rd_port_priority;				//!< PCFGR_n.rd_port_priority
	} axiReadParams_t;

	/**
	 * @brief AXI port write parameters
	 */
	typedef struct tag_axiWriteParms_t {
		uint32_t wr_port_pagematch_en;	//!< PCFGW_n.wr_port_pagematch_en
		uint32_t wr_port_urgent_en;		//!< PCFGW_n.wr_port_urgent_en
		uint32_t wr_port_aging_en;		//!< PCFGW_n.wr_port_aging_en
		uint32_t wr_port_priority;		//!< PCFGW_n.wr_port_priority
	} axiWriteParms_t;

	/**
	 * @brief AHB port parameters
	 */
	typedef struct tag_ahbParams_t {
		uint32_t ahb_endianness;		//!< PCFGC_n.ahb_endianness
	} ahbParams_t;

	/**
	 * @brief virtual channel config
	 */
	typedef struct axiVirtChanConfig_t {
		uint32_t id_mask;	//!< PCFGIDMASKCH m_n.id_mask
		uint32_t id_value;	//!< PCFGIDVALUECH m_n.id_value
	} axiVirtChanConfig_t;

	/**
	 * @brief port configuration
	 */
	typedef struct portConfiguration_t {
		uint32_t port_en;								//!< PCTRL_n.port_en
		axiReadParams_t readParms_m;					//!< AXI read port parameter
		axiWriteParms_t writeParms_m;					//!< AXI write port parameter
		ahbParams_t ahbParms;							//!< AHB port parameter
		axiQoSReadConfig_t readAxiQoSParms_m;			//!< AXI QoS read port parameter
		axiQoSWriteConfig_t writeAxiQoSParms_m;			//!< AXI QoS write port parameter
		axiVirtChanConfig_t virtChanAxiParms_ma[16];	//!< Static virtual channel mode parameters
	} portConfiguration_t;

	/*************************************************************************
	 * G L O B A L    V A R I A B L E S
	 *************************************************************************/

	extern const uint8_t axiPortRdWrOrderedEnable_ca[16];
	extern const uint8_t axiPortVprEnable_ca[16];
	extern const uint8_t axiPortVpwEnable_ca[16];
	extern const uint8_t isAhbPort_ca[16];
	extern const uint8_t axiPortInStaticVirtualChannelMode[16];
	extern const uint8_t axiPortNumVirtualChannels[16];


	/*************************************************************************
	 * F U N C T I O N    P R O T O T Y P E S
	 *************************************************************************/

	void ApplyPortConfiguration(SubsysHdlr_t* hdlr);

#ifdef	__cplusplus
}
#endif
#endif	//AXI_QOS_H

