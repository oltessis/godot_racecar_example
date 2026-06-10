
// just WASD to servo and motor 
// WASD into DUT as ppm 
// servo and motor out as PWM
// throttle and steering 
// 	these are normalized values betwen [-1,1]
// potentially make it based off of wasd positioning 
#include "car_controller_testbench.h"
#include "Vv_car_controller.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

float delay = 300.0;
float stop = 3000.0;
uint64_t last_rise_time = 0;
uint16_t last_pulse_width = 1500;

bool prev_pwm = false;

CarController::CarController(){
	top = new Vv_car_controller;
	top->clk = 0;
}

CarController::~CarController(){
	delete top;
}

void CarController::_bind_methods(){
	ClassDB::bind_method(D_METHOD("step"), &CarController::step);
	ClassDB::bind_method(D_METHOD("set_ppm_input", "v"), &CarController::set_ppm_input);
	ClassDB::bind_method(D_METHOD("get_servo_pwm"), &CarController::get_servo_pwm);
}

void CarController::step() {
	ControlState cs;
	read_input(cs);
	
	ppm_channels[0] = 1500 + (int)(cs.throttle * 500.0f);
	ppm_channels[1] = 1500 + (int)(cs.steering * 500.0f);

	update_ppm(cs);

	top->clk = 1;
	top->eval();

	top->clk = 0;
	top->eval();

	sim_time += 2;

	update_pwm_measurement();
}

void CarController::read_input(ControlState &cs){
	Input *input = Input::get_singleton();

	cs.throttle = 
		input->get_action_strength("throttle_up") -
		input->get_action_strength("throttle_down");

	cs.steering =
		input->get_action_strength("steer_left") -
		input->get_action_strength("steer_right");

}

uint16_t to_ppm(float value){
	return 1500 + (int)(value * 500.0f);
}

void CarController::update_ppm(const ControlState &cs){
	static int channel = 0;
	static int time = 0;
	static bool high = false;

	if (!high){
		top->ppm_input = 0;

		if(time >= delay){
			time = 0;
			high = true;
		}
	} else {
		top->ppm_input = 1;

		uint16_t duration; 

		if(channel < 2){
			duration = ppm_channels[channel];
		} else {
			duration = stop;
		}

		if (time >= duration){
			time = 0;
			high = false;
			channel++;

			if(channel > 2){
				channel = 0;
			}
		}
	}
	
	time++;
}

void CarController::set_ppm_input(bool v){
	top->ppm_input = v;
}

bool CarController::get_servo_pwm() {
	// decode pwm convert to float 
	float v = (last_pulse_width - 1500.0f) / 500.0f;

	if (v > 1.0f) v = 1.0f;
	if (v < -1.0f) v = -1.0f;

	return v;
}

void CarController::update_pwm_measurement(){
	bool current = top->servo_pwm;

	if(current && !prev_pwm){
		last_rise_time = sim_time;
	}

	if(!current && prev_pwm){
		last_pulse_width = sim_time - last_rise_time;
	}
	
	// UtilityFunctions::print("PWM width: ", last_pulse_width);

	prev_pwm = current;
}

bool CarController::get_motor_pwm(){
	// decode pwm 
	return top->motor_pwm;
}
