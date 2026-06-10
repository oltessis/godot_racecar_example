
#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input.hpp>
#include "Vv_car_controller.h"
#include <iostream>

using namespace godot;

class CarController : public Node {
    GDCLASS(CarController, Node);

    private:
      Vv_car_controller* top;
      uint64_t sim_time = 0;
      uint16_t ppm_channels[2] = {1500, 1500};

    protected:
      static void _bind_methods();

    public: 
      CarController();
      ~CarController();

      struct ControlState {
          float throttle;
          float steering;
      };

      void step();
      void update_ppm(const ControlState &cs);
      void update_pwm_measurement();
      void read_input(ControlState &cs);

      void set_ppm_input(bool v);
      bool get_servo_pwm();
      bool get_motor_pwm();
};

