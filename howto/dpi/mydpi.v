reg [7:0] uartcount;
reg transmit;
wire received;
reg [7:0] tx_byte;
wire [7:0] rx_byte;
wire is_receiving;
wire is_transmitting;
wire recv_error;
wire uartclk = tb_top.chip_inst.u_peri1_ss.peri1_apb_clk;

initial
	begin
		uartcount = 8'h00;
		transmit = 0;
		tx_byte = 8'h00;
	end

uart uartd(
	.clk(uartclk),
	.rx(tb_top.chip_inst.GPIO52),
	.tx(tb_top.chip_inst.GPIO53),
	.transmit(transmit),
	.tx_byte(tx_byte),
	.received(received),
	.rx_byte(rx_byte),
	.is_receiving(is_receiving),
	.is_transmitting(is_transmitting),
	.recv_error(recv_error)
);

import "DPI" function int mychar(int c);

always @ (posedge received) begin
	mychar(rx_byte);
end

always @ (posedge uartclk) begin
	uartcount = uartcount + 1;
	if (uartcount == 255) begin
		tx_byte = mychar(0);
		if (tx_byte) begin
			transmit = 1;
		end
	end else begin
		transmit = 0;
	end
end

import "DPI" function int do_jtag();
import "DPI" function void do_jtag_tdo(int tdo);

reg jcount;
wire jtck;
reg  jtms;
reg  jtdi;
wire jtdo;

assign jtck = jcount;
assign jtdo = tb_top.chip_inst.TDO;
assign tb_top.chip_inst.TDI = jtdi;
assign tb_top.chip_inst.TMS = jtms;
assign tb_top.chip_inst.TCK = jtck;
assign tb_top.chip_inst.nTRST = tb_top.chip_inst.nRESETN_I;

initial
	begin
		jcount = 0;
		jtms = 1;
		jtdi = 0;
	end

`ifndef DUMMY_DBG_TOP
always @ (posedge tb_top.chip_inst.u_ap0_ss.clk_core0_i) begin
	jcount = ~jcount;
	if (jcount == 0) begin
		{jtms, jtdi} = do_jtag();
	end else begin
		if (jcount == 1) begin
			do_jtag_tdo(jtdo);
		end
	end
end
`endif
