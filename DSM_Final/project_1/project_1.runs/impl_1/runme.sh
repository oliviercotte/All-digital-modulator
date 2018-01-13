#!/bin/sh

# 
# PlanAhead(TM)
# runme.sh: a PlanAhead-generated Runs Script for UNIX
# Copyright 1986-1999, 2001-2013 Xilinx, Inc. All Rights Reserved.
# 

echo "This script was generated under a different operating system."
echo "Please update the PATH and LD_LIBRARY_PATH variables below, before executing this script"
exit

if [ -z "$PATH" ]; then
  PATH=C:/Xilinx/14.7/ISE_DS/EDK/bin/nt;C:/Xilinx/14.7/ISE_DS/EDK/lib/nt;C:/Xilinx/14.7/ISE_DS/ISE/bin/nt;C:/Xilinx/14.7/ISE_DS/ISE/lib/nt;C:/Xilinx/14.7/ISE_DS/common/bin/nt;C:/Xilinx/14.7/ISE_DS/common/lib/nt:C:/Xilinx/14.7/ISE_DS/PlanAhead/bin
else
  PATH=C:/Xilinx/14.7/ISE_DS/EDK/bin/nt;C:/Xilinx/14.7/ISE_DS/EDK/lib/nt;C:/Xilinx/14.7/ISE_DS/ISE/bin/nt;C:/Xilinx/14.7/ISE_DS/ISE/lib/nt;C:/Xilinx/14.7/ISE_DS/common/bin/nt;C:/Xilinx/14.7/ISE_DS/common/lib/nt:C:/Xilinx/14.7/ISE_DS/PlanAhead/bin:$PATH
fi
export PATH

if [ -z "$LD_LIBRARY_PATH" ]; then
  LD_LIBRARY_PATH=
else
  LD_LIBRARY_PATH=:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

HD_PWD=`dirname "$0"`
cd "$HD_PWD"

HD_LOG=runme.log
/bin/touch $HD_LOG

ISEStep="./ISEWrap.sh"
EAStep()
{
     $ISEStep $HD_LOG "$@" >> $HD_LOG 2>&1
     if [ $? -ne 0 ]
     then
         exit
     fi
}

EAStep ngdbuild -intstyle ise -p xc6slx150fgg484-3 -dd _ngo -uc "all_digital_modulator.ucf" "all_digital_modulator.edf"
EAStep map -intstyle pa -w -pr b -timing -logic_opt on -global_opt speed -ol high -xe n -mt on "all_digital_modulator.ngd"
EAStep par -intstyle pa "all_digital_modulator.ncd" -w "all_digital_modulator_routed.ncd" -ol high -mt 4
EAStep trce -intstyle ise -o "all_digital_modulator.twr" -v 30 -l 30 "all_digital_modulator_routed.ncd" "all_digital_modulator.pcf"
EAStep xdl -secure -ncd2xdl -nopips "all_digital_modulator_routed.ncd" "all_digital_modulator_routed.xdl"
