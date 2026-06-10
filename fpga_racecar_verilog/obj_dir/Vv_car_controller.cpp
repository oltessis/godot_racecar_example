// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vv_car_controller__pch.h"

//============================================================
// Constructors

Vv_car_controller::Vv_car_controller(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vv_car_controller__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , ppm_input{vlSymsp->TOP.ppm_input}
    , rst{vlSymsp->TOP.rst}
    , servo_pwm{vlSymsp->TOP.servo_pwm}
    , motor_pwm{vlSymsp->TOP.motor_pwm}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vv_car_controller::Vv_car_controller(const char* _vcname__)
    : Vv_car_controller(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vv_car_controller::~Vv_car_controller() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vv_car_controller___024root___eval_debug_assertions(Vv_car_controller___024root* vlSelf);
#endif  // VL_DEBUG
void Vv_car_controller___024root___eval_static(Vv_car_controller___024root* vlSelf);
void Vv_car_controller___024root___eval_initial(Vv_car_controller___024root* vlSelf);
void Vv_car_controller___024root___eval_settle(Vv_car_controller___024root* vlSelf);
void Vv_car_controller___024root___eval(Vv_car_controller___024root* vlSelf);

void Vv_car_controller::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vv_car_controller::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vv_car_controller___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vv_car_controller___024root___eval_static(&(vlSymsp->TOP));
        Vv_car_controller___024root___eval_initial(&(vlSymsp->TOP));
        Vv_car_controller___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vv_car_controller___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vv_car_controller::eventsPending() { return false; }

uint64_t Vv_car_controller::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vv_car_controller::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vv_car_controller___024root___eval_final(Vv_car_controller___024root* vlSelf);

VL_ATTR_COLD void Vv_car_controller::final() {
    Vv_car_controller___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vv_car_controller::hierName() const { return vlSymsp->name(); }
const char* Vv_car_controller::modelName() const { return "Vv_car_controller"; }
unsigned Vv_car_controller::threads() const { return 1; }
void Vv_car_controller::prepareClone() const { contextp()->prepareClone(); }
void Vv_car_controller::atClone() const {
    contextp()->threadPoolpOnClone();
}
