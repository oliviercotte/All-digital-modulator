
-- ----------------------------------------------
-- File Name: MWMdioAdv.vhd
-- Created:   29-Dec-2017 04:08:53
-- Copyright  2017 MathWorks, Inc.
-- ----------------------------------------------

LIBRARY IEEE;
USE IEEE.std_logic_1164.all;
USE IEEE.std_logic_unsigned.all;
USE IEEE.numeric_std.ALL;

ENTITY MWMdioAdv IS 
generic(
    DownSampleFactor: integer := 50;
    data0: std_logic_vector(15 downto 0):="0000001001000000";
    data1: std_logic_vector(15 downto 0):="0000001001000000";
    data2: std_logic_vector(15 downto 0):="0000011001001001";
    data3: std_logic_vector(15 downto 0):="0000111100000000";
    data4: std_logic_vector(15 downto 0):="0000011001011011";
    data5: std_logic_vector(15 downto 0):="1000000010001111";
    data6: std_logic_vector(15 downto 0):="0000011001000000";
    data7: std_logic_vector(15 downto 0):="1001000000000000");
PORT (
    CLK          : IN std_logic;
    ETH_RESET_n  : out std_logic;
    RESET      : IN  std_logic;
    ETH_MDIO     : INOUT  std_logic;
    ETH_MDC      : Out  std_logic);
END MWMdioAdv;

architecture rtl of MWMdioAdv is

type CTRL_STATE_TYPE is (CTRL_INIT_STATE, 
    CTRL_FETCHCMD_STATE, 
    CTRL_FETCHDATA_STATE,
    CTRL_STARTMDIO_STATE,
    CTRL_WAIT_STATE, 
    CTRL_IDLE_STATE);

    component MDIOROM IS
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
    end component;
    
    signal state          : CTRL_STATE_TYPE;
    signal mdcCnt         : unsigned(7 downto 0);
    signal cmdReg         : std_logic_vector(1 downto 0);
    signal clk_en         : std_logic;
	signal counter        : std_logic_vector(15 downto 0);
	signal mdiodv         : std_logic;
	signal mdio_cnt       : std_logic_vector(5 downto 0);

	signal reg_addr       : std_logic_vector(4 downto 0);
	signal phy_addr       : std_logic_vector(4 downto 0);
	signal reg_write      : std_logic_vector(15 downto 0);
	signal rw_cmd         : std_logic; 
    
	signal mdio_rw_cmd    : std_logic; 
    signal mdio_phy_addr  : std_logic_vector(4 downto 0);
    signal mdio_reg_addr  : std_logic_vector(4 downto 0);
	signal mdio_busy      : std_logic;

    signal mdcClk         : std_logic;

    -- rom related signals --
	signal rom_addr: STD_LOGIC_VECTOR(5 downto 0);
	signal rom_data: STD_LOGIC_VECTOR(15 downto 0);
    
begin

--ETH_RESET_n <= reset_n;
--eth_reset_n<= '1'; --reset_n;

u_rom: MDIOROM
    generic map(
        data0=>data0,
        data1=>data1,
        data2=>data2,
        data3=>data3,
        data4=>data4,
        data5=>data5,
        data6=>data6,
        data7=>data7)
    PORT map(
        clock => clk,
        address => rom_addr,
        data_out => rom_data);

process(clk, reset)
begin
    if reset = '1' then
        mdcCnt <= (others => '0');
        clk_en <= '0';
    elsif clk'event and clk = '1' then
        if mdcCnt = to_unsigned(DownSampleFactor,8) then
            mdcCnt <= (others => '0');
            clk_en <= '1';
            mdcClk <= '0';
        elsif mdcCnt = to_unsigned(DownSampleFactor/2,8) then
            mdcCnt <= mdcCnt + 1;
            clk_en <= '0';
            mdcClk <= '1';
        else
            mdcCnt <= mdcCnt + 1;
            clk_en <= '0';
        end if;
    end if;
end process;

ETH_MDC <= mdcClk;

process(clk)
begin  
    if clk'event and clk = '1' then            
        if reset = '1' then
            counter  <= (others => '0');
            state    <= CTRL_INIT_STATE;       
            rom_addr <= (others => '0');
            mdiodv <= '0';
            rw_cmd <= '0';
        elsif clk_en = '1' then
            if state = CTRL_INIT_STATE then
                counter <= counter + '1';
                rom_addr <= (others => '0');
                if counter = "0111111111111111" then
                    ETH_RESET_n <= '0';
                else
                    ETH_RESET_n <= '1';
                end if;                    
                if counter = "1111111111111111" then
                    state <= CTRL_FETCHCMD_STATE;
                end if;
                mdiodv <= '0';
            elsif state = CTRL_FETCHCMD_STATE then
                reg_addr <= rom_data(4 downto 0);
                phy_addr <= rom_data(9 downto 5);
                cmdReg   <= rom_data(11 downto 10);
                mdiodv   <= '0';
                -- Read command
                if rom_data(10) = '0' then 
                    state  <= CTRL_STARTMDIO_STATE;                    
                    rw_cmd <= '0';
                -- Write command
                elsif rom_data(11 downto 10) = "01" then
                    rom_addr    <= rom_addr + '1'; 
                    state  <= CTRL_STARTMDIO_STATE;                    
                    rw_cmd <= '1';         
                elsif rom_data(11 downto 10) = "11" then
                    state <= CTRL_IDLE_STATE;
                end if;                
            --elsif state = CTRL_FETCHDATA_STATE then                
            --    state       <= CTRL_STARTMDIO_STATE;              
            --    mdiodv      <= '0';
            elsif state = CTRL_STARTMDIO_STATE then
                -- Just wait until MDIO is ready
                if mdio_busy = '0' then
                    -- Start MDIO 
                    mdiodv <= '1';
                elsif mdiodv <= '1' and mdio_busy = '1' then
                    -- Need to wait for one more cycle before jumping to the next state
                    mdiodv <= '0';
                    state   <= CTRL_WAIT_STATE;
                end if;                
            elsif state = CTRL_WAIT_STATE then
                -- Wait until MDIO is free
                if mdio_busy = '0' then
                    state       <= CTRL_FETCHCMD_STATE;
                    if cmdReg = "10" then
                        rom_addr <= rom_addr;
                    else
                        rom_addr    <= rom_addr + '1';  
                    end if;
                end if;   
            elsif state = CTRL_IDLE_STATE then
                state <= CTRL_IDLE_STATE;
            end if;
        end if;
    end if;
end process;
    
process(clk)
begin
    if clk'event and clk = '1' then 
        if clk_en = '1' then
            if reset = '1' then 
                mdio_busy <= '0';
                mdio_cnt <= "000000";
                mdio_rw_cmd <= '0';
                ETH_MDIO <= 'Z';
            elsif mdiodv = '1' and mdio_busy = '0' then 
                mdio_busy   <= '1';
                mdio_cnt    <= "000000";
                mdio_rw_cmd <= rw_cmd;
                reg_write   <= rom_data; 
                mdio_phy_addr <= phy_addr;
                mdio_reg_addr <= reg_addr;
                ETH_MDIO        <= 'Z';
            elsif mdio_busy = '1' then
                mdio_cnt <= mdio_cnt + '1';
                if mdio_cnt = "111111" then
                    mdio_busy <= '0'; -- done with mdio
                end if;
                
                if mdio_cnt(5) = '0' then
                     ETH_MDIO <= '1';
                elsif mdio_cnt = "100000" then
                     ETH_MDIO <= '0'; --ST
                elsif mdio_cnt = "100001" then
                     ETH_MDIO <= '1'; --ST
                elsif mdio_cnt = "100010" then
                    if mdio_rw_cmd = '0' then
                        ETH_MDIO <= '1'; --read
                    else
                        ETH_MDIO <= '0'; --write
                    end if;
                elsif mdio_cnt = "100011" then
                    if mdio_rw_cmd = '0' then
                        ETH_MDIO <= '0'; --read
                    else
                        ETH_MDIO <= '1'; --write
                    end if;
                elsif mdio_cnt = "100100" then       
                     ETH_MDIO <= mdio_phy_addr(4); -- phy addr
                elsif mdio_cnt = "100101" then
                     ETH_MDIO <= mdio_phy_addr(3); -- phy addr
                elsif mdio_cnt = "100110" then
                     ETH_MDIO <= mdio_phy_addr(2); -- phy addr
                elsif mdio_cnt = "100111" then
                     ETH_MDIO <= mdio_phy_addr(1); -- phy addr
                elsif mdio_cnt = "101000" then
                     ETH_MDIO <= mdio_phy_addr(0); -- phy addr
                elsif mdio_cnt = "101001" then     					
                     ETH_MDIO <= mdio_reg_addr(4); --addr
                elsif mdio_cnt = "101010" then
                     ETH_MDIO <= mdio_reg_addr(3); --addr
                elsif mdio_cnt = "101011" then
                     ETH_MDIO <= mdio_reg_addr(2); --addr
                elsif mdio_cnt = "101100" then
                     ETH_MDIO <= mdio_reg_addr(1); --addr
                elsif mdio_cnt = "101101" then
                     ETH_MDIO <= mdio_reg_addr(0); --addr     
                elsif mdio_cnt = "101110" then
                    if mdio_rw_cmd = '0' then
                        ETH_MDIO <= 'Z'; -- Turnaround Time
                    else
                        ETH_MDIO <= '1';
                    end if;
                elsif mdio_cnt = "101111" then
                    if mdio_rw_cmd = '1' then -- Turnaround Time
                        ETH_MDIO <= '0';
                    end if;                
                elsif mdio_cnt(5 downto 4) = "11" then
                    if mdio_rw_cmd = '1' then
                        ETH_MDIO <= reg_write(15); -- MSB out first
                        reg_write(15 downto 1) <= reg_write(14 downto 0);
                    end if;
                end if;
            else
                ETH_MDIO <= 'Z';
            end if;
        end if;
    end if;
end process;

end rtl;