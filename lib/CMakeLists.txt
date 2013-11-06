# Wenn diese Bibliothek zusätzliche includes benötigt, müssen diese
# natürlich eingefügt werden.

include_directories ( src header )

# Hier wird definiert, welche Quellcodedateien zur Bibliothek dazugehören.
# Bei großen Projekten ist eine logische Unterteilung sinnvoll.
set(pi_SRCS
    src/pi/pibcm2835.cpp
    src/pi/pii2cbus.cpp
    src/pi/pii2c.cpp
)

find_package( Boost REQUIRED )

# Es wird festgelegt, dass es sich um eine gemeinsam genutzt Bibliothek
# handelt. Um eine statische Bibliothek zu bekommen, wird
# SHARED durch STATIC ersetzt.
add_library (pi STATIC ${pi_SRCS})
target_link_libraries ( pi bcm2835 )

