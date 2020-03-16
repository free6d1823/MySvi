#!/bin/sh
make clean PROTOCOL=lpddr5
make PHY_VDEFINES_FILE=/projects/soc_prj1/se1000/shuo.zhang/se1000/thirdip/ddrctl/DWC_ddrctl_v2.0/sim_mctl/testbench/macros/dwc_ddrphy_VDEFINES.v PROTOCOL=lpddr5 VERSION=1.00a-ea06 >& cinit_lpddr5_compile.log
if [ $? -eq 0 ] 
then
  echo "CINIT compiled ok"
else
  exit 1
fi

