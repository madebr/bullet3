# App_BasicExample is a minimal sample creating, stepping and deleting a Bullet dynamics world

add_executable(App_BasicExample
	BasicExample.cpp
	main.cpp
)

if(WIN32)
	target_sources(App_BasicExample
		PRIVATE
			"${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc"
	)
endif()

target_link_libraries(App_BasicExample
	PUBLIC
		BulletDynamics
		BulletCollision
		LinearMath
)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(App_BasicExample PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(App_BasicExample PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(App_BasicExample PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()

#################
# Standalone BasicExampleGui using OpenGL (but not the example browser)

set(AppBasicExampleGui_SRCS
	BasicExample.cpp
        "${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc"
        ../ExampleBrowser/OpenGLGuiHelper.cpp
        ../ExampleBrowser/GL_ShapeDrawer.cpp
        ../ExampleBrowser/CollisionShape2TriangleMesh.cpp
)

add_executable(AppBasicExampleGui
	${AppBasicExampleGui_SRCS}
)

#this define maps StandaloneExampleCreateFunc to the right 'CreateFunc'
target_compile_definitions(AppBasicExampleGui
	PRIVATE
		"B3_USE_STANDALONE_EXAMPLE"
)

target_include_directories(AppBasicExampleGui
	PUBLIC
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad"
)


target_link_libraries(AppBasicExampleGui
	PUBLIC
		b3Clock
		main_opengl_single_example
		BulletDynamics
		BulletCollision
		LinearMath
		OpenGLWindow
		Bullet3Common
)

#some code to support OpenGL and Glew cross platform
if(WIN32)
        target_compile_definitions(AppBasicExampleGui
        	PRIVATE
        		"GLEW_STATIC"
        )
	target_link_libraries(AppBasicExampleGui
		PUBLIC
			${OPENGL_gl_LIBRARY}
			${OPENGL_glu_LIBRARY}
	)
else()
	if(APPLE)
		target_link_libraries(AppBasicExampleGui
			PUBLIC
				${COCOA_LIBRARY}
				${OPENGL_gl_LIBRARY}
				${OPENGL_glu_LIBRARY}
		)
        else()
		target_compile_definitions(AppBasicExampleGui
			PRIVATE
				"GLEW_INIT_OPENGL11_FUNCTIONS=1"
				"GLEW_STATIC"
				"GLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1"
		)
		target_link_libraries(AppBasicExampleGui
			PUBLIC
				pthread
				${DL}
		)
	endif()
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppBasicExampleGui PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(AppBasicExampleGui PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(AppBasicExampleGui PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()
