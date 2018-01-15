
# PlanAhead Launch Script for Post PAR Floorplanning, created by Project Navigator

create_project -name dac_mod_2_4_sim_cw -dir "C:/FIL/JTAG/netlist/planAhead_run_2" -part xc6slx45csg324-3
set srcset [get_property srcset [current_run -impl]]
set_property design_mode GateLvl $srcset
set_property edif_top_file "C:/FIL/JTAG/netlist/dac_mod_2_4_sim_cw.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {C:/FIL/JTAG/netlist} }
set_property target_constrs_file "dac_mod_2_4_sim_cw.ucf" [current_fileset -constrset]
add_files [list {dac_mod_2_4_sim_cw.ucf}] -fileset [get_property constrset [current_run]]
link_design
read_xdl -file "C:/FIL/JTAG/netlist/dac_mod_2_4_sim_cw.xdl"
if {[catch {read_twx -name results_1 -file "C:/FIL/JTAG/netlist/dac_mod_2_4_sim_cw.twx"} eInfo]} {
   puts "WARNING: there was a problem importing \"C:/FIL/JTAG/netlist/dac_mod_2_4_sim_cw.twx\": $eInfo"
}
