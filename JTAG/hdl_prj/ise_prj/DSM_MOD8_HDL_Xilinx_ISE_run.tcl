# HDL Coder Downstream Integration Tcl Script

set myTool "Xilinx ISE 14.7"
set myProject "DSM_MOD8_HDL_ise"
set myProjectFile "DSM_MOD8_HDL_ise.xise"
set myTopLevelEntity "DSM_MOD8_HDL"

set Family "Spartan6"
set Device "xc6slx45"
set Package "csg324"
set Speed "-3"
set MapTimeReportType "Verbose Report"
set MapTimePathNumber "3"
set MapTimeAdvAnalysis "True"
set PARTimeReportType "Verbose Report"
set PARTimePathNumber "3"
set PARTimeAdvAnalysis "True"

# Open existing project
puts "### Open existing $myTool project hdl_prj\\ise_prj\\DSM_MOD8_HDL_ise.xise"
project open $myProject

# Running Map
puts "### Running Map in $myTool ..."
process run "Translate"
process run "Map"
puts "### Map Complete."

# Running PostMapTiming
puts "### Running PostMapTiming in $myTool ..."
project set "Report Type" "$MapTimeReportType" -process "Generate Post-Map Static Timing"
project set "Number of Paths in Error/Verbose Report" $MapTimePathNumber -process "Generate Post-Map Static Timing"
project set "Perform Advanced Analysis" $MapTimeAdvAnalysis -process "Generate Post-Map Static Timing"
process run "Generate Post-Map Static Timing"
puts "### PostMapTiming Complete."

# Close project
puts "### Close $myTool project."
project close

