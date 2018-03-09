add_library(ConstraintsDemo STATIC EXCLUDE_FROM_ALL
	../Constraints/ConstraintDemo.h
	../Constraints/ConstraintDemo.cpp

	../Constraints/ConstraintPhysicsSetup.h
	../Constraints/ConstraintPhysicsSetup.cpp

	../Constraints/TestHingeTorque.h
	../Constraints/TestHingeTorque.cpp

	../Constraints/Dof6Spring2Setup.h
	../Constraints/Dof6Spring2Setup.cpp
)

target_link_libraries(ConstraintsDemo
	PUBLIC
		LinearMath
		BulletDynamics
)

set_target_properties(ConstraintsDemo
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
