add_library(GyroscopicSetup STATIC EXCLUDE_FROM_ALL
	GyroscopicSetup.h
	GyroscopicSetup.cpp
)

target_link_libraries(GyroscopicSetup
	PUBLIC
		BulletDynamics
)

set_target_properties(GyroscopicSetup
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
