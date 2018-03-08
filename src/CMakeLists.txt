subdirs(
	LinearMath
	BulletCollision
	Bullet3Common
	BulletDynamics
	BulletInverseDynamics
	BulletSoftBody
)

if(BUILD_BULLET3)
	subdirs(
		Bullet3Geometry
		Bullet3Collision
		Bullet3Serialize/Bullet2FileLoader
		Bullet3Dynamics
		Bullet3OpenCL
	)
endif()

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
