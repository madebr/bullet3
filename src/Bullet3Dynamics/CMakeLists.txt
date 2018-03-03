include_directories("${BULLET_PHYSICS_SOURCE_DIR}/src")

set(Bullet3Dynamics_SRCS
	b3CpuRigidBodyPipeline.cpp
	ConstraintSolver/b3FixedConstraint.cpp
	ConstraintSolver/b3Generic6DofConstraint.cpp
	ConstraintSolver/b3PgsJacobiSolver.cpp
	ConstraintSolver/b3Point2PointConstraint.cpp
	ConstraintSolver/b3TypedConstraint.cpp
)

set(Bullet3Dynamics_HDRS
	b3CpuRigidBodyPipeline.h
	ConstraintSolver/b3ContactSolverInfo.h
	ConstraintSolver/b3FixedConstraint.h
	ConstraintSolver/b3Generic6DofConstraint.h
	ConstraintSolver/b3JacobianEntry.h
	ConstraintSolver/b3PgsJacobiSolver.h
	ConstraintSolver/b3Point2PointConstraint.h
	ConstraintSolver/b3SolverBody.h
	ConstraintSolver/b3SolverConstraint.h
	ConstraintSolver/b3TypedConstraint.h
	shared/b3ContactConstraint4.h
	shared/b3ConvertConstraint4.h
	shared/b3Inertia.h
	shared/b3IntegrateTransforms.h
)

add_library(Bullet3Dynamics ${Bullet3Dynamics_SRCS} ${Bullet3Dynamics_HDRS})
if(BUILD_SHARED_LIBS)
	target_link_libraries(Bullet3Dynamics Bullet3Collision)
endif()
set_target_properties(Bullet3Dynamics PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(Bullet3Dynamics PROPERTIES SOVERSION ${BULLET_VERSION})

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS Bullet3Dynamics DESTINATION .)

			set_target_properties(Bullet3Dynamics PROPERTIES FRAMEWORK true)
			set_target_properties(Bullet3Dynamics PROPERTIES PUBLIC_HEADER "${Bullet3Dynamics_HDRS}")
		else()
			install(
				TARGETS Bullet3Dynamics
				RUNTIME DESTINATION bin
				LIBRARY DESTINATION lib${LIB_SUFFIX}
				ARCHIVE DESTINATION lib${LIB_SUFFIX}
				)
			install(
				DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
				DESTINATION ${INCLUDE_INSTALL_DIR}
				FILES_MATCHING
					PATTERN "*.h"
					PATTERN ".svn" EXCLUDE
					PATTERN "CMakeFiles" EXCLUDE
				)
		endif()
	endif()
endif()
