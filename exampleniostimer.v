module exampleniostimer(
	input 		          		CLOCK2_50,
	input 		          		CLOCK3_50,
	input 		          		CLOCK4_50,
	input 		          		CLOCK_50,
	input 		     [3:0]		KEY
);

  wire clk;
  wire rst;

  platformniostimer u0 ( .clk_clk(clk),
   	                      .reset_reset_n(rst)
   	                      );

  assign clk = CLOCK_50;
  assign rst = KEY[0];
									 
endmodule
