
open(PIDFILE, '> pidfile.txt') || die 'Couldn\'t write process ID to file.';
print PIDFILE "$$\n";
close(PIDFILE);

eval {
  # Call script(s).
  my $instrs;
  my $results = [];
$ENV{'SYSGEN'} = 'C:/Xilinx/14.7/ISE_DS/ISE/sysgen';
  use Sg;
  $instrs = {
    'HDLCodeGenStatus' => 0.0,
    'HDL_PATH' => 'C:/FIL/JTAG',
    'Impl_file' => 'ISE Defaults',
    'Impl_file_sgadvanced' => '',
    'Synth_file' => 'XST Defaults',
    'Synth_file_sgadvanced' => '',
    'TEMP' => 'C:/Users/o_cotte/AppData/Local/Temp',
    'TMP' => 'C:/Users/o_cotte/AppData/Local/Temp',
    'Temp' => 'C:/Users/o_cotte/AppData/Local/Temp',
    'Tmp' => 'C:/Users/o_cotte/AppData/Local/Temp',
    'base_system_period_hardware' => 2.0345052083333335,
    'base_system_period_simulink' => 2.0345052083333334E-9,
    'block_icon_display' => 'Default',
    'block_type' => 'sysgen',
    'block_version' => '',
    'ce_clr' => 0.0,
    'clock_domain' => 'default',
    'clock_loc' => 'Fixed',
    'clock_wrapper' => 'Clock Enables',
    'clock_wrapper_sgadvanced' => '',
    'compilation' => 'Atlys_491_52',
    'compilation_lut' => {
      'keys' => [
        'HDL Netlist',
        'Atlys',
        'Atlys_491_52',
      ],
      'values' => [
        'target1',
        'target2',
        'target3',
      ],
    },
    'compilation_target' => 'Atlys_491_52',
    'core_generation' => 1.0,
    'core_generation_sgadvanced' => '',
    'core_is_deployed' => 0.0,
    'coregen_core_generation_tmpdir' => 'C:/Users/o_cotte/AppData/Local/Temp/sysgentmp-o_cotte/cg_wk/c78485218a994fe42',
    'coregen_part_family' => 'spartan6',
    'createTestbench' => 0,
    'create_interface_document' => 'off',
    'dbl_ovrd' => -1.0,
    'dbl_ovrd_sgadvanced' => '',
    'dcm_input_clock_period' => 10.0,
    'deprecated_control' => 'off',
    'deprecated_control_sgadvanced' => '',
    'design' => 'DAC_MOD_5_SIM',
    'design_full_path' => 'C:\\FIL\\JTAG\\DAC_MOD_5_SIM.slx',
    'device' => 'xc6slx45-3csg324',
    'device_speed' => '-3',
    'directory' => 'C:/FIL/JTAG/netlist',
    'dsp_cache_root_path' => 'C:/Users/o_cotte/AppData/Local/Temp/sysgentmp-o_cotte',
    'eval_field' => '0',
    'fileDeliveryDefaults' => [
      [
        '(?i)\\.vhd$',
        { 'fileName' => 'C:/FIL/JTAG/netlist/sysgen/perl_results.vhd', },
      ],
      [
        '(?i)\\.v$',
        { 'fileName' => 'C:/FIL/JTAG/netlist/sysgen/perl_results.v', },
      ],
    ],
    'force_scheduling' => 0.0,
    'fxdptinstalled' => 1.0,
    'generateUsing71FrontEnd' => 1,
    'generating_island_subsystem_handle' => 2079.0003662109375,
    'generating_subsystem_handle' => 2079.0003662109375,
    'generation_directory' => './netlist',
    'getimportblock_fcn' => 'xlGetHwcosimBlockName',
    'has_advanced_control' => '0',
    'hdlDir' => 'C:/Xilinx/14.7/ISE_DS/ISE/sysgen/hdl',
    'hdlKind' => 'vhdl',
    'hdl_path' => 'C:/FIL/JTAG',
    'impl_file' => 'ISE Defaults*',
    'incr_netlist' => 'off',
    'incr_netlist_sgadvanced' => '',
    'infoedit' => ' System Generator',
    'isdeployed' => 0,
    'ise_version' => '14.7i',
    'master_sysgen_token_handle' => 2080.0003662109375,
    'matlab' => 'C:/Program Files/MATLAB/R2013b',
    'matlab_fixedpoint' => 1.0,
    'mdlHandle' => 2079.0003662109375,
    'mdlPath' => 'C:/FIL/JTAG/DAC_MOD_5_SIM.mdl',
    'modelDiagnostics' => [
      {
        'count' => 338.0,
        'isMask' => 0.0,
        'type' => 'DAC_MOD_5_SIM Total blocks',
      },
      {
        'count' => 2.0,
        'isMask' => 0.0,
        'type' => 'Constant',
      },
      {
        'count' => 2.0,
        'isMask' => 0.0,
        'type' => 'DataTypeDuplicate',
      },
      {
        'count' => 89.0,
        'isMask' => 0.0,
        'type' => 'Delay',
      },
      {
        'count' => 2.0,
        'isMask' => 0.0,
        'type' => 'DiscretePulseGenerator',
      },
      {
        'count' => 90.0,
        'isMask' => 0.0,
        'type' => 'Gain',
      },
      {
        'count' => 7.0,
        'isMask' => 0.0,
        'type' => 'Inport',
      },
      {
        'count' => 1.0,
        'isMask' => 0.0,
        'type' => 'MultiPortSwitch',
      },
      {
        'count' => 11.0,
        'isMask' => 0.0,
        'type' => 'Outport',
      },
      {
        'count' => 31.0,
        'isMask' => 0.0,
        'type' => 'S-Function',
      },
      {
        'count' => 1.0,
        'isMask' => 0.0,
        'type' => 'SignalSpecification',
      },
      {
        'count' => 8.0,
        'isMask' => 0.0,
        'type' => 'SubSystem',
      },
      {
        'count' => 89.0,
        'isMask' => 0.0,
        'type' => 'Sum',
      },
      {
        'count' => 1.0,
        'isMask' => 0.0,
        'type' => 'Switch',
      },
      {
        'count' => 2.0,
        'isMask' => 0.0,
        'type' => 'Terminator',
      },
      {
        'count' => 1.0,
        'isMask' => 0.0,
        'type' => 'ToWorkspace',
      },
      {
        'count' => 1.0,
        'isMask' => 0.0,
        'type' => 'UnitDelay',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Counter Limited',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Data Type Propagation',
      },
      {
        'count' => 3.0,
        'isMask' => 1.0,
        'type' => 'FIR Interpolation',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Real World Value Increment',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Sine Wave',
      },
      {
        'count' => 2.0,
        'isMask' => 1.0,
        'type' => 'Upsample',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Wrap To Zero',
      },
      {
        'count' => 5.0,
        'isMask' => 1.0,
        'type' => 'Xilinx Accumulator Block',
      },
      {
        'count' => 7.0,
        'isMask' => 1.0,
        'type' => 'Xilinx Adder/Subtracter Block',
      },
      {
        'count' => 8.0,
        'isMask' => 1.0,
        'type' => 'Xilinx Constant Multiplier Block',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Xilinx Gateway In Block',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Xilinx Gateway Out Block',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Xilinx System Generator Block',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Xilinx Threshold Block',
      },
      {
        'count' => 1.0,
        'isMask' => 1.0,
        'type' => 'Xilinx Type Converter Block',
      },
    ],
    'model_globals_initialized' => 1.0,
    'model_path' => 'C:/FIL/JTAG/DAC_MOD_5_SIM.mdl',
    'myxilinx' => 'C:/Xilinx/14.7/ISE_DS/ISE',
    'ngc_files' => [ 'xlpersistentdff.ngc', ],
    'num_sim_cycles' => '8192',
    'package' => 'csg324',
    'part' => 'xc6slx45',
    'partFamily' => 'spartan6',
    'port_data_types_enabled' => 1.0,
    'postgeneration_fcn' => 'atlys_postgeneration',
    'precompile_fcn' => 'xlJTAGPreCompile',
    'preserve_hierarchy' => 0.0,
    'proj_type' => 'Project Navigator',
    'proj_type_sgadvanced' => '',
    'report_true_rates' => 0.0,
    'run_coregen' => 'off',
    'run_coregen_sgadvanced' => '',
    'sample_time_colors_enabled' => 1.0,
    'sampletimecolors' => 1.0,
    'settings_fcn' => 'xlJTAGXFlowSettings',
    'sg_blockgui_xml' => '',
    'sg_icon_stat' => '50,50,-1,-1,token,white,0,07734,right,,[ ],[ ]',
    'sg_list_contents' => '',
    'sg_mask_display' => 'fprintf(\'\',\'COMMENT: begin icon graphics\');
patch([0 50 50 0 0 ],[0 0 50 50 0 ],[1 1 1 ]);
patch([1.6375 16.81 27.31 37.81 48.31 27.31 12.1375 1.6375 ],[36.655 36.655 47.155 36.655 47.155 47.155 47.155 36.655 ],[0.933333 0.203922 0.141176 ]);
patch([12.1375 27.31 16.81 1.6375 12.1375 ],[26.155 26.155 36.655 36.655 26.155 ],[0.698039 0.0313725 0.219608 ]);
patch([1.6375 16.81 27.31 12.1375 1.6375 ],[15.655 15.655 26.155 26.155 15.655 ],[0.933333 0.203922 0.141176 ]);
patch([12.1375 48.31 37.81 27.31 16.81 1.6375 12.1375 ],[5.155 5.155 15.655 5.155 15.655 15.655 5.155 ],[0.698039 0.0313725 0.219608 ]);
fprintf(\'\',\'COMMENT: end icon graphics\');
fprintf(\'\',\'COMMENT: begin icon text\');
fprintf(\'\',\'COMMENT: end icon text\');',
    'sg_version' => '',
    'sggui_pos' => '-1,-1,-1,-1',
    'simulation_island_subsystem_handle' => 2079.0003662109375,
    'simulink_accelerator_running' => 0.0,
    'simulink_debugger_running' => 0.0,
    'simulink_period' => 2.0345052083333334E-9,
    'speed' => '-3',
    'synth_file' => 'XST Defaults*',
    'synthesisTool' => 'XST',
    'synthesis_language' => 'vhdl',
    'synthesis_tool' => 'XST',
    'synthesis_tool_sgadvanced' => '',
    'sysclk_period' => 2.0345052083333335,
    'sysgen' => 'C:/Xilinx/14.7/ISE_DS/ISE/sysgen',
    'sysgenRoot' => 'C:/Xilinx/14.7/ISE_DS/ISE/sysgen',
    'sysgenTokenSettings' => {
      'Impl_file' => 'ISE Defaults',
      'Impl_file_sgadvanced' => '',
      'Synth_file' => 'XST Defaults',
      'Synth_file_sgadvanced' => '',
      'base_system_period_hardware' => 2.0345052083333335,
      'base_system_period_simulink' => 2.0345052083333334E-9,
      'block_icon_display' => 'Default',
      'block_type' => 'sysgen',
      'block_version' => '',
      'ce_clr' => 0.0,
      'clock_loc' => 'Fixed',
      'clock_wrapper' => 'Clock Enables',
      'clock_wrapper_sgadvanced' => '',
      'compilation' => 'Atlys_491_52',
      'compilation_lut' => {
        'keys' => [
          'HDL Netlist',
          'Atlys',
          'Atlys_491_52',
        ],
        'values' => [
          'target1',
          'target2',
          'target3',
        ],
      },
      'core_generation' => 1.0,
      'core_generation_sgadvanced' => '',
      'coregen_part_family' => 'spartan6',
      'create_interface_document' => 'off',
      'dbl_ovrd' => -1.0,
      'dbl_ovrd_sgadvanced' => '',
      'dcm_input_clock_period' => 10.0,
      'deprecated_control' => 'off',
      'deprecated_control_sgadvanced' => '',
      'directory' => './netlist',
      'eval_field' => '0',
      'getimportblock_fcn' => 'xlGetHwcosimBlockName',
      'has_advanced_control' => '0',
      'impl_file' => 'ISE Defaults*',
      'incr_netlist' => 'off',
      'incr_netlist_sgadvanced' => '',
      'infoedit' => ' System Generator',
      'master_sysgen_token_handle' => 2080.0003662109375,
      'package' => 'csg324',
      'part' => 'xc6slx45',
      'postgeneration_fcn' => 'atlys_postgeneration',
      'precompile_fcn' => 'xlJTAGPreCompile',
      'preserve_hierarchy' => 0.0,
      'proj_type' => 'Project Navigator',
      'proj_type_sgadvanced' => '',
      'run_coregen' => 'off',
      'run_coregen_sgadvanced' => '',
      'settings_fcn' => 'xlJTAGXFlowSettings',
      'sg_blockgui_xml' => '',
      'sg_icon_stat' => '50,50,-1,-1,token,white,0,07734,right,,[ ],[ ]',
      'sg_list_contents' => '',
      'sg_mask_display' => 'fprintf(\'\',\'COMMENT: begin icon graphics\');
patch([0 50 50 0 0 ],[0 0 50 50 0 ],[1 1 1 ]);
patch([1.6375 16.81 27.31 37.81 48.31 27.31 12.1375 1.6375 ],[36.655 36.655 47.155 36.655 47.155 47.155 47.155 36.655 ],[0.933333 0.203922 0.141176 ]);
patch([12.1375 27.31 16.81 1.6375 12.1375 ],[26.155 26.155 36.655 36.655 26.155 ],[0.698039 0.0313725 0.219608 ]);
patch([1.6375 16.81 27.31 12.1375 1.6375 ],[15.655 15.655 26.155 26.155 15.655 ],[0.933333 0.203922 0.141176 ]);
patch([12.1375 48.31 37.81 27.31 16.81 1.6375 12.1375 ],[5.155 5.155 15.655 5.155 15.655 15.655 5.155 ],[0.698039 0.0313725 0.219608 ]);
fprintf(\'\',\'COMMENT: end icon graphics\');
fprintf(\'\',\'COMMENT: begin icon text\');
fprintf(\'\',\'COMMENT: end icon text\');',
      'sggui_pos' => '-1,-1,-1,-1',
      'simulation_island_subsystem_handle' => 2079.0003662109375,
      'simulink_period' => 2.0345052083333334E-9,
      'speed' => '-3',
      'synth_file' => 'XST Defaults*',
      'synthesis_language' => 'vhdl',
      'synthesis_tool' => 'XST',
      'synthesis_tool_sgadvanced' => '',
      'sysclk_period' => 2.0345052083333335,
      'testbench' => 0,
      'testbench_sgadvanced' => '',
      'trim_vbits' => 1.0,
      'trim_vbits_sgadvanced' => '',
      'xilinx_device' => 'xc6slx45-3csg324',
      'xilinxfamily' => 'spartan6',
    },
    'sysgen_Root' => 'C:/Xilinx/14.7/ISE_DS/ISE/sysgen',
    'systemClockPeriod' => 2.0345052083333335,
    'tempdir' => 'C:/Users/o_cotte/AppData/Local/Temp',
    'testbench' => 0,
    'testbench_sgadvanced' => '',
    'tmpDir' => 'C:/FIL/JTAG/netlist/sysgen',
    'trim_vbits' => 1.0,
    'trim_vbits_sgadvanced' => '',
    'use_strict_names' => 1,
    'user_tips_enabled' => 0.0,
    'usertemp' => 'C:/Users/o_cotte/AppData/Local/Temp/sysgentmp-o_cotte',
    'using71Netlister' => 1,
    'verilog_files' => [
      'conv_pkg.v',
      'synth_reg.v',
      'synth_reg_w_init.v',
      'convert_type.v',
    ],
    'version' => '',
    'vhdl_files' => [
      'conv_pkg.vhd',
      'synth_reg.vhd',
      'synth_reg_w_init.vhd',
    ],
    'vsimtime' => '18608.666667 ns',
    'xilinx' => 'C:/Xilinx/14.7/ISE_DS/ISE',
    'xilinx_device' => 'xc6slx45-3csg324',
    'xilinx_family' => 'spartan6',
    'xilinx_package' => 'csg324',
    'xilinx_part' => 'xc6slx45',
    'xilinxdevice' => 'xc6slx45-3csg324',
    'xilinxfamily' => 'spartan6',
    'xilinxpart' => 'xc6slx45',
  };
  push(@$results, &Sg::setAttributes($instrs));
  use SgDeliverFile;
  $instrs = {
    'collaborationName' => 'conv_pkg.vhd',
    'sourceFile' => 'hdl/conv_pkg.vhd',
    'templateKeyValues' => {},
  };
  push(@$results, &SgDeliverFile::saveCollaborationInfo($instrs));
  $instrs = {
    'collaborationName' => 'synth_reg.vhd',
    'sourceFile' => 'hdl/synth_reg.vhd',
    'templateKeyValues' => {},
  };
  push(@$results, &SgDeliverFile::saveCollaborationInfo($instrs));
  $instrs = {
    'collaborationName' => 'synth_reg_w_init.vhd',
    'sourceFile' => 'hdl/synth_reg_w_init.vhd',
    'templateKeyValues' => {},
  };
  push(@$results, &SgDeliverFile::saveCollaborationInfo($instrs));
  $instrs = {
    'collaborationName' => 'xlpersistentdff.ngc',
    'sourceFile' => 'hdl/xlpersistentdff.ngc',
    'templateKeyValues' => {},
  };
  push(@$results, &SgDeliverFile::saveCollaborationInfo($instrs));
  $instrs = {
    'entity_declaration_hash' => '879fde236a9d533966b23f2f908ce373',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal b_17_24: signed((46 - 1) downto 0);
  signal accum_reg_41_23: signed((46 - 1) downto 0) := "0000000000000000000000000000000000000000000000";
begin
  b_17_24 <= std_logic_vector_to_signed(b);
  proc_accum_reg_41_23: process (clk)
  is
  begin
    if (clk\'event and (clk = \'1\')) then
      if (ce = \'1\') then
        accum_reg_41_23 <= accum_reg_41_23 + b_17_24;
      end if;
    end if;
  end process proc_accum_reg_41_23;
  q <= signed_to_std_logic_vector(accum_reg_41_23);
end',
      'crippled_entity' => 'is
  port (
    b : in std_logic_vector((46 - 1) downto 0);
    q : out std_logic_vector((46 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'accum_04e257417a',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  use SgGenerateCores;
  $instrs = [
    'SELECT Adder_Subtracter spartan6 Xilinx,_Inc. 11.0',
    '# 14.7_P.79',
    '# DEVICE spartan6',
    '# VHDL',
    'CSET AINIT_Value = 0',
    'CSET A_Type = Signed',
    'CSET A_Width = 47',
    'CSET Add_Mode = Subtract',
    'CSET B_Constant = false',
    'CSET B_Type = Signed',
    'CSET B_Value = 0',
    'CSET B_Width = 47',
    'CSET Borrow_Sense = Active_Low',
    'CSET Bypass = false',
    'CSET Bypass_CE_Priority = Bypass_Overrides_CE',
    'CSET Bypass_Sense = Active_Low',
    'CSET CE = false',
    'CSET C_In = false',
    'CSET C_Out = false',
    'CSET Implementation = DSP48',
    'CSET Latency = 0',
    'CSET Out_Width = 47',
    'CSET SCLR = false',
    'CSET SINIT = false',
    'CSET SINIT_Value = 0',
    'CSET SSET = false',
    'CSET Sync_CE_Priority = Sync_Overrides_CE',
    'CSET Sync_Ctrl_Priority = Reset_Overrides_Set',
    'CSET component_name = addsb_11_0_378a84205e17796b',
    'GENERATE',
  ];
  push(@$results, &SgGenerateCores::saveXcoSequence($instrs));
  $instrs = {
    'entity_declaration_hash' => '1604e5ac798f7d3af6302c8a3ed1a38f',
    'sourceFile' => 'hdl/xladdsub.vhd',
    'templateKeyValues' => {
      'core_component_def' => '    a: in std_logic_vector(47 - 1 downto 0);
    s: out std_logic_vector(c_output_width - 1 downto 0);
    b: in std_logic_vector(47 - 1 downto 0)',
      'core_instance_text' => '         a => full_a,
         s => core_s,
         b => full_b',
      'core_name0' => 'addsb_11_0_378a84205e17796b',
      'entityName' => 'xladdsub_DAC_MOD_5_SIM',
      'entity_name.0' => 'xladdsub',
      'needs_core' => 1,
      'vivado_flow' => 0,
    },
  };
  push(@$results, &SgDeliverFile::saveCollaborationInfo($instrs));
  $instrs = {
    'entity_declaration_hash' => 'd934a4c8017b7d983a6113408e27571e',
    'sourceFile' => 'C:/Xilinx/14.7/ISE_DS/ISE/sysgen/hdl/xlconvert.vhd',
  };
  push(@$results, &SgDeliverFile::saveCollaborationInfo($instrs));
  $instrs = {
    'entity_declaration_hash' => 'b5274bd0f4ea7f575b692a455d509487',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal x_1_20: signed((46 - 1) downto 0);
  signal slice_5_41: unsigned((1 - 1) downto 0);
  signal concat_5_32: unsigned((2 - 1) downto 0);
  signal unregy_5_5_force: signed((2 - 1) downto 0);
begin
  x_1_20 <= std_logic_vector_to_signed(x);
  slice_5_41 <= s2u_slice(x_1_20, 45, 45);
  concat_5_32 <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(slice_5_41) & unsigned_to_std_logic_vector(std_logic_vector_to_unsigned("1")));
  unregy_5_5_force <= unsigned_to_signed(concat_5_32);
  y <= signed_to_std_logic_vector(unregy_5_5_force);
end',
      'crippled_entity' => 'is
  port (
    x : in std_logic_vector((46 - 1) downto 0);
    y : out std_logic_vector((2 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'sgn_5729cb6742',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  $instrs = {
    'entity_declaration_hash' => 'ae8b7f972243b1912a038ad579e4f58d',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal a_1_22: signed((46 - 1) downto 0);
  type array_type_op_mem_71_20 is array (0 to (1 - 1)) of signed((46 - 1) downto 0);
  signal op_mem_71_20: array_type_op_mem_71_20 := (
    0 => "0000000000000000000000000000000000000000000000");
  signal op_mem_71_20_front_din: signed((46 - 1) downto 0);
  signal op_mem_71_20_back: signed((46 - 1) downto 0);
  signal op_mem_71_20_push_front_pop_back_en: std_logic;
  signal mult_52_58: signed((93 - 1) downto 0);
  signal cast_product_52_5_convert: signed((92 - 1) downto 0);
  signal cast_product_61_3_convert: signed((46 - 1) downto 0);
begin
  a_1_22 <= std_logic_vector_to_signed(a);
  op_mem_71_20_back <= op_mem_71_20(0);
  proc_op_mem_71_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk\'event and (clk = \'1\')) then
      if ((ce = \'1\') and (op_mem_71_20_push_front_pop_back_en = \'1\')) then
        op_mem_71_20(0) <= op_mem_71_20_front_din;
      end if;
    end if;
  end process proc_op_mem_71_20;
  mult_52_58 <= (a_1_22 * std_logic_vector_to_signed("00000000000000000110000011010010000100111100101"));
  cast_product_52_5_convert <= s2s_cast(mult_52_58, 80, 92, 80);
  cast_product_61_3_convert <= s2s_cast(cast_product_52_5_convert, 80, 46, 40);
  op_mem_71_20_push_front_pop_back_en <= \'0\';
  p <= signed_to_std_logic_vector(cast_product_61_3_convert);
end',
      'crippled_entity' => 'is
  port (
    a : in std_logic_vector((46 - 1) downto 0);
    p : out std_logic_vector((46 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'cmult_069b545419',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  $instrs = {
    'entity_declaration_hash' => '0859c1d78dadd9f7f4c771f53b13d551',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal a_1_22: signed((46 - 1) downto 0);
  type array_type_op_mem_71_20 is array (0 to (1 - 1)) of signed((46 - 1) downto 0);
  signal op_mem_71_20: array_type_op_mem_71_20 := (
    0 => "0000000000000000000000000000000000000000000000");
  signal op_mem_71_20_front_din: signed((46 - 1) downto 0);
  signal op_mem_71_20_back: signed((46 - 1) downto 0);
  signal op_mem_71_20_push_front_pop_back_en: std_logic;
  signal mult_52_58: signed((93 - 1) downto 0);
  signal cast_product_52_5_convert: signed((92 - 1) downto 0);
  signal cast_product_61_3_convert: signed((46 - 1) downto 0);
begin
  a_1_22 <= std_logic_vector_to_signed(a);
  op_mem_71_20_back <= op_mem_71_20(0);
  proc_op_mem_71_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk\'event and (clk = \'1\')) then
      if ((ce = \'1\') and (op_mem_71_20_push_front_pop_back_en = \'1\')) then
        op_mem_71_20(0) <= op_mem_71_20_front_din;
      end if;
    end if;
  end process proc_op_mem_71_20;
  mult_52_58 <= (a_1_22 * std_logic_vector_to_signed("00000000000000111000101111110110000011011100111"));
  cast_product_52_5_convert <= s2s_cast(mult_52_58, 80, 92, 80);
  cast_product_61_3_convert <= s2s_cast(cast_product_52_5_convert, 80, 46, 40);
  op_mem_71_20_push_front_pop_back_en <= \'0\';
  p <= signed_to_std_logic_vector(cast_product_61_3_convert);
end',
      'crippled_entity' => 'is
  port (
    a : in std_logic_vector((46 - 1) downto 0);
    p : out std_logic_vector((46 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'cmult_cb03f3eccc',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  $instrs = {
    'entity_declaration_hash' => '7e6b1c8b2584a8170f123267b3c71880',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal a_1_22: signed((46 - 1) downto 0);
  type array_type_op_mem_71_20 is array (0 to (1 - 1)) of signed((46 - 1) downto 0);
  signal op_mem_71_20: array_type_op_mem_71_20 := (
    0 => "0000000000000000000000000000000000000000000000");
  signal op_mem_71_20_front_din: signed((46 - 1) downto 0);
  signal op_mem_71_20_back: signed((46 - 1) downto 0);
  signal op_mem_71_20_push_front_pop_back_en: std_logic;
  signal mult_52_58: signed((93 - 1) downto 0);
  signal cast_product_52_5_convert: signed((92 - 1) downto 0);
  signal cast_product_61_3_convert: signed((46 - 1) downto 0);
begin
  a_1_22 <= std_logic_vector_to_signed(a);
  op_mem_71_20_back <= op_mem_71_20(0);
  proc_op_mem_71_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk\'event and (clk = \'1\')) then
      if ((ce = \'1\') and (op_mem_71_20_push_front_pop_back_en = \'1\')) then
        op_mem_71_20(0) <= op_mem_71_20_front_din;
      end if;
    end if;
  end process proc_op_mem_71_20;
  mult_52_58 <= (a_1_22 * std_logic_vector_to_signed("00000000000110110011011100010110100101111111011"));
  cast_product_52_5_convert <= s2s_cast(mult_52_58, 80, 92, 80);
  cast_product_61_3_convert <= s2s_cast(cast_product_52_5_convert, 80, 46, 40);
  op_mem_71_20_push_front_pop_back_en <= \'0\';
  p <= signed_to_std_logic_vector(cast_product_61_3_convert);
end',
      'crippled_entity' => 'is
  port (
    a : in std_logic_vector((46 - 1) downto 0);
    p : out std_logic_vector((46 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'cmult_c754f0e813',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  $instrs = {
    'entity_declaration_hash' => 'b6108314fd32832937400aa4feae3814',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal a_1_22: signed((46 - 1) downto 0);
  type array_type_op_mem_71_20 is array (0 to (1 - 1)) of signed((46 - 1) downto 0);
  signal op_mem_71_20: array_type_op_mem_71_20 := (
    0 => "0000000000000000000000000000000000000000000000");
  signal op_mem_71_20_front_din: signed((46 - 1) downto 0);
  signal op_mem_71_20_back: signed((46 - 1) downto 0);
  signal op_mem_71_20_push_front_pop_back_en: std_logic;
  signal mult_52_58: signed((93 - 1) downto 0);
  signal cast_product_52_5_convert: signed((92 - 1) downto 0);
  signal cast_product_61_3_convert: signed((46 - 1) downto 0);
begin
  a_1_22 <= std_logic_vector_to_signed(a);
  op_mem_71_20_back <= op_mem_71_20(0);
  proc_op_mem_71_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk\'event and (clk = \'1\')) then
      if ((ce = \'1\') and (op_mem_71_20_push_front_pop_back_en = \'1\')) then
        op_mem_71_20(0) <= op_mem_71_20_front_din;
      end if;
    end if;
  end process proc_op_mem_71_20;
  mult_52_58 <= (a_1_22 * std_logic_vector_to_signed("00000000011100010011100011001010111011110101110"));
  cast_product_52_5_convert <= s2s_cast(mult_52_58, 80, 92, 80);
  cast_product_61_3_convert <= s2s_cast(cast_product_52_5_convert, 80, 46, 40);
  op_mem_71_20_push_front_pop_back_en <= \'0\';
  p <= signed_to_std_logic_vector(cast_product_61_3_convert);
end',
      'crippled_entity' => 'is
  port (
    a : in std_logic_vector((46 - 1) downto 0);
    p : out std_logic_vector((46 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'cmult_9dd1c9e77a',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  $instrs = {
    'entity_declaration_hash' => 'fc8c47f1b1e1cd44c56239636c592a86',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal a_1_22: signed((46 - 1) downto 0);
  type array_type_op_mem_71_20 is array (0 to (1 - 1)) of signed((46 - 1) downto 0);
  signal op_mem_71_20: array_type_op_mem_71_20 := (
    0 => "0000000000000000000000000000000000000000000000");
  signal op_mem_71_20_front_din: signed((46 - 1) downto 0);
  signal op_mem_71_20_back: signed((46 - 1) downto 0);
  signal op_mem_71_20_push_front_pop_back_en: std_logic;
  signal mult_52_58: signed((93 - 1) downto 0);
  signal cast_product_52_5_convert: signed((92 - 1) downto 0);
  signal cast_product_61_3_convert: signed((46 - 1) downto 0);
begin
  a_1_22 <= std_logic_vector_to_signed(a);
  op_mem_71_20_back <= op_mem_71_20(0);
  proc_op_mem_71_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk\'event and (clk = \'1\')) then
      if ((ce = \'1\') and (op_mem_71_20_push_front_pop_back_en = \'1\')) then
        op_mem_71_20(0) <= op_mem_71_20_front_din;
      end if;
    end if;
  end process proc_op_mem_71_20;
  mult_52_58 <= (a_1_22 * std_logic_vector_to_signed("00000001001000010100010110010000101110000110100"));
  cast_product_52_5_convert <= s2s_cast(mult_52_58, 80, 92, 80);
  cast_product_61_3_convert <= s2s_cast(cast_product_52_5_convert, 80, 46, 40);
  op_mem_71_20_push_front_pop_back_en <= \'0\';
  p <= signed_to_std_logic_vector(cast_product_61_3_convert);
end',
      'crippled_entity' => 'is
  port (
    a : in std_logic_vector((46 - 1) downto 0);
    p : out std_logic_vector((46 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'cmult_722f29eb1c',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  $instrs = {
    'entity_declaration_hash' => '8cc8947b348ded93d85a72994ed01d83',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal a_1_22: signed((46 - 1) downto 0);
  type array_type_op_mem_71_20 is array (0 to (1 - 1)) of signed((46 - 1) downto 0);
  signal op_mem_71_20: array_type_op_mem_71_20 := (
    0 => "0000000000000000000000000000000000000000000000");
  signal op_mem_71_20_front_din: signed((46 - 1) downto 0);
  signal op_mem_71_20_back: signed((46 - 1) downto 0);
  signal op_mem_71_20_push_front_pop_back_en: std_logic;
  signal mult_52_58: signed((93 - 1) downto 0);
  signal cast_product_52_5_convert: signed((92 - 1) downto 0);
  signal cast_product_61_3_convert: signed((46 - 1) downto 0);
begin
  a_1_22 <= std_logic_vector_to_signed(a);
  op_mem_71_20_back <= op_mem_71_20(0);
  proc_op_mem_71_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk\'event and (clk = \'1\')) then
      if ((ce = \'1\') and (op_mem_71_20_push_front_pop_back_en = \'1\')) then
        op_mem_71_20(0) <= op_mem_71_20_front_din;
      end if;
    end if;
  end process proc_op_mem_71_20;
  mult_52_58 <= (a_1_22 * std_logic_vector_to_signed("00000000000001011011011111010001010110100011001"));
  cast_product_52_5_convert <= s2s_cast(mult_52_58, 80, 92, 80);
  cast_product_61_3_convert <= s2s_cast(cast_product_52_5_convert, 80, 46, 40);
  op_mem_71_20_push_front_pop_back_en <= \'0\';
  p <= signed_to_std_logic_vector(cast_product_61_3_convert);
end',
      'crippled_entity' => 'is
  port (
    a : in std_logic_vector((46 - 1) downto 0);
    p : out std_logic_vector((46 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'cmult_241e5f2332',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  $instrs = {
    'entity_declaration_hash' => '053ab7119edfdad824ecd65fdc6c093f',
    'sourceFile' => 'hdl/xlmcode.vhd',
    'templateKeyValues' => {
      'crippled_architecture' => 'is
  signal a_1_22: signed((46 - 1) downto 0);
  type array_type_op_mem_71_20 is array (0 to (1 - 1)) of signed((46 - 1) downto 0);
  signal op_mem_71_20: array_type_op_mem_71_20 := (
    0 => "0000000000000000000000000000000000000000000000");
  signal op_mem_71_20_front_din: signed((46 - 1) downto 0);
  signal op_mem_71_20_back: signed((46 - 1) downto 0);
  signal op_mem_71_20_push_front_pop_back_en: std_logic;
  signal mult_52_58: signed((93 - 1) downto 0);
  signal cast_product_52_5_convert: signed((92 - 1) downto 0);
  signal cast_product_61_3_convert: signed((46 - 1) downto 0);
begin
  a_1_22 <= std_logic_vector_to_signed(a);
  op_mem_71_20_back <= op_mem_71_20(0);
  proc_op_mem_71_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk\'event and (clk = \'1\')) then
      if ((ce = \'1\') and (op_mem_71_20_push_front_pop_back_en = \'1\')) then
        op_mem_71_20(0) <= op_mem_71_20_front_din;
      end if;
    end if;
  end process proc_op_mem_71_20;
  mult_52_58 <= (a_1_22 * std_logic_vector_to_signed("00000000000100000010101010010111001001010010100"));
  cast_product_52_5_convert <= s2s_cast(mult_52_58, 80, 92, 80);
  cast_product_61_3_convert <= s2s_cast(cast_product_52_5_convert, 80, 46, 40);
  op_mem_71_20_push_front_pop_back_en <= \'0\';
  p <= signed_to_std_logic_vector(cast_product_61_3_convert);
end',
      'crippled_entity' => 'is
  port (
    a : in std_logic_vector((46 - 1) downto 0);
    p : out std_logic_vector((46 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end',
      'entity_name' => 'cmult_1692099eb8',
    },
  };
  push(@$results, &SgDeliverFile::deliverFile($instrs));
  local *wrapup = $Sg::{'wrapup'};
  push(@$results, &Sg::wrapup())   if (defined(&wrapup));
  local *wrapup = $SgDeliverFile::{'wrapup'};
  push(@$results, &SgDeliverFile::wrapup())   if (defined(&wrapup));
  local *wrapup = $SgGenerateCores::{'wrapup'};
  push(@$results, &SgGenerateCores::wrapup())   if (defined(&wrapup));
  use Carp qw(croak);
  $ENV{'SYSGEN'} = 'C:/Xilinx/14.7/ISE_DS/ISE/sysgen';
  open(RESULTS, '> C:/FIL/JTAG/netlist/sysgen/script_results8454824489245775422') || 
    croak 'couldn\'t open C:/FIL/JTAG/netlist/sysgen/script_results8454824489245775422';
  binmode(RESULTS);
  print RESULTS &Sg::toString($results) . "\n";
  close(RESULTS) || 
    croak 'trouble writing C:/FIL/JTAG/netlist/sysgen/script_results8454824489245775422';
};

if ($@) {
  open(RESULTS, '> C:/FIL/JTAG/netlist/sysgen/script_results8454824489245775422') || 
    croak 'couldn\'t open C:/FIL/JTAG/netlist/sysgen/script_results8454824489245775422';
  binmode(RESULTS);
  print RESULTS $@ . "\n";
  close(RESULTS) || 
    croak 'trouble writing C:/FIL/JTAG/netlist/sysgen/script_results8454824489245775422';
  exit(1);
}

exit(0);
