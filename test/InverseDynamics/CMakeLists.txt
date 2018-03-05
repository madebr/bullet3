include_directories(
	.
	../../src
	../gtest-1.7.0/include
	../../Extras/InverseDynamics
)

#add_definitions(-DGTEST_HAS_PTHREAD=1)
add_definitions(-D_VARIADIC_MAX=10)

link_libraries(
	BulletInverseDynamicsUtils BulletInverseDynamics Bullet3Common LinearMath gtest
)

if(NOT WIN32)
	link_libraries(pthread)
endif()


add_executable(Test_BulletInverseDynamicsJacobian
	test_invdyn_jacobian.cpp
)

add_test(Test_BulletInverseDynamicsJacobian_PASS Test_BulletInverseDynamicsJacobian)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(Test_BulletInverseDynamicsJacobian PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(Test_BulletInverseDynamicsJacobian PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(Test_BulletInverseDynamicsJacobian PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()

include_directories(
        .
        ../../src
        ../gtest-1.7.0/include
        ../../Extras/InverseDynamics
        ../../examples/ThirdPartyLibs
)

#add_definitions(-DGTEST_HAS_PTHREAD=1)
add_definitions(-D_VARIADIC_MAX=10)

link_libraries(
	BulletDynamics BulletCollision  BulletInverseDynamicsUtils BulletInverseDynamics Bullet3Common LinearMath gtest
)

if(NOT WIN32)
	link_libraries(pthread)
endif()


ADD_EXECUTABLE(Test_BulletInverseForwardDynamics
	test_invdyn_bullet.cpp
	../../examples/Utils/b3ResourcePath.cpp
	../../examples/Importers/ImportURDFDemo/ConvertRigidBodies2MultiBody.h
	../../examples/Importers/ImportURDFDemo/MultiBodyCreationInterface.h
	../../examples/Importers/ImportURDFDemo/MyMultiBodyCreator.cpp
	../../examples/Importers/ImportURDFDemo/MyMultiBodyCreator.h
	../../examples/Importers/ImportURDFDemo/BulletUrdfImporter.cpp
	../../examples/Importers/ImportURDFDemo/BulletUrdfImporter.h
	../../examples/Importers/ImportURDFDemo/urdfStringSplit.cpp
	../../examples/Importers/ImportURDFDemo/UrdfParser.cpp
	../../examples/Importers/ImportURDFDemo/UrdfParser.h
	../../examples/Importers/ImportURDFDemo/URDF2Bullet.cpp
	../../examples/Importers/ImportURDFDemo/URDF2Bullet.h
	../../examples/Importers/ImportMeshUtility/b3ImportMeshUtility.cpp
	../../examples/ThirdPartyLibs/stb_image/stb_image.cpp
	../../examples/Utils/b3Clock.cpp
	../../Extras/Serialize/BulletWorldImporter/btBulletWorldImporter.cpp
	../../Extras/Serialize/BulletWorldImporter/btWorldImporter.cpp
	../../Extras/Serialize/BulletFileLoader/bChunk.cpp
	../../Extras/Serialize/BulletFileLoader/bFile.cpp
	../../Extras/Serialize/BulletFileLoader/bDNA.cpp
	../../Extras/Serialize/BulletFileLoader/btBulletFile.cpp
	../../examples/Importers/ImportURDFDemo/URDFImporterInterface.h
	../../examples/Importers/ImportURDFDemo/URDFJointTypes.h
	../../examples/Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp
	../../examples/Importers/ImportObjDemo/LoadMeshFromObj.cpp
	../../examples/Importers/ImportSTLDemo/ImportSTLSetup.h
	../../examples/Importers/ImportSTLDemo/LoadMeshFromSTL.h
	../../examples/Importers/ImportColladaDemo/LoadMeshFromCollada.cpp
	../../examples/Importers/ImportColladaDemo/ColladaGraphicsInstance.h
	../../examples/ThirdPartyLibs/Wavefront/tiny_obj_loader.cpp
	../../examples/ThirdPartyLibs/tinyxml/tinystr.cpp
	../../examples/ThirdPartyLibs/tinyxml/tinyxml.cpp
	../../examples/ThirdPartyLibs/tinyxml/tinyxmlerror.cpp
	../../examples/ThirdPartyLibs/tinyxml/tinyxmlparser.cpp
)

add_test(Test_BulletInverseForwardDynamics_PASS Test_BulletInverseForwardDynamics)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(Test_BulletInverseForwardDynamics PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(Test_BulletInverseForwardDynamics PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(Test_BulletInverseForwardDynamics PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()

include_directories(
	.
	../../src
	../gtest-1.7.0/include
	../../Extras/InverseDynamics
)

#add_definitions(-DGTEST_HAS_PTHREAD=1)
add_definitions(-D_VARIADIC_MAX=10)

link_libraries(
	BulletInverseDynamicsUtils BulletInverseDynamics Bullet3Common LinearMath gtest
)
if(NOT WIN32)
	link_libraries(pthread)
endif()

add_executable(Test_BulletInverseDynamics
	test_invdyn_kinematics.cpp
)

add_test(Test_BulletInverseDynamics_PASS Test_BulletInverseDynamics)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(Test_BulletInverseDynamics PROPERTIES  DEBUG_POSTFIX "_Debug")
	set_target_properties(Test_BulletInverseDynamics PROPERTIES  MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(Test_BulletInverseDynamics PROPERTIES  RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()
