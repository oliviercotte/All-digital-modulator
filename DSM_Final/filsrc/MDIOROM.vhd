
-- ----------------------------------------------
-- File Name: MDIOROM.vhd
-- Created:   29-Dec-2017 04:08:53
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY MDIOROM IS
generic(
    data0: std_logic_vector(15 downto 0):="0000001001000000";
    data1: std_logic_vector(15 downto 0):="0000001001000000";
    data2: std_logic_vector(15 downto 0):="0000011001001001";
    data3: std_logic_vector(15 downto 0):="0000111100000000";
    data4: std_logic_vector(15 downto 0):="0000011001011011";
    data5: std_logic_vector(15 downto 0):="1000000010001111";
    data6: std_logic_vector(15 downto 0):="0000011001000000";
    data7: std_logic_vector(15 downto 0):="1001000000000000");    
PORT (
	clock: 		IN STD_LOGIC;
	address: 	IN STD_LOGIC_VECTOR(5 downto 0);
	data_out: 	OUT STD_LOGIC_VECTOR(15 downto 0)
);
END MDIOROM;

ARCHITECTURE rtl OF MDIOROM IS
BEGIN
	PROCESS (clock)
	BEGIN
		IF clock'event and clock='1' THEN
			CASE address IS
				WHEN "000000" => data_out <= data0;
				WHEN "000001" => data_out <= data1;
				WHEN "000010" => data_out <= data2; -- reg 9: GigaE capability
                WHEN "000011" => data_out <= data3; -- bit 8&9: 1 - 1000M			
				WHEN "000100" => data_out <= data4; -- reg 1b: GMII
                WHEN "000101" => data_out <= data5; -- bit[3:0]: 1111 - gmii
				WHEN "000110" => data_out <= data6; -- reset
                WHEN "000111" => data_out <= data7;		
                when "111111" => data_out <= "0000110000000000";
				WHEN OTHERS   => data_out <= "0000111001011011";
			END CASE;
		END IF;
	END PROCESS;
END rtl;