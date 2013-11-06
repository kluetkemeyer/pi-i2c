
include_directories ( ${CMAKE_SOURCE_DIR}/lib/header src )


add_executable ( mpu6050 src/mpu6050_main.cpp )
add_executable ( mpl3115a2 src/mpl3115a2_main.cpp )
target_link_libraries ( mpu6050 bcm2835 pi )
target_link_libraries ( mpl3115a2 bcm2835 pi )
