
module v_counter #(
  parameter WIDTH = 32;
)(
  input wire clk,
  input wire rst,
  input wire en,

  input wire [WIDTH-1:0] max_value,

  output reg [WIDTH-1:0] count,
  output reg tick 
);
  always @(posedge clk) begin
    if(rst) begin 
      count <= 0;
      tick <= 0;
    end else begin 
      tick <= 0;

      if(en)begin 
        if (count >= max_value)begin 
          count <= 0;
          tick <= 1;
        end else begin 
          count <= count + 1;
        end 
      end 
    end 
  end

endmodule
