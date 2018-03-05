subdirs(pendulum)

include_directories(
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/test/gtest-1.7.0/include"
)

add_definitions(-DUSE_GTEST)
add_definitions(-D_VARIADIC_MAX=10)

link_libraries(BulletDynamics BulletCollision LinearMath gtest)

if(NOT WIN32)
	link_libraries(pthread)
endif()

add_executable(Test_btKinematicCharacterController
	test_btKinematicCharacterController.cpp
)

add_test(Test_btKinematicCharacterController_PASS Test_btKinematicCharacterController)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(Test_btKinematicCharacterController PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(Test_btKinematicCharacterController PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(Test_btKinematicCharacterController PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()
