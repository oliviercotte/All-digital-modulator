--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   01:29:40 01/07/2018
-- Design Name:   
-- Module Name:   C:/FIL/JTAG/DSM_SIM/testbench.vhd
-- Project Name:  DSM_SIM
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: top_fpga
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
 
    COMPONENT top_fpga
    PORT(
			sys_clk : in  STD_LOGIC;
			sys_rst_n : in  STD_LOGIC;
			DAC_IN1,DAC_IN2,DAC_IN3 : in  STD_LOGIC_VECTOR (45 downto 0);
			DAC_OUT13,DAC_OUT14,DAC_OUT15 : out  STD_LOGIC_VECTOR (1 downto 0));
    END COMPONENT;
    

   --Inputs
   signal sys_clk : std_logic := '0';
   signal sys_rst_n : std_logic := '0';
   signal DAC_IN1,DAC_IN2,DAC_IN3 : STD_LOGIC_VECTOR (45 downto 0) := (others => '0');

 	--Outputs
   signal DAC_OUT13,DAC_OUT14,DAC_OUT15 :  STD_LOGIC_VECTOR (1 downto 0);

   -- Clock period definitions
   constant sys_clk_period : time := 2.0345052083333 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: top_fpga PORT MAP (
          sys_clk => sys_clk,
          sys_rst_n => sys_rst_n,
          DAC_IN1 => DAC_IN1,
			 DAC_IN2 => DAC_IN2,
			 DAC_IN3 => DAC_IN3,
          DAC_OUT13 => DAC_OUT13,
          DAC_OUT14 => DAC_OUT14,
			 DAC_OUT15 => DAC_OUT15
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
      -- hold reset state for 100 ns.
		sys_rst_n <= '0';
		
      wait for 100 ns;	

      wait for sys_clk_period*10;

      -- insert stimulus here
		sys_rst_n <= '1';

      wait;
   end process;

END;
