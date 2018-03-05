subdirs(
	HelloWorld
	BasicDemo
)

if(BUILD_BULLET3)
	subdirs(
		ThirdPartyLibs/BussIK
		ExampleBrowser
		RobotSimulator
		SharedMemory
		ThirdPartyLibs/Gwen
		ThirdPartyLibs/clsocket
		OpenGLWindow TwoJoint
	)
endif()

if(BUILD_PYBULLET)
	subdirs(pybullet)
endif()
