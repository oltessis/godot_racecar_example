// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VV_CAR_CONTROLLER__SYMS_H_
#define VERILATED_VV_CAR_CONTROLLER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vv_car_controller.h"

// INCLUDE MODULE CLASSES
#include "Vv_car_controller___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vv_car_controller__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vv_car_controller* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vv_car_controller___024root    TOP;

    // CONSTRUCTORS
    Vv_car_controller__Syms(VerilatedContext* contextp, const char* namep, Vv_car_controller* modelp);
    ~Vv_car_controller__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
