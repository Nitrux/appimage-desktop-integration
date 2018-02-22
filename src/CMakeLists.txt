# LibAppimage
include(../external_projects/libappimage.cmake)
install(FILES ${libappimage_PATH} DESTINATION lib)

# Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)

# Targets
add_subdirectory(first_run)