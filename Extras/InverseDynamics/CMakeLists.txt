include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
)

add_library(BulletInverseDynamicsUtils
	CloneTreeCreator.cpp
	CoilCreator.cpp
	MultiBodyTreeCreator.cpp
	btMultiBodyTreeCreator.cpp
	DillCreator.cpp
	MultiBodyTreeDebugGraph.cpp
	invdyn_bullet_comparison.cpp
	IDRandomUtil.cpp
	RandomTreeCreator.cpp
	SimpleTreeCreator.cpp
	MultiBodyNameMap.cpp
	User2InternalIndex.cpp
)

set_target_properties(BulletInverseDynamicsUtils PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(BulletInverseDynamicsUtils PROPERTIES SOVERSION ${BULLET_VERSION})

if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletInverseDynamicsUtils BulletInverseDynamics BulletDynamics BulletCollision Bullet3Common LinearMath)
endif()

if(INSTALL_EXTRA_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletInverseDynamicsUtils  DESTINATION .)

			set_target_properties(BulletInverseDynamicsUtils  PROPERTIES FRAMEWORK true)
			set_target_properties(BulletInverseDynamicsUtils PROPERTIES PUBLIC_HEADER "BulletInverseDynamicsUtilsCommon.h" )
		else()
			install(
				TARGETS BulletInverseDynamicsUtils
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
