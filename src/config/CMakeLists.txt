SET(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Gui Widgets)

add_executable(appimage-desktop-integration-config
    main.cpp
    GreeterDialog.h
    GreeterDialog.cpp
    GreeterDialog.ui
    FirstRunConfig.cpp
    FirstRunConfig.h
    UserAppsMonitorConfig.h
    UserAppsMonitorConfig.cpp
    )

target_include_directories(appimage-desktop-integration-config PRIVATE
    PRIVATE ${CMAKE_SOURCE_DIR}/src/core
    )

target_link_libraries(appimage-desktop-integration-config Qt5::Core Qt5::Gui Qt5::Widgets)

install(TARGETS appimage-desktop-integration-config RUNTIME DESTINATION bin COMPONENT config)
install(FILES org.appimage.desktop-integration-tool.desktop DESTINATION share/applications COMPONENT config)