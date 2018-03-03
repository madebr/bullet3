include_directories("${BULLET_PHYSICS_SOURCE_DIR}/src")

add_definitions(-DB3_USE_CLEW)

set(Bullet3OpenCL_clew_SRCS
	../clew/clew.c
	BroadphaseCollision/b3GpuGridBroadphase.cpp
	BroadphaseCollision/b3GpuSapBroadphase.cpp
	BroadphaseCollision/b3GpuParallelLinearBvhBroadphase.cpp
	BroadphaseCollision/b3GpuParallelLinearBvh.cpp
	Initialize/b3OpenCLUtils.cpp
	NarrowphaseCollision/b3ContactCache.cpp
	NarrowphaseCollision/b3ConvexHullContact.cpp
	NarrowphaseCollision/b3GjkEpa.cpp
	NarrowphaseCollision/b3OptimizedBvh.cpp
	NarrowphaseCollision/b3QuantizedBvh.cpp
	NarrowphaseCollision/b3StridingMeshInterface.cpp
	NarrowphaseCollision/b3TriangleCallback.cpp
	NarrowphaseCollision/b3TriangleIndexVertexArray.cpp
	NarrowphaseCollision/b3VoronoiSimplexSolver.cpp
	ParallelPrimitives/b3BoundSearchCL.cpp
	ParallelPrimitives/b3FillCL.cpp
	ParallelPrimitives/b3LauncherCL.cpp
	ParallelPrimitives/b3PrefixScanCL.cpp
	ParallelPrimitives/b3PrefixScanFloat4CL.cpp
	ParallelPrimitives/b3RadixSort32CL.cpp
	Raycast/b3GpuRaycast.cpp
	RigidBody/b3GpuGenericConstraint.cpp
	RigidBody/b3GpuJacobiContactSolver.cpp
	RigidBody/b3GpuNarrowPhase.cpp
	RigidBody/b3GpuPgsConstraintSolver.cpp
	RigidBody/b3GpuPgsContactSolver.cpp
	RigidBody/b3GpuRigidBodyPipeline.cpp
	RigidBody/b3Solver.cpp
)

set(Bullet3OpenCL_clew_HDRS
#	${Root_HDRS}
)

add_library(Bullet3OpenCL_clew ${Bullet3OpenCL_clew_SRCS} ${Bullet3OpenCL_clew_HDRS})
set_target_properties(Bullet3OpenCL_clew PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(Bullet3OpenCL_clew PROPERTIES SOVERSION ${BULLET_VERSION})
if(BUILD_SHARED_LIBS)
 	target_link_libraries(Bullet3OpenCL_clew LinearMath Bullet3Dynamics ${CMAKE_DL_LIBS})
endif()

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		#INSTALL of other files requires CMake 2.6
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(
				TARGETS Bullet3OpenCL_clew
				DESTINATION .
			)

			set_target_properties(Bullet3OpenCL_clew PROPERTIES FRAMEWORK true)

			set_target_properties(Bullet3OpenCL_clew PROPERTIES PUBLIC_HEADER "${Root_HDRS}")
			# Have to list out sub-directories manually:
			set_property(SOURCE ${BroadphaseCollision_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/BroadphaseCollision)
		else()
			install(
				TARGETS Bullet3OpenCL_clew
				RUNTIME DESTINATION bin
				LIBRARY DESTINATION lib${LIB_SUFFIX}
				ARCHIVE DESTINATION lib${LIB_SUFFIX}
				)
			install(
				DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
				DESTINATION "${INCLUDE_INSTALL_DIR}"
				FILES_MATCHING
					PATTERN "*.h"
					PATTERN ".svn" EXCLUDE
					PATTERN "CMakeFiles" EXCLUDE
				)
#			install(FILES ../btBullet3OpenCL_clewCommon.h
#				DESTINATION ${INCLUDE_INSTALL_DIR}/Bullet3OpenCL_clew
#				)
		endif()
	endif()
endif()
