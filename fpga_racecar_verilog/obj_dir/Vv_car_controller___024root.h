// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vv_car_controller.h for the primary calling header

#ifndef VERILATED_VV_CAR_CONTROLLER___024ROOT_H_
#define VERILATED_VV_CAR_CONTROLLER___024ROOT_H_  // guard

#include "verilated.h"


class Vv_car_controller__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vv_car_controller___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(ppm_input,0,0);
    VL_IN8(rst,0,0);
    VL_OUT8(servo_pwm,0,0);
    VL_OUT8(motor_pwm,0,0);
    CData/*0:0*/ v_car_controller__DOT__ppm_prev;
    CData/*3:0*/ v_car_controller__DOT__channel_index;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ v_car_controller__DOT__counter;
    IData/*31:0*/ v_car_controller__DOT__ch1_ticks;
    IData/*31:0*/ v_car_controller__DOT__ch2_ticks;
    IData/*31:0*/ v_car_controller__DOT__pwm_ch1__DOT__counter;
    IData/*31:0*/ v_car_controller__DOT__pwm_ch2__DOT__counter;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vv_car_controller__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vv_car_controller___024root(Vv_car_controller__Syms* symsp, const char* v__name);
    ~Vv_car_controller___024root();
    VL_UNCOPYABLE(Vv_car_controller___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
