SET(SDNA_DEPENDENCIES
	"${CMAKE_CURRENT_SOURCE_DIR}/DNA_rigidbody.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btVector3.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btQuaternion.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btMatrix3x3.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btTransform.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/BroadphaseCollision/btQuantizedBvh.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btCollisionShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btStaticPlaneShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConvexInternalShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btMultiSphereShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btStridingMeshInterface.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btCompoundShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btCylinderShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConeShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btCapsuleShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btTriangleInfoMap.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/NarrowPhaseCollision/btPersistentManifold.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/Gimpact/btGImpactShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConvexHullShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionDispatch/btCollisionObject.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btContactSolverInfo.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/Dynamics/btDynamicsWorld.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/Dynamics/btRigidBody.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btTypedConstraint.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btHingeConstraint.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btConeTwistConstraint.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btSliderConstraint.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/ConstraintSolver/btGearConstraint.h"

	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletSoftBody/btSoftBodyData.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/Featherstone/btMultiBody.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics/Featherstone/btMultiBodyLinkCollider.h"
)

SET(SDNA_INCLUDEFILES_INCLUDE "${PROJECT_BINARY_DIR}/sdna_includefiles.h")
SET(SDNA_INCLUDEFILES_INCLUDE_TMP "${PROJECT_BINARY_DIR}/sdna_includefiles_tmp.h")
FILE(WRITE "${SDNA_INCLUDEFILES_INCLUDE_TMP}")
FOREACH(HDR ${SDNA_DEPENDENCIES})
	FILE(APPEND "${SDNA_INCLUDEFILES_INCLUDE_TMP}" "\"${HDR}\",\n")
ENDFOREACH()
EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${SDNA_INCLUDEFILES_INCLUDE_TMP}" "${SDNA_INCLUDEFILES_INCLUDE}")

SET(MAKESDNA_HDRS
	${SDNA_INCLUDEFILES_INCLUDE}
 	${SDNA_DEPENDENCIES}
)

SET(MAKESDNA_SRC
	makesdna.cpp
)

ADD_EXECUTABLE(makesdna ${MAKESDNA_SRC} ${MAKESDNA_HDRS})
TARGET_INCLUDE_DIRECTORIES(makesdna PRIVATE "${PROJECT_BINARY_DIR}")

SET_PROPERTY(GLOBAL PROPERTY SDNA_SOURCES ${SDNA_DEPENDENCIES})

FUNCTION(GENERATE_SDNA OUTPUT)
	GET_PROPERTY(SDNA_DEPENDENCIES GLOBAL PROPERTY SDNA_SOURCES)

	MESSAGE(STATUS "makesdna will generate ${OUTPUT}")

	ADD_CUSTOM_COMMAND(
		OUTPUT "${OUTPUT}"
		COMMAND makesdna "${OUTPUT}" ""
		DEPENDS makesdna ${SDNA_DEPENDENCIES}
		VERBATIM)
ENDFUNCTION()
