set(Bullet3Collision_SRCS
	BroadPhaseCollision/b3DynamicBvh.cpp
	BroadPhaseCollision/b3DynamicBvhBroadphase.cpp
	BroadPhaseCollision/b3OverlappingPairCache.cpp
	NarrowPhaseCollision/b3ConvexUtility.cpp
	NarrowPhaseCollision/b3CpuNarrowPhase.cpp
)

set(Bullet3CollisionBroadPhase_HDRS
	BroadPhaseCollision/b3BroadphaseCallback.h
	BroadPhaseCollision/b3DynamicBvh.h
	BroadPhaseCollision/b3DynamicBvhBroadphase.h
	BroadPhaseCollision/b3OverlappingPair.h
	BroadPhaseCollision/b3OverlappingPairCache.h
)

set(Bullet3CollisionBroadPhaseShared_HDRS
	BroadPhaseCollision/shared/b3Aabb.h
)

set(Bullet3CollisionNarrowPhase_HDRS
	NarrowPhaseCollision/b3Config.h
	NarrowPhaseCollision/b3Contact4.h
	NarrowPhaseCollision/b3ConvexUtility.h
	NarrowPhaseCollision/b3CpuNarrowPhase.h
	NarrowPhaseCollision/b3RaycastInfo.h
	NarrowPhaseCollision/b3RigidBodyCL.h
)

set(Bullet3CollisionNarrowPhaseShared_HDRS
	NarrowPhaseCollision/shared/b3BvhSubtreeInfoData.h
	NarrowPhaseCollision/shared/b3BvhTraversal.h
	NarrowPhaseCollision/shared/b3ClipFaces.h
	NarrowPhaseCollision/shared/b3Collidable.h
	NarrowPhaseCollision/shared/b3Contact4Data.h
	NarrowPhaseCollision/shared/b3ContactConvexConvexSAT.h
	NarrowPhaseCollision/shared/b3ContactSphereSphere.h
	NarrowPhaseCollision/shared/b3ConvexPolyhedronData.h
	NarrowPhaseCollision/shared/b3FindConcaveSatAxis.h
	NarrowPhaseCollision/shared/b3FindSeparatingAxis.h
	NarrowPhaseCollision/shared/b3MprPenetration.h
	NarrowPhaseCollision/shared/b3NewContactReduction.h
	NarrowPhaseCollision/shared/b3QuantizedBvhNodeData.h
	NarrowPhaseCollision/shared/b3ReduceContacts.h
	NarrowPhaseCollision/shared/b3RigidBodyData.h
	NarrowPhaseCollision/shared/b3UpdateAabbs.h
)

set(Bullet3Collision_HDRS
	${Bullet3CollisionBroadPhase_HDRS}
	${Bullet3CollisionBroadPhaseShared_HDRS}
	${Bullet3CollisionNarrowPhaseShared_HDRS}
	${Bullet3CollisionNarrowPhase_HDRS}
)

add_library(Bullet3Collision
	${Bullet3Collision_SRCS}
	${Bullet3Collision_HDRS}
)

target_include_directories(Bullet3Collision
	PUBLIC
		"${BULLET_PHYSICS_SOURCE_DIR}/src"
)

target_link_libraries(Bullet3Collision
	PUBLIC
		Bullet3Geometry
)

set_target_properties(Bullet3Collision PROPERTIES VERSION ${BULLET_VERSION})
set_target_properties(Bullet3Collision PROPERTIES SOVERSION ${BULLET_VERSION})

if(INSTALL_LIBS)
	if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		if(APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
			install(TARGETS Bullet3Collision DESTINATION .)

			set_target_properties(Bullet3Collision PROPERTIES FRAMEWORK true)
			set_target_properties(Bullet3Collision PROPERTIES PUBLIC_HEADER "${Bullet3Collision_HDRS}")
			# Have to list out sub-directories manually:
			#todo
			#set_property(SOURCE ${Bullet3CollisionBroadPhase_HDRS} PROPERTY MACOSX_PACKAGE_LOCATION Headers/BroadPhaseCollision)
		else()
			install(
				TARGETS Bullet3Collision
				RUNTIME DESTINATION bin
				LIBRARY DESTINATION lib${LIB_SUFFIX}
				ARCHIVE DESTINATION lib${LIB_SUFFIX}
			)
			install(
				DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
				DESTINATION "${INCLUDE_INSTALL_DIR}"
				FILES_MATCHING
					PATTERN "*.h"
					PATTERN ".svn" EXCLUDE
					PATTERN "CMakeFiles" EXCLUDE
			)
		endif()
	endif()
endif()
