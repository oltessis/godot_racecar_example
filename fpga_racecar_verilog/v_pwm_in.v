
module v_pwm_in (
  parameter COUNTER_WIDTH = 32;
)(
    input wire clk,
    input wire rst,
    input wire signal,

    output reg [COUNTER_WIDTH-1:0] period,
    output reg [COUNTER_WIDTH-1:0] high_time,
    output reg valid
);

    reg [COUNTER_WIDTH-1:0] counter;
    reg [COUNTER_WIDTH-1:0] high_counter;

    reg signal_d;

    wire rising_edge = signal & ~signal_d;
    wire falling_edge = ~signal & signal_d;

    always @(posedge clk) begin
      if(rst) begin  
        counter <= 0;
        high_counter <= 0;
        period <= 0;
        high_time <= 0;
        signal_d <= 0;
        valid <= 0;
      end else begin 
        signal_d <= signal;
        
        counter <= counter + 1;

        if (signal)
          high_counter <= high_counter + 1;

        if (rising_edge) begin 
          period <= counter;
          high_time <= high_counter;

          counter <= 0;
          high_counter <= 0;

          valid <= 1;
        end else begin 
          valid <= 0; 
        end 
      end 
    end

  // Module body
endmodule
