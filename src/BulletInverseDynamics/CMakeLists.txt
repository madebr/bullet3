include_directories("${BULLET_PHYSICS_SOURCE_DIR}/src")

set(BulletInverseDynamics_SRCS
	IDMath.cpp
	MultiBodyTree.cpp
	details/MultiBodyTreeInitCache.cpp
	details/MultiBodyTreeImpl.cpp
)

set(BulletInverseDynamicsRoot_HDRS
	IDConfig.hpp
	IDConfigEigen.hpp
	IDMath.hpp
	IDConfigBuiltin.hpp
	IDErrorMessages.hpp
	MultiBodyTree.hpp
)
set(BulletInverseDynamicsDetails_HDRS
	details/IDEigenInterface.hpp
	details/IDMatVec.hpp
	details/IDLinearMathInterface.hpp
	details/MultiBodyTreeImpl.hpp
	details/MultiBodyTreeInitCache.hpp
)

set(BulletInverseDynamics_HDRS
	${BulletInverseDynamicsRoot_HDRS}
	${BulletInverseDynamicsDetails_HDRS}
)


add_library(BulletInverseDynamics ${BulletInverseDynamics_SRCS} ${BulletInverseDynamics_HDRS})
set_target_properties(BulletInverseDynamics PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(BulletInverseDynamics PROPERTIES SOVERSION ${BULLET_VERSION})
if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletInverseDynamics Bullet3Common LinearMath)
endif()

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS BulletInverseDynamics DESTINATION .)

			set_target_properties(BulletInverseDynamics PROPERTIES FRAMEWORK true)

			set_target_properties(BulletInverseDynamics PROPERTIES PUBLIC_HEADER "${BulletInverseDynamicsRoot_HDRS}")
			# Have to list out sub-directories manually:
			set_propert(SOURCE ${BulletInverseDynamicsDetails_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/details)
		else()
			install(TARGETS BulletInverseDynamics
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
				FILES ../btBulletCollisionCommon.h
				DESTINATION ${INCLUDE_INSTALL_DIR}/BulletInverseDynamics
				)
		endif()
	endif()
endif()
