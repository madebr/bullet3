add_library(glad STATIC EXCLUDE_FROM_ALL
	glad.c
)

target_include_directories(glad
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)

set_target_properties(glad
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)

target_link_libraries(glad
	PUBLIC
		"${DL}"
)

#################

if(UNIX AND NOT APPLE)
	add_library(glad_glx STATIC EXCLUDE_FROM_ALL
		glad_glx.c
	)

	target_include_directories(glad_glx
		PUBLIC
			"${CMAKE_CURRENT_LIST_DIR}"
	)

	set_target_properties(glad_glx
		PROPERTIES
			POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
	)

	target_link_libraries(glad_glx
		PUBLIC
			optionalX11
			"${DL}"
	)
endif()
