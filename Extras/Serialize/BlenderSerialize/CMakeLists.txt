include_directories(
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
	"${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletFileLoader"
	"${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BlenderSerialize"
)

add_library(BlenderSerialize
	bBlenderFile.h
	bMain.h

	dna249.cpp
	dna249-64bit.cpp
	bBlenderFile.cpp
	bMain.cpp
)
