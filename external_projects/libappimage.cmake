message(STATUS "Downloading and building LibAppImage")

include(ExternalProject)

ExternalProject_Add(AppImageKit
    GIT_REPOSITORY https://github.com/AppImage/AppImageKit.git
    GIT_TAG appimagetool/master
    GIT_SUBMODULES ""
    BUILD_COMMAND make gtest libappimage
    INSTALL_COMMAND make install DESTDIR=<INSTALL_DIR>
    )

ExternalProject_Get_Property(AppImageKit INSTALL_DIR)
set(AppImageKit_INSTALL_DIR ${INSTALL_DIR})

set(libappimage_PATH ${AppImageKit_INSTALL_DIR}${CMAKE_INSTALL_PREFIX}/lib/libappimage.so)
set(libappimage_INCLUDE_DIRECTORIES ${AppImageKit_INSTALL_DIR}${CMAKE_INSTALL_PREFIX}/include/)


add_library(libappimage SHARED IMPORTED)
set_property(TARGET libappimage PROPERTY IMPORTED_LOCATION ${libappimage_PATH})
set_property(TARGET libappimage PROPERTY INCLUDE_DIRECTORIES ${libappimage_INCLUDE_DIRECTORIES})
add_dependencies(libappimage AppImageKit)