CXX = g++

SRC = \
    vehicle_bridge.cpp \
    register_types.cpp \
    $(wildcard fpga_racecar_verilog/obj_dir/*.cpp) \
    /usr/share/verilator/include/verilated.cpp \
    /usr/share/verilator/include/verilated_threads.cpp

TARGET = libvehicle_bridge.so

CXXFLAGS = -std=c++20 -fPIC \
    -Igodot-cpp/include \
    -Igodot-cpp/gen/include \
    -Ifpga_racecar_verilog/obj_dir \
    -I/usr/share/verilator/include

LDFLAGS = -shared

LIBS = \
    godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o $(TARGET)
	cp $(TARGET) fpga-racecar/$(TARGET)
