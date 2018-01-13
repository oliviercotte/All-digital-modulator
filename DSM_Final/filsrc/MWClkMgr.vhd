
-- ----------------------------------------------
-- File Name: MWClkMgr.vhd
-- Created:   29-Dec-2017 14:19:48
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
      RESET_IN                        : IN  std_logic;
      CLK_IN                          : IN  std_logic;
      RESET_OUT                       : OUT std_logic;
      TXCLK                           : OUT std_logic;
      MACRXCLK                        : OUT std_logic;
      MACTXCLK                        : OUT std_logic;
      DUTCLK                          : OUT std_logic
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
GENERIC MAP (CLKDV_DIVIDE => 4.000,
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
        CLKDV                => CLKDV,
        CLK90                => OPEN,
        DSSEN                => '0',
        PSEN                 => '0',
        CLK2X                => OPEN,
        CLK180               => OPEN,
        RST                  => RESET_IN,
        STATUS               => OPEN,
        CLK270               => OPEN,
        CLK0                 => clk0,
        PSINCDEC             => '0',
        CLKFB                => clkfb0,
        PSCLK                => '0',
        PSDONE               => OPEN,
        CLKIN                => CLK_IN,
        LOCKED               => LOCKED,
        CLKFX180             => dcmclk125_180,
        CLKFX                => dcmclk125,
        CLK2X180             => OPEN
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
        Q                    => TXCLK,
        C0                   => clk125,
        R                    => '0',
        CE                   => '1',
        S                    => '0',
        C1                   => clk125_180,
        D0                   => '1',
        D1                   => '0'
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
