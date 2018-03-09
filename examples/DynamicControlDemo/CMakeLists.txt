add_library(DynamicControlDemo STATIC EXCLUDE_FROM_ALL
	MotorDemo.h
	MotorDemo.cpp
)

target_link_libraries(DynamicControlDemo
	PUBLIC
		LinearMath
		BulletDynamics
)

set_target_properties(DynamicControlDemo
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
