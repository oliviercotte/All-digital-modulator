----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    01:29:15 01/07/2018 
-- Design Name: 
-- Module Name:    top_fpga - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity top_fpga is
    Port ( sys_clk : in  STD_LOGIC;
           sys_rst_n : in  STD_LOGIC;
           DAC_IN1,DAC_IN2,DAC_IN3 : in  STD_LOGIC_VECTOR (35 downto 0);
			  DAC_OUT13,DAC_OUT14,DAC_OUT15 : out  STD_LOGIC_VECTOR (35 downto 0));
end top_fpga;

architecture Behavioral of top_fpga is

	signal sys_rst : std_logic;
	
	COMPONENT MASH_HDL
		PORT(
			clk                               :   IN    std_logic;
			reset                             :   IN    std_logic;
			clk_enable                        :   IN    std_logic;
			In1                               :   IN    std_logic_vector(35 DOWNTO 0);  -- sfix36_En22
			ce_out                            :   OUT   std_logic;
			Modulator_output                  :   OUT   std_logic_vector(35 DOWNTO 0)  -- sfix36_En22
		);
	END COMPONENT;

	COMPONENT DSM_MOD8_HDL
		PORT (
			clk                               :   IN    std_logic;
			reset                             :   IN    std_logic;
			clk_enable                        :   IN    std_logic;
			In1                               :   IN    std_logic_vector(45 DOWNTO 0);  -- sfix36_En32
			ce_out                            :   OUT   std_logic;
			Out1                              :   OUT   std_logic_vector(1 DOWNTO 0)  -- sfix2
		);
	END COMPONENT;
	
	COMPONENT Eight_order_delta_sigma_modulator
		PORT (
			clk                               :   IN    std_logic;
			reset                             :   IN    std_logic;
			clk_enable                        :   IN    std_logic;
			Baseband_signal                   :   IN    std_logic_vector(35 DOWNTO 0);  -- sfix36_En32
			ce_out                            :   OUT   std_logic;
			Modulator_output                  :   OUT   std_logic_vector(35 DOWNTO 0)  -- sfix36_En32
		);
	END COMPONENT;

begin

	sys_rst <= not sys_rst_n;
	
	U1 : Eight_order_delta_sigma_modulator
		PORT MAP(
			clk => sys_clk,
			reset => sys_rst,
			clk_enable => '1',
			Baseband_signal => DAC_IN1,
			ce_out => open,
			Modulator_output => DAC_OUT13
	);
	
--	U2 : DSM_MOD8_LTE_HDL
--		PORT MAP(
--			clk => sys_clk,
--			reset => sys_rst,
--			clk_enable => '1',
--			In1 => DAC_IN2,
--			ce_out => open,
--			Out1 => DAC_OUT14
--	);
--	
--	U3 : MASH_HDL
--		PORT MAP(
--			clk => sys_clk,
--			reset => sys_rst,
--			clk_enable => '1',
--			In1 => DAC_IN3,
--			ce_out => open,
--			Modulator_output => DAC_OUT15
--	);
	
end Behavioral;

