project new fil_test_fil
project set family spartan6
project set device xc6slx45
project set package csg324
project set speed -2
project set "Optimization Goal" "Speed"
project set "Combinatorial Logic Optimization" "True" -process Map
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/fil_test.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/MWClkMgr.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwrxmac.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwtxmac.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwpingram.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/MWMAC.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/MWDPRAM.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/FILUDPCRC.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/FILPktMUX.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/FILCmdProc.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/MWAsyncFIFO.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/FILDataProc.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/MWPKTBuffer.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/MWUDPPKTBuilder.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/FILPktProc.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/FILCommLayer.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwfil_dpscram.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwfil_udfifo.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwfil_bus2dut.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwfil_chifcore.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwfil_controller.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwfil_dut2bus.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/fil_test_wrapper.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/mwfil_chiftop.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/FILCore.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/MWMdioBasic.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/fil_test_fil.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/filsrc/fil_test_fil.ucf
project set top fil_test_fil
project clean
process run "Generate Programming File"
set result [process get "Generate Programming File" status]
if {$result == "errors" || $result == "never_run"} {
   exit 2
}
set par_file "fil_test_fil.par"
set timing_err ""
if { [catch {open $par_file r} par_fid] } {
      set timing_err "Warning: Skipped timing check because PAR report does not exist."
} else {
   set par_str [read $par_fid]
   close $par_fid
   set result [regexp {[1-9]\d* constraints? not met} $par_str match]
   if {$result > 0} {
      set timing_err "Warning: Design does not meet all timing constraints.\nCheck PAR report \"fil_test_fil.par\" for details."
   }
}
project close
set log ""
lappend log "\n\n------------------------------------"
lappend log "   FPGA-in-the-Loop build summary"
lappend log "------------------------------------\n"
set expected_file fil_test_fil.bit
set copied_file C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/fil_test_fil.bit
if [catch {file copy -force $expected_file ..}] {
   file delete ../$expected_file
   lappend log "Expected programming file not generated."
   lappend log "FPGA-in-the-Loop build failed.\n"
} else {
   if {[string length $timing_err] > 0} {
      lappend log "$timing_err\n"
      set warn_str " with warning"
   } else {
      set warn_str ""
   }
   lappend log "Programming file generated:"
   lappend log "$copied_file\n"
   lappend log "FPGA-in-the-Loop build completed$warn_str."
   lappend log "You may close this shell.\n"
}
foreach j $log {puts $j}
if { [catch {open fpgaproj.log w} log_fid] } {
} else {
    foreach j $log {puts $log_fid $j}
}
close $log_fid
