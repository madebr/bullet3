add_library(ExtendedTutorials STATIC EXCLUDE_FROM_ALL
	Bridge.h
	Bridge.cpp
	Chain.h
	Chain.cpp
	CompoundBoxes.h
	CompoundBoxes.cpp
	InclinedPlane.h
	InclinedPlane.cpp
	MultiPendulum.h
	MultiPendulum.cpp
	MultipleBoxes.h
	MultipleBoxes.cpp
	NewtonsCradle.h
	NewtonsCradle.cpp
	NewtonsRopeCradle.h
	NewtonsRopeCradle.cpp
	RigidBodyFromObj.h
	RigidBodyFromObj.cpp
	SimpleBox.h
	SimpleBox.cpp
	SimpleCloth.h
	SimpleCloth.cpp
	SimpleJoint.h
	SimpleJoint.cpp
)

target_link_libraries(ExtendedTutorials
	PUBLIC
		LinearMath
		BulletDynamics
		TimeSeriesCanvas
)

set_target_properties(EvolutionDemo
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
