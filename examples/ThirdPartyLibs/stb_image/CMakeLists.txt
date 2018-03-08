add_library(stb_image_header_only INTERFACE)

target_include_directories(stb_image_header_only
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}/.."
)

##################

add_library(stb_image STATIC EXCLUDE_FROM_ALL
	stb_image.cpp
)

target_include_directories(stb_image
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/.."
)

set_target_properties(stb_image
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
