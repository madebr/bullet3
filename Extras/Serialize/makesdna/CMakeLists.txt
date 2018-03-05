cmake_minimum_required(VERSION 3.2.2)

include_directories("${BULLET_PHYSICS_SOURCE_DIR}/src")

set(INC_FILES
	DNA_rigidbody.h

	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btVector3.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btMatrix3x3.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btTransform.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btCollisionShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionShapes/btConvexInternalShape.h"
	"${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision/CollisionDispatch/btCollisionObject.h"
)

set(makesdna_SRC
	makesdna.cpp
)

add_executable(makesdna
	${makesdna_SRC}
	${INC_FILES}
)

if(CMAKE_CL_64)
	# Output BulletDNA.c
	add_custom_command(
		OUTPUT "${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer64.cpp"
		COMMAND ${CMAKE_CFG_INTDIR}/makesdna ${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer64.cpp ${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/CommonSerialize/
		DEPENDS makesdna
	)
	set(BulletDNA_SRC
		"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer64.cpp"
	)

else()
	# Output BulletDNA.c
	add_custom_command(
		OUTPUT "${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer.cpp"
		COMMAND ${CMAKE_CFG_INTDIR}/makesdna ${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer.cpp ${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/CommonSerialize/
		DEPENDS makesdna
	)
	set(BulletDNA_SRC
		"${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath/btSerializer.cpp"
	)
endif()

# Build bf_dna library

add_library(BulletDNA
	${BulletDNA_SRC}
	${INC_FILES}
)

message(STATUS "Configuring makesdna")
