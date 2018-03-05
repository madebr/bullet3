include_directories(
	.
)

set(BussIK_SRCS
	Jacobian.cpp
	LinearR2.cpp
	LinearR3.cpp
	LinearR4.cpp
	MatrixRmn.cpp
	Misc.cpp
	Node.cpp
	Tree.cpp
	VectorRn.cpp
)

set(BussIK_HDRS
	Jacobian.h
	LinearR2.h
	LinearR3.h
	LinearR4.h
	MathMisc.h
	MatrixRmn.h
	Node.h
	Spherical.h
	Tree.h
	VectorRn.h
)

add_library(BussIK
	${BussIK_SRCS}
	${BussIK_HDRS}
)
