subdirs(
	Utils
	ThirdPartyLibs/BussIK
	ThirdPartyLibs/glad
	ThirdPartyLibs/optionalX11
	ThirdPartyLibs/stb_image
	StandaloneMain
	OpenGLWindow

	HelloWorld
	BasicDemo
)

if(BUILD_BULLET3)
	subdirs(
		ExampleBrowser/GwenGUISupport

		Benchmarks
		Constraints
		Collision
		DynamicControlDemo
		Evolution
		InverseKinematics
		RenderingExamples

		ExampleBrowser
		RobotSimulator
		SharedMemory
		ThirdPartyLibs/Gwen
		ThirdPartyLibs/clsocket
		TwoJoint
	)
endif()

if(BUILD_PYBULLET)
	subdirs(pybullet)
endif()
