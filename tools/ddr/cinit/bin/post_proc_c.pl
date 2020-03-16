#!/usr/bin/perl
#-------------------------------------------------------------------------------
#
# Copyright 2019 Synopsys, INC.
#
# This Synopsys IP and all associated documentation are proprietary to
# Synopsys, Inc. and may only be used pursuant to the terms and conditions of a
# written license agreement with Synopsys, Inc. All other use, reproduction,
# modification, or distribution of the Synopsys IP or the associated
# documentation is strictly prohibited.
#
# Component Name   : DWC_ddrctl
# Component Version: 1.00a-ea06
# Release Type     : EA
#-------------------------------------------------------------------------------

# This script has 3 modes of operation
# 1. A very simple script to convert C header syntax to system-verilog syntax.
# 2. To remove #ifdef from C src file
# 3. TO remove base address macros from coreConsultant header
#
use strict;
use warnings;
use Getopt::Long;     # -- process command line options
use Pod::Usage;       # -- for printing help message
my $verbose=0;
my $opt_c_h='tbd';
my $opt_c_to_sv=0;
my $opt_umctl_header=0;
my $help        = 0;
my $opt_outf = 'tbd';
my $opt_strip_ifdef=0;
GetOptions(
    'src=s' => \$opt_c_h,
    'out=s' => \$opt_outf,
    'c_to_sv' => \$opt_c_to_sv, 
    'umctl_header' => \$opt_umctl_header, 
    'strip_ifdef' =>\$opt_strip_ifdef,
    'help|h'        => \$help         # ask for help
   ) or pod2usage(2);
pod2usage(1) if $help;

if($opt_c_to_sv) {
  print "opt_c_to_sv\n" if($verbose);
  &c_to_sv();
  exit 0;
}
if($opt_umctl_header) {
  print "opt_umctl_header\n" if($verbose);
  &proc_umctl_header();
  exit 0;
}
if($opt_strip_ifdef) {
  print "opt_strip_ifdef\n" if($verbose);
  &strip_ifdef();
  exit 0;
}
pod2usage(2);
###################################################
# Covert C src file to systemverilog syntax
#########################################################
sub c_to_sv {
my $c_svh=$opt_c_h;
$c_svh=~s/\.h/\.svh/g;

print "Opening $opt_c_h for reading\n" if($verbose);
open(IN,"<$opt_c_h") || die("Could not open $opt_c_h for reading.");

print "Opening $c_svh for writing\n" if($verbose);
open(OUT,">$c_svh") || die("Could not open $c_svh for writing.");
# Read in C write out SVH
while(<IN>) {
  $_=~s/\[UMCTL2_FREQUENCY_NUM/\[`UMCTL2_FREQUENCY_NUM/g;
  $_=~s/\[UMCTL2_A_NSAR/\[`UMCTL2_A_NSAR/g;
  $_=~s/\[UMCTL2_A_NPORTS/\[`UMCTL2_A_NPORTS/g;
  $_=~s/\[UMCTL2_NUM_DATA_CHANNEL/\[`UMCTL2_NUM_DATA_CHANNEL/g;

  $_=~s/uint32_rnd_t/rand int unsigned/g;
  $_=~s/uint32_t/int unsigned/g;
  $_=~s/uint16_rnd_t/rand shortint unsigned/g;
  $_=~s/uint16_t/shortint unsigned/g;
  $_=~s/uint8_rnd_t/rand byte/g;
  $_=~s/uint8_t/byte/g;
  $_=~s/bool_rnd_t/rand bit/g;
  $_=~s/bool/bit/g;

  $_=~s/#ifdef/`ifdef/g;
  $_=~s/#ifndef/`ifndef/g;
  $_=~s/#endif/`endif/g;
  $_=~s/#define/`define/g;
  $_=~s/struct tag_(\S+)/struct /g;
  $_=~s/enum tag_(\S+)/enum /g;
  # 
  # specific to cinit_cfg.svh
  # SubsysHdlr_t is forwardly declared and needs special care.
  # add rand to allow randomization in UVM simulation.
  $_=~s/}; \/\/ fwd SubsysHdlr_t/\} SubsysHdlr_t;/g;
  $_=~s/struct (\S+)_priv/typedef struct /g;
  $_=~s/^\s+mctl_static_cfg_t/  rand mctl_static_cfg_t/g;
  $_=~s/^\s+mctl_qdyn_cfg_t/  rand mctl_qdyn_cfg_t/g;
  $_=~s/^\s+mctl_dyn_cfg_t/  rand mctl_dyn_cfg_t/g;
  $_=~s/mctl_t  memCtrlr_m/rand mctl_t  memCtrlr_m/g;
  $_=~s/lpddr4_mode_registers_t lpddr4_mr/rand lpddr4_mode_registers_t lpddr4_mr/g;
  $_=~s/lpddr5_mode_registers_t lpddr5_mr/rand lpddr5_mode_registers_t lpddr5_mr/g;
  $_=~s/ddr4_mode_registers_t ddr4_mr/rand ddr4_mode_registers_t ddr4_mr/g;
  $_=~s/ddr5_mode_registers_t ddr5_mr/rand ddr5_mode_registers_t ddr5_mr/g;
  $_=~s/^\s+ddr4_mr/rand ddr4_mr/g;
  $_=~s/^\s+ddr5_mr/rand ddr5_mr/g;
  $_=~s/^\s+lpddr4_mr/rand lpddr4_mr/g;
  $_=~s/^\s+lpddr5_mr/rand lpddr5_mr/g;
  # void * is equivalent to chandle in SV
  $_=~s/void \*/chandle /g;

  print OUT $_;
}

close(IN);
close(OUT);
}
##########################################################
# Sub routine to remove base addresses macros from the header
# scratch/headers/DWC_ddrctl_header.h 
# These base addresses cause loads of compile warnings.
##########################################################
sub proc_umctl_header {
my $header=$opt_c_h ;
my $outf=$opt_outf;
print "$0: creating DWC_ddrctl_header.h\n" if($verbose);
open(IN,"<$header") || die("Could not open $header for reading.\n");
open(OUT,">$outf") || die("Could not open $outf for writing.\n");
while(<IN>) {
  my $line=$_;
  if(/BaseAddress \+/  ) {
     $line = "// " . $line;
  } 
  print OUT $line;
 
}

close(IN);
close(OUT);

}
##########################################################
# Sub Routine to remove all ifdef in the src file
#
##########################################################
sub strip_ifdef {
  my $src=$opt_c_h ;
  my $outf=$opt_outf;
  open(IN,"<$src") || die("Could not open $src for reading.\n");
  open(OUT,">$outf") || die("Could not open $outf for writing.\n");
  while(<IN>) {


  }
}
# end of script
exit(0);


__END__

=head1 NAME

post_proc_c.pl - Post process some C or C headers that were automated by in coreBuilder or coreConsultant.

=head1 SYNOPSIS

post_proc_c.pl [--c_to_sv ] [--umctl_header ] [--src <file>]  [--out <file>] [--help]

 Options:
   --help              : print this message
   --c_to_sv           : Convert C to SV 
   --umctl_header      : process umctl_header file
   --src               : C source file
   --out               : Output file name 

=head1 AUTHOR

 (colm@synopsys.com)

=head1 COPYRIGHT

(C) COPYRIGHT 2002-2017 SYNOPSYS, INC. ALL RIGHTS RESERVED
This software and the associated documentation are confidential and
proprietary to Synopsys, Inc.  Your use or disclosure of this
software is subject to the terms and conditions of a written
license agreement between you, or your company, and Synopsys, Inc.
The entire notice above must be reproduced on all authorized copies.

=cut
