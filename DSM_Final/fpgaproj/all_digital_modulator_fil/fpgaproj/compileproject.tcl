project open all_digital_modulator_fil
process run "Generate Programming File"
set par_file "all_digital_modulator_fil.par"
set timing_err ""
if { [catch {open $par_file r} par_fid] } {
      set timing_err "Warning: Skipped timing check because PAR report does not exist."
} else {
   set par_str [read $par_fid]
   close $par_fid
   set result [regexp {[1-9]\d* constraints? not met} $par_str match]
   if {$result > 0} {
      set timing_err "Warning: Design does not meet all timing constraints.\nCheck PAR report \"all_digital_modulator_fil.par\" for details."
   }
}
project close
set log ""
lappend log "\n\n------------------------------------"
lappend log "   FPGA-in-the-Loop build summary"
lappend log "------------------------------------\n"
set expected_file all_digital_modulator_fil.bit
set copied_file C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/all_digital_modulator_fil/all_digital_modulator_fil.bit
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
