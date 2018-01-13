setMode -bs
setMode -bs
setMode -bs
setMode -bs
setCable -port auto
Identify -inferir 
identifyMPM 
assignFile -p 1 -file "C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/fpgaproj/all_digital_modulator_fil.bit"
ReadIdcode -p 1 
ReadUsercode -p 1 
ReadStatusRegister -p 1 
expresssvf -p 1 -program -verify -file "C:\Xilinx\default.svf" 
expressxsvf -p 1 -program -verify -file "C:\Xilinx\default.xsvf" 
setCable -port auto
readdna -p 1 
Program -p 1 
assignFile -p 1 -file "C:/Newcomputer/DSM_Final/DSM_Final/fpgaproj/fil_test_fil2.bit"
assignFile -p 1 -file "C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/fpgaproj/all_digital_modulator_fil.bit"
setMode -bs
setMode -bs
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
setMode -bs
saveProjectFile -file "C:\Xilinx\\auto_project.ipf"
setMode -bs
setMode -bs
deleteDevice -position 1
setMode -bs
setMode -ss
setMode -sm
setMode -hw140
setMode -spi
setMode -acecf
setMode -acempm
setMode -pff
