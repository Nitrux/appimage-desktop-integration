add_executable(appimage_first_run
    main.cpp)

target_include_directories(appimage_first_run PRIVATE ${libappimage_INCLUDE_DIRECTORIES})

target_link_libraries(appimage_first_run libappimage Qt5::Core)

add_dependencies(appimage_first_run libappimage)

install(TARGETS appimage_first_run RUNTIME DESTINATION bin)
install(FILES org.appimage.first.run.Desktop DESTINATION share/applications)
