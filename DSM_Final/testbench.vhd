--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   01:57:42 12/28/2017
-- Design Name:   
-- Module Name:   C:/Newcomputer/DSM_Final/DSM_Final/testbench.vhd
-- Project Name:  DSM_Final
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: all_digital_modulator
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY testbench IS
END testbench;
 
ARCHITECTURE behavior OF testbench IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT all_digital_modulator
    PORT(
         sys_clk : IN  std_logic;
         sys_rst_n : IN  std_logic;
         bypass : IN  std_logic;
         DAC_IN : IN  std_logic_vector(33 downto 0);
         DAC_OUT1 : OUT  std_logic_vector(1 downto 0);
         DAC_OUT2 : OUT  std_logic_vector(1 downto 0);
         DAC_OUT3 : OUT  std_logic_vector(1 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal sys_clk : std_logic := '0';
   signal sys_rst_n : std_logic := '0';
   signal bypass : std_logic := '0';
   signal DAC_IN : std_logic_vector(33 downto 0) := (others => '0');

 	--Outputs
   signal DAC_OUT1 : std_logic_vector(1 downto 0);
   signal DAC_OUT2 : std_logic_vector(1 downto 0);
   signal DAC_OUT3 : std_logic_vector(1 downto 0);

   -- Clock period definitions
   constant sys_clk_period : time := 32.552083333333 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: all_digital_modulator PORT MAP (
          sys_clk => sys_clk,
          sys_rst_n => sys_rst_n,
          bypass => bypass,
          DAC_IN => DAC_IN,
          DAC_OUT1 => DAC_OUT1,
          DAC_OUT2 => DAC_OUT2,
          DAC_OUT3 => DAC_OUT3
        );

   -- Clock process definitions
   sys_clk_process :process
   begin
		sys_clk <= '0';
		wait for sys_clk_period/2;
		sys_clk <= '1';
		wait for sys_clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 135 ns.
      wait for 100 ns;	
		sys_rst_n <= '0';
      -- insert stimulus here 
		sys_rst_n <= '1';
      wait;
   end process;

END;
