library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "DAC_MOD_5_SIM"

entity dac_mod_5_sim is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    gateway_in: in std_logic_vector(45 downto 0); 
    gateway_out3: out std_logic_vector(1 downto 0)
  );
end dac_mod_5_sim;

architecture structural of dac_mod_5_sim is
  attribute core_generation_info: string;
  attribute core_generation_info of structural : architecture is "DAC_MOD_5_SIM,sysgen_core,{clock_period=2.03450521,clocking=Clock_Enables,sample_periods=1.00000000000,testbench=0,total_blocks=338,xilinx_accumulator_block=5,xilinx_adder_subtracter_block=7,xilinx_constant_multiplier_block=8,xilinx_gateway_in_block=1,xilinx_gateway_out_block=1,xilinx_system_generator_block=1,xilinx_threshold_block=1,xilinx_type_converter_block=1,}";

  signal a31_p_net: std_logic_vector(45 downto 0);
  signal a32_p_net: std_logic_vector(45 downto 0);
  signal a33_p_net: std_logic_vector(45 downto 0);
  signal a34_p_net: std_logic_vector(45 downto 0);
  signal a35_p_net: std_logic_vector(45 downto 0);
  signal accumulator12_q_net: std_logic_vector(45 downto 0);
  signal accumulator13_q_net: std_logic_vector(45 downto 0);
  signal accumulator14_q_net: std_logic_vector(45 downto 0);
  signal accumulator15_q_net: std_logic_vector(45 downto 0);
  signal accumulator16_q_net: std_logic_vector(45 downto 0);
  signal addsub18_s_net: std_logic_vector(45 downto 0);
  signal addsub19_s_net: std_logic_vector(45 downto 0);
  signal addsub20_s_net: std_logic_vector(45 downto 0);
  signal addsub21_s_net: std_logic_vector(45 downto 0);
  signal addsub22_s_net: std_logic_vector(45 downto 0);
  signal addsub23_s_net: std_logic_vector(45 downto 0);
  signal addsub24_s_net: std_logic_vector(45 downto 0);
  signal b31_p_net: std_logic_vector(45 downto 0);
  signal ce_1_sg_x0: std_logic;
  signal clk_1_sg_x0: std_logic;
  signal error_feedback: std_logic_vector(45 downto 0);
  signal gateway_in_net: std_logic_vector(45 downto 0);
  signal gateway_out3_net: std_logic_vector(1 downto 0);
  signal resonator_feedback: std_logic_vector(45 downto 0);
  signal resonator_feedback_x0: std_logic_vector(45 downto 0);

begin
  ce_1_sg_x0 <= ce_1;
  clk_1_sg_x0 <= clk_1;
  gateway_in_net <= gateway_in;
  gateway_out3 <= gateway_out3_net;

  a31: entity work.cmult_069b545419
    port map (
      a => error_feedback,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      p => a31_p_net
    );

  a32: entity work.cmult_cb03f3eccc
    port map (
      a => error_feedback,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      p => a32_p_net
    );

  a33: entity work.cmult_c754f0e813
    port map (
      a => error_feedback,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      p => a33_p_net
    );

  a34: entity work.cmult_9dd1c9e77a
    port map (
      a => error_feedback,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      p => a34_p_net
    );

  a35: entity work.cmult_722f29eb1c
    port map (
      a => error_feedback,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      p => a35_p_net
    );

  accumulator12: entity work.accum_04e257417a
    port map (
      b => addsub19_s_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      q => accumulator12_q_net
    );

  accumulator13: entity work.accum_04e257417a
    port map (
      b => addsub20_s_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      q => accumulator13_q_net
    );

  accumulator14: entity work.accum_04e257417a
    port map (
      b => addsub22_s_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      q => accumulator14_q_net
    );

  accumulator15: entity work.accum_04e257417a
    port map (
      b => addsub23_s_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      q => accumulator15_q_net
    );

  accumulator16: entity work.accum_04e257417a
    port map (
      b => addsub18_s_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      q => accumulator16_q_net
    );

  addsub18: entity work.xladdsub_DAC_MOD_5_SIM
    generic map (
      a_arith => xlSigned,
      a_bin_pt => 40,
      a_width => 46,
      b_arith => xlSigned,
      b_bin_pt => 40,
      b_width => 46,
      c_has_c_out => 0,
      c_latency => 0,
      c_output_width => 47,
      core_name0 => "addsb_11_0_378a84205e17796b",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 47,
      latency => 0,
      overflow => 1,
      quantization => 1,
      s_arith => xlSigned,
      s_bin_pt => 40,
      s_width => 46
    )
    port map (
      a => b31_p_net,
      b => a31_p_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      en => "1",
      s => addsub18_s_net
    );

  addsub19: entity work.xladdsub_DAC_MOD_5_SIM
    generic map (
      a_arith => xlSigned,
      a_bin_pt => 40,
      a_width => 46,
      b_arith => xlSigned,
      b_bin_pt => 40,
      b_width => 46,
      c_has_c_out => 0,
      c_latency => 0,
      c_output_width => 47,
      core_name0 => "addsb_11_0_378a84205e17796b",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 47,
      latency => 0,
      overflow => 1,
      quantization => 1,
      s_arith => xlSigned,
      s_bin_pt => 40,
      s_width => 46
    )
    port map (
      a => addsub24_s_net,
      b => resonator_feedback,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      en => "1",
      s => addsub19_s_net
    );

  addsub20: entity work.xladdsub_DAC_MOD_5_SIM
    generic map (
      a_arith => xlSigned,
      a_bin_pt => 40,
      a_width => 46,
      b_arith => xlSigned,
      b_bin_pt => 40,
      b_width => 46,
      c_has_c_out => 0,
      c_latency => 0,
      c_output_width => 47,
      core_name0 => "addsb_11_0_378a84205e17796b",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 47,
      latency => 0,
      overflow => 1,
      quantization => 1,
      s_arith => xlSigned,
      s_bin_pt => 40,
      s_width => 46
    )
    port map (
      a => accumulator12_q_net,
      b => a33_p_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      en => "1",
      s => addsub20_s_net
    );

  addsub21: entity work.xladdsub_DAC_MOD_5_SIM
    generic map (
      a_arith => xlSigned,
      a_bin_pt => 40,
      a_width => 46,
      b_arith => xlSigned,
      b_bin_pt => 40,
      b_width => 46,
      c_has_c_out => 0,
      c_latency => 0,
      c_output_width => 47,
      core_name0 => "addsb_11_0_378a84205e17796b",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 47,
      latency => 0,
      overflow => 1,
      quantization => 1,
      s_arith => xlSigned,
      s_bin_pt => 40,
      s_width => 46
    )
    port map (
      a => accumulator13_q_net,
      b => a34_p_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      en => "1",
      s => addsub21_s_net
    );

  addsub22: entity work.xladdsub_DAC_MOD_5_SIM
    generic map (
      a_arith => xlSigned,
      a_bin_pt => 40,
      a_width => 46,
      b_arith => xlSigned,
      b_bin_pt => 40,
      b_width => 46,
      c_has_c_out => 0,
      c_latency => 0,
      c_output_width => 47,
      core_name0 => "addsb_11_0_378a84205e17796b",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 47,
      latency => 0,
      overflow => 1,
      quantization => 1,
      s_arith => xlSigned,
      s_bin_pt => 40,
      s_width => 46
    )
    port map (
      a => addsub21_s_net,
      b => resonator_feedback_x0,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      en => "1",
      s => addsub22_s_net
    );

  addsub23: entity work.xladdsub_DAC_MOD_5_SIM
    generic map (
      a_arith => xlSigned,
      a_bin_pt => 40,
      a_width => 46,
      b_arith => xlSigned,
      b_bin_pt => 40,
      b_width => 46,
      c_has_c_out => 0,
      c_latency => 0,
      c_output_width => 47,
      core_name0 => "addsb_11_0_378a84205e17796b",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 47,
      latency => 0,
      overflow => 1,
      quantization => 1,
      s_arith => xlSigned,
      s_bin_pt => 40,
      s_width => 46
    )
    port map (
      a => accumulator14_q_net,
      b => a35_p_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      en => "1",
      s => addsub23_s_net
    );

  addsub24: entity work.xladdsub_DAC_MOD_5_SIM
    generic map (
      a_arith => xlSigned,
      a_bin_pt => 40,
      a_width => 46,
      b_arith => xlSigned,
      b_bin_pt => 40,
      b_width => 46,
      c_has_c_out => 0,
      c_latency => 0,
      c_output_width => 47,
      core_name0 => "addsb_11_0_378a84205e17796b",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 47,
      latency => 0,
      overflow => 1,
      quantization => 1,
      s_arith => xlSigned,
      s_bin_pt => 40,
      s_width => 46
    )
    port map (
      a => accumulator16_q_net,
      b => a32_p_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      en => "1",
      s => addsub24_s_net
    );

  b31: entity work.cmult_069b545419
    port map (
      a => gateway_in_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      p => b31_p_net
    );

  convert3: entity work.xlconvert
    generic map (
      bool_conversion => 0,
      din_arith => 2,
      din_bin_pt => 0,
      din_width => 2,
      dout_arith => 2,
      dout_bin_pt => 40,
      dout_width => 46,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      din => gateway_out3_net,
      en => "1",
      dout => error_feedback
    );

  g31: entity work.cmult_241e5f2332
    port map (
      a => accumulator13_q_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      p => resonator_feedback
    );

  g32: entity work.cmult_1692099eb8
    port map (
      a => accumulator15_q_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      p => resonator_feedback_x0
    );

  threshold3: entity work.sgn_5729cb6742
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      x => accumulator15_q_net,
      y => gateway_out3_net
    );

end structural;
