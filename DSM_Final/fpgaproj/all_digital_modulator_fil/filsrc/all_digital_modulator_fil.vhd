
-- ----------------------------------------------
-- File Name: all_digital_modulator_fil.vhd
-- Created:   29-Dec-2017 22:14:30
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------

LIBRARY UNISIM;
USE UNISIM.VComponents.all;
LIBRARY IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.numeric_std.ALL;


ENTITY all_digital_modulator_fil IS 
PORT (
      sysrst                          : IN  std_logic;
      ETH_RXD                         : IN  std_logic_vector(7 DOWNTO 0);
      ETH_RXCLK                       : IN  std_logic;
      ETH_RXER                        : IN  std_logic;
      sysclk                          : IN  std_logic;
      ETH_CRS                         : IN  std_logic;
      ETH_RXDV                        : IN  std_logic;
      ETH_COL                         : IN  std_logic;
      ETH_TXER                        : OUT std_logic;
      ETH_RESET_n                     : OUT std_logic;
      ETH_MDC                         : OUT std_logic;
      ETH_TXEN                        : OUT std_logic;
      ETH_TXD                         : OUT std_logic_vector(7 DOWNTO 0);
      ETH_GTXCLK                      : OUT std_logic;
      ETH_MDIO                        : INOUT std_logic
);
END all_digital_modulator_fil;

ARCHITECTURE rtl of all_digital_modulator_fil IS

COMPONENT MWClkMgr IS 
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
END COMPONENT;

COMPONENT FILCore IS 
PORT (
      clk                             : IN  std_logic;
      reset                           : IN  std_logic;
      txclk_en                        : IN  std_logic;
      rxclk_en                        : IN  std_logic;
      gmii_rxd                        : IN  std_logic_vector(7 DOWNTO 0);
      gmii_rx_er                      : IN  std_logic;
      gmii_tx_clk                     : IN  std_logic;
      gmii_rx_dv                      : IN  std_logic;
      gmii_rx_clk                     : IN  std_logic;
      gmii_crs                        : IN  std_logic;
      gmii_col                        : IN  std_logic;
      gmii_txd                        : OUT std_logic_vector(7 DOWNTO 0);
      gmii_tx_er                      : OUT std_logic;
      gmii_tx_en                      : OUT std_logic
);
END COMPONENT;

COMPONENT MWMdioBasic IS 
PORT (
      RESET_IN                        : IN  std_logic;
      ETH_RESET_n                     : OUT std_logic;
      ETH_MDC                         : OUT std_logic;
      ETH_MDIO                        : INOUT std_logic
);
END COMPONENT;

  SIGNAL dutClk                           : std_logic; -- boolean
  SIGNAL rst                              : std_logic; -- boolean
  SIGNAL ClkIn                            : std_logic; -- boolean
  SIGNAL rxclk                            : std_logic; -- boolean
  SIGNAL txclk                            : std_logic; -- boolean
  SIGNAL rxd                              : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL txd                              : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL txclk_en                         : std_logic; -- boolean
  SIGNAL rxclk_en                         : std_logic; -- boolean
  SIGNAL dcm_reset                        : std_logic; -- boolean
  SIGNAL rxdvld                           : std_logic; -- boolean
  SIGNAL rxerror                          : std_logic; -- boolean
  SIGNAL txen                             : std_logic; -- boolean
  SIGNAL txerror                          : std_logic; -- boolean
  SIGNAL col                              : std_logic; -- boolean
  SIGNAL crs                              : std_logic; -- boolean
  SIGNAL rst_n                            : std_logic; -- boolean
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
  SIGNAL dut_rst                          : std_logic; -- boolean
  SIGNAL dut_din                          : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL dut_dinvld                       : std_logic; -- boolean
  SIGNAL dut_dinrdy                       : std_logic; -- boolean
  SIGNAL simcycle                         : std_logic_vector(15 DOWNTO 0); -- std16
  SIGNAL dut_dout                         : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL dut_doutvld                      : std_logic; -- boolean
  SIGNAL dut_doutrdy                      : std_logic; -- boolean

BEGIN

u_IBUFG: IBUFG 
PORT MAP(
        O                    => ClkIn,
        I                    => sysclk
);

u_ClockManager: MWClkMgr 
PORT MAP(
        TXCLK                => ETH_GTXCLK,
        RESET_OUT            => rst,
        DUTCLK               => dutClk,
        RXCLK_IN             => ETH_RXCLK,
        CLK_IN               => ClkIn,
        MACTXCLK             => txclk,
        MACRXCLK             => rxclk,
        RESET_IN             => dcm_reset
);

u_FILCore: FILCore 
PORT MAP(
        clk                  => dutClk,
        reset                => rst,
        txclk_en             => txclk_en,
        rxclk_en             => rxclk_en,
        gmii_rxd             => rxd,
        gmii_txd             => txd,
        gmii_rx_er           => rxerror,
        gmii_tx_clk          => txclk,
        gmii_tx_er           => txerror,
        gmii_rx_dv           => rxdvld,
        gmii_rx_clk          => rxclk,
        gmii_tx_en           => txen,
        gmii_crs             => crs,
        gmii_col             => col
);

u_MWMdioAdv: MWMdioBasic 
PORT MAP(
        RESET_IN             => rst,
        ETH_RESET_n          => ETH_RESET_n,
        ETH_MDIO             => ETH_MDIO,
        ETH_MDC              => ETH_MDC
);

 PROCESS (ETH_RXCLK, rst)
  BEGIN -- PROCESS
   IF rst = '1' THEN
    rxdvld      <= '0';
   ELSIF ETH_RXCLK'EVENT AND ETH_RXCLK = '1' THEN 
       rxdvld      <= ETH_RXDV;
   END IF;
 END PROCESS;

 PROCESS (ETH_RXCLK, rst)
  BEGIN -- PROCESS
   IF rst = '1' THEN
    rxerror      <= '0';
   ELSIF ETH_RXCLK'EVENT AND ETH_RXCLK = '1' THEN 
       rxerror      <= ETH_RXER;
   END IF;
 END PROCESS;

 PROCESS (ETH_RXCLK, rst)
  BEGIN -- PROCESS
   IF rst = '1' THEN
    rxd      <= (OTHERS => '0');
   ELSIF ETH_RXCLK'EVENT AND ETH_RXCLK = '1' THEN 
       rxd      <= ETH_RXD;
   END IF;
 END PROCESS;

 PROCESS (ETH_RXCLK, rst)
  BEGIN -- PROCESS
   IF rst = '1' THEN
    col      <= '0';
   ELSIF ETH_RXCLK'EVENT AND ETH_RXCLK = '1' THEN 
       col      <= ETH_COL;
   END IF;
 END PROCESS;

 PROCESS (ETH_RXCLK, rst)
  BEGIN -- PROCESS
   IF rst = '1' THEN
    crs      <= '0';
   ELSIF ETH_RXCLK'EVENT AND ETH_RXCLK = '1' THEN 
       crs      <= ETH_CRS;
   END IF;
 END PROCESS;

 PROCESS (txclk, rst)
  BEGIN -- PROCESS
   IF rst = '1' THEN
    ETH_TXD      <= (OTHERS => '0');
   ELSIF txclk'EVENT AND txclk = '1' THEN 
       ETH_TXD      <= txd;
   END IF;
 END PROCESS;

 PROCESS (txclk, rst)
  BEGIN -- PROCESS
   IF rst = '1' THEN
    ETH_TXEN      <= '0';
   ELSIF txclk'EVENT AND txclk = '1' THEN 
       ETH_TXEN      <= txen;
   END IF;
 END PROCESS;

 PROCESS (txclk, rst)
  BEGIN -- PROCESS
   IF rst = '1' THEN
    ETH_TXER      <= '0';
   ELSIF txclk'EVENT AND txclk = '1' THEN 
       ETH_TXER      <= txerror;
   END IF;
 END PROCESS;

txclk_en <= '1';
rxclk_en <= '1';
dcm_reset <=  NOT sysrst;

END;
