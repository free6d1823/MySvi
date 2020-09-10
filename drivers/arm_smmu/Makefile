# SPDX-License-Identifier: GPL-2.0+
#
# (C) Copyright 2019
# siengine

# bugs exist in simple smmu driver, don't use it currently
#SIMPLE_TEST := 1
ifdef SIMPLE_TEST
obj-y += smmu_super_simple.o
else
obj-y += arm-smmu-v3.o
obj-y += io-pgtable-arm.o
obj-y += io-pgtable.o
endif