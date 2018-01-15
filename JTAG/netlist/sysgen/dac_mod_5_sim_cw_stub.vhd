----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Design Name: 
-- Module Name: 
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity dac_mod_5_sim_cw_stub is
    port (
      ce: in std_logic := '1'; 
      clk: in std_logic; -- clock period = 2.03450520833333 ns (491.52000000000083 Mhz)
      gateway_in: in std_logic_vector(45 downto 0); 
      gateway_out3: out std_logic_vector(1 downto 0)
    );
end dac_mod_5_sim_cw_stub;

architecture Behavioral of dac_mod_5_sim_cw_stub is

  component dac_mod_5_sim_cw
    port (
      ce: in std_logic := '1'; 
      clk: in std_logic; -- clock period = 2.03450520833333 ns (491.52000000000083 Mhz)
      gateway_in: in std_logic_vector(45 downto 0); 
      gateway_out3: out std_logic_vector(1 downto 0)
    );
  end component;
begin

dac_mod_5_sim_cw_i : dac_mod_5_sim_cw
  port map (
    ce => ce,
    clk => clk,
    gateway_in => gateway_in,
    gateway_out3 => gateway_out3);
end Behavioral;

