setMode -bscan
setCable -target "digilent_plugin"
identify
assignFile -p 1 -file "DUT_topatlys.bit"
program -p 1
quit
