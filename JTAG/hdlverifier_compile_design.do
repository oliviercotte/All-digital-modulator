# Create design library
vlib work
# Create and open project
project new . compile_project
project open compile_project
# Add source files to project
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/all_digital_modulator.vhd"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/Halfband_4_491_52.vhd"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/PLL_CLOCK.vhd"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/float_pkg_c.vhdl"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/fixed_pkg_c.vhdl"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/fixed_float_types_c.vhdl"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Clock_Generator_1.vhd"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/dds.vhd"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Halfband_1_61_44.vhd"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Halfband_2_122_88.vhd"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Halfband_3_245_76.vhd"
project addfile "C:/Newcomputer/DSM_Final/DSM_Final/ipcore_dir/Channel_Filter.vhd"
# Calculate compilation order
project calculateorder
set compcmd [project compileall -n]
# Close project
project close
# Compile all files and report error
if [catch {eval $compcmd}] {
    exit -code 1
}
