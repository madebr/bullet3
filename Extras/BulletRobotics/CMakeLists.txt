include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/enet/include"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/clsocket/src"
)

set(BulletRobotics_SRCS
	../../examples/SharedMemory/IKTrajectoryHelper.cpp
	../../examples/SharedMemory/IKTrajectoryHelper.h
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
	../../examples/SharedMemory/SharedMemoryPublic.h

	../../examples/SharedMemory/Win32SharedMemory.cpp
	../../examples/SharedMemory/Win32SharedMemory.h
	../../examples/SharedMemory/PosixSharedMemory.cpp
	../../examples/SharedMemory/PosixSharedMemory.h

	../../examples/Utils/b3ResourcePath.cpp
	../../examples/Utils/b3ResourcePath.h
	../../examples/Utils/RobotLoggingUtil.cpp
	../../examples/Utils/RobotLoggingUtil.h
	../../examples/Utils/b3Clock.cpp
	../../examples/Utils/b3ResourcePath.cpp
	../../examples/Utils/b3ERPCFMHelper.hpp
	../../examples/Utils/b3ReferenceFrameHelper.hpp
	../../examples/Utils/ChromeTraceUtil.cpp

	../../examples/ThirdPartyLibs/tinyxml/tinystr.cpp
	../../examples/ThirdPartyLibs/tinyxml/tinyxml.cpp
	../../examples/ThirdPartyLibs/tinyxml/tinyxmlerror.cpp
	../../examples/ThirdPartyLibs/tinyxml/tinyxmlparser.cpp

	../../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp
	../../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.h

	../../examples/ThirdPartyLibs/stb_image/stb_image.cpp

	../../examples/ThirdPartyLibs/BussIK/Jacobian.cpp
	../../examples/ThirdPartyLibs/BussIK/LinearR2.cpp
	../../examples/ThirdPartyLibs/BussIK/LinearR3.cpp
	../../examples/ThirdPartyLibs/BussIK/LinearR4.cpp
	../../examples/ThirdPartyLibs/BussIK/MatrixRmn.cpp
	../../examples/ThirdPartyLibs/BussIK/Misc.cpp
	../../examples/ThirdPartyLibs/BussIK/Node.cpp
	../../examples/ThirdPartyLibs/BussIK/Tree.cpp
	../../examples/ThirdPartyLibs/BussIK/VectorRn.cpp

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
else(WIN32)
	if(BUILD_ENET)
		add_definitions(-DHAS_SOCKLEN_T -DBT_ENABLE_ENET)
	endif()

	if(BUILD_CLSOCKET)
		add_definitions(${OSDEF})
	endif()
		
	if(NOT APPLE)
		link_libraries(pthread ${DL})
	endif()
endif()

if(BUILD_ENET)
	set(BulletRobotics_SRCS
		${BulletRobotics_SRCS}

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
	set(BulletRobotics_SRCS
		${BulletRobotics_SRCS}

		../../examples/SharedMemory/PhysicsClientTCP.cpp
		../../examples/SharedMemory/PhysicsClientTCP.h
		../../examples/SharedMemory/PhysicsClientTCP_C_API.cpp
		../../examples/SharedMemory/PhysicsClientTCP_C_API.h
		../../examples/ThirdPartyLibs/clsocket/src/SimpleSocket.cpp
		../../examples/ThirdPartyLibs/clsocket/src/ActiveSocket.cpp
		../../examples/ThirdPartyLibs/clsocket/src/PassiveSocket.cpp
	)
endif()

add_definitions(-DPHYSICS_SERVER_DIRECT)

add_library(BulletRobotics ${BulletRobotics_SRCS})

set_target_properties(BulletRobotics PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(BulletRobotics PROPERTIES SOVERSION ${BULLET_VERSION})

if(BUILD_SHARED_LIBS)
	target_link_libraries(BulletRobotics BulletInverseDynamicsUtils BulletWorldImporter BulletFileLoader BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamics LinearMath Bullet3Common)
endif()

if(INSTALL_EXTRA_LIBS)
	install(
		FILES
			../../examples/SharedMemory/PhysicsClientC_API.h
			../../examples/SharedMemory/PhysicsClientSharedMemory_C_API.h
			../../examples/SharedMemory/PhysicsClientSharedMemory2_C_API.h
			../../examples/SharedMemory/PhysicsDirectC_API.h
			../../examples/SharedMemory/PhysicsClientUDP_C_API.h
			../../examples/SharedMemory/PhysicsClientTCP_C_API.h
			../../examples/SharedMemory/SharedMemoryInProcessPhysicsC_API.h
			../../examples/SharedMemory/SharedMemoryPublic.h
		DESTINATION include/bullet
	)
	install(
		TARGETS BulletRobotics
		LIBRARY DESTINATION lib${LIB_SUFFIX}
		ARCHIVE DESTINATION lib${LIB_SUFFIX}
	)
	if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
		set_target_properties(BulletRobotics  PROPERTIES FRAMEWORK true)
		set_target_properties(BulletRobotics PROPERTIES PUBLIC_HEADER "PhysicsClientC_API.h" )
	endif()
endif()
