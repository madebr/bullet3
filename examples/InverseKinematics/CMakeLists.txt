add_library(InverseKinematicsExample STATIC EXCLUDE_FROM_ALL
	InverseKinematicsExample.h
	InverseKinematicsExample.cpp
)

target_include_directories(InverseKinematicsExample
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(InverseKinematicsExample
	PUBLIC
		Bullet3Common
		OpenGLWindow
		BussIK
)

set_target_properties(InverseKinematicsExample
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
