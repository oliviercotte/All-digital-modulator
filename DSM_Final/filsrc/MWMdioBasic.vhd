
-- ----------------------------------------------
-- File Name: MWMdioBasic.vhd
-- Created:   29-Dec-2017 14:19:51
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------


-- ----------------------------------------------
-- File Name: MWMdioBasic.vhd
-- Created:   06-Jul-2017 12:23:35
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------

LIBRARY IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.std_logic_unsigned.all;
USE IEEE.numeric_std.ALL;

ENTITY MWMdioBasic IS 
PORT (
	 RESET_IN     : IN std_logic;
    ETH_MDIO     : INOUT  std_logic;
    ETH_MDC      : OUT  std_logic;
    ETH_RESET_n  : OUT std_logic);
END MWMdioBasic;

architecture rtl of MWMdioBasic is   
begin

ETH_RESET_n <= not RESET_IN;
ETH_MDC <= '1';
ETH_MDIO <= 'Z';

end rtl;