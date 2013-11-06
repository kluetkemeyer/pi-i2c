
include_directories ( ${CMAKE_SOURCE_DIR}/lib/header src )

set ( app_SRCS
	src/main.cpp
)

add_executable ( app ${app_SRCS} )
target_link_libraries ( app bcm2835 pi )
