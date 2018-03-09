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
		Experiments
		ExtendedTutorials
		ForkLift
		FractureDemo
		GyroscopicDemo
		Importers
		InverseKinematics
		RenderingExamples

		ExampleBrowser
		RobotSimulator
		SharedMemory
		ThirdPartyLibs/Gwen
		ThirdPartyLibs/clsocket
		ThirdPartyLibs/Wavefront
		TwoJoint
	)
endif()

if(BUILD_PYBULLET)
	subdirs(pybullet)
endif()
