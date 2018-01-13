
-- ----------------------------------------------
-- File Name: mwfil_chiftop.vhd
-- Created:   29-Dec-2017 14:26:21
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------

LIBRARY IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.numeric_std.ALL;


ENTITY mwfil_chiftop IS 
PORT (
      clk                             : IN  std_logic;
      reset                           : IN  std_logic;
      din                             : IN  std_logic_vector(7 DOWNTO 0);
      din_valid                       : IN  std_logic;
      dout_ready                      : IN  std_logic;
      simcycle                        : IN  std_logic_vector(15 DOWNTO 0);
      din_ready                       : OUT std_logic;
      dout                            : OUT std_logic_vector(7 DOWNTO 0);
      dout_valid                      : OUT std_logic
);
END mwfil_chiftop;

ARCHITECTURE rtl of mwfil_chiftop IS

COMPONENT mwfil_chifcore IS 
GENERIC (INWORD: integer := 1;
OUTWORD: integer := 1;
WORDSIZE: integer := 64;
HASENABLE: integer := 1
);
PORT (
      clk                             : IN  std_logic;
      reset                           : IN  std_logic;
      din                             : IN  std_logic_vector(7 DOWNTO 0);
      din_valid                       : IN  std_logic;
      dout_ready                      : IN  std_logic;
      simcycle                        : IN  std_logic_vector(15 DOWNTO 0);
      dut_dout                        : IN  std_logic_vector(119 DOWNTO 0);
      din_ready                       : OUT std_logic;
      dout                            : OUT std_logic_vector(7 DOWNTO 0);
      dout_valid                      : OUT std_logic;
      dut_din                         : OUT std_logic_vector(63 DOWNTO 0);
      dut_enable                      : OUT std_logic
);
END COMPONENT;

COMPONENT all_digital_modulator_wrapper IS 
PORT (
      clk                             : IN  std_logic;
      enb                             : IN  std_logic;
      reset                           : IN  std_logic;
      din                             : IN  std_logic_vector(63 DOWNTO 0);
      dout                            : OUT std_logic_vector(119 DOWNTO 0)
);
END COMPONENT;

  SIGNAL dut_din                          : std_logic_vector(63 DOWNTO 0); -- std64
  SIGNAL dut_dout                         : std_logic_vector(119 DOWNTO 0); -- std120
  SIGNAL dut_clkenb                       : std_logic; -- boolean
  SIGNAL dutclk                           : std_logic; -- boolean
  SIGNAL bypass                           : std_logic; -- boolean
  SIGNAL bypass_tmp                       : std_logic; -- boolean
  SIGNAL dac_in                           : std_logic_vector(33 DOWNTO 0); -- std34
  SIGNAL dac_in_tmp                       : std_logic_vector(33 DOWNTO 0); -- std34
  SIGNAL ce                               : std_logic; -- boolean
  SIGNAL ce_tmp                           : std_logic; -- boolean
  SIGNAL enb                              : std_logic; -- boolean
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

u_mwfil_chifcore: mwfil_chifcore 
GENERIC MAP (INWORD => 8,
OUTWORD => 15,
WORDSIZE => 8,
HASENABLE => 0
)
PORT MAP(
        clk                  => clk,
        reset                => reset,
        din                  => din,
        din_valid            => din_valid,
        din_ready            => din_ready,
        dout                 => dout,
        dout_valid           => dout_valid,
        dout_ready           => dout_ready,
        simcycle             => simcycle,
        dut_din              => dut_din,
        dut_dout             => dut_dout,
        dut_enable           => dut_clkenb
);

u_dut: all_digital_modulator_wrapper 
PORT MAP(
        clk                  => clk,
        enb                  => dut_clkenb,
        reset                => reset,
        din                  => dut_din,
        dout                 => dut_dout
);


END;
