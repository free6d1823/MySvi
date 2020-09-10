#!/bin/sh
make FIRMWARE_PATH=/projects/soc_prj1/se1000/shuo.zhang/se1000/thirdip/ddrctl/DWC_ddrctl_v2.0/sim_mctl/sw_utilities/phy/firmware SR_FW_FILES_LOC=/projects/soc_prj1/se1000/shuo.zhang/se1000/thirdip/ddrctl/DWC_ddrctl_v2.0/sim_mctl/sw_utilities/phy/firmware/save_restore >& phyinit_lpddr5_compile.log
if [ $? -eq 0 ] 
then
  echo "PHYINIT compiled ok"
if [ -d "../lpddr5_64" ]; then rm -rf ../lpddr5_64; fi
mkdir ../lpddr5_64
cp -rf obj/* ../lpddr5_64/
make clean
else
  exit 1
fi

