module v_pwm_out #(
    parameter CLK_FREQ = 50_000_000,
    parameter PWM_FREQ = 50
)(
  input wire clk,
  input wire rst,

  input wire [31:0] pulse_width_ticks,

  output reg pwm 
);
  
  localparam PERIOD_TICKS = CLK_FREQ / PWM_FREQ;

  reg [31:0] counter;

  always @(posedge clk) begin
    if(rst) begin 
      counter <= 0;
      pwm <= 0;
    end else begin 
      if (counter >= PERIOD_TICKS - 1)
        counter <= 0;
      else 
        counter <= counter + 1;

      if(counter < pulse_width_ticks)
        pwm <= 1;
      else 
        pwm <= 0; 
    end 
  end

endmodule
