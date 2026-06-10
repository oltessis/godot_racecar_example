#include "vehicle_bridge.h"
#include <chrono>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

float get_wasd_prev_throttle = 999.0;
float push_to_dut_prev_throttle = 999.0;
float pull_from_dut_prev_throttle = 999.0;


struct Pulse {
	bool level;
	int duration_ticks;
};

struct Pwm {
	bool current_level;
	bool prev_level;
	int duration_ticks;
};

// here is the interface
//    VL_IN8(&clk,0,0);
//    VL_IN8(&ppm_input,0,0);
//    VL_IN8(&rst,0,0);
//    VL_OUT8(&servo_pwm,0,0);
//    VL_OUT8(&motor_pwm,0,0);


void VehicleBridge::get_wasd(){
	Input *input = Input::get_singleton();

	i_throttle = 0.0f;
	i_steer = 0.0f;

	if (input->is_action_pressed("throttle_up")) {
		i_throttle = 1.0f;
	}

	if (input->is_action_pressed("throttle_down")) {
		i_throttle = -1.0f;
	}

	if (input->is_action_pressed("steer_right")) {
		i_steer = -1.0f;
	}

	if (input->is_action_pressed("steer_left")) {
		i_steer = 1.0f;
	}

}


void VehicleBridge::run_simulation(){
// convert throttle and steering to ppm 
// 1000 - 2000ms for pulse values 
// 3ms gaps at the end of the frames
// 3000ms to mark the end of frames 

	int throttle_us = 1500 + (i_throttle * 500);
	int steering_us = 1500 + (i_steer * 500);

	std::vector<Pulse> ppm_frame = 
	{
		{0, 300},
		{1, throttle_us},
		{0, 300},
		{1, steering_us},
		{0,300},
		{1,3000}
	};

	static int pulse_index = 0;
	static int remaining_ticks = 0;

	const int frame_size = ppm_frame.size();
	
	for(int i=0; i < 20000; i++){

		if(remaining_ticks <= 0){
			pulse_index = (pulse_index + 1) % frame_size;
			remaining_ticks = ppm_frame[pulse_index].duration_ticks;
		}

		dut->ppm_input = ppm_frame[pulse_index].level;
		
		remaining_ticks--;

		dut->clk = 1;
		dut->eval();

		// pull from dut logic moved inside loop
		bool motor = dut->motor_pwm;
		bool servo = dut->servo_pwm;

		// rising edge detector
		if(motor && !prev_motor_pwm){
			motor_count = 0;
		}
		if(servo && !prev_servo_pwm){
			servo_count = 0;
		}

		if(motor){
			motor_count++;
		}
		if(servo){
			servo_count++;
		}
		
		// falling edge detector
		if(!motor && prev_motor_pwm){
			motor_pulse_width = motor_count;
		}
		if(!servo && prev_servo_pwm){
			servo_pulse_width = servo_count;
		}

		prev_motor_pwm = motor;
		prev_servo_pwm = servo;

		dut->clk = 0;
		dut->eval();
	}

	o_throttle = std::clamp(((motor_pulse_width - 1500.0f) / 500.0f), -1.0f, 1.0f);
	o_steer = std::clamp(((servo_pulse_width - 1500.0f) / 500.0f), -1.0f, 1.0f);
}


float VehicleBridge::get_throttle() const{
	return o_throttle;
}


float VehicleBridge::get_steering() const{
	return o_steer;
}


void VehicleBridge::_ready(){
	set_physics_process(true);
	
	InputMap *im = InputMap::get_singleton();
	
	// Ensure required actions exist
	const char* required_actions[] = {"throttle_up", "throttle_down", "steer_left", "steer_right", "handbrake"};
	for (const char* action : required_actions) {
		if (!im->has_action(action)) {
			im->add_action(action);
			UtilityFunctions::print("VehicleBridge: Added missing input action: ", action);
		}
	}

	TypedArray<StringName> actions = im->get_actions();
	UtilityFunctions::print("Available actions count: ", actions.size());
}


// basically the main loop, this get triggered at 60hz
void VehicleBridge::_physics_process(double delta){

	get_wasd();
	run_simulation();

	current_state.i_throttle = i_throttle;
	current_state.i_steer = i_steer;

	
	current_state.throttle_us =
        1500 + (i_throttle * 500);

  current_state.steering_us =
        1500 + (i_steer * 500);

  current_state.motor_pulse_width =
        motor_pulse_width;

  current_state.servo_pulse_width =
        servo_pulse_width;

  current_state.o_throttle =
        o_throttle;

  current_state.o_steer =
        o_steer;

	// Compare current frame to previous frame
	String changes =
			current_state.diff(prev_state);

	// Print only if something changed
	if (!changes.is_empty()) {
			UtilityFunctions::print(changes);
	}

	prev_state = current_state;

}

void VehicleBridge::_bind_methods(){
	ClassDB::bind_method(
			D_METHOD("get_throttle"),
			&VehicleBridge::get_throttle 
	);

	ClassDB::bind_method(
			D_METHOD("get_steering"),
			&VehicleBridge::get_steering 
	);

		
	ADD_PROPERTY(
		PropertyInfo(Variant::FLOAT, "throttle"),
		"",
		"get_throttle"
	);

	ADD_PROPERTY(
		PropertyInfo(Variant::FLOAT, "steering"),
		"",
		"get_steering"
	);

}

VehicleBridge::VehicleBridge(){
	dut = new Vv_car_controller;
	motor_pulse_width = 1500;
	servo_pulse_width = 1500;
}

VehicleBridge::~VehicleBridge() {
	delete dut;
}




