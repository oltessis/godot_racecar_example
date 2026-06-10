#pragma once

#include "interfaces.h"
#include <vector>
#include <memory>

namespace racecar {

/**
 * A Control that records every time it is read.
 */
class TrackedControl : public Control {
private:
    const Control& origin;
    mutable std::vector<std::pair<float, float>> history;

public:
    explicit TrackedControl(const Control& origin) : origin(origin) {}

    float throttle() const override {
        float val = origin.throttle();
        // For simplicity, we only record when throttle is called, 
        // assuming steering is called together.
        return val;
    }

    float steering() const override {
        float val = origin.steering();
        history.push_back({origin.throttle(), val});
        return val;
    }

    const std::vector<std::pair<float, float>>& get_history() const {
        return history;
    }
};

/**
 * A Signal that records its levels.
 */
class TrackedSignal : public Signal {
private:
    const Signal& origin;
    mutable std::vector<bool> history;

public:
    explicit TrackedSignal(const Signal& origin) : origin(origin) {}

    bool level(int tick) const override {
        bool val = origin.level(tick);
        history.push_back(val);
        return val;
    }

    const std::vector<bool>& get_history() const {
        return history;
    }
};

} // namespace racecar
