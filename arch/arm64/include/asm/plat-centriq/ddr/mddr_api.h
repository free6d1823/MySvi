#ifndef __CENTRIQ_MDDR_API_H_INCLUDE__
#define __CENTRIQ_MDDR_API_H_INCLUDE__

/* ============================================================================
**  Function : logical channel to physical table
** ===========================================================================*/
uint8_t ddr_logical_to_physical_channel(uint8_t logical_ch);

/* ============================================================================
**  Function : Physical channle to logical table
** ===========================================================================*/
uint8_t ddr_physical_to_logical_channel(uint8_t logical_ch);

/******************************************************************************
* Function Prototypes
******************************************************************************/
unsigned mddr_validate_input(mddr_settings_t *mddr_settings_ptr);
void mddr_get_dimm_configs(void);
unsigned mddr_verify_dimm_combination_configs(mddr_settings_t *mddr_settings_ptr);
void mddr_get_combined_timing_vals(uint32_t mem_freq_ps);
void mddr_get_latency_vals(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr, mddr_latencies_t *latencies_ptr);
void mddr_get_slots_ck_cke(void);
void mddr_record_init_parms(mddr_settings_t *settings_ptr);
uint16_t mddr_get_dimms_max_clk(void);
void mddr_update_compression_settings(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);



void mddr_deassert_chan_gcc_apb_reset(uint8_t ddr_chan);
void mddr_deassert_chan_gcc_phy_areset(uint8_t ddr_chan);
void mddr_update_chan_gcc_reset(uint8_t ddr_chan, uint32_t val);
void mddr_disable_chan_gcc_ahb_clock(uint8_t ddr_chan);
void mddr_enable_chan_gcc_ahb_clock(uint8_t ddr_chan);
void mddr_disable_chan_gcc_2x_clock(uint8_t ddr_chan);
void mddr_enable_chan_gcc_2x_clock(uint8_t ddr_chan);
void mddr_cbc_enable(uint64_t reg_addr, char *reg_name_str);
void mddr_deassert_clkgen_pwrdn_b(uint8_t ddr_chan);
void mddr_release_chan_gcc_resetr(mddr_settings_t *mddr_settings_ptr);
void mddr_set_ddr_clk_mux(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan);
void mddr_get_si(mddr_settings_t *mddr_settings_ptr);
#ifdef CONFIG_TESTOS_EMU
void mddr_presil_set_ddr_clk_mux(uint8_t ddr_chan);
#endif
void mddr_clkgen_init(mddr_settings_t *mddr_settings_ptr, uint64_t mddr_base_addr, uint8_t ddr_chan);
unsigned mddr_set_clock_frequency(mddr_settings_t *mddr_settings_ptr);
void mddr_lockdown_unused_chan(uint8_t ddr_channel);

#endif
