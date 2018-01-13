# HDL Coder Downstream Integration Tcl Script

set myTool "Xilinx ISE 14.7"
set myProject "DUT_topatlys_ise"
set myProjectFile "DUT_topatlys_ise.xise"
set myTopLevelEntity "DUT_topatlys"

set Family "Spartan6"
set Device "xc6slx45"
set Package "csg324"
set Speed "-2"
set MapTimeReportType "Verbose Report"
set MapTimePathNumber "3"
set MapTimeAdvAnalysis "False"
set PARTimeReportType "Verbose Report"
set PARTimePathNumber "3"
set PARTimeAdvAnalysis "False"

# Open existing project
puts "### Open existing $myTool project C:\\Newcomputer\\DSM_Final\\DSM_Final\\fpgaproj\\DUT_topatlys_ise.xise"
project open $myProject

# Running ProgrammingFile
puts "### Running ProgrammingFile in $myTool ..."
process run "Generate Programming File"
puts "### ProgrammingFile Complete."

# Close project
puts "### Close $myTool project."
project close

