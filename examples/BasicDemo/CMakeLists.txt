# App_BasicExample is a minimal sample creating, stepping and deleting a Bullet dynamics world

include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
)

link_libraries(
	BulletDynamics
	BulletCollision
	LinearMath
)

if(WIN32)
	add_executable(App_BasicExample
		BasicExample.cpp
		main.cpp
		"${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc"
	)
else()
	add_executable(App_BasicExample
		BasicExample.cpp
		main.cpp
	)
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(App_BasicExample PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(App_BasicExample PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(App_BasicExample PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
ENDIF(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)


#################
# Standalone BasicExampleGui using OpenGL (but not the example browser)

include_directories(
        "${BULLET_PHYSICS_SOURCE_DIR}/src"
        "${BULLET_PHYSICS_SOURCE_DIR}/btgui"
        "${BULLET_PHYSICS_SOURCE_DIR}/examples"
        "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad"
)

set(AppBasicExampleGui_SRCS
	BasicExample.cpp
        "${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc"
	../StandaloneMain/main_opengl_single_example.cpp
        ../ExampleBrowser/OpenGLGuiHelper.cpp
        ../ExampleBrowser/GL_ShapeDrawer.cpp
        ../ExampleBrowser/CollisionShape2TriangleMesh.cpp
	../Utils/b3Clock.cpp
)

#this define maps StandaloneExampleCreateFunc to the right 'CreateFunc'
add_definitions(-DB3_USE_STANDALONE_EXAMPLE)

link_libraries(
        BulletDynamics BulletCollision LinearMath OpenGLWindow Bullet3Common 
)

#some code to support OpenGL and Glew cross platform
if(WIN32)
        include_directories(
             "${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows"
        )
        add_definitions(-DGLEW_STATIC)
	link_libraries(${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
else()
	if(APPLE)
		find_library(COCOA NAMES Cocoa REQUIRED)
		message("Cocoa library: ${COCOA}")
		link_libraries(${COCOA} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
        else()
		include_directories(
			"${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows"
		)
		add_definitions("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
		add_definitions("-DGLEW_STATIC")
		add_definitions("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")

		link_libraries( pthread ${DL})
	endif()
endif()

add_executable(AppBasicExampleGui
	${AppBasicExampleGui_SRCS}
)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(AppBasicExampleGui PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(AppBasicExampleGui PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(AppBasicExampleGui PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()
