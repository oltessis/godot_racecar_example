// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vv_car_controller.h for the primary calling header

#include "Vv_car_controller__pch.h"
#include "Vv_car_controller___024root.h"

VL_ATTR_COLD void Vv_car_controller___024root___eval_static(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_static\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vv_car_controller___024root___eval_initial(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_initial\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vv_car_controller___024root___eval_final(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_final\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vv_car_controller___024root___eval_settle(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___eval_settle\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vv_car_controller___024root___dump_triggers__act(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___dump_triggers__act\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vv_car_controller___024root___dump_triggers__nba(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___dump_triggers__nba\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vv_car_controller___024root___ctor_var_reset(Vv_car_controller___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vv_car_controller___024root___ctor_var_reset\n"); );
    Vv_car_controller__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->ppm_input = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 171014415259859041ull);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->servo_pwm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16799601483404756680ull);
    vlSelf->motor_pwm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13729791733360175450ull);
    vlSelf->v_car_controller__DOT__ppm_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9096726633618623291ull);
    vlSelf->v_car_controller__DOT__counter = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3161364531241322946ull);
    vlSelf->v_car_controller__DOT__channel_index = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7890455007155522077ull);
    vlSelf->v_car_controller__DOT__ch1_ticks = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 102402047618277806ull);
    vlSelf->v_car_controller__DOT__ch2_ticks = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15987607694588563708ull);
    vlSelf->v_car_controller__DOT__pwm_ch1__DOT__counter = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8660533388947770848ull);
    vlSelf->v_car_controller__DOT__pwm_ch2__DOT__counter = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3204262875917689102ull);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9526919608049418986ull);
}
