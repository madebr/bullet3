include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/include"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src"
)

set(RobotSimulator_SRCS
	RobotSimulatorMain.cpp
	b3RobotSimulatorClientAPI.cpp
	b3RobotSimulatorClientAPI.h
	b3RobotSimulatorClientAPI_NoGUI.cpp
	b3RobotSimulatorClientAPI_NoGUI.h
	MinitaurSetup.cpp
	MinitaurSetup.h
	../../examples/ExampleBrowser/InProcessExampleBrowser.cpp
	../../examples/SharedMemory/PhysicsServerExample.cpp
	../../examples/SharedMemory/PhysicsServerExampleBullet2.cpp
	../../examples/SharedMemory/SharedMemoryInProcessPhysicsC_API.cpp
)

if(BUILD_CLSOCKET)
	add_definitions(-DBT_ENABLE_CLSOCKET)
endif()

if(WIN32)
	link_libraries(
		${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
	)
endif()

#some code to support OpenGL and Glew cross platform
if(WIN32)
	include_directories(
		${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows
	)
	add_definitions(-DGLEW_STATIC)
	link_libraries(${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
else()
	if(APPLE)
		find_library(COCOA NAMES Cocoa)
		message("Cocoa library: ${COCOA}")
		link_libraries(${COCOA} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
	else()
		include_directories(
		${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows
		)
		add_definitions("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
		add_definitions("-DGLEW_STATIC")
		add_definitions("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")
		link_libraries(pthread ${DL})
	endif()
endif()


add_executable(App_RobotSimulator  ${RobotSimulator_SRCS})

set_target_properties(App_RobotSimulator PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(App_RobotSimulator PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(App_RobotSimulator PROPERTIES COMPILE_DEFINITIONS "B3_USE_ROBOTSIM_GUI")

if(WIN32)
	if(BUILD_ENET OR BUILD_CLSOCKET)
		target_link_libraries(App_RobotSimulator ws2_32 )
	endif()
endif()

target_link_libraries(App_RobotSimulator BulletRobotics BulletExampleBrowserLib BulletFileLoader BulletWorldImporter BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils BulletInverseDynamics LinearMath OpenGLWindow gwen Bullet3Common)

include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/include"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src"
  )

set(RobotSimulator_NoGUI_SRCS
	RobotSimulatorMain.cpp
	b3RobotSimulatorClientAPI_NoGUI.cpp
	b3RobotSimulatorClientAPI_NoGUI.h	
	MinitaurSetup.cpp
	MinitaurSetup.h
)

add_executable(App_RobotSimulator_NoGUI ${RobotSimulator_NoGUI_SRCS})

set_target_properties(App_RobotSimulator_NoGUI PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(App_RobotSimulator_NoGUI PROPERTIES DEBUG_POSTFIX "_d")

if(WIN32)
	if(BUILD_ENET OR BUILD_CLSOCKET)
		target_link_libraries(App_RobotSimulator_NoGUI ws2_32)
	endif()
else()
	if(NOT APPLE)
		target_link_libraries( App_RobotSimulator_NoGUI pthread ${DL})
	endif()
endif()

target_link_libraries(App_RobotSimulator_NoGUI BulletRobotics BulletFileLoader BulletWorldImporter BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils BulletInverseDynamics LinearMath Bullet3Common)
