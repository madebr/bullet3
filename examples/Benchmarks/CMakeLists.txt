add_library(BenchmarkDemo STATIC EXCLUDE_FROM_ALL
	BenchmarkDemo.cpp
	BenchmarkDemo.h
)

target_include_directories(BenchmarkDemo
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(BenchmarkDemo
	PUBLIC
		LinearMath
		Bullet3Common
		BulletCollision
)

set_target_properties(BenchmarkDemo
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
