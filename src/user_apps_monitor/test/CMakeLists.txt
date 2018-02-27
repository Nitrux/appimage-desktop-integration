enable_testing()

include(../../../external-projects/gtest.cmake)

add_executable(user_apps_monitor_tests
    $<TARGET_OBJECTS:user_apps_monitor_core>

    main.cpp
    TestRegistry.cpp
    )

target_include_directories(user_apps_monitor_tests
    PRIVATE ${CMAKE_SOURCE_DIR}/src/core
    private ${gtest_INCLUDE_DIRS}
    PRIVATE ${Qt5Core_INCLUDE_DIRS}
    )

target_compile_definitions(user_apps_monitor_tests
    PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/"
    )

target_link_libraries(user_apps_monitor_tests
    libappimage
    Qt5::Core

    ${gtest_LIBRARIES}
    pthread # this must be last else it fails at linking
    )

add_dependencies(user_apps_monitor_tests gtest)