#!/bin/sh
make clean PROTOCOL=lpddr4
make PHY_VDEFINES_FILE=/projects/soc_prj1/se1000/shuo.zhang/se1000/thirdip/ddrctl/DWC_ddrctl_v2.0/sim_mctl/testbench/macros/dwc_ddrphy_VDEFINES.v PROTOCOL=lpddr4 VERSION=1.00a-ea06 >& cinit_lpddr4_compile.log
if [ $? -eq 0 ] 
then
  echo "CINIT compiled ok"
else
  exit 1
fi

