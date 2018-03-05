project(GEN)

set(cpp_SRC
	apiGen.cpp
)

set(h_SRC
)

set(includes
	.
	"${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BulletFileLoader"
	"${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/BlenderSerialize"
	"${BULLET_PHYSICS_SOURCE_DIR}/src"
)

link_libraries(
	BulletFileLoader
	LinearMath
)

include_directories(${includes})

set(Main_LIBS LinearMath)

add_executable(HeaderGenerator
	${cpp_SRC}
	${h_SRC}
)

if(NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
	add_custom_command(
		TARGET HeaderGenerator
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/HeaderGenerator/createDnaString.bat ${CMAKE_CURRENT_BINARY_DIR}/createDnaString.bat
		COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${BULLET_PHYSICS_SOURCE_DIR}/Extras/Serialize/HeaderGenerator/bulletGenerate.py ${CMAKE_CURRENT_BINARY_DIR}/bulletGenerate.py
	)
endif()
