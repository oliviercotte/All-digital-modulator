project new all_digital_modulator_fil
project set family spartan6
project set device xc6slx45
project set package csg324
project set speed -2
project set "Optimization Goal" "Speed"
project set "Combinatorial Logic Optimization" "True" -process Map
xfile add C:/Newcomputer/DSM_Final/DSM_Final/float_pkg_c.vhdl
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fixed_pkg_c.vhdl
xfile add C:/Newcomputer/DSM_Final/DSM_Final/fixed_float_types_c.vhdl
xfile add C:/Newcomputer/DSM_Final/DSM_Final/cordic_types.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/trigonometric_fct_generator.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/top_level_ddfs.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/Second_order_delta_sigma_modulator.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/PLL_CLOCK.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/phase_generator.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/phase_accumulator.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/MATLAB_Function.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/Halfband_4_491_52.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/Fourth_order_delta_sigma_modulator.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/Eight_order_delta_sigma_modulator.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/ddfs_ctrl.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/cordic_core.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/Channel_Filter.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Clock_Generator_1.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Clock_Generator_2.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/dds.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Halfband_1_61_44.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Halfband_2_122_88.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Halfband_3_245_76.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/MWClkMgr.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwrxmac.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwtxmac.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwpingram.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/MWMAC.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/MWDPRAM.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/FILUDPCRC.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/FILPktMUX.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/FILCmdProc.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/MWAsyncFIFO.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/FILDataProc.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/MWPKTBuffer.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/MWUDPPKTBuilder.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/FILPktProc.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/FILCommLayer.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwfil_dpscram.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwfil_udfifo.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwfil_bus2dut.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwfil_chifcore.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwfil_controller.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwfil_dut2bus.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/all_digital_modulator_wrapper.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/mwfil_chiftop.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/FILCore.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/MWMdioBasic.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/all_digital_modulator_fil.vhd
xfile add C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator_fil/filsrc/all_digital_modulator_fil.ucf
project set top all_digital_modulator_fil
project clean
process run "Check Syntax"
set result [process get "Check Syntax" status]
if {$result == "errors"} {
   exit 2
}
project close
