add_library(EvolutionDemo STATIC EXCLUDE_FROM_ALL
	NN3DWalkers.h
	NN3DWalkers.cpp
	NN3DWalkersTimeWarpBase.h
)

target_link_libraries(EvolutionDemo
	PUBLIC
		LinearMath
		BulletDynamics
		TimeSeriesCanvas
)

set_target_properties(EvolutionDemo
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
