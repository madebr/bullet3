include_directories(
		"${BULLET_PHYSICS_SOURCE_DIR}/src"
		"${BULLET_PHYSICS_SOURCE_DIR}/examples"
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/include"
                "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src"
		"${PYTHON_INCLUDE_DIRS}"
)

if(BUILD_PYBULLET_NUMPY)
	include_directories(
		${PYTHON_NUMPY_INCLUDE_DIR}
	)
endif()

set(pybullet_SRCS
	pybullet.c

	../../examples/SharedMemory/IKTrajectoryHelper.cpp
	../../examples/SharedMemory/IKTrajectoryHelper.h
	../../examples/ExampleBrowser/InProcessExampleBrowser.cpp
	../../examples/SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.cpp
	../../examples/SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.h
	../../examples/SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.cpp
	../../examples/SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.h
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
	../../examples/SharedMemory/b3PluginManager.h

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

if(BUILD_PYBULLET_CLSOCKET)
	add_definitions(-DBT_ENABLE_CLSOCKET)
endif()

if(WIN32)
	link_librariesLINK_LIBRARIES(
		${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
	)
	if(BUILD_PYBULLET_ENET)
		add_definitions(-DWIN32 -DBT_ENABLE_ENET)
	endif()
	if(BUILD_PYBULLET_CLSOCKET)
		add_definitions(-DWIN32)
	endif()
else()
	if(BUILD_PYBULLET_ENET)
		add_definitions(-DHAS_SOCKLEN_T -DBT_ENABLE_ENET)
	endif()

	if(BUILD_PYBULLET_CLSOCKET)
		add_definitions(${OSDEF})
	endif()
endif()

if(BUILD_PYBULLET_ENET)
	set(pybullet_SRCS
		${pybullet_SRCS}

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

if(BUILD_PYBULLET_CLSOCKET)
	set(pybullet_SRCS
		${pybullet_SRCS}

		 ../../examples/SharedMemory/PhysicsClientTCP.cpp
                 ../../examples/SharedMemory/PhysicsClientTCP.h
                 ../../examples/SharedMemory/PhysicsClientTCP_C_API.cpp
                 ../../examples/SharedMemory/PhysicsClientTCP_C_API.h
		 ../../examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp
		 ../../examples/ThirdPartyLibs/clsocket/src/ActiveSocket.cpp
		 ../../examples/ThirdPartyLibs/clsocket/src/PassiveSocket.cpp
	)
endif()

add_library(pybullet SHARED ${pybullet_SRCS})

set_target_properties(pybullet PROPERTIES PREFIX "")
set_target_properties(pybullet PROPERTIES POSTFIX "")

set_target_properties(pybullet PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(pybullet PROPERTIES SOVERSION ${BULLET_VERSION})
set_target_properties(pybullet PROPERTIES DEBUG_POSTFIX "_d")


if(WIN32)
	if(BUILD_PYBULLET_ENET OR BUILD_PYBULLET_CLSOCKET)
		target_link_libraries(pybullet ws2_32 )
	endif()

	set_target_properties(pybullet PROPERTIES SUFFIX ".pyd")
endif()

target_link_libraries(pybullet BulletExampleBrowserLib BulletFileLoader BulletWorldImporter BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK Bullet3Common ${PYTHON_LIBRARIES})
