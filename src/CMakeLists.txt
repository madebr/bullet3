if(BUILD_BULLET3)
	subdirs(
		Bullet3OpenCL
		Bullet3Serialize/Bullet2FileLoader
		Bullet3Dynamics
		Bullet3Collision
		Bullet3Geometry
		)
endif()


subdirs(
	BulletInverseDynamics
	BulletSoftBody
	BulletCollision
	BulletDynamics
	LinearMath
	Bullet3Common
	)


if(INSTALL_LIBS)
	if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
		# Don't actually need to install any common files, the frameworks include everything
	else()
		install(
			FILES btBulletCollisionCommon.h btBulletDynamicsCommon.h
			DESTINATION "${INCLUDE_INSTALL_DIR}"
			)
	endif()
endif()
