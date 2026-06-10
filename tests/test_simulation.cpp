#include <gtest/gtest.h>
#include "core/interfaces.h"
#include "core/tracked.h"
#include "core/ppm_encoder.h"
#include "core/verilated_car.h"

using namespace racecar;

class MockControl : public Control {
public:
    float throttle() const override { return 1.0f; } // Full throttle
    float steering() const override { return -0.5f; } // Slight right
};

TEST(RacecarTest, TrackValuesThroughSystem) {
    // 1. Setup Input
    MockControl raw_input;
    TrackedControl input(raw_input);

    // 2. Setup Encoder (Signal)
    PpmEncoder encoder(input);
    TrackedSignal signal(encoder);

    // 3. Setup DUT
    VerilatedCar car;

    // 4. Run simulation for a few ticks
    for (int i = 0; i < 10000; ++i) {
        bool level = signal.level(i);
        car.step(level);
    }

    // 5. Assertions and Value Tracking
    auto input_history = input.get_history();
    auto signal_history = signal.get_history();

    EXPECT_FALSE(input_history.empty());
    EXPECT_EQ(signal_history.size(), 10000);

    // We can "track" exactly what went into the DUT at any tick
    std::cout << "Tick 500 signal level: " << signal_history[500] << std::endl;
    std::cout << "Input throttle used: " << input_history[0].first << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
