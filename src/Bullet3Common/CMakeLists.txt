include_directories("${BULLET_PHYSICS_SOURCE_DIR}/src")

set(Bullet3Common_SRCS
	b3AlignedAllocator.cpp
	b3Vector3.cpp
	b3Logging.cpp
)

set(Bullet3Common_HDRS
	b3AlignedAllocator.h
	b3AlignedObjectArray.h
	b3CommandLineArgs.h
	b3HashMap.h
	b3Logging.h
	b3Matrix3x3.h
	b3MinMax.h
	b3PoolAllocator.h
	b3QuadWord.h
	b3Quaternion.h
	b3Random.h
	b3Scalar.h
	b3StackAlloc.h
	b3Transform.h
	b3TransformUtil.h
	b3Vector3.h
	shared/b3Float4
	shared/b3Int2.h
	shared/b3Int4.h
	shared/b3Mat3x3.h
	shared/b3PlatformDefinitions
	shared/b3Quat.h
)

add_library(Bullet3Common ${Bullet3Common_SRCS} ${Bullet3Common_HDRS})

set_target_properties(Bullet3Common PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(Bullet3Common PROPERTIES SOVERSION ${BULLET_VERSION})

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS Bullet3Common DESTINATION .)

			set_target_properties(Bullet3Common PROPERTIES FRAMEWORK true)
			set_target_properties(Bullet3Common PROPERTIES PUBLIC_HEADER "${Bullet3Common_HDRS}")
		else()
			install(
				TARGETS Bullet3Common
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
		endif()
	endif()
endif()
