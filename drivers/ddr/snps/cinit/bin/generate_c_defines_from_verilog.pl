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


use warnings;
use strict;
# Not every customer has Bit::Vector installed
#use Bit::Vector;
# ------------------------------------------------------------------------------
# declare all sub prototypes
# ------------------------------------------------------------------------------
sub usage;
sub getFilesList;
sub processFiles;


if (scalar(@ARGV) < 2) {
  &usage();
}

my @args = @ARGV;
my $outFile = shift @args;
my @files = @args;

processFiles($outFile, @files);
# ------------------------------------------------------------------------------
# Subroutine : b2h()
# Description: input binary string and return hex value
# https://www.perlmonks.org/?node_id=644225
# ------------------------------------------------------------------------------

sub b2h {
    my $num   = shift;
    my $WIDTH = 32;
    my $index = length($num) - $WIDTH;
    my $hex = '';
    #print "num = $num\n";
    do {
        my $width = $WIDTH;
        if ($index < 0) {
            $width += $index;
            $index = 0;
        }
        my $cut_string = substr($num, $index, $width);
        $hex = sprintf('%X', oct("0b$cut_string")) . $hex;
        $index -= $WIDTH;
    } while ($index > (-1 * $WIDTH));
    #print "b2h ", $hex,"\n";
    
    return $hex;
}
# ------------------------------------------------------------------------------
# Subroutine : usage()
# Description: print out script usage
# ------------------------------------------------------------------------------
sub usage 
{
  print "Usage: $0 snpsDdrDefines.h file1.v file2.v ...etc\n";
  exit -1;
}

# ------------------------------------------------------------------------------
# Subroutine : getFilesList()
# Description: return the list of files listed in argv arguments
# ------------------------------------------------------------------------------
sub getFilesList
{
  my $inFile = shift;
  my @files;

  if (! -r $inFile) {
    die "Can't read input file '$inFile'\n";
  }

  print "Processing $inFile...\n";

  open (IN, "$inFile") || die "Can't open the file $inFile!";
  @files = <IN>; 
  close IN;

  return @files;
}

# ------------------------------------------------------------------------------
# Subroutine : processFiles()
# Description: parses each listed file (constants, globals, defines, etc) and 
# generate a master defines file.
# ------------------------------------------------------------------------------
sub processFiles
{
  my ($outFile, @files) = @_;

  my $v1 = 0;
  my $v2 = 0;
  my $multiLine = 0;
  my @lines = ();
  my $line = "";
  my $file = "";
  my $tmp1 = "";
  my $tmp2 = "";
  my $hdr = "";

  open (OUT, ">$outFile") || die "Can't open the file $outFile!";

  $hdr = "/*****************************************************************************\n";
  $hdr = $hdr." *\n"; 
  $hdr = $hdr." *\n";
  $hdr = $hdr." *                    (C) COPYRIGHT 2014 SYNOPSYS, INC.\n";
  $hdr = $hdr." *                            ALL RIGHTS RESERVED\n";
  $hdr = $hdr." *\n";
  $hdr = $hdr." * This software and the associated  documentation are proprietary to \n";
  $hdr = $hdr." * Synopsys, Inc. This software may only be used in accordance with the terms \n";
  $hdr = $hdr." * and conditions of a written license agreement with Synopsys, Inc. All other\n";
  $hdr = $hdr." * use, reproduction, or distribution of this software is strictly prohibited.\n";
  $hdr = $hdr." *\n";
  $hdr = $hdr." * The entire notice above must be reproduced on all authorized copies.\n";
  $hdr = $hdr." *\n";
  $hdr = $hdr." *****************************************************************************/\n\n";
  $hdr = $hdr."#ifndef SNPSDDRDEFINES_H\n";
  $hdr = $hdr."#define SNPSDDRDEFINES_H\n\n";
  $hdr = $hdr."#ifdef	__cplusplus\n";
  $hdr = $hdr."extern \"C\" {\n";
  $hdr = $hdr."#endif\n\n";
  $hdr = $hdr."/*************************************************************************\n";
  $hdr = $hdr." * T Y P E D E F S    &    D E F I N E S\n";
  $hdr = $hdr." *************************************************************************/\n\n";
  print OUT "$hdr";

  foreach $file (@files) {
    chomp $file;
    if (! -r $file) {
      die "Can't read file '$file'\n";
    }
    
    open (FILE, "$file") || die "Can't open the file $file!";
    @lines = <FILE>;
    close FILE; 

    print "Processing $file...\n";
    print OUT "\n//Autogenerated from $file\n";
    foreach $line (@lines) {
      $line =~ s/\/\/(.*)//; # remove comments

      # exception list: remove unneeded defines, comments, etc.
      if (($line =~ /^\`define(\s+)log(\s*)(\()(\s*)([a-zA-Z0-9]+)(\s*)(\))(\s*)/) || # not needed --> `define log(n)
          ($line =~ /^\`define(\s+)UMCTL_LOG2(\s*)(\()(\s*)([a-zA-Z0-9]+)(\s*)(\))(\s*)/) || # not needed --> `define UMCTL_LOG2(n)
          ($line =~ /([a-zA-Z0-9_]+)(\.)([a-zA-Z0-9_]+)/) || # not needed --> 'xxx.yyy.zzz...'
          ($line =~ /\`define(\s*)(SYS)(\s+)/) || # not needed --> testbench related defines
          ($line =~ /\`define(\s*)UMCTL2_PORT_DW_TABLE(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s*)UMCTL2_NUM_VIR_CH_TABLE(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s*)MEMC_DCERRFIELD(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s*)MEMC_WRCMD_ENTRIES_ADDR(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s*)UMCTL2_REG_MSK_STAT_OPERATING_MODE(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s*)UMCTL2_REG_MSK_STAT(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s*)UMCTL2_REG_MSK_/) || # not needed --> unused register mask define
          ($line =~ /\`define(\s*)UMCTL2_REG_SIZE_/) || # not needed --> unused register size define
          ($line =~ /\`define(\s*)UMCTL2_REG_OFFSET_/) || # not needed --> unused register offset define
          ($line =~ /\SHIFTAPBADDR(\s*)(\()/) || # not needed --> unused register address define
          ($line =~ /\`define(\s+)__INCLUDE_DDRC_PKG(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)TOP(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)TB_DUT(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)TB_DDR_CHIP(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)DDR_CHIP_TOP(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)UMCTL2_TOP(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)MIN(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)MAX(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)log(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)dut_error(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)dut_warning(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_WRITE(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_WRITE_B(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)WRITE_DDRCIF_B(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)WRITE_DDRCIF(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)DDRCIF_TO_DR(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)DDRCIF_TO_APB(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_READ_DR(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_READ_RD(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)ONE_PCLK(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_POLLING_DR(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_POLLING_NE_RD(\s*)/) || # not needed --> unused define  
          ($line =~ /\`define(\s+)APB_POLLING_NE_DR(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_QUASI_DYN_G0_SLEEP(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_READ_DR_EXT(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_READ_RD_EXT(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)APB_POLLING_DR_EXT(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)MR_ACCESS(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)POLL_RANK_REFRESH_BUSY(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)SET_RANK_REFRESH(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)DDRC_TEST_END(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)DDRC_TEST_PASSED(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)PUB_([0-9a-zA-Z]+)_DEFAULT(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)DX_NUM(\s*)/) || # not needed --> unused define
          ($line =~ /\`define(\s+)assert(\s*)/) ||
          ($line =~ /\`define(\s+)ASSERT(\s*)/) ||
		  ($line =~ /`define\s+.*\.\w+/) || # eg. `define DWC_VSS_CAP_VREF_CONNECT .MVREF
		  ($line =~ /\`define(\s+).*\{.*\}/) || #{ }
		  ($line =~ /\`define(\s+)DWC_FIRMWARE_RID_/) ||
		  ($line =~ /\`define(\s+)SNPS_SVA_MSG/)
         )
      {
      	#printf "skipping %s \n", $line;
        next;
      }
      
	  # define without value assigned to it and without a comment
      if ($line =~ /\`define(\s+)([a-zA-Z0-9_]+)(\s+)$/) {
        print OUT "#define $2\n";
        next;
      }
      
	  # handle define statement that spans multilines
      if ($multiLine == 1) {
        $line =~ s/^(\s+)/ /;
        $line =~ s/([0-9]+)(\'h)/0x/g ; # convert 'h to 0x
        $line =~ s/([0-9]+)(\'d)([0-9]+)/$3/g ; # convert 'd to proper decimal
        # Not every customer has Bit::Vector installed
        # so comment it out
        #while ($line =~ /(\s*)([0-9]+)(\'b)([0-1]+)/) {
           #print "here line = $line\n";
           #$v1 = Bit::Vector->new_Bin($2, $4);
          #$v2 = $v1->to_Hex();
          #$line =~ s/$2$3$4/0x$v2/;
          #} 
        $line =~ s/`//g;
        if ($line =~ /(\s*)(\\)(\s*)/) {
          $tmp1 = $line;
          $tmp1 =~ s/(\s*)(\\)(\s*)//g;
          print OUT " $tmp1";
        } else {
          $tmp1 = $line;
          $tmp1 =~ s/(\s*)(\\)(\s*)//g;
          print OUT " $tmp1\n";
          $multiLine = 0;
        }
      }
	  
      # define without value assigned to it but with a comment
      if ($line =~ /\`define(\s+)([a-zA-Z0-9_]+)(\s*)(\/\/)(.*)$/) {
        print OUT "#define $2\n";
        next;
      }
	  
      if ($line =~ /\`define(\s+)([a-zA-Z0-9_]+)(.*)/) {
        $tmp1 = $2;
        ($tmp2 = $3) =~ s/\`//g;
        $tmp2 =~ s/([0-9]+)(\'h)/0x/g ; # convert 'h to 0x
        $tmp2 =~ s/([0-9]+)(\'d)([0-9]+)/$3/g ; # convert 'd to proper decimal  
        if ($tmp2 =~ /([{]+)(\s*)([0-9]+)(\'b)([0-1]+)/) {
          print OUT "#define $tmp1 $tmp2 ";
          if ($line =~ /(\\)$/) {
            $multiLine = 1;
          } else {
            print OUT "\n";
          }
          next;
        }  
        while ($tmp2 =~ /(\s*)([0-9]+)(\'b)([0-1]+)/) {
           #print "here2 line=$line, tmp2 = $tmp2\n";
           #   my @h=split(/(\'b)/, $tmp2);
           my @h=split(/(\s*)([0-9]+)(\'b)([0-1]+)(\s*)/, $tmp2);
           #foreach my $i (@h) {
           #  print "i = $i\n";
           #}
           
           my $new_hex=&b2h($h[4]);
           $tmp2 =~ s/(\s*)([0-9]+)(\'b)([0-1]+)/0x$new_hex/;
           # Not every customer has Bit::Vector installed
           #$v1 = Bit::Vector->new_Bin($2, $4);
           #$v2 = $v1->to_Hex();
           #$tmp2 =~ s/$2$3$4/0x$v2/;
           #print "tmp2 = $tmp2\n";
        }
        $tmp2 =~ s/\\//g; 
        print OUT "#define $tmp1 $tmp2";
        if ($line =~ /(\\)(\s*)$/) {
          $multiLine = 1;
        } else {
          print OUT "\n";
        }
        next;
      }

      if ($line =~ /\`ifdef(\s+)([a-zA-Z0-9_]+)(\s*)$/) {
        print OUT "#ifdef $2\n";
        next;
      }

      if ($line =~ /\`ifndef(\s+)([a-zA-Z0-9_]+)(\s*)$/) {
        print OUT "#ifndef $2\n";
        next;
      }

      if ($line =~ /\`else/) {
        print OUT "#else\n";
        next;
      }

      if ($line =~ /\`elsif(\s+)([a-zA-Z0-9_]+)(\s*)$/) {
        print OUT "#elif defined($2)\n";
        next;
      }

      if ($line =~ /\`endif/) {
        print OUT "#endif\n";
        next;
      }
	  
      if ($line =~ /\`undef(\s+)([a-zA-Z0-9_]+)(\s*)$/) {
        print OUT "#undef $2\n";
        next;
      }
	  

    }
  }

  $hdr = "\n/*************************************************************************\n";
  $hdr = $hdr." * G L O B A L    V A R I A B L E S\n";
  $hdr = $hdr." *************************************************************************/\n\n";
  $hdr = $hdr."/*************************************************************************\n";
  $hdr = $hdr." * F U N C T I O N    P R O T O T Y P E S\n";
  $hdr = $hdr." *************************************************************************/\n\n\n";
  $hdr = $hdr."#ifdef	__cplusplus\n";
  $hdr = $hdr."}\n";
  $hdr = $hdr."#endif\n\n";
  $hdr = $hdr."#endif	/* SNPSDDRDEFINES_H */\n";
  print OUT "$hdr";

  close OUT;

	#post process the generated file to remove empty defines
	open my $in_file, '<', $outFile or die "Couldn't open file: $outFile $!";
	local $/ = undef;
	my $lines = <$in_file>;
	close($in_file);

	my $replacementMade = 0;
	
	do {
		$replacementMade = 0;

		my $pat = '(#elif\s+?defined\s*?\(\s*?\w+?\s*?\)\s*)#elif';
		while ( $lines =~ /$pat/msg ) {
			$lines =~ s/$pat/#elif/msg;
			$replacementMade++;
		}
	
		$pat = '(#elif\s+?defined\s*?\(\s*?\w+?\s*?\)\s*)#else';
		while ( $lines =~ /$pat/msg ) {
			$lines =~ s/$pat/#else/msg;
			$replacementMade++;
		}
	
		$pat = '(#else\s*?)#endif';
		while ( $lines =~ /$pat/msg ) {
			$lines =~ s/$pat/#endif/msg;
			$replacementMade++;
		}
	
		$pat = '(#ifdef\s+?\w+?\s*?#endif\s*)';
		while ( $lines =~ /$pat/msg ) {
			$lines =~ s/$pat//msg;
			$replacementMade++;
		}
	
		$pat = '(#ifndef\s+?\w+?\s*?#endif\s*)';
		while ( $lines =~ /$pat/msg ) {
			$lines =~ s/$pat//msg;
			$replacementMade++;
		}
	} while ($replacementMade);



	open my $out_file, '>', $outFile or die "Couldn't open file: $outFile $!";
	printf {$out_file} "$lines";
	close($out_file);

	
  print "Generated $outFile\n";
}
