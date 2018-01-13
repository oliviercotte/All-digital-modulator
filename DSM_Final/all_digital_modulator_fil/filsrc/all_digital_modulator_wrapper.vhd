
-- ----------------------------------------------
-- File Name: all_digital_modulator_wrapper.vhd
-- Created:   29-Dec-2017 14:26:21
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------

LIBRARY IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.numeric_std.ALL;


ENTITY all_digital_modulator_wrapper IS 
PORT (
      clk                             : IN  std_logic;
      enb                             : IN  std_logic;
      reset                           : IN  std_logic;
      din                             : IN  std_logic_vector(63 DOWNTO 0);
      dout                            : OUT std_logic_vector(119 DOWNTO 0)
);
END all_digital_modulator_wrapper;

ARCHITECTURE rtl of all_digital_modulator_wrapper IS

COMPONENT all_digital_modulator IS 
PORT (
      sys_rst_n                       : IN  std_logic;
      ce                              : IN  std_logic;
      sys_clk                         : IN  std_logic;
      bypass                          : IN  std_logic;
      dac_in                          : IN  std_logic_vector(33 DOWNTO 0);
      enb                             : IN  std_logic;
      dac_out2                        : OUT std_logic_vector(35 DOWNTO 0);
      dac_out1                        : OUT std_logic_vector(35 DOWNTO 0);
      dac_out3                        : OUT std_logic_vector(35 DOWNTO 0)
);
END COMPONENT;

  SIGNAL dutclk                           : std_logic; -- boolean
  SIGNAL bypass                           : std_logic; -- boolean
  SIGNAL bypass_tmp                       : std_logic; -- boolean
  SIGNAL dac_in                           : std_logic_vector(33 DOWNTO 0); -- std34
  SIGNAL dac_in_tmp                       : std_logic_vector(33 DOWNTO 0); -- std34
  SIGNAL ce                               : std_logic; -- boolean
  SIGNAL ce_tmp                           : std_logic; -- boolean
  SIGNAL enb_1                            : std_logic; -- boolean
  SIGNAL enb_tmp                          : std_logic; -- boolean
  SIGNAL dac_out1                         : std_logic_vector(35 DOWNTO 0); -- std36
  SIGNAL dac_out1_tmp                     : std_logic_vector(35 DOWNTO 0); -- std36
  SIGNAL zero0                            : std_logic_vector(3 DOWNTO 0); -- std4
  SIGNAL dac_out2                         : std_logic_vector(35 DOWNTO 0); -- std36
  SIGNAL dac_out2_tmp                     : std_logic_vector(35 DOWNTO 0); -- std36
  SIGNAL zero1                            : std_logic_vector(3 DOWNTO 0); -- std4
  SIGNAL dac_out3                         : std_logic_vector(35 DOWNTO 0); -- std36
  SIGNAL dac_out3_tmp                     : std_logic_vector(35 DOWNTO 0); -- std36
  SIGNAL zero2                            : std_logic_vector(3 DOWNTO 0); -- std4
  SIGNAL tmpconcat                        : std_logic_vector(119 DOWNTO 0); -- std120

BEGIN

u_all_digital_modulator: all_digital_modulator 
PORT MAP(
        sys_rst_n            => reset,
        dac_out2             => dac_out2,
        ce                   => ce,
        sys_clk              => dutclk,
        bypass               => bypass,
        dac_in               => dac_in,
        dac_out1             => dac_out1,
        dac_out3             => dac_out3,
        enb                  => enb_1
);

dutclk <=  NOT enb;
bypass <= bypass_tmp;

bypass_tmp <= din(0);
dac_in <= dac_in_tmp;
dac_in_tmp <= din(41 DOWNTO 8);
ce <= ce_tmp;

ce_tmp <= din(48);
enb_1 <= enb_tmp;

enb_tmp <= din(56);
dac_out1_tmp <= dac_out1;
dac_out1_tmp <= dac_out1;
zero0 <= (others => '0');
dac_out2_tmp <= dac_out2;
dac_out2_tmp <= dac_out2;
zero1 <= (others => '0');
dac_out3_tmp <= dac_out3;
dac_out3_tmp <= dac_out3;
zero2 <= (others => '0');
dout <= zero2 & dac_out3_tmp & zero1 & dac_out2_tmp & zero0 & dac_out1_tmp;

END;
