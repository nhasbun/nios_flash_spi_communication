# Clock constraints
create_clock -name "CLOCK_IN_100" -period 10.000ns [get_ports {CLOCK_EXT_100}]

# Automatically constrain PLL and other generated clocks
derive_pll_clocks -create_base_clocks
derive_clock_uncertainty

