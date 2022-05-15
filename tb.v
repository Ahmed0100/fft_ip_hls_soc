	initial
	begin`timescale 1ns / 1ps
module uart_rx_tb;

	reg clk;
	reg clk_n;

	reg reset;
	reg data_valid = 0;
	reg [7:0] data_byte = 0;
	reg [2:0] current_state = 0;
	reg buff_index = 0;
	reg [7:0] buff [19:0];

	parameter CLKS_PER_BIT = 100000000/230400;

	parameter IDLE=3'b0,
	RX_START_BIT=3'b001,
	RX_DATA_BITS=3'b010,
	RX_STOP_BIT=3'b011,
	CLEAN_UP = 3'b100;

	reg [31:0] clk_count = 0;
	reg [2:0] bit_index = 0;

	wire uart_dout;


		clk = 0;
		reset=0;
		#100 reset=1;
	end

	always begin
		#5 clk=!clk;
		clk_n = !clk;
	end

	always @(posedge clk)
	begin
		case(current_state)
		IDLE:
		begin
			data_valid <= 0;
			clk_count <= 0;
			bit_index <= 0;
			if(uart_dout == 1'b0)
				current_state <= RX_START_BIT;
			else
				current_state <= IDLE;
		end
		RX_START_BIT:
		begin
			if(clk_count == (CLKS_PER_BIT-1)/2)
			begin
				if(uart_dout == 1'b0)
				begin
					clk_count <= 0;
					current_state <= RX_DATA_BITS;
				end
				else
					current_state<= IDLE;
			end
			else
			begin
				clk_count <= clk_count +1;
				current_state <= RX_START_BIT;
			end
		end
		RX_DATA_BITS:
		begin
			if(clk_count < CLKS_PER_BIT -1)
			begin
				clk_count <= clk_count + 1;
				current_state <= RX_DATA_BITS;
			end
			else
			begin
				clk_count<=0;
				data_byte[bit_index] <= uart_dout;
				if(bit_index<7)
				begin
					bit_index<=bit_index+1;
					current_state<=RX_DATA_BITS;
				end
				else
				begin
					bit_index <= 0;
					current_state <= RX_STOP_BIT;
				end
			end
		end
		RX_STOP_BIT:
		begin
			if(clk_count < CLKS_PER_BIT-1)
			begin
				clk_count<=clk_count+1;
				current_state<=RX_STOP_BIT;
			end
			else
			begin
				data_valid <= 1;
				clk_count<=0;
				current_state <= CLEAN_UP;
			end
		end
		CLEAN_UP:
		begin
			current_state<=IDLE;
			data_valid <= 0;
		end
		default:
			current_state<=IDLE;
		endcase
	end
	always @(posedge clk)
	begin
		if(data_valid==1'b1)//Just a case used to indicate the end of the test when loaded from the test file.
		begin
			$write("%s",data_byte);//To be sent to the terminal.
		end
	end
	
	design_1_wrapper dut
	(.diff_clock_rtl_0_clk_n(clk_n), .diff_clock_rtl_0_clk_p(clk), .reset_rtl_0(reset),
		.usb_uart_txd(uart_dout),
		.usb_uart_rxd()
	);


endmodule