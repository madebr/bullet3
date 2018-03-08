set(Bullet3Geometry_SRCS
	b3ConvexHullComputer.cpp
	b3GeometryUtil.cpp
)

set(Bullet3Geometry_HDRS
	b3AabbUtil.h
	b3ConvexHullComputer.h
	b3GeometryUtil.h
	b3GrahamScan2dConvexHull.h
)

add_library(Bullet3Geometry ${Bullet3Geometry_SRCS} ${Bullet3Geometry_HDRS})
target_include_directories(Bullet3Geometry
	PUBLIC
		"${BULLET_PHYSICS_SOURCE_DIR}/src"
)

target_link_libraries(Bullet3Geometry
	PUBLIC
		Bullet3Common
)

set_target_properties(Bullet3Geometry PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(Bullet3Geometry PROPERTIES SOVERSION ${BULLET_VERSION})

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS Bullet3Geometry DESTINATION .)

			set_target_properties(Bullet3Geometry PROPERTIES FRAMEWORK true)
			set_target_properties(Bullet3Geometry PROPERTIES PUBLIC_HEADER "${Bullet3Geometry_HDRS}")
		else()
			install(
				TARGETS Bullet3Geometry
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
