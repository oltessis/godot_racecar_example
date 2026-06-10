#pragma once

#include "interfaces.h"
#include <vector>

namespace racecar {

class PpmEncoder : public Signal {
private:
    const Control& control;
    const int pulse_delay = 300;
    const int frame_stop = 3000;

public:
    explicit PpmEncoder(const Control& ctrl) : control(ctrl) {}

    bool level(int tick) const override;
};

} // namespace racecar
