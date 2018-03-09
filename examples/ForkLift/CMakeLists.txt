add_library(ForkLiftDemo STATIC EXCLUDE_FROM_ALL
	ForkLiftDemo.h
	ForkLiftDemo.cpp
)

target_link_libraries(ForkLiftDemo
	PUBLIC
		LinearMath
		BulletCollision
		BulletDynamics
)

set_target_properties(ForkLiftDemo
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
