if(UNIX AND NOT APPLE)
	add_library(optionalX11 INTERFACE)

	target_include_directories(optionalX11
		INTERFACE
			"${CMAKE_CURRENT_LIST_DIR}"
	)
endif()
