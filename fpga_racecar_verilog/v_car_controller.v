
module v_car_controller (
    // Ports
    input  wire ppm_input,
    input  wire clk,
    input  wire rst,
    output wire servo_pwm,
    output wire motor_pwm
);
  // ppm in two pwm channels out, (motor, servo)
  
  // lets say 2500 clock cycles stops the gap 
  localparam GAP_THRESHOLD = 2500;

  reg ppm_prev;
  reg [31:0] counter;
  reg [3:0] channel_index;
  
  reg [31:0] ch1_ticks;
  reg [31:0] ch2_ticks;

  wire falling = (ppm_input == 0 && ppm_prev == 1);

  // ppm splitter
  // send two pwm channels 
  v_pwm_out #(
      .CLK_FREQ(1_000_000),
      .PWM_FREQ(50)
  ) pwm_ch1 (
      .clk(clk),
      .rst(rst),
      .pulse_width_ticks(ch1_ticks),
      .pwm(servo_pwm)
  );

  v_pwm_out #(
      .CLK_FREQ(1_000_000),
      .PWM_FREQ(50)
  ) pwm_ch2 (
      .clk(clk),
      .rst(rst),
      .pulse_width_ticks(ch2_ticks),
      .pwm(motor_pwm)
  );

  // split ppm signal into two channels
  always @(posedge clk) begin
    if (rst) begin
      ppm_prev <= 0;
      counter <= 0;
      channel_index <= 0;
      ch1_ticks <= 0;
      ch2_ticks <= 0;
    end else begin
      ppm_prev <= ppm_input;

      if (ppm_input) 
        counter <= counter + 1;

      if (falling) begin
        if (counter > GAP_THRESHOLD) begin
          channel_index <= 0;  // new frame
        end else begin
          case (channel_index)
            4'd0: ch1_ticks <= counter;
            4'd1: ch2_ticks <= counter;
            default: ;
          endcase
          channel_index <= channel_index + 4'd1;
        end
        counter <= 0;
      end
    end
  end

endmodule
