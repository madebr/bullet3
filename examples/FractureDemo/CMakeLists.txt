add_library(FractureDemo STATIC EXCLUDE_FROM_ALL
	FractureDemo.h
	FractureDemo.cpp
	btFractureDynamicsWorld.h
	btFractureDynamicsWorld.cpp
	btFractureBody.h
	btFractureBody.cpp
)

target_link_libraries(FractureDemo
	PUBLIC
		LinearMath
		BulletCollision
		BulletDynamics
)

set_target_properties(FractureDemo
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
