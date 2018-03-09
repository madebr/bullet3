add_library(WaveFront STATIC EXCLUDE_FROM_ALL
	tiny_obj_loader.h
	tiny_obj_loader.cpp
)

target_include_directories(WaveFront
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}/.."
)

set_target_properties(WaveFront
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)

##################

add_executable(App_WavefrontObjLoader
	main.cpp
)

target_link_libraries(App_WavefrontObjLoader
	PUBLIC
		WaveFront
)
