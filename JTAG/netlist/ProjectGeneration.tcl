#
# Created by System Generator     Sun Jan  7 23:24:04 2018
#
# Note: This file is produced automatically, and will be overwritten the next
# time you press "Generate" in System Generator.
#

namespace eval ::xilinx::dsptool::iseproject::param {
    set SynthStrategyName {XST Defaults*}
    set ImplStrategyName {ISE Defaults*}
    set Compilation {Atlys_491_52}
    set Project {dac_mod_5_sim_cw}
    set DSPFamily {Spartan6}
    set DSPDevice {xc6slx45}
    set DSPPackage {csg324}
    set DSPSpeed {-3}
    set HDLLanguage {vhdl}
    set SynthesisTool {XST}
    set Simulator {Modelsim-SE}
    set ReadCores {False}
    set MapEffortLevel {High}
    set ParEffortLevel {High}
    set Frequency {491.520000000001}
    set CreateInterfaceDocument {off}
    set NewXSTParser {1}
	if { [ string equal $Compilation {IP Packager} ] == 1 } {
		set PostProjectCreationProc {dsp_package_for_vivado_ip_integrator}
		set IP_Library_Text {SysGen}
		set IP_Vendor_Text {Xilinx}
		set IP_Version_Text {1.0}
		set IP_Categories_Text {System Generator for DSP}
		set IP_Common_Repos {0}
		set IP_Dir {}
		set IP_LifeCycle_Menu {1}
		set IP_Description    {}
		
	}
    set ProjectFiles {
        {{dac_mod_5_sim_cw.vhd} -view All}
        {{dac_mod_5_sim.vhd} -view All}
        {{dac_mod_5_sim_cw.ucf}}
        {{dac_mod_5_sim_cw.xdc}}
        {{C:\FIL\JTAG\DAC_MOD_5_SIM.slx}}
    }
    set TopLevelModule {dac_mod_5_sim_cw}
    set SynthesisConstraintsFile {dac_mod_5_sim_cw.xcf}
    set ImplementationStopView {Structural}
    set ProjectGenerator {SysgenDSP}
}
    source SgIseProject.tcl
    ::xilinx::dsptool::iseproject::create
