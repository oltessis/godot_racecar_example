#include "core/ppm_encoder.h"
#include <vector>

namespace racecar {

struct Pulse {
    bool level;
    int duration;
};

bool PpmEncoder::level(int tick) const {
    int throttle_us = 1500 + static_cast<int>(control.throttle() * 500);
    int steering_us = 1500 + static_cast<int>(control.steering() * 500);

    std::vector<Pulse> pulses = {
        {false, pulse_delay},
        {true,  throttle_us},
        {false, pulse_delay},
        {true,  steering_us},
        {false, pulse_delay},
        {true,  frame_stop}
    };

    int total_period = 0;
    for (const auto& p : pulses) total_period += p.duration;

    int local_tick = tick % total_period;
    int cumulative = 0;
    for (const auto& p : pulses) {
        cumulative += p.duration;
        if (local_tick < cumulative) {
            return p.level;
        }
    }
    return false;
}

} // namespace racecar
