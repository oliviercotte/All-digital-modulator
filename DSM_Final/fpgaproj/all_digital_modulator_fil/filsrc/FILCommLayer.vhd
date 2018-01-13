
-- ----------------------------------------------
-- File Name: FILCommLayer.vhd
-- Created:   29-Dec-2017 22:14:29
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------

LIBRARY IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.numeric_std.ALL;


ENTITY FILCommLayer IS 
PORT (
      clk                             : IN  std_logic;
      reset                           : IN  std_logic;
      txclk_en                        : IN  std_logic;
      rxclk_en                        : IN  std_logic;
      dut_dinrdy                      : IN  std_logic;
      dut_dout                        : IN  std_logic_vector(7 DOWNTO 0);
      dut_doutvld                     : IN  std_logic;
      gmii_rxd                        : IN  std_logic_vector(7 DOWNTO 0);
      gmii_rx_er                      : IN  std_logic;
      gmii_tx_clk                     : IN  std_logic;
      gmii_rx_dv                      : IN  std_logic;
      gmii_rx_clk                     : IN  std_logic;
      gmii_crs                        : IN  std_logic;
      gmii_col                        : IN  std_logic;
      dut_rst                         : OUT std_logic;
      dut_din                         : OUT std_logic_vector(7 DOWNTO 0);
      dut_dinvld                      : OUT std_logic;
      simcycle                        : OUT std_logic_vector(15 DOWNTO 0);
      dut_doutrdy                     : OUT std_logic;
      gmii_txd                        : OUT std_logic_vector(7 DOWNTO 0);
      gmii_tx_er                      : OUT std_logic;
      gmii_tx_en                      : OUT std_logic
);
END FILCommLayer;

ARCHITECTURE rtl of FILCommLayer IS

COMPONENT MWMAC IS 
GENERIC (MWMACADDR1: integer := 0;
MWMACADDR2: integer := 10;
MWMACADDR3: integer := 53;
MWMACADDR4: integer := 2;
MWMACADDR5: integer := 33;
MWMACADDR6: integer := 138;
MWIPADDR1: integer := 192;
MWIPADDR2: integer := 168;
MWIPADDR3: integer := 0;
MWIPADDR4: integer := 2;
ONEUDP: integer := 1;
BUFFERADDRWIDTH: integer := 12
);
PORT (
      rxclk                           : IN  std_logic;
      rxclk_en                        : IN  std_logic;
      txclk                           : IN  std_logic;
      txclk_en                        : IN  std_logic;
      gmii_rxd                        : IN  std_logic_vector(7 DOWNTO 0);
      gmii_rx_dv                      : IN  std_logic;
      gmii_rx_er                      : IN  std_logic;
      gmii_col                        : IN  std_logic;
      gmii_crs                        : IN  std_logic;
      RxReset                         : IN  std_logic;
      TxData                          : IN  std_logic_vector(7 DOWNTO 0);
      TxDataValid                     : IN  std_logic;
      TxEOP                           : IN  std_logic;
      TxDataLength                    : IN  std_logic_vector(12 DOWNTO 0);
      TxSrcPort                       : IN  std_logic_vector(1 DOWNTO 0);
      TxReset                         : IN  std_logic;
      gmii_txd                        : OUT std_logic_vector(7 DOWNTO 0);
      gmii_tx_en                      : OUT std_logic;
      gmii_tx_er                      : OUT std_logic;
      RxData                          : OUT std_logic_vector(7 DOWNTO 0);
      RxDataValid                     : OUT std_logic;
      RxEOP                           : OUT std_logic;
      RxCRCOK                         : OUT std_logic;
      RxCRCBad                        : OUT std_logic;
      RxDstPort                       : OUT std_logic_vector(1 DOWNTO 0);
      TxReady                         : OUT std_logic
);
END COMPONENT;

COMPONENT FILPktProc IS 
GENERIC (VERSION: std_logic_vector(15 DOWNTO 0) := X"0200"
);
PORT (
      rxclk                           : IN  std_logic;
      txclk                           : IN  std_logic;
      rxclk_en                        : IN  std_logic;
      txclk_en                        : IN  std_logic;
      RxData                          : IN  std_logic_vector(7 DOWNTO 0);
      RxDataValid                     : IN  std_logic;
      RxEOP                           : IN  std_logic;
      RxCRCOK                         : IN  std_logic;
      RxCRCBad                        : IN  std_logic;
      RxDstPort                       : IN  std_logic_vector(1 DOWNTO 0);
      TxReady                         : IN  std_logic;
      clk                             : IN  std_logic;
      rst                             : IN  std_logic;
      dut_dinrdy                      : IN  std_logic;
      dut_dout                        : IN  std_logic_vector(7 DOWNTO 0);
      dut_doutvld                     : IN  std_logic;
      RxReset                         : OUT std_logic;
      TxData                          : OUT std_logic_vector(7 DOWNTO 0);
      TxDataValid                     : OUT std_logic;
      TxEOP                           : OUT std_logic;
      TxReset                         : OUT std_logic;
      TxDataLength                    : OUT std_logic_vector(12 DOWNTO 0);
      TxSrcPort                       : OUT std_logic_vector(1 DOWNTO 0);
      dut_rst                         : OUT std_logic;
      dut_din                         : OUT std_logic_vector(7 DOWNTO 0);
      dut_dinvld                      : OUT std_logic;
      simcycle                        : OUT std_logic_vector(15 DOWNTO 0);
      dut_doutrdy                     : OUT std_logic
);
END COMPONENT;

  SIGNAL mac_rxdata                       : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL mac_rxvld                        : std_logic; -- boolean
  SIGNAL mac_rxeop                        : std_logic; -- boolean
  SIGNAL mac_rxcrcok                      : std_logic; -- boolean
  SIGNAL mac_rxcrcbad                     : std_logic; -- boolean
  SIGNAL mac_rxdstport                    : std_logic_vector(1 DOWNTO 0); -- std2
  SIGNAL mac_rxreset                      : std_logic; -- boolean
  SIGNAL mac_txreset                      : std_logic; -- boolean
  SIGNAL mac_txdata                       : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL mac_txvld                        : std_logic; -- boolean
  SIGNAL mac_txeop                        : std_logic; -- boolean
  SIGNAL mac_txrdy                        : std_logic; -- boolean
  SIGNAL mac_txdatalength                 : std_logic_vector(12 DOWNTO 0); -- std13
  SIGNAL mac_txsrcport                    : std_logic_vector(1 DOWNTO 0); -- std2
  SIGNAL hostmacaddr1                     : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostmacaddr2                     : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostmacaddr3                     : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostmacaddr4                     : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostmacaddr5                     : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostmacaddr6                     : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostipaddr1                      : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostipaddr2                      : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostipaddr3                      : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL hostipaddr4                      : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpsrcport0_1                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpsrcport0_2                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpdstport0_1                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpdstport0_2                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpsrcport1_1                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpsrcport1_2                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpdstport1_1                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpdstport1_2                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpsrcport2_1                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpsrcport2_2                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpdstport2_1                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpdstport2_2                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpsrcport3_1                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpsrcport3_2                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpdstport3_1                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL udpdstport3_2                    : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL rxaddrvalid                      : std_logic; -- boolean
  SIGNAL replyping                        : std_logic; -- boolean
  SIGNAL replyarp                         : std_logic; -- boolean
  SIGNAL pingrdaddr                       : std_logic_vector(8 DOWNTO 0); -- std9
  SIGNAL pingrddata                       : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL pingwraddr                       : std_logic_vector(8 DOWNTO 0); -- std9
  SIGNAL pingwrdata                       : std_logic_vector(7 DOWNTO 0); -- std8
  SIGNAL pingwren                         : std_logic; -- boolean

BEGIN

u_MWMAC: MWMAC 
GENERIC MAP (MWMACADDR1 => 160,
MWMACADDR2 => 179,
MWMACADDR3 => 204,
MWMACADDR4 => 81,
MWMACADDR5 => 97,
MWMACADDR6 => 242,
MWIPADDR1 => 192,
MWIPADDR2 => 168,
MWIPADDR3 => 2,
MWIPADDR4 => 5,
ONEUDP => 1,
BUFFERADDRWIDTH => 12
)
PORT MAP(
        rxclk                => gmii_rx_clk,
        rxclk_en             => rxclk_en,
        txclk                => gmii_tx_clk,
        txclk_en             => txclk_en,
        gmii_rxd             => gmii_rxd,
        gmii_rx_dv           => gmii_rx_dv,
        gmii_rx_er           => gmii_rx_er,
        gmii_txd             => gmii_txd,
        gmii_tx_en           => gmii_tx_en,
        gmii_tx_er           => gmii_tx_er,
        gmii_col             => gmii_col,
        gmii_crs             => gmii_crs,
        RxData               => mac_rxdata,
        RxDataValid          => mac_rxvld,
        RxEOP                => mac_rxeop,
        RxCRCOK              => mac_rxcrcok,
        RxCRCBad             => mac_rxcrcbad,
        RxDstPort            => mac_rxdstport,
        RxReset              => mac_rxreset,
        TxData               => mac_txdata,
        TxDataValid          => mac_txvld,
        TxReady              => mac_txrdy,
        TxEOP                => mac_txeop,
        TxDataLength         => mac_txdatalength,
        TxSrcPort            => mac_txsrcport,
        TxReset              => mac_txreset
);

u_FILPktProc: FILPktProc 
GENERIC MAP (VERSION => X"0200"
)
PORT MAP(
        rxclk                => gmii_rx_clk,
        txclk                => gmii_tx_clk,
        rxclk_en             => rxclk_en,
        txclk_en             => txclk_en,
        RxData               => mac_rxdata,
        RxDataValid          => mac_rxvld,
        RxEOP                => mac_rxeop,
        RxCRCOK              => mac_rxcrcok,
        RxCRCBad             => mac_rxcrcbad,
        RxDstPort            => mac_rxdstport,
        RxReset              => mac_rxreset,
        TxData               => mac_txdata,
        TxDataValid          => mac_txvld,
        TxEOP                => mac_txeop,
        TxReady              => mac_txrdy,
        TxReset              => mac_txreset,
        TxDataLength         => mac_txdatalength,
        TxSrcPort            => mac_txsrcport,
        clk                  => clk,
        rst                  => reset,
        dut_rst              => dut_rst,
        dut_din              => dut_din,
        dut_dinvld           => dut_dinvld,
        dut_dinrdy           => dut_dinrdy,
        simcycle             => simcycle,
        dut_dout             => dut_dout,
        dut_doutvld          => dut_doutvld,
        dut_doutrdy          => dut_doutrdy
);


END;
