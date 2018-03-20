# required for DEB-DEFAULT to work as intended
cmake_minimum_required(VERSION 3.6)

set(PROJECT_VERSION 1.0)
set(CPACK_GENERATOR "DEB")

set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})

# determine Git commit ID
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message("GIT_COMMIT: ${GIT_COMMIT}")
set(CPACK_DEBIAN_PACKAGE_RELEASE "git${GIT_COMMIT}")

if (DEFINED ENV{ARCH})
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE $ENV{ARCH})
    if (CPACK_DEBIAN_PACKAGE_ARCHITECTURE MATCHES "i686")
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386")
    endif ()
endif ()

message("CPACK_DEBIAN_PACKAGE_ARCHITECTURE: ${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alexis Lopez Zubieta")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/azubieta/appimage-desktop-integration")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")


set(CPACK_DEBIAN_FIRST-RUN_PACKAGE_DEPENDS "libqt5core5a, libqt5widgets5, libappimage, libarchive13, libc6 (>= 2.4), libglib2.0-0, zlib1g, fuse")
set(CPACK_COMPONENT_FIRST-RUN_DESCRIPTION "First run utility\n Use it to handle newly downloaded appimages. Allow to verify and deploy desktop integration files.")


set(CPACK_DEBIAN_USER-APPS-MONITOR_PACKAGE_DEPENDS "libappimage, libarchive13, libc6 (>= 2.4), libglib2.0-0, zlib1g, fuse")
set(CPACK_COMPONENT_USER-APPS-MONITOR_DESCRIPTION "
    Monitor appimage files.\n Monitor appimage files in HOME/Applications and /opt/applications to create or remove proper desktop integration files.")


set(CPACK_COMPONENTS_ALL first-run user-apps-monitor)
set(CPACK_DEB_COMPONENT_INSTALL ON)

include(CPack)