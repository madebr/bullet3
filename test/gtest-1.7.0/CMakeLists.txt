include_directories(
	.
	include
)

set(gtest-1.7.0_SRCS
	src/gtest-all.cc
)

#add_definitions(-DGTEST_HAS_PTHREAD=1)
add_definitions(-D_VARIADIC_MAX=10)

file(GLOB_RECURSE gtest-1.7.0_HDRS "*.h")

add_library(gtest
	${gtest-1.7.0_SRCS}
	${gtest-1.7.0_HDRS}
)
