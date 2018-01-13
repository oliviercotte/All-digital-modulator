-- -------------------------------------------------------------
-- 
-- File Name: hdl_prj\hdlsrc\turnkey_test_model\DUT.vhd
-- Created: 2017-12-29 18:33:13
-- 
-- Generated by MATLAB 9.3 and HDL Coder 3.11
-- 
-- 
-- -------------------------------------------------------------
-- Rate and Clocking Details
-- -------------------------------------------------------------
-- Model base rate: 1
-- Target subsystem base rate: 1
-- 
-- 
-- Clock Enable  Sample Time
-- -------------------------------------------------------------
-- ce_out        1
-- -------------------------------------------------------------
-- 
-- 
-- Output Signal                 Clock Enable  Sample Time
-- -------------------------------------------------------------
-- Out1                          ce_out        1
-- -------------------------------------------------------------
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: DUT
-- Source Path: turnkey_test_model/DUT
-- Hierarchy Level: 0
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY DUT IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        clk_enable                        :   IN    std_logic;
        ce_out                            :   OUT   std_logic;
        Out1                              :   OUT   std_logic_vector(7 DOWNTO 0)  -- uint8
        );
END DUT;


ARCHITECTURE rtl OF DUT IS

  -- Signals
  SIGNAL enb                              : std_logic;
  SIGNAL Counter_Free_Running_out1        : unsigned(31 DOWNTO 0);  -- uint32
  SIGNAL Extract_Bits_out1                : unsigned(7 DOWNTO 0);  -- uint8

BEGIN
  enb <= clk_enable;

  -- Free running, Unsigned Counter
  --  initial value   = 0
  --  step value      = 1
  Counter_Free_Running_process : PROCESS (clk, reset)
  BEGIN
    IF reset = '1' THEN
      Counter_Free_Running_out1 <= to_unsigned(0, 32);
    ELSIF clk'EVENT AND clk = '1' THEN
      IF enb = '1' THEN
        Counter_Free_Running_out1 <= Counter_Free_Running_out1 + to_unsigned(1, 32);
      END IF;
    END IF;
  END PROCESS Counter_Free_Running_process;


  Extract_Bits_out1 <= Counter_Free_Running_out1(31 DOWNTO 24);

  Out1 <= std_logic_vector(Extract_Bits_out1);

  ce_out <= clk_enable;

END rtl;
