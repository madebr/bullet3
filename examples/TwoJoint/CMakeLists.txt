include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/include"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src"
)

set(RobotSimulator_SRCS
	TwoJointMain.cpp
		../../examples/SharedMemory/IKTrajectoryHelper.cpp
		../../examples/SharedMemory/IKTrajectoryHelper.h
		../../examples/ExampleBrowser/InProcessExampleBrowser.cpp
		../../examples/SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.cpp
		../../examples/SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.cpp
		../../examples/OpenGLWindow/SimpleCamera.cpp
		../../examples/OpenGLWindow/SimpleCamera.h
		../../examples/TinyRenderer/geometry.cpp
		../../examples/TinyRenderer/model.cpp
		../../examples/TinyRenderer/tgaimage.cpp
		../../examples/TinyRenderer/our_gl.cpp
		../../examples/TinyRenderer/TinyRenderer.cpp
		../../examples/SharedMemory/InProcessMemory.cpp
		../../examples/SharedMemory/PhysicsClient.cpp
		../../examples/SharedMemory/PhysicsClient.h
		../../examples/SharedMemory/PhysicsServer.cpp
		../../examples/SharedMemory/PhysicsServer.h
		../../examples/SharedMemory/PhysicsServerExample.cpp
		../../examples/SharedMemory/PhysicsServerExampleBullet2.cpp
		../../examples/SharedMemory/SharedMemoryInProcessPhysicsC_API.cpp
		../../examples/SharedMemory/PhysicsServerSharedMemory.cpp
		../../examples/SharedMemory/PhysicsServerSharedMemory.h
		../../examples/SharedMemory/PhysicsDirect.cpp
		../../examples/SharedMemory/PhysicsDirect.h
		../../examples/SharedMemory/PhysicsDirectC_API.cpp
		../../examples/SharedMemory/PhysicsDirectC_API.h
		../../examples/SharedMemory/PhysicsServerCommandProcessor.cpp
		../../examples/SharedMemory/PhysicsServerCommandProcessor.h
		../../examples/SharedMemory/b3PluginManager.cpp

		../../examples/SharedMemory/PhysicsClientSharedMemory.cpp
		../../examples/SharedMemory/PhysicsClientSharedMemory.h
		../../examples/SharedMemory/PhysicsClientSharedMemory_C_API.cpp
		../../examples/SharedMemory/PhysicsClientSharedMemory_C_API.h
		../../examples/SharedMemory/PhysicsClientC_API.cpp
		../../examples/SharedMemory/PhysicsClientC_API.h
		../../examples/SharedMemory/Win32SharedMemory.cpp
		../../examples/SharedMemory/Win32SharedMemory.h
		../../examples/SharedMemory/PosixSharedMemory.cpp
		../../examples/SharedMemory/PosixSharedMemory.h
		../../examples/Utils/b3ResourcePath.cpp
		../../examples/Utils/b3ResourcePath.h
		../../examples/Utils/RobotLoggingUtil.cpp
		../../examples/Utils/RobotLoggingUtil.h
		../../examples/ThirdPartyLibs/tinyxml/tinystr.cpp
		../../examples/ThirdPartyLibs/tinyxml/tinyxml.cpp
		../../examples/ThirdPartyLibs/tinyxml/tinyxmlerror.cpp
		../../examples/ThirdPartyLibs/tinyxml/tinyxmlparser.cpp
		../../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp
		../../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.h
		../../examples/ThirdPartyLibs/stb_image/stb_image.cpp
		../../examples/Importers/ImportColladaDemo/LoadMeshFromCollada.cpp
		../../examples/Importers/ImportObjDemo/LoadMeshFromObj.cpp
		../../examples/Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp
		../../examples/Importers/ImportMJCFDemo/BulletMJCFImporter.cpp
		../../examples/Importers/ImportURDFDemo/BulletUrdfImporter.cpp
		../../examples/Importers/ImportURDFDemo/MyMultiBodyCreator.cpp
		../../examples/Importers/ImportURDFDemo/URDF2Bullet.cpp
		../../examples/Importers/ImportURDFDemo/UrdfParser.cpp
		../../examples/Importers/ImportURDFDemo/urdfStringSplit.cpp
		../../examples/Importers/ImportMeshUtility/b3ImportMeshUtility.cpp
		../../examples/MultiThreading/b3PosixThreadSupport.cpp
		../../examples/MultiThreading/b3Win32ThreadSupport.cpp
		../../examples/MultiThreading/b3ThreadSupportInterface.cpp
)

if(BUILD_CLSOCKET)
	add_definitions(-DBT_ENABLE_CLSOCKET)
endif()

if(WIN32)
	link_libraries(
		${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
	)
	if(BUILD_ENET)
		add_definitions(-DWIN32 -DBT_ENABLE_ENET)
	endif()
	if(BUILD_CLSOCKET)
		add_definitions(-DWIN32)
	endif()
else()
	if(BUILD_ENET)
		add_definitions(-DHAS_SOCKLEN_T -DBT_ENABLE_ENET)
	endif()

	if(BUILD_CLSOCKET)
		add_definitions(${OSDEF})
	endif()
endif()


if(BUILD_ENET)
	set(RobotSimulator_SRCS ${RobotSimulator_SRCS}
			../../examples/SharedMemory/PhysicsClientUDP.cpp
		../../examples/SharedMemory/PhysicsClientUDP_C_API.cpp
		../../examples/SharedMemory/PhysicsClientUDP.h
		../../examples/SharedMemory/PhysicsClientUDP_C_API.h
		../../examples/ThirdPartyLibs/enet/win32.c
		../../examples/ThirdPartyLibs/enet/unix.c
		../../examples/ThirdPartyLibs/enet/callbacks.c
		../../examples/ThirdPartyLibs/enet/compress.c
		../../examples/ThirdPartyLibs/enet/host.c
		../../examples/ThirdPartyLibs/enet/list.c
		../../examples/ThirdPartyLibs/enet/packet.c
		../../examples/ThirdPartyLibs/enet/peer.c
		../../examples/ThirdPartyLibs/enet/protocol.c
	)
endif()

if(BUILD_CLSOCKET)
	set(RobotSimulator_SRCS ${RobotSimulator_SRCS}
		../../examples/SharedMemory/PhysicsClientTCP.cpp
		../../examples/SharedMemory/PhysicsClientTCP.h
		../../examples/SharedMemory/PhysicsClientTCP_C_API.cpp
		../../examples/SharedMemory/PhysicsClientTCP_C_API.h
		../../examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp
		../../examples/ThirdPartyLibs/clsocket/src/ActiveSocket.cpp
		../../examples/ThirdPartyLibs/clsocket/src/PassiveSocket.cpp
	)
endif()

#some code to support OpenGL and Glew cross platform
if(WIN32)
	include_directories(
		"${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows"
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
			"${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows"
		)
		add_definitions("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
		add_definitions("-DGLEW_STATIC")
		add_definitions("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")

		link_libraries(pthread ${DL})
	endif()
endif()


add_executable(App_TwoJoint ${RobotSimulator_SRCS})

set_target_properties(App_TwoJoint PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(App_TwoJoint PROPERTIES DEBUG_POSTFIX "_d")

if(WIN32)
	if(BUILD_ENET OR BUILD_CLSOCKET)
		target_link_libraries(App_TwoJoint ws2_32)
	endif()
endif()

target_link_libraries(App_TwoJoint BulletExampleBrowserLib BulletFileLoader BulletWorldImporter BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK Bullet3Common)
