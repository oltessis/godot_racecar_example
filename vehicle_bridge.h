
#pragma once

#include <godot_cpp/classes/vehicle_body3d.hpp>
#include "verilated.h"
#include "Vv_car_controller.h"

using namespace godot;

class VehicleBridge : public VehicleBody3D {
  GDCLASS(VehicleBridge, VehicleBody3D);


  struct DebugState {
    float i_throttle = 0.0f;
    float i_steer = 0.0f;

    int throttle_us = 1500;
    int steering_us = 1500;

    int motor_pulse_width = 1500;
    int servo_pulse_width = 1500;

    float o_throttle = 0.0f;
    float o_steer = 0.0f;

    String to_string() const {
      return vformat(
        "\n"
        "Input:\n" 
        " throttle: %.2f\n"
        " steer: %.2f\n"
        "\n"
        "PPM:\n"
        " throttle_us: %d\n"
        " steering_us: %d\n" 
        "\n" 
        "PWM:\n"
        " motor_width: %d\n" 
        " servo_width: %d\n" 
        "\n" 
        "Output:\n" 
        " throttle: %.2f\n" 
        " steer: %.2f",
        i_throttle,
        i_steer,
        throttle_us,
        steering_us,
        motor_pulse_width,
        servo_pulse_width,
        o_throttle,
        o_steer 
      );
    }

    String diff(const DebugState &prev) const {
        String out;

        if (i_throttle != prev.i_throttle)
            out += vformat(
                "i_throttle: %.2f → %.2f\n",
                prev.i_throttle,
                i_throttle
            );

        if (i_steer != prev.i_steer)
            out += vformat(
                "i_steer: %.2f → %.2f\n",
                prev.i_steer,
                i_steer
            );

        if (throttle_us != prev.throttle_us)
            out += vformat(
                "throttle_us: %d → %d\n",
                prev.throttle_us,
                throttle_us
            );

        if (motor_pulse_width != prev.motor_pulse_width)
            out += vformat(
                "motor_pwm: %d → %d\n",
                prev.motor_pulse_width,
                motor_pulse_width
            );

        if (o_throttle != prev.o_throttle)
            out += vformat(
                "o_throttle: %.2f → %.2f\n",
                prev.o_throttle,
                o_throttle
            );

        return out;
      }
    };

  private:
   Vv_car_controller* dut;

   float i_steer = 0.0f;
   float i_throttle = 0.0f;
   float o_steer = 0.0f;
   float o_throttle = 0.0f;
    int motor_count = 0;
    int servo_count = 0;
    int servo_pulse_width = 0;
    int motor_pulse_width = 0;
    bool prev_motor_pwm = false;
    bool prev_servo_pwm = false;

    DebugState current_state;
    DebugState prev_state;
    
  protected:
    void get_wasd();
    void run_simulation();

  public:
    VehicleBridge();
    ~VehicleBridge();
    
    static void _bind_methods();

    void _ready();
    void _physics_process(double);

    float get_throttle() const;
    float get_steering() const;

  };
