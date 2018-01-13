setMode -bs
setCable -target "digilent_plugin"
Identify -inferir
identifyMPM
assignFile -p 1 -file "C:\Newcomputer\DSM_Final\DSM_Final\all_digital_modulator_fil\all_digital_modulator_fil.bit"
program -p 1
quit
