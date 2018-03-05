if(BUILD_BULLET3)
	#subdirs(TestBullet3OpenCL)
	subdirs(
		InverseDynamics
		SharedMemory
	)
endif()

subdirs(
	gtest-1.7.0
	collision
	BulletDynamics
)
