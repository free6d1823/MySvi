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



#ifndef BIT_MACROS_H
#define	BIT_MACROS_H

#ifdef	__cplusplus
extern "C" {
#endif

	/*************************************************************************
	 * T Y P E D E F S    &    D E F I N E S
	 *************************************************************************/

	#define MASK32(lsb,size)														\
		(((0xFFFFFFFF >> lsb) << lsb) << (32 - size - lsb) >> (32 - size - lsb))

	/**
	 * @brief Macro utility to set a single bit
	 * @param reg Variable to set bit
	 * @param lsb Least significant bit to set
	 * @param val Value to set (0 / 1)
	 */
	#define SNPS_SETBIT(reg,lsb,val)							\
		reg = (((reg) & ~(1<<(lsb))) | (((val)&0x1)<<(lsb)))

	/**
	 * @brief Macro utility to retrieve value of single bit
	 * @param reg 32-bit value to extract bit value
	 * @param lsb Bit position
	 */
	#define SNPS_GETBIT(reg,lsb)	\
		(((reg) >> (lsb)) & 0x1)

	/**
	 * @brief Macro utility to create a bit mask with bits sets.
	 *
	 * For example, SNPS_BITMASK(6:4) yields 0x00000070
	 *
	 * @param msb Most significant bit of set mask
	 * @param lsb Least significant bit of set mask
	 */
	#define SNPS_BITMASK(msb,lsb)									\
		(((uint32_t) -1 >> (31 - (msb))) & ~((1U << (lsb)) - 1))

	/**
	 * @brief Macro utility to set a selection of bits within a 32-bit value
	 *
	 * @param regVal 32-bit unsigned value
	 * @param msb most significant bit
	 * @param lsb least significant bit
	 * @param val bit field value
	 */
	#define SNPS_SETBITMASK(reg,msb,lsb,val)							\
		do {															\
			(reg) = ((((reg) & ~SNPS_BITMASK(msb, lsb))) |				\
						(((val) << (lsb)) & SNPS_BITMASK(msb, lsb)));	\
		} while (0)

	/**
	 * @brief Macro utility to get a selection of bits within a 32-bit value
	 *
	 * @param reg 32-bit register value
	 * @param msb Most significant bit
	 * @param lsb Least significant bit
	 * @return Bit field value
	 */
	#define SNPS_GETBITMASK(reg,msb,lsb)			\
		(((reg) & SNPS_BITMASK(msb,lsb)) >> (lsb))

	/**
	 * @brief Macro utility to shift a bit field left
	 * @param val Value (less than 32-bit value) to shift
	 * @param size Size of value (number of bits, 1..32)
	 * @param lsb Least significant bit (shift left, 0..31)
	 */
	#define SNPS_SETREGBITFIELDSHIFT(val,size,lsb)		\
		(((val) & SNPS_BITMASK(((size)-1),0)) << (lsb))

	/**
	 * @brief Macro utility to set register bit field. Same as setting bit
	 * mask but uses mask and least significant bit instead
	 * @param reg 32-bit register value
	 * @param lsb Least significant bit
	 * @param mask 32-bit mask indicating valid bits
	 * @param val Bit field value
	 */
	#define SETREGBITFILD(reg,lsb,mask,val)	\
		do { reg = (((reg) & ~(mask)) |				\
			(((val) << (lsb)) & (mask)));			\
		} while (0)

	/**
	 * @brief Macro utility to retrieve register bit field. Same as retrieving
	 * bit mask but uses mask and least significant bit instead.
	 * @param reg 32-bit register value
	 * @param lsb Least significant bit
	 * @param mask 32-bit mask indicating valid bits
	 * @return Bit field value
	 */
	#define SNPS_GETREGBITFIELD(reg,lsb,mask) \
		(((reg) & (mask)) >> (lsb))

	/**
	 * @brief Macro utility to create mask for register field
         * the mask is not shifted to field bit position in 32-bit
         * register.
         * */
        #define SNPS_FIELD_MASK(size) \
          (0xFFFFFFFF>> (32-size))


    	/**
	 * @brief Macro utility to update a register field within a 32 bit register value.
         * The mask and lsb is calculated using macros from
         * coreConsultant. 
	 * @param reg 32-bit register variable 
	 * @param register name
         * @param register field name
         * @param value to be applied
         *  example usage:
         *  APPLYREGFIELD(mstr, MSTR0, data_bus_width,  reg->data_bus_width )
         *  */
    #define APPLYREGFIELD(_var, _regn, _fieldn, _val) \
    do { SETREGBITFILD(_var, \
            _regn##_##_fieldn##_BitAddressOffset, \
            MASK32(_regn##_##_fieldn##_BitAddressOffset,\
                   _regn##_##_fieldn##_RegisterSize ) , \
            _val); } while(0)

    /** @brief Macro utility to update a register field from configuration struct.
    */
    #define APPLY_CFG_TO_REGFIELD(_cfg, _regn,_fieldn)\
      CONSTRAIN_INSIDE( _cfg->_fieldn,0,  SNPS_FIELD_MASK(_regn##_##_fieldn##_RegisterSize)  ); \
      SETREGBITFILD(reg->_fieldn, 0, SNPS_FIELD_MASK(_regn##_##_fieldn##_RegisterSize) , _cfg->_fieldn); \
      APPLYREGFIELD(reg->value, _regn, _fieldn,reg->_fieldn)\

    /** @brief Macro utility to update a register field from configuration struct with pstate index.
    */

    #define APPLY_CFG_TO_REGFIELD_P(_cfg, _regn,_fieldn,_pstate)\
      CONSTRAIN_INSIDE( _cfg->_fieldn[_pstate],0,  SNPS_FIELD_MASK(_regn##_##_fieldn##_RegisterSize)  ); \
      SETREGBITFILD(reg->_fieldn,0, SNPS_FIELD_MASK(_regn##_##_fieldn##_RegisterSize), _cfg->_fieldn[_pstate]);\
      APPLYREGFIELD(reg->value, _regn, _fieldn,reg->_fieldn)\

    /** @brief Macro utility to update a register field from configuration struct with pstate index and channel.
    */

    #define APPLY_CFG_TO_REGFIELD_P_CH(_cfg, _regn,_fieldn,_pstate,_channel)\
      CONSTRAIN_INSIDE( _cfg->_fieldn[_pstate][_channel],0,  SNPS_FIELD_MASK(_regn##_##_fieldn##_RegisterSize)  ); \
      SETREGBITFILD(reg->_fieldn,0, SNPS_FIELD_MASK(_regn##_##_fieldn##_RegisterSize), _cfg->_fieldn[_pstate][_channel]);\
      APPLYREGFIELD(reg->value, _regn, _fieldn,reg->_fieldn)\







    
#ifdef	__cplusplus
}
#endif

#endif	//BIT_MACROS_H

