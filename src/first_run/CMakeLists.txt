SET(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Gui Widgets)

add_executable(appimage_first_run
    main.cpp
    core/Validator.h
    core/Validator.cpp
    core/Deployer.h
    core/Deployer.cpp
    core/Executor.h
    core/Executor.cpp
    gui/ValidationDialog.h
    gui/ValidationDialog.cpp
    gui/ValidationDialog.ui
    gui/UiController.cpp
    gui/UiController.h
    gui/UnsecureAppimageDialog.h
    gui/UnsecureAppimageDialog.cpp
    gui/UnsecureAppimageDialog.ui
    gui/DeploymentDialog.h
    gui/DeploymentDialog.cpp
    gui/DeploymentDialog.ui
    ../../res/res.qrc)

target_include_directories(appimage_first_run PRIVATE ${libappimage_INCLUDE_DIRECTORIES})

target_link_libraries(appimage_first_run libappimage Qt5::Core Qt5::Gui Qt5::Widgets)

add_dependencies(appimage_first_run libappimage)

install(TARGETS appimage_first_run RUNTIME DESTINATION bin)
install(FILES org.appimage.first.run.Desktop DESTINATION share/applications)
