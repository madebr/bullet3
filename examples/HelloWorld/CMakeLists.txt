# HelloWorld is a minimal sample creating, stepping and deleting a Bullet dynamics world

link_libraries(
	BulletDynamics
	BulletCollision
	LinearMath
)

add_executable(App_HelloWorld
	HelloWorld.cpp
	"${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc"
)

if(WIN32)
	target_sources(App_HelloWorld
		PRIVATE
			"${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc"
	)
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(App_HelloWorld PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(App_HelloWorld PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(App_HelloWorld PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()
