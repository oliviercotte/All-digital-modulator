

# Global period constraint
create_clock -name clk -period 2.03450520833333 [get_ports clk]
# LOC constraints
set_property LOC Fixed [get_ports clk]
