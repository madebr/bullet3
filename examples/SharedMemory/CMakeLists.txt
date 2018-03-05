set(SharedMemory_SRCS
	IKTrajectoryHelper.cpp
	IKTrajectoryHelper.h
	PhysicsClient.cpp
	PhysicsClientSharedMemory.cpp
	PhysicsClientExample.cpp
	PhysicsServerExample.cpp
	PhysicsServerExampleBullet2.cpp
	PhysicsServerSharedMemory.cpp
	PhysicsServerSharedMemory.h
	PhysicsServer.cpp
	PhysicsServer.h
	PhysicsClientC_API.cpp
	SharedMemoryCommands.h
	SharedMemoryPublic.h
	PhysicsServer.cpp
	PosixSharedMemory.cpp
	Win32SharedMemory.cpp
	InProcessMemory.cpp
	PhysicsDirect.cpp
	PhysicsDirect.h
	PhysicsDirectC_API.cpp
	PhysicsDirectC_API.h
	PhysicsLoopBack.cpp
	PhysicsLoopBack.h
	PhysicsLoopBackC_API.cpp
	PhysicsLoopBackC_API.h
	PhysicsClientSharedMemory_C_API.cpp
	PhysicsClientSharedMemory_C_API.h
	PhysicsClientSharedMemory2_C_API.cpp
	PhysicsClientSharedMemory2_C_API.h
	PhysicsClientSharedMemory2.cpp
	PhysicsClientSharedMemory2.h
	SharedMemoryCommandProcessor.cpp
	SharedMemoryCommandProcessor.h
	PhysicsServerCommandProcessor.cpp
	PhysicsServerCommandProcessor.h
	plugins/tinyRendererPlugin/tinyRendererPlugin.cpp
	plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.cpp
	SharedMemoryCommands.h
	SharedMemoryPublic.h
	b3PluginManager.cpp
	../TinyRenderer/geometry.cpp
	../TinyRenderer/model.cpp
	../TinyRenderer/tgaimage.cpp
	../TinyRenderer/our_gl.cpp
	../TinyRenderer/TinyRenderer.cpp
	../OpenGLWindow/SimpleCamera.cpp
	../OpenGLWindow/SimpleCamera.h
	../Importers/ImportURDFDemo/ConvertRigidBodies2MultiBody.h
	../Importers/ImportURDFDemo/MultiBodyCreationInterface.h
	../Importers/ImportURDFDemo/MyMultiBodyCreator.cpp
	../Importers/ImportURDFDemo/MyMultiBodyCreator.h
	../Importers/ImportURDFDemo/BulletUrdfImporter.cpp
	../Importers/ImportURDFDemo/BulletUrdfImporter.h
	../Importers/ImportURDFDemo/UrdfParser.cpp
	../Importers/ImportURDFDemo/urdfStringSplit.cpp
	../Importers/ImportURDFDemo/UrdfParser.cpp
	../Importers/ImportURDFDemo/UrdfParser.h
	../Importers/ImportURDFDemo/URDF2Bullet.cpp
	../Importers/ImportURDFDemo/URDF2Bullet.h
	../Importers/ImportMJCFDemo/BulletMJCFImporter.cpp
	../Importers/ImportMJCFDemo/BulletMJCFImporter.h
	../Utils/b3ResourcePath.cpp
	../Utils/b3Clock.cpp
	../Utils/RobotLoggingUtil.cpp
	../Utils/RobotLoggingUtil.h
	../Utils/ChromeTraceUtil.cpp
	../Utils/ChromeTraceUtil.h
	../Importers/ImportURDFDemo/URDFImporterInterface.h
	../Importers/ImportURDFDemo/URDFJointTypes.h
	../Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp
	../Importers/ImportObjDemo/LoadMeshFromObj.cpp
	../Importers/ImportSTLDemo/ImportSTLSetup.h
	../Importers/ImportSTLDemo/LoadMeshFromSTL.h
	../Importers/ImportColladaDemo/LoadMeshFromCollada.cpp
	../Importers/ImportColladaDemo/ColladaGraphicsInstance.h
	../ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp
	../ThirdPartyLibs/tinyxml/tinystr.cpp
	../ThirdPartyLibs/tinyxml/tinyxml.cpp
	../ThirdPartyLibs/tinyxml/tinyxmlerror.cpp
	../ThirdPartyLibs/tinyxml/tinyxmlparser.cpp
	../Importers/ImportMeshUtility/b3ImportMeshUtility.cpp
	../ThirdPartyLibs/stb_image/stb_image.cpp
	../MultiThreading/b3ThreadSupportInterface.cpp
	../MultiThreading/b3ThreadSupportInterface.h
)

include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
)

if(USE_SOFT_BODY_MULTI_BODY_DYNAMICS_WORLD)
	link_libraries(BulletSoftBody)
endif()

link_libraries(
	Bullet3Common BulletWorldImporter BulletFileLoader BulletInverseDynamicsUtils BulletInverseDynamics BulletDynamics BulletCollision LinearMath BussIK
)

if(WIN32)
	add_executable(App_PhysicsServer_SharedMemory
		${SharedMemory_SRCS}
		main.cpp
		../MultiThreading/b3Win32ThreadSupport.cpp
		../MultiThreading/b3Win32ThreadSupport.h
		${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc
	)
else(WIN32)
	if(APPLE)
		link_libraries(pthread dl)
		add_executable(App_PhysicsServer_SharedMemory
			${SharedMemory_SRCS}
			../MultiThreading/b3PosixThreadSupport.cpp
			../MultiThreading/b3PosixThreadSupport.h
			main.cpp
		)
        else()
		link_libraries(pthread ${DL})
		add_executable(App_PhysicsServer_SharedMemory
			${SharedMemory_SRCS}
			../MultiThreading/b3PosixThreadSupport.cpp
			../MultiThreading/b3PosixThreadSupport.h
			main.cpp
		)
	endif()
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(App_PhysicsServer_SharedMemory PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(App_PhysicsServer_SharedMemory PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(App_PhysicsServer_SharedMemory PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()

include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad"
)

add_definitions(-DB3_USE_STANDALONE_EXAMPLE)

link_libraries(
	BulletSoftBody Bullet3Common BulletWorldImporter BulletInverseDynamicsUtils BulletInverseDynamics BulletDynamics BulletCollision LinearMath BussIK OpenGLWindow
)

if(WIN32)
	add_definitions(-DGLEW_STATIC)
	link_libraries(${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

        add_executable(App_PhysicsServer_SharedMemory_GUI
		${SharedMemory_SRCS}
		../StandaloneMain/main_opengl_single_example.cpp
		../ExampleBrowser/OpenGLGuiHelper.cpp
		../ExampleBrowser/GL_ShapeDrawer.cpp
		../ExampleBrowser/CollisionShape2TriangleMesh.cpp
		../MultiThreading/b3Win32ThreadSupport.cpp
		../MultiThreading/b3Win32ThreadSupport.h
		${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc
	)
else()
	if(APPLE)
		link_libraries(pthread dl)
		find_library(COCOA NAMES Cocoa)
		message("Cocoa library: ${COCOA}")
		link_libraries(${COCOA} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

		add_executable(App_PhysicsServer_SharedMemory_GUI
			${SharedMemory_SRCS}
			../StandaloneMain/main_opengl_single_example.cpp
			../ExampleBrowser/OpenGLGuiHelper.cpp
			../ExampleBrowser/GL_ShapeDrawer.cpp
			../ExampleBrowser/CollisionShape2TriangleMesh.cpp
			../MultiThreading/b3PosixThreadSupport.cpp
			../MultiThreading/b3PosixThreadSupport.h
		)
        else()
		link_libraries(pthread ${DL})
		add_definitions("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
		add_definitions("-DGLEW_STATIC")
		add_definitions("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")

		add_executable(App_PhysicsServer_SharedMemory_GUI
			${SharedMemory_SRCS}
			../StandaloneMain/main_opengl_single_example.cpp
			../ExampleBrowser/OpenGLGuiHelper.cpp
			../ExampleBrowser/GL_ShapeDrawer.cpp
			../ExampleBrowser/CollisionShape2TriangleMesh.cpp
			../MultiThreading/b3PosixThreadSupport.cpp
			../MultiThreading/b3PosixThreadSupport.h
		)
        endif()
endif()

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(App_PhysicsServer_SharedMemory_GUI PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(App_PhysicsServer_SharedMemory_GUI PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(App_PhysicsServer_SharedMemory_GUI PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
ENDIF(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)


#VR/OpenVR only on Windows and Mac OSX for now
if(WIN32 OR APPLE)

	include_directories(
		${BULLET_PHYSICS_SOURCE_DIR}/src
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/openvr/headers
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/openvr/samples/shared
	)

	link_libraries(
		Bullet3Common BulletWorldImporter BulletInverseDynamicsUtils BulletInverseDynamics BulletDynamics BulletCollision LinearMath BussIK openvr_api OpenGLWindow
	)

	add_definitions(-DGLEW_STATIC)
	link_libraries( ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} )

	if(WIN32)
		set(Platform_SRCS
			../MultiThreading/b3Win32ThreadSupport.cpp
			../MultiThreading/b3Win32ThreadSupport.h
			"${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc"
		)
		if(CMAKE_CL_64)
			link_directories("${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/openvr/lib/win64")
		else()
			link_directories("${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/openvr/lib/win32")
		endif()
	else()
		set_source_files_properties(../ThirdPartyLibs/openvr/samples/shared/pathtools.cpp ../StandaloneMain/hellovr_opengl_main.cpp  PROPERTIES COMPILE_FLAGS "-x objective-c++")
		find_library(FOUNDATION_FRAMEWORK Foundation)
		mark_as_advanced(FOUNDATION_FRAMEWORK)
		set(EXTRA_LIBS ${EXTRA_LIBS} ${FOUNDATION_FRAMEWORK})

		set(CMAKE_MACOSX_RPATH 0)
  					
		set(Platform_SRCS
			../MultiThreading/b3PosixThreadSupport.cpp
			../MultiThreading/b3PosixThreadSupport.h
		)

		if(CMAKE_SIZEOF_VOID_P MATCHES 8)
			message("CL64")
			link_directories("${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/openvr/bin/osx64")
		else()
			message("CL32")
			set(ARCH_TARGET osx32)
			link_directories("${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/openvr/bin/osx32")
		endif()
		add_definitions(-DOSX -DPOSIX)
	endif()

        add_executable(App_PhysicsServer_SharedMemory_VR
		${SharedMemory_SRCS}
		${Platform_SRCS}
		../StandaloneMain/hellovr_opengl_main.cpp
		../ExampleBrowser/OpenGLGuiHelper.cpp
		../ExampleBrowser/GL_ShapeDrawer.cpp
		../ExampleBrowser/CollisionShape2TriangleMesh.cpp
		../RenderingExamples/TinyVRGui.cpp
		../RenderingExamples/TimeSeriesCanvas.cpp
		../RenderingExamples/TimeSeriesFontData.cpp
		../ThirdPartyLibs/openvr/samples/shared/lodepng.cpp
		../ThirdPartyLibs/openvr/samples/shared/lodepng.h
		../ThirdPartyLibs/openvr/samples/shared/Matrices.cpp
		../ThirdPartyLibs/openvr/samples/shared/Matrices.h
		../ThirdPartyLibs/openvr/samples/shared/pathtools.cpp
		../ThirdPartyLibs/openvr/samples/shared/pathtools.h
		../ThirdPartyLibs/openvr/samples/shared/strtools.cpp
		../ThirdPartyLibs/openvr/samples/shared/strtools.h
		../ThirdPartyLibs/openvr/samples/shared/Vectors.h
	)

	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(CMAKE_CL_64)
			add_custom_command(
				TARGET App_PhysicsServer_SharedMemory_VR
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/openvr/bin/win64/openvr_api.dll  ${CMAKE_CURRENT_BINARY_DIR}/openvr64pi.dll
			)
		else()
			add_custom_command(
				TARGET App_PhysicsServer_SharedMemory_VR
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/openvr/bin/win32/openvr_api.dll  ${CMAKE_CURRENT_BINARY_DIR}/openvr_api.dll
			)
		endif()

		add_custom_command(
			TARGET App_PhysicsServer_SharedMemory_VR
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory ${BULLET_PHYSICS_SOURCE_DIR}/data ${PROJECT_BINARY_DIR}/data
		)
	endif()

	set_target_properties(App_PhysicsServer_SharedMemory_VR PROPERTIES COMPILE_DEFINITIONS BT_ENABLE_VR )

	if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
		set_target_properties(App_PhysicsServer_SharedMemory_VR PROPERTIES DEBUG_POSTFIX "_Debug")
		set_target_properties(App_PhysicsServer_SharedMemory_VR PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
		set_target_properties(App_PhysicsServer_SharedMemory_VR PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
	endif()

endif()
