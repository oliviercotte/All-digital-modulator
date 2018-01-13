
-- ----------------------------------------------
-- File Name: MWClkMgr.vhd
-- Created:   29-Dec-2017 22:14:28
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------

LIBRARY UNISIM;
USE UNISIM.VComponents.all;
LIBRARY IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.numeric_std.ALL;


ENTITY MWClkMgr IS 
PORT (
      RXCLK_IN                        : IN  std_logic;
      CLK_IN                          : IN  std_logic;
      RESET_IN                        : IN  std_logic;
      TXCLK                           : OUT std_logic;
      RESET_OUT                       : OUT std_logic;
      DUTCLK                          : OUT std_logic;
      MACTXCLK                        : OUT std_logic;
      MACRXCLK                        : OUT std_logic
);
END MWClkMgr;

ARCHITECTURE rtl of MWClkMgr IS

  SIGNAL clk0                             : std_logic; -- boolean
  SIGNAL clkfb0                           : std_logic; -- boolean
  SIGNAL clk125                           : std_logic; -- boolean
  SIGNAL clk125_180                       : std_logic; -- boolean
  SIGNAL dcmclk125                        : std_logic; -- boolean
  SIGNAL dcmclk125_180                    : std_logic; -- boolean
  SIGNAL LOCKED                           : std_logic; -- boolean
  SIGNAL rxClk_internal                   : std_logic; -- boolean
  SIGNAL notLocked                        : std_logic; -- boolean
  SIGNAL CLKDV                            : std_logic; -- boolean

BEGIN

u_dcm: DCM_SP 
GENERIC MAP (CLKDV_DIVIDE => 2.000,
CLKIN_DIVIDE_BY_2 => FALSE,
CLKFX_DIVIDE => 4,
CLKFX_MULTIPLY => 5,
CLKIN_PERIOD => 10.000000,
CLKOUT_PHASE_SHIFT => "NONE",
CLK_FEEDBACK => "1X",
DESKEW_ADJUST => "SYSTEM_SYNCHRONOUS",
PHASE_SHIFT => 0,
STARTUP_WAIT => FALSE
)
PORT MAP(
        PSEN                 => '0',
        CLKFX180             => dcmclk125_180,
        CLK270               => OPEN,
        CLK0                 => clk0,
        CLKFX                => dcmclk125,
        CLKIN                => CLK_IN,
        RST                  => RESET_IN,
        CLK2X                => OPEN,
        LOCKED               => LOCKED,
        CLKDV                => CLKDV,
        CLKFB                => clkfb0,
        CLK90                => OPEN,
        CLK180               => OPEN,
        PSCLK                => '0',
        DSSEN                => '0',
        PSDONE               => OPEN,
        CLK2X180             => OPEN,
        STATUS               => OPEN,
        PSINCDEC             => '0'
);

u_BUFG: BUFG 
PORT MAP(
        O                    => clkfb0,
        I                    => clk0
);

u_BUFG_inst1: BUFG 
PORT MAP(
        O                    => clk125,
        I                    => dcmclk125
);

u_BUFG_inst2: BUFG 
PORT MAP(
        O                    => clk125_180,
        I                    => dcmclk125_180
);

u_ODDR2: ODDR2 
GENERIC MAP (DDR_ALIGNMENT => "NONE",
INIT => '0',
SRTYPE => "SYNC"
)
PORT MAP(
        C1                   => clk125_180,
        R                    => '0',
        Q                    => TXCLK,
        S                    => '0',
        CE                   => '1',
        D1                   => '0',
        D0                   => '1',
        C0                   => clk125
);

u_BUFG_inst3: BUFG 
PORT MAP(
        O                    => DUTCLK,
        I                    => CLKDV
);

MACTXCLK <= clk125;

MACRXCLK <= RXCLK_IN;

RESET_OUT <=  NOT LOCKED;

END;
