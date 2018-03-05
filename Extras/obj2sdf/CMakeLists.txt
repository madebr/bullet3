set(includes
	.
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
)

link_libraries(
	 Bullet3Common
)

include_directories(${includes})

add_executable(App_obj2sdf
	obj2sdf.cpp
	../../examples/Utils/b3ResourcePath.cpp
	../../examples/Utils/b3ResourcePath.h
	../../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp
)
