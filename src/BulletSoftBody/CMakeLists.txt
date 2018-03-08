set(BulletSoftBody_SRCS
	btSoftBody.cpp
	btSoftBodyConcaveCollisionAlgorithm.cpp
	btSoftBodyHelpers.cpp
	btSoftBodyRigidBodyCollisionConfiguration.cpp
	btSoftRigidCollisionAlgorithm.cpp
	btSoftRigidDynamicsWorld.cpp
	btSoftMultiBodyDynamicsWorld.cpp
	btSoftSoftCollisionAlgorithm.cpp
	btDefaultSoftBodySolver.cpp
)

set(BulletSoftBody_HDRS
	btSoftBody.h
	btSoftBodyData.h
	btSoftBodyConcaveCollisionAlgorithm.h
	btSoftBodyHelpers.h
	btSoftBodyRigidBodyCollisionConfiguration.h
	btSoftRigidCollisionAlgorithm.h
	btSoftRigidDynamicsWorld.h
	btSoftMultiBodyDynamicsWorld.h
	btSoftSoftCollisionAlgorithm.h
	btSparseSDF.h

	btSoftBodySolvers.h
	btDefaultSoftBodySolver.h

	btSoftBodySolverVertexBuffer.h
)

add_library(BulletSoftBody ${BulletSoftBody_SRCS} ${BulletSoftBody_HDRS})

target_include_directories(BulletSoftBody
	PUBLIC
		"${BULLET_PHYSICS_SOURCE_DIR}/src"
)

target_link_libraries(BulletSoftBody
	PUBLIC BulletDynamics
)

set_target_properties(BulletSoftBody PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(BulletSoftBody PROPERTIES SOVERSION ${BULLET_VERSION})

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletSoftBody DESTINATION .)

			set_target_properties(BulletSoftBody PROPERTIES FRAMEWORK true)
			set_target_properties(BulletSoftBody PROPERTIES PUBLIC_HEADER "${BulletSoftBody_HDRS}")
		else()
			install(
				TARGETS BulletSoftBody
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
