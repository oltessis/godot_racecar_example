#pragma once

#include <vector>

namespace racecar {

/**
 * Representing the driver's intent.
 */
class Control {
public:
    virtual ~Control() = default;
    virtual float throttle() const = 0;
    virtual float steering() const = 0;
};

/**
 * Representing a physical signal level (0 or 1) at a given time tick.
 */
class Signal {
public:
    virtual ~Signal() = default;
    virtual bool level(int tick) const = 0;
};

/**
 * The Device Under Test (FPGA Car Controller).
 */
class CarController {
public:
    virtual ~CarController() = default;
    virtual void step(bool ppm_input) = 0;
    virtual bool motor_pwm() const = 0;
    virtual bool servo_pwm() const = 0;
};

/**
 * Decoded output from the car.
 */
class DecodedOutput {
public:
    virtual ~DecodedOutput() = default;
    virtual float throttle() const = 0;
    virtual float steering() const = 0;
};

} // namespace racecar
