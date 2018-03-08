set(BulletDynamics_SRCS
	Character/btKinematicCharacterController.cpp
	ConstraintSolver/btConeTwistConstraint.cpp
	ConstraintSolver/btContactConstraint.cpp
	ConstraintSolver/btFixedConstraint.cpp
	ConstraintSolver/btGearConstraint.cpp
	ConstraintSolver/btGeneric6DofConstraint.cpp
	ConstraintSolver/btGeneric6DofSpringConstraint.cpp
	ConstraintSolver/btGeneric6DofSpring2Constraint.cpp
	ConstraintSolver/btHinge2Constraint.cpp
	ConstraintSolver/btHingeConstraint.cpp
	ConstraintSolver/btPoint2PointConstraint.cpp
	ConstraintSolver/btSequentialImpulseConstraintSolver.cpp
	ConstraintSolver/btNNCGConstraintSolver.cpp
	ConstraintSolver/btSliderConstraint.cpp
	ConstraintSolver/btSolve2LinearConstraint.cpp
	ConstraintSolver/btTypedConstraint.cpp
	ConstraintSolver/btUniversalConstraint.cpp
	Dynamics/btDiscreteDynamicsWorld.cpp
	Dynamics/btDiscreteDynamicsWorldMt.cpp
	Dynamics/btSimulationIslandManagerMt.cpp
	Dynamics/btRigidBody.cpp
	Dynamics/btSimpleDynamicsWorld.cpp
#	Dynamics/Bullet-C-API.cpp
	Vehicle/btRaycastVehicle.cpp
	Vehicle/btWheelInfo.cpp
	Featherstone/btMultiBody.cpp
	Featherstone/btMultiBodyConstraintSolver.cpp
	Featherstone/btMultiBodyDynamicsWorld.cpp
	Featherstone/btMultiBodyJointLimitConstraint.cpp
	Featherstone/btMultiBodyConstraint.cpp
	Featherstone/btMultiBodyPoint2Point.cpp
	Featherstone/btMultiBodyFixedConstraint.cpp
	Featherstone/btMultiBodySliderConstraint.cpp
	Featherstone/btMultiBodyJointMotor.cpp
	Featherstone/btMultiBodyGearConstraint.cpp
	MLCPSolvers/btDantzigLCP.cpp
	MLCPSolvers/btMLCPSolver.cpp
	MLCPSolvers/btLemkeAlgorithm.cpp
)

set(Root_HDRS
	../btBulletDynamicsCommon.h
	../btBulletCollisionCommon.h
)

set(ConstraintSolver_HDRS
	ConstraintSolver/btConeTwistConstraint.h
	ConstraintSolver/btConstraintSolver.h
	ConstraintSolver/btContactConstraint.h
	ConstraintSolver/btContactSolverInfo.h
	ConstraintSolver/btFixedConstraint.h
	ConstraintSolver/btGearConstraint.h
	ConstraintSolver/btGeneric6DofConstraint.h
	ConstraintSolver/btGeneric6DofSpringConstraint.h
	ConstraintSolver/btGeneric6DofSpring2Constraint.h
	ConstraintSolver/btHinge2Constraint.h
	ConstraintSolver/btHingeConstraint.h
	ConstraintSolver/btJacobianEntry.h
	ConstraintSolver/btPoint2PointConstraint.h
	ConstraintSolver/btSequentialImpulseConstraintSolver.h
	ConstraintSolver/btNNCGConstraintSolver.h
	ConstraintSolver/btSliderConstraint.h
	ConstraintSolver/btSolve2LinearConstraint.h
	ConstraintSolver/btSolverBody.h
	ConstraintSolver/btSolverConstraint.h
	ConstraintSolver/btTypedConstraint.h
	ConstraintSolver/btUniversalConstraint.h
)

set(Dynamics_HDRS
	Dynamics/btActionInterface.h
	Dynamics/btDiscreteDynamicsWorld.h
	Dynamics/btDiscreteDynamicsWorldMt.h
	Dynamics/btSimulationIslandManagerMt.h
	Dynamics/btDynamicsWorld.h
	Dynamics/btSimpleDynamicsWorld.h
	Dynamics/btRigidBody.h
)

set(Vehicle_HDRS
	Vehicle/btRaycastVehicle.h
	Vehicle/btVehicleRaycaster.h
	Vehicle/btWheelInfo.h
)

set(Featherstone_HDRS
	Featherstone/btMultiBody.h
	Featherstone/btMultiBodyConstraintSolver.h
	Featherstone/btMultiBodyDynamicsWorld.h
	Featherstone/btMultiBodyLink.h
	Featherstone/btMultiBodyLinkCollider.h
	Featherstone/btMultiBodySolverConstraint.h
	Featherstone/btMultiBodyConstraint.h
	Featherstone/btMultiBodyJointLimitConstraint.h
	Featherstone/btMultiBodyConstraint.h
	Featherstone/btMultiBodyPoint2Point.h
	Featherstone/btMultiBodyFixedConstraint.h
	Featherstone/btMultiBodySliderConstraint.h
	Featherstone/btMultiBodyJointMotor.h
	Featherstone/btMultiBodyGearConstraint.h	
)

set(MLCPSolvers_HDRS
	MLCPSolvers/btDantzigLCP.h
	MLCPSolvers/btDantzigSolver.h
	MLCPSolvers/btMLCPSolver.h
	MLCPSolvers/btMLCPSolverInterface.h
	MLCPSolvers/btPATHSolver.h
	MLCPSolvers/btSolveProjectedGaussSeidel.h
	MLCPSolvers/btLemkeSolver.h
	MLCPSolvers/btLemkeAlgorithm.h
)

set(Character_HDRS
	Character/btCharacterControllerInterface.h
	Character/btKinematicCharacterController.h
)

set(BulletDynamics_HDRS
	${Root_HDRS}
	${ConstraintSolver_HDRS}
	${Dynamics_HDRS}
	${Vehicle_HDRS}
	${Character_HDRS}
	${Featherstone_HDRS}
	${MLCPSolvers_HDRS}
)

add_library(BulletDynamics
${BulletDynamics_SRCS}
${BulletDynamics_HDRS})

target_include_directories(BulletDynamics
	PUBLIC
		"${BULLET_PHYSICS_SOURCE_DIR}/src"
)
target_link_libraries(BulletDynamics
	PUBLIC
		LinearMath
		BulletCollision
)

set_target_properties(BulletDynamics PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(BulletDynamics PROPERTIES SOVERSION ${BULLET_VERSION})

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletDynamics DESTINATION .)

			set_target_properties(BulletDynamics PROPERTIES FRAMEWORK true)
			set_target_properties(BulletDynamics PROPERTIES PUBLIC_HEADER "${Root_HDRS}")

			# Have to list out sub-directories manually:
			set_property(SOURCE ${ConstraintSolver_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/ConstraintSolver)
			set_property(SOURCE ${Dynamics_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/Dynamics)
			set_property(SOURCE ${Vehicle_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/Vehicle)
			set_property(SOURCE ${Character_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/Character)
			set_property(SOURCE ${Featherstone_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/Featherstone)
			set_property(SOURCE ${MLCPSolvers_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/MLCPSolvers)
		else()
			install(
				TARGETS BulletDynamics
				RUNTIME DESTINATION bin
				LIBRARY DESTINATION lib${LIB_SUFFIX}
				ARCHIVE DESTINATION lib${LIB_SUFFIX}
			)
			install(
				DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
				DESTINATION "${INCLUDE_INSTALL_DIR}"
				FILES_MATCHING
					PATTERN "*.h"
					PATTERN ".svn" EXCLUDE
					PATTERN "CMakeFiles" EXCLUDE
			)
			install(
				FILES ../btBulletDynamicsCommon.h
				DESTINATION ${INCLUDE_INSTALL_DIR}/BulletDynamics
			)
		endif()
	endif()
endif()
