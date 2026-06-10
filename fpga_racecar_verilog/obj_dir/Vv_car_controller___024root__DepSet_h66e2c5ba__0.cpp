// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vv_car_controller.h for the primary calling header

#include "Vv_car_controller__pch.h"
#include "Vv_car_controller___024root.h"

void Vv_car_controller___024root___eval_act(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_act\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vv_car_controller___024root___nba_sequent__TOP__0(Vv_car_controller___024root* vlSelf);

void Vv_car_controller___024root___eval_nba(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_nba\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vv_car_controller___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vv_car_controller___024root___nba_sequent__TOP__0(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___nba_sequent__TOP__0\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __Vdly__v_car_controller__DOT__counter;
    __Vdly__v_car_controller__DOT__counter = 0;
    CData/*3:0*/ __Vdly__v_car_controller__DOT__channel_index;
    __Vdly__v_car_controller__DOT__channel_index = 0;
    IData/*31:0*/ __Vdly__v_car_controller__DOT__pwm_ch1__DOT__counter;
    __Vdly__v_car_controller__DOT__pwm_ch1__DOT__counter = 0;
    IData/*31:0*/ __Vdly__v_car_controller__DOT__pwm_ch2__DOT__counter;
    __Vdly__v_car_controller__DOT__pwm_ch2__DOT__counter = 0;
    // Body
    __Vdly__v_car_controller__DOT__counter = vlSelfRef.v_car_controller__DOT__counter;
    __Vdly__v_car_controller__DOT__channel_index = vlSelfRef.v_car_controller__DOT__channel_index;
    __Vdly__v_car_controller__DOT__pwm_ch1__DOT__counter 
        = vlSelfRef.v_car_controller__DOT__pwm_ch1__DOT__counter;
    __Vdly__v_car_controller__DOT__pwm_ch2__DOT__counter 
        = vlSelfRef.v_car_controller__DOT__pwm_ch2__DOT__counter;
    if (vlSelfRef.rst) {
        __Vdly__v_car_controller__DOT__pwm_ch1__DOT__counter = 0U;
        vlSelfRef.servo_pwm = 0U;
        __Vdly__v_car_controller__DOT__pwm_ch2__DOT__counter = 0U;
        vlSelfRef.motor_pwm = 0U;
        __Vdly__v_car_controller__DOT__counter = 0U;
        __Vdly__v_car_controller__DOT__channel_index = 0U;
        vlSelfRef.v_car_controller__DOT__ch1_ticks = 0U;
        vlSelfRef.v_car_controller__DOT__ch2_ticks = 0U;
    } else {
        __Vdly__v_car_controller__DOT__pwm_ch1__DOT__counter 
            = ((0x4e1fU <= vlSelfRef.v_car_controller__DOT__pwm_ch1__DOT__counter)
                ? 0U : ((IData)(1U) + vlSelfRef.v_car_controller__DOT__pwm_ch1__DOT__counter));
        vlSelfRef.servo_pwm = (vlSelfRef.v_car_controller__DOT__pwm_ch1__DOT__counter 
                               < vlSelfRef.v_car_controller__DOT__ch1_ticks);
        __Vdly__v_car_controller__DOT__pwm_ch2__DOT__counter 
            = ((0x4e1fU <= vlSelfRef.v_car_controller__DOT__pwm_ch2__DOT__counter)
                ? 0U : ((IData)(1U) + vlSelfRef.v_car_controller__DOT__pwm_ch2__DOT__counter));
        vlSelfRef.motor_pwm = (vlSelfRef.v_car_controller__DOT__pwm_ch2__DOT__counter 
                               < vlSelfRef.v_car_controller__DOT__ch2_ticks);
        if (vlSelfRef.ppm_input) {
            __Vdly__v_car_controller__DOT__counter 
                = ((IData)(1U) + vlSelfRef.v_car_controller__DOT__counter);
        }
        if (((~ (IData)(vlSelfRef.ppm_input)) & (IData)(vlSelfRef.v_car_controller__DOT__ppm_prev))) {
            if ((0x9c4U < vlSelfRef.v_car_controller__DOT__counter)) {
                __Vdly__v_car_controller__DOT__channel_index = 0U;
            } else {
                if ((0U == (IData)(vlSelfRef.v_car_controller__DOT__channel_index))) {
                    vlSelfRef.v_car_controller__DOT__ch1_ticks 
                        = vlSelfRef.v_car_controller__DOT__counter;
                } else if ((1U == (IData)(vlSelfRef.v_car_controller__DOT__channel_index))) {
                    vlSelfRef.v_car_controller__DOT__ch2_ticks 
                        = vlSelfRef.v_car_controller__DOT__counter;
                }
                __Vdly__v_car_controller__DOT__channel_index 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelfRef.v_car_controller__DOT__channel_index)));
            }
            __Vdly__v_car_controller__DOT__counter = 0U;
        }
    }
    vlSelfRef.v_car_controller__DOT__pwm_ch1__DOT__counter 
        = __Vdly__v_car_controller__DOT__pwm_ch1__DOT__counter;
    vlSelfRef.v_car_controller__DOT__pwm_ch2__DOT__counter 
        = __Vdly__v_car_controller__DOT__pwm_ch2__DOT__counter;
    vlSelfRef.v_car_controller__DOT__counter = __Vdly__v_car_controller__DOT__counter;
    vlSelfRef.v_car_controller__DOT__channel_index 
        = __Vdly__v_car_controller__DOT__channel_index;
    vlSelfRef.v_car_controller__DOT__ppm_prev = ((1U 
                                                  & (~ (IData)(vlSelfRef.rst))) 
                                                 && (IData)(vlSelfRef.ppm_input));
}

void Vv_car_controller___024root___eval_triggers__act(Vv_car_controller___024root* vlSelf);

bool Vv_car_controller___024root___eval_phase__act(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_phase__act\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vv_car_controller___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vv_car_controller___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vv_car_controller___024root___eval_phase__nba(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_phase__nba\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vv_car_controller___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vv_car_controller___024root___dump_triggers__nba(Vv_car_controller___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vv_car_controller___024root___dump_triggers__act(Vv_car_controller___024root* vlSelf);
#endif  // VL_DEBUG

void Vv_car_controller___024root___eval(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vv_car_controller___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("v_car_controller.v", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vv_car_controller___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("v_car_controller.v", 2, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vv_car_controller___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vv_car_controller___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vv_car_controller___024root___eval_debug_assertions(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_debug_assertions\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.ppm_input & 0xfeU)))) {
        Verilated::overWidthError("ppm_input");}
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
