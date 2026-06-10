extends VehicleBridge

@export var MAX_STEER = 2.0 
@export var ENGINE_POWER = 2000 
var throttle_input: float = 0.0 
var steering_input: float = 0.0  

@export_group("Stability Control")
@export var roll_influence: float = 0.5 
var anti_roll_torque: Vector3
var downforce: Vector3  
@export var anti_roll_force = 20.0  
@export var downforce_factor: float = 50.0 

@export_group("Speed")
@export var max_speed = 50.0 
@export var acceleration: float = 120 
var vehicle_linear_velocity: float = 0.0

@export_group("Steering & Brake")
@export var steering_speed = 1.5 
@export var max_steering_angle = 0.65 
@export var handbrake_force = 5.0 
var handbrake: bool = false 

@export_group("Wheel")
@export var front_left_wheel: VehicleWheel3D
@export var front_right_wheel: VehicleWheel3D
@export var rear_left_wheel: VehicleWheel3D
@export var rear_right_wheel: VehicleWheel3D

@export_group("Suspension Setting")
@export var wheel_friction: float = 6.0
@export var suspension_stiff_value: float = 4.0 

func _process(_delta: float) -> void:
		print(throttle)

func _physics_process(delta: float) -> void:
	#steering = move_toward(steering, Input.get_axis("steer_left", "steer_right") * MAX_STEER, delta * 10)
	#engine_force = Input.get_axis("throttle_down", "throttle_up") * ENGINE_POWER
	handle_vehicle_control(delta)
	handle_engine_velocity()
#	handle_anti_roll()

func _ready():
	#super._ready()
	center_of_mass_mode = RigidBody3D.CENTER_OF_MASS_MODE_CUSTOM
	global_position.y += 5
	for wheel in [front_left_wheel, front_right_wheel, rear_left_wheel, rear_right_wheel]:
			wheel.suspension_stiffness = suspension_stiff_value
			wheel.wheel_friction_slip = wheel_friction
	fix_wheel_symmetry()

func handle_vehicle_control(delta):
	# throttle and steering are properties from VehicleBridge
	steering_input = self.steering
	handbrake = Input.is_action_pressed("handbrake") 
	
	#steering = move_toward(steering, steering_input * max_steering_angle, delta * steering_speed)

func handle_engine_velocity():
	vehicle_linear_velocity = linear_velocity.length() 
	engine_force = self.throttle * ENGINE_POWER

func handle_anti_roll(): 
	anti_roll_torque = -global_transform.basis.z * global_rotation.z * anti_roll_force * max_speed 
	apply_torque(anti_roll_torque) 
	
	downforce = -global_transform.basis.y * vehicle_linear_velocity * downforce_factor 
	apply_central_force(downforce)
	
	for wheel in [front_left_wheel, front_right_wheel, rear_left_wheel, rear_right_wheel]:
		wheel.wheel_roll_influence = roll_influence

func fix_wheel_symmetry():
	# Based on the model orientation: X = length (Front/Back), Z = width (Left/Right)
	var wheels = [front_left_wheel, front_right_wheel, rear_left_wheel, rear_right_wheel]
	
	# 1. Clean up rotations to be perfectly parallel (facing +X)
	# Godot's VehicleWheel3D faces -Z by default. To face +X, we rotate 90 degrees around Y.
	var clean_basis = Basis(Vector3(0,0,-1), Vector3(0,1,0), Vector3(1,0,0))
	
	# 2. Fix positions for symmetry
	# FRONT WHEELS
	var fl = front_left_wheel.transform.origin
	var fr = front_right_wheel.transform.origin
	var front_x = (fl.x + fr.x) / 2.0
	var front_y = (fl.y + fr.y) / 2.0
	var front_z_center = (fl.z + fr.z) / 2.0
	var front_z_half_width = abs(fl.z - fr.z) / 2.0
	
	front_left_wheel.transform.origin = Vector3(front_x, front_y, front_z_center - front_z_half_width)
	front_right_wheel.transform.origin = Vector3(front_x, front_y, front_z_center + front_z_half_width)

	# REAR WHEELS
	var rl = rear_left_wheel.transform.origin
	var rr = rear_right_wheel.transform.origin
	var rear_x = (rl.x + rr.x) / 2.0
	var rear_y = (rl.y + rr.y) / 2.0
	var rear_z_center = (rl.z + rr.z) / 2.0
	var rear_z_half_width = abs(rl.z - rr.z) / 2.0
	
	rear_left_wheel.transform.origin = Vector3(rear_x, rear_y, rear_z_center - rear_z_half_width)
	rear_right_wheel.transform.origin = Vector3(rear_x, rear_y, rear_z_center + rear_z_half_width)
	
	# Apply clean rotations
	for wheel in wheels:
		wheel.transform.basis = clean_basis

	# 3. Set Center of Mass to the midpoint of the wheels
	var total_center_z = (front_z_center + rear_z_center) / 2.0
	var total_center_x = (front_x + rear_x) / 2.0
	center_of_mass = Vector3(total_center_x, -0.5, total_center_z)
