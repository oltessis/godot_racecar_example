#pragma once

#include "interfaces.h"
#include "Vv_car_controller.h"
#include <memory>

namespace racecar {

class VerilatedCar : public CarController {
private:
    std::unique_ptr<Vv_car_controller> top;

public:
    VerilatedCar() : top(std::make_unique<Vv_car_controller>()) {
        top->clk = 0;
    }

    void step(bool ppm_input) override {
        top->ppm_input = ppm_input;
        
        top->clk = 1;
        top->eval();
        
        top->clk = 0;
        top->eval();
    }

    bool motor_pwm() const override {
        return top->motor_pwm;
    }

    bool servo_pwm() const override {
        return top->servo_pwm;
    }
};

} // namespace racecar
