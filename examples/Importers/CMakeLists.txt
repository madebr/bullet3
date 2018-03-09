add_library(ImportersExample STATIC EXCLUDE_FROM_ALL
	../Importers/ImportBsp/ImportBspExample.h
	../Importers/ImportBsp/ImportBspExample.cpp
	../Importers/ImportBsp/BspLoader.h
	../Importers/ImportBsp/BspLoader.cpp
	../Importers/ImportBsp/BspConverter.h
	../Importers/ImportBsp/BspConverter.cpp

	../Importers/ImportBullet/SerializeSetup.h
	../Importers/ImportBullet/SerializeSetup.cpp

	../Importers/ImportColladaDemo/btMatrix4x4.h
	../Importers/ImportColladaDemo/ColladaGraphicsInstance.h
	../Importers/ImportColladaDemo/ImportColladaSetup.h
	../Importers/ImportColladaDemo/ImportColladaSetup.cpp
	../Importers/ImportColladaDemo/LoadMeshFromCollada.h
	../Importers/ImportColladaDemo/LoadMeshFromCollada.cpp

	../Importers/ImportMeshUtility/b3ImportMeshUtility.h
	../Importers/ImportMeshUtility/b3ImportMeshUtility.cpp

	../Importers/ImportMJCFDemo/BulletMJCFImporter.h
	../Importers/ImportMJCFDemo/BulletMJCFImporter.cpp
	../Importers/ImportMJCFDemo/ImportMJCFSetup.h
	../Importers/ImportMJCFDemo/ImportMJCFSetup.cpp

	../Importers/ImportObjDemo/ImportObjExample.h
	../Importers/ImportObjDemo/ImportObjExample.cpp
	../Importers/ImportObjDemo/LoadMeshFromObj.h
	../Importers/ImportObjDemo/LoadMeshFromObj.cpp
	../Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.h
	../Importers/ImportObjDemo/Wavefront2GLInstanceGraphicsShape.cpp

	../Importers/ImportSDFDemo/ImportSDFSetup.h
	../Importers/ImportSDFDemo/ImportSDFSetup.cpp

	../Importers/ImportSTLDemo/ImportSTLSetup.h
	../Importers/ImportSTLDemo/ImportSTLSetup.cpp
	../Importers/ImportSTLDemo/LoadMeshFromSTL.h

	../Importers/ImportURDFDemo/BulletUrdfImporter.h
	../Importers/ImportURDFDemo/BulletUrdfImporter.cpp
	../Importers/ImportURDFDemo/ConvertRigidBodies2MultiBody.h
	../Importers/ImportURDFDemo/ImportURDFSetup.h
	../Importers/ImportURDFDemo/ImportURDFSetup.cpp
	../Importers/ImportURDFDemo/MultiBodyCreationInterface.h
	../Importers/ImportURDFDemo/MyMultiBodyCreator.h
	../Importers/ImportURDFDemo/MyMultiBodyCreator.cpp
	../Importers/ImportURDFDemo/SDFAudioTypes.h
	../Importers/ImportURDFDemo/URDF2Bullet.h
	../Importers/ImportURDFDemo/URDF2Bullet.cpp
	../Importers/ImportURDFDemo/urdf_samples.h
	../Importers/ImportURDFDemo/URDFImporterInterface.h
	../Importers/ImportURDFDemo/URDFJointTypes.h
	../Importers/ImportURDFDemo/urdfLexicalCast.h
	../Importers/ImportURDFDemo/UrdfParser.h
	../Importers/ImportURDFDemo/UrdfParser.cpp
	../Importers/ImportURDFDemo/UrdfRenderingInterface.h
	../Importers/ImportURDFDemo/urdfStringSplit.cpp
	../Importers/ImportURDFDemo/urdfStringSplit.h
)

target_include_directories(ImportersExample
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(ImportersExample
	PUBLIC
		LinearMath
		BulletDynamics
		WaveFront
		stb_image
)

set_target_properties(ImportersExample
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
