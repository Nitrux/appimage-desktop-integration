SET(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Gui Widgets)

add_executable(appimage_first_run
    main.cpp
    FirstRun.cpp
    FirstRun.h
    FirstRunUiController.cpp
    FirstRunUiController.h
    ProgressDialog.h
    ProgressDialog.cpp
    ProgressDialog.ui
    HandleUnsecureAppimageDialog.h
    HandleUnsecureAppimageDialog.cpp
    HandleUnsecureAppimageDialog.ui
    FailureDialog.h
    FailureDialog.cpp
    FailureDialog.ui
    ../../res/res.qrc)

target_include_directories(appimage_first_run PRIVATE ${libappimage_INCLUDE_DIRECTORIES})

target_link_libraries(appimage_first_run libappimage Qt5::Core Qt5::Gui Qt5::Widgets)

add_dependencies(appimage_first_run libappimage)

install(TARGETS appimage_first_run RUNTIME DESTINATION bin)
install(FILES org.appimage.first.run.Desktop DESTINATION share/applications)
