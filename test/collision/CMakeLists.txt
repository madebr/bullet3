include_directories(
	.
	../../src
	../gtest-1.7.0/include
)

#add_definitions(-DGTEST_HAS_PTHREAD=1)
add_definitions(-D_VARIADIC_MAX=10)

link_libraries(
	LinearMath gtest
)

if(NOT WIN32)
	link_libraries(pthread)
endif()

add_executable(Test_Collision
	main.cpp
	../../src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp
	../../src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h
	../../src/BulletCollision/CollisionShapes/btSphereShape.cpp
	../../src/BulletCollision/CollisionShapes/btMultiSphereShape.cpp
	../../src/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp
	../../src/BulletCollision/CollisionShapes/btConvexShape.cpp
	../../src/BulletCollision/CollisionShapes/btConvexInternalShape.cpp
	../../src/BulletCollision/CollisionShapes/btCollisionShape.cpp
	../../src/BulletCollision/CollisionShapes/btConvexPolyhedron.cpp
)

add_test(Test_Collision_PASS Test_Collision)

if(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
	set_target_properties(Test_Collision PROPERTIES DEBUG_POSTFIX "_Debug")
	set_target_properties(Test_Collision PROPERTIES MINSIZEREL_POSTFIX "_MinsizeRel")
	set_target_properties(Test_Collision PROPERTIES RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
endif()
