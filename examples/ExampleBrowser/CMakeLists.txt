include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
)

file(GLOB GwenGUISupport_SRCS "GwenGUISupport/*")
file(GLOB GwenGUISupport_HDRS "GwenGUISupport/*")

if(WIN32)
	include_directories(
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad"
	)
	add_definitions(-DGLEW_STATIC)
else()
	if(APPLE)
		find_library(COCOA NAMES Cocoa)
	else()
		add_definitions("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
		add_definitions("-DGLEW_STATIC")
		add_definitions("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")
		include_directories("${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad")
	endif()
endif()

add_library(BulletExampleBrowserLib
	OpenGLExampleBrowser.cpp
	OpenGLGuiHelper.cpp
	GL_ShapeDrawer.cpp
	CollisionShape2TriangleMesh.cpp
	CollisionShape2TriangleMesh.h
	../Utils/b3Clock.cpp
	../Utils/b3Clock.h
	../Utils/ChromeTraceUtil.cpp
	../Utils/ChromeTraceUtil.h
	../Utils/b3ResourcePath.cpp
	../Utils/b3ResourcePath.h
	../Utils/b3ERPCFMHelper.hpp
	../Utils/b3ReferenceFrameHelper.hpp
	${GwenGUISupport_SRCS}
	${GwenGUISupport_HDRS}
)

set_target_properties(BulletExampleBrowserLib PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(BulletExampleBrowserLib PROPERTIES SOVERSION ${BULLET_VERSION})

if(BUILD_SHARED_LIBS)
	if(WIN32)
		target_link_libraries(
                        BulletExampleBrowserLib Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils
                        BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
                        ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
                )
	else()
        	if(APPLE)
			target_link_libraries(
				BulletExampleBrowserLib Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils
				BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
				${COCOA} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
			)
		else()
			TARGET_LINK_LIBRARIES(
				BulletExampleBrowserLib Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils
				BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
				pthread ${DL}
			)
		endif()
	endif()
endif()


####################
#
# Bullet Example Browser main app
#
####################

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}"
        "${BULLET_PHYSICS_SOURCE_DIR}/src"
        "${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs"
)

link_libraries(
	BulletExampleBrowserLib Bullet3Common BulletSoftBody BulletDynamics BulletCollision BulletInverseDynamicsUtils BulletInverseDynamics LinearMath OpenGLWindow gwen BussIK
)

if(WIN32)
	include_directories(
		${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad
	)
	link_libraries(
		${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
	)
	add_definitions(-DGLEW_STATIC)
else()
	if(APPLE)
		find_library(COCOA NAMES Cocoa)
		message("Cocoa library: ${COCOA}")
		link_libraries(${COCOA} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
		include_directories("${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad")
	else()
		add_definitions("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
		add_definitions("-DGLEW_STATIC")
		add_definitions("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")
		include_directories("${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad")
		link_libraries(pthread ${DL})
	endif()
endif()

set(ExtendedTutorialsSources
	../ExtendedTutorials/Chain.cpp
	../ExtendedTutorials/Chain.h
	../ExtendedTutorials/Bridge.cpp
	../ExtendedTutorials/Bridge.h
	../ExtendedTutorials/RigidBodyFromObj.cpp
	../ExtendedTutorials/RigidBodyFromObj.h
	../ExtendedTutorials/SimpleBox.cpp
	../ExtendedTutorials/SimpleBox.h
	../ExtendedTutorials/MultipleBoxes.cpp
	../ExtendedTutorials/MultipleBoxes.h
	../ExtendedTutorials/CompoundBoxes.cpp
	../ExtendedTutorials/CompoundBoxes.h
	../ExtendedTutorials/SimpleCloth.cpp
	../ExtendedTutorials/SimpleCloth.h
	../ExtendedTutorials/SimpleJoint.cpp
	../ExtendedTutorials/SimpleJoint.h
	../ExtendedTutorials/NewtonsCradle.cpp
	../ExtendedTutorials/NewtonsCradle.h
	../ExtendedTutorials/InclinedPlane.cpp
	../ExtendedTutorials/InclinedPlane.h
	../ExtendedTutorials/MultiPendulum.cpp
	../ExtendedTutorials/MultiPendulum.h
)

set(BulletExampleBrowser_SRCS
	../TinyRenderer/geometry.cpp
	../TinyRenderer/model.cpp
	../TinyRenderer/tgaimage.cpp
	../TinyRenderer/our_gl.cpp
	../TinyRenderer/TinyRenderer.cpp
	../SharedMemory/plugins/tinyRendererPlugin/tinyRendererPlugin.cpp
	../SharedMemory/plugins/tinyRendererPlugin/TinyRendererVisualShapeConverter.cpp
	../SharedMemory/IKTrajectoryHelper.cpp
	../SharedMemory/IKTrajectoryHelper.h
	../SharedMemory/PhysicsServer.cpp
	../SharedMemory/PhysicsClientSharedMemory.cpp
	../SharedMemory/PhysicsClientSharedMemory_C_API.cpp
	../SharedMemory/PhysicsClient.cpp
	../SharedMemory/PhysicsClientC_API.cpp
	../SharedMemory/PhysicsServerExample.cpp
	../SharedMemory/PhysicsServerExampleBullet2.cpp
	../SharedMemory/PhysicsClientExample.cpp
	../SharedMemory/PosixSharedMemory.cpp
	../SharedMemory/Win32SharedMemory.cpp
	../SharedMemory/InProcessMemory.cpp
	../SharedMemory/PhysicsServerSharedMemory.cpp
	../SharedMemory/PhysicsDirect.cpp
	../SharedMemory/PhysicsDirect.h
	../SharedMemory/PhysicsDirectC_API.cpp
	../SharedMemory/PhysicsDirectC_API.h
	../SharedMemory/SharedMemoryInProcessPhysicsC_API.cpp
	../SharedMemory/PhysicsLoopBack.cpp
	../SharedMemory/PhysicsLoopBack.h
	../SharedMemory/PhysicsLoopBackC_API.cpp
	../SharedMemory/PhysicsLoopBackC_API.h
	../SharedMemory/PhysicsServerCommandProcessor.cpp
	../SharedMemory/PhysicsServerCommandProcessor.h
	../SharedMemory/SharedMemoryCommands.h
	../SharedMemory/SharedMemoryPublic.h
	../SharedMemory/b3PluginManager.cpp
	../RobotSimulator/b3RobotSimulatorClientAPI.cpp
	../RobotSimulator/b3RobotSimulatorClientAPI.h
	../RobotSimulator/b3RobotSimulatorClientAPI_NoGUI.cpp
	../RobotSimulator/b3RobotSimulatorClientAPI_NoGUI.h
	../BasicDemo/BasicExample.cpp
	../BasicDemo/BasicExample.h
	../InverseDynamics/InverseDynamicsExample.cpp
	../InverseDynamics/InverseDynamicsExample.h
	../ForkLift/ForkLiftDemo.cpp
	../ForkLift/ForkLiftDemo.h
	../MultiThreadedDemo/MultiThreadedDemo.cpp
	../MultiThreadedDemo/MultiThreadedDemo.h
	../MultiThreadedDemo/CommonRigidBodyMTBase.cpp
	../MultiThreadedDemo/CommonRigidBodyMTBase.h
	../Tutorial/Tutorial.cpp
	../Tutorial/Tutorial.h
	../Tutorial/Dof6ConstraintTutorial.cpp
	../Tutorial/Dof6ConstraintTutorial.h
	../Evolution/NN3DWalkers.cpp
	../Evolution/NN3DWalkers.h
	../Evolution/NN3DWalkersTimeWarpBase.h
	../ExtendedTutorials/NewtonsRopeCradle.cpp
	../ExtendedTutorials/NewtonsRopeCradle.h
	../Collision/CollisionSdkC_Api.cpp
	../Collision/CollisionSdkC_Api.h
	../Collision/CollisionTutorialBullet2.cpp
	../Collision/CollisionTutorialBullet2.h
	../Collision/Internal/Bullet2CollisionSdk.cpp
	../Collision/Internal/Bullet2CollisionSdk.h
	../Collision/Internal/CollisionSdkInterface.h
	../Collision/Internal/RealTimeBullet3CollisionSdk.cpp
	../Collision/Internal/RealTimeBullet3CollisionSdk.h
	../GyroscopicDemo/GyroscopicSetup.cpp
	../GyroscopicDemo/GyroscopicSetup.h
	../Planar2D/Planar2D.cpp
	../Planar2D/Planar2D.h
	../RollingFrictionDemo/RollingFrictionDemo.cpp
	../RollingFrictionDemo/RollingFrictionDemo.h
	../FractureDemo/FractureDemo.cpp
	../FractureDemo/btFractureBody.cpp
	../FractureDemo/btFractureDynamicsWorld.cpp
	../FractureDemo/FractureDemo.h
	../FractureDemo/btFractureBody.h
	../FractureDemo/btFractureDynamicsWorld.h
	../DynamicControlDemo/MotorDemo.cpp
	../DynamicControlDemo/MotorDemo.h
	../MultiThreading/MultiThreadingExample.cpp
	../MultiThreading/b3PosixThreadSupport.cpp
	../MultiThreading/b3Win32ThreadSupport.cpp
	../MultiThreading/b3ThreadSupportInterface.cpp
	../MultiThreading/btTaskScheduler.cpp
	../RenderingExamples/TinyRendererSetup.cpp
	../RenderingExamples/TimeSeriesCanvas.cpp
	../RenderingExamples/TimeSeriesCanvas.h
	../RenderingExamples/TimeSeriesFontData.cpp
	../RenderingExamples/TimeSeriesFontData.h
	../RenderingExamples/DynamicTexturedCubeDemo.cpp
	../RenderingExamples/DynamicTexturedCubeDemo.h
	../RenderingExamples/TinyVRGui.cpp
	../RenderingExamples/TinyVRGui.h
	
	../RoboticsLearning/GripperGraspExample.cpp
	../RoboticsLearning/GripperGraspExample.h
	../RoboticsLearning/R2D2GraspExample.cpp
	../RoboticsLearning/R2D2GraspExample.h
	../RoboticsLearning/KukaGraspExample.cpp
	../RoboticsLearning/KukaGraspExample.h
	../RenderingExamples/CoordinateSystemDemo.cpp
	../RenderingExamples/CoordinateSystemDemo.h
	../RenderingExamples/RaytracerSetup.cpp
	../RenderingExamples/RaytracerSetup.h
	../RenderingExamples/RenderInstancingDemo.cpp
	../RenderingExamples/RenderInstancingDemo.h
	../RenderingExamples/TimeSeriesExample.cpp
	../Benchmarks/landscapeData.h
	../Benchmarks/TaruData
	../Raycast/RaytestDemo.cpp
	../Importers/ImportBsp/BspConverter.h
	../Importers/ImportBullet/SerializeSetup.cpp
	../Importers/ImportBullet/SerializeSetup.h
	../Importers/ImportMeshUtility/b3ImportMeshUtility.cpp
	../Importers/ImportMeshUtility/b3ImportMeshUtility.h
	../../Extras/Serialize/BulletWorldImporter/btWorldImporter.cpp
	../../Extras/Serialize/BulletWorldImporter/btMultiBodyWorldImporter.cpp
	../../Extras/Serialize/BulletWorldImporter/btBulletWorldImporter.cpp
	../../Extras/Serialize/BulletFileLoader/bChunk.cpp		
	../../Extras/Serialize/BulletFileLoader/bFile.cpp
	../../Extras/Serialize/BulletFileLoader/bDNA.cpp		
	../../Extras/Serialize/BulletFileLoader/btBulletFile.cpp

	../Importers/ImportBsp/BspLoader.h
	../Importers/ImportBsp/ImportBspExample.h
	../Importers/ImportColladaDemo/btMatrix4x4.h
	../Importers/ImportColladaDemo/ColladaGraphicsInstance.h
	../Importers/ImportColladaDemo/ImportColladaSetup.h
	../Importers/ImportColladaDemo/LoadMeshFromCollada.h
	../Importers/ImportObjDemo/ImportObjExample.h
	../Importers/ImportObjDemo/LoadMeshFromObj.h
	../Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.h
	../Importers/ImportSTLDemo/ImportSTLSetup.h
	../Importers/ImportSTLDemo/LoadMeshFromSTL.h
	../Importers/ImportURDFDemo/ConvertRigidBodies2MultiBody.h
	../Importers/ImportURDFDemo/ImportURDFSetup.h
	../Importers/ImportURDFDemo/URDF2Bullet.h
	../Importers/ImportURDFDemo/urdf_samples.h
	../Importers/ImportURDFDemo/urdf_samples.h
	../Importers/ImportMJCFDemo/BulletMJCFImporter.cpp
	../Importers/ImportMJCFDemo/BulletMJCFImporter.h
	../Importers/ImportMJCFDemo/ImportMJCFSetup.cpp
	../Importers/ImportMJCFDemo/ImportMJCFSetup.h
	../Importers/ImportBsp/BspConverter.cpp
	../Importers/ImportBsp/BspLoader.cpp
	../Importers/ImportBsp/ImportBspExample.cpp
	../Importers/ImportColladaDemo/ImportColladaSetup.cpp
	../Importers/ImportColladaDemo/LoadMeshFromCollada.cpp
	../Importers/ImportObjDemo/ImportObjExample.cpp
	../Importers/ImportObjDemo/LoadMeshFromObj.cpp
	../Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp
	../Importers/ImportSTLDemo/ImportSTLSetup.cpp
	../Importers/ImportSDFDemo/ImportSDFSetup.cpp
	../Importers/ImportURDFDemo/ImportURDFSetup.cpp
	../Importers/ImportURDFDemo/URDF2Bullet.cpp
	../Importers/ImportURDFDemo/MyMultiBodyCreator.cpp
	../Importers/ImportURDFDemo/MyMultiBodyCreator.h
	../Importers/ImportURDFDemo/UrdfParser.cpp
	../Utils/RobotLoggingUtil.cpp
	../Utils/RobotLoggingUtil.h
	../Importers/ImportURDFDemo/urdfStringSplit.cpp
	../Importers/ImportURDFDemo/urdfStringSplit.h
	../Importers/ImportURDFDemo/BulletUrdfImporter.cpp
	../Importers/ImportURDFDemo/BulletUrdfImporter.h
	../VoronoiFracture/VoronoiFractureDemo.cpp
	../VoronoiFracture/VoronoiFractureDemo.h
	../VoronoiFracture/btConvexConvexMprAlgorithm.cpp
	../VoronoiFracture/btConvexConvexMprAlgorithm.h
	../Vehicles/Hinge2Vehicle.cpp
	../Vehicles/Hinge2Vehicle.h
	../MultiBody/Pendulum.cpp
	../MultiBody/MultiBodySoftContact.cpp
	../MultiBody/TestJointTorqueSetup.cpp
	../MultiBody/TestJointTorqueSetup.h
	../MultiBody/InvertedPendulumPDControl.cpp
	../MultiBody/InvertedPendulumPDControl.h
	../MultiBody/MultiBodyConstraintFeedback.cpp
	../MultiBody/MultiDofDemo.cpp
	../MultiBody/MultiDofDemo.h
	../RigidBody/RigidBodySoftContact.cpp
	../Constraints/TestHingeTorque.cpp
	../Constraints/TestHingeTorque.h
	../Constraints/ConstraintDemo.cpp
	../Constraints/ConstraintDemo.h
	../Constraints/Dof6Spring2Setup.cpp
	../Constraints/Dof6Spring2Setup.h
	../Constraints/ConstraintPhysicsSetup.cpp
	../Constraints/ConstraintPhysicsSetup.h


	../ThirdPartyLibs/stb_image/stb_image.cpp
	../ThirdPartyLibs/stb_image/stb_image.h
	
	../ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp
	../ThirdPartyLibs/tinyxml/tinystr.cpp
	../ThirdPartyLibs/tinyxml/tinyxml.cpp
	../ThirdPartyLibs/tinyxml/tinyxmlerror.cpp
	../ThirdPartyLibs/tinyxml/tinyxmlparser.cpp

	../ThirdPartyLibs/tinyxml/tinystr.cpp
	../ThirdPartyLibs/tinyxml/tinyxml.cpp
	../ThirdPartyLibs/tinyxml/tinyxmlerror.cpp
	../ThirdPartyLibs/tinyxml/tinyxmlparser.cpp
	InProcessExampleBrowser.cpp
	"${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc"
)

add_executable(App_ExampleBrowser
	main.cpp
	ExampleEntries.cpp
	ExampleEntries.h
	${ExtendedTutorialsSources}
	${BulletExampleBrowser_SRCS}
)

target_link_libraries(App_ExampleBrowser
	PUBLIC
		BenchmarkDemo
		InverseKinematicsExample
)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/data" )

add_custom_command(
	TARGET App_ExampleBrowser
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory ${BULLET_PHYSICS_SOURCE_DIR}/data ${PROJECT_BINARY_DIR}/data
)

IF (BULLET2_USE_TBB_MULTITHREADING AND WIN32)
	# add a post build command to copy some dlls to the executable directory
	set(TBB_VC_VER "vc12")
	set(TBB_VC_ARCH "ia32")
	# assume 32-bit build in VC12 for now
	# checks can be added here at a later time
	add_custom_command(
		TARGET App_ExampleBrowser
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${BULLET2_TBB_INCLUDE_DIR}/../bin/${TBB_VC_ARCH}/${TBB_VC_VER}/tbb.dll" $<TARGET_FILE_DIR:App_ExampleBrowser>
	)
	add_custom_command(
		TARGET App_ExampleBrowser
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${BULLET2_TBB_INCLUDE_DIR}/../bin/${TBB_VC_ARCH}/${TBB_VC_VER}/tbbmalloc.dll" $<TARGET_FILE_DIR:App_ExampleBrowser>
	)
endif()


if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(App_ExampleBrowser PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(App_ExampleBrowser PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(App_ExampleBrowser PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()
