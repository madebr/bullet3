add_library(b3Clock STATIC EXCLUDE_FROM_ALL
	b3Clock.h
	b3Clock.cpp
)

target_include_directories(b3Clock
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}"
)
