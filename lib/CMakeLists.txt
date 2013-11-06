# Wenn diese Bibliothek zusätzliche includes benötigt, müssen diese
# natürlich eingefügt werden.

include_directories ( src header )

OPTION(WITH_MPL3115A2 "Include Sensor MPL3115A2" ON)
OPTION(WITH_MPU6050 "Include Sensor MPU6050" ON)


# Hier wird definiert, welche Quellcodedateien zur Bibliothek dazugehören.
# Bei großen Projekten ist eine logische Unterteilung sinnvoll.
set(pi_SRCS
    src/pi/pibcm2835.cpp
    src/pi/pii2cbus.cpp
    src/pi/pii2c.cpp
)

if (WITH_MPL3115A2)
  set (pi_SRCS ${pi_SRCS}
    src/pi/interfaces/MPL3115A2.cpp
  )
endif (WITH_MPL3115A2)

if (WITH_MPU6050)
  set (pi_SRCS ${pi_SRCS}
    src/pi/interfaces/MPU6050.cpp
  )
endif (WITH_MPU6050)



find_package( Boost REQUIRED )

# Es wird festgelegt, dass es sich um eine gemeinsam genutzt Bibliothek
# handelt. Um eine statische Bibliothek zu bekommen, wird
# SHARED durch STATIC ersetzt.
add_library (pi STATIC ${pi_SRCS})
target_link_libraries ( pi bcm2835 )

