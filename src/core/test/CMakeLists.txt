enable_testing()

include(../../../third-party/gtest.cmake)

add_executable(core_tests
    $<TARGET_OBJECTS:appimage_dektop_integration>

    main.cpp
    TestRegistry.cpp
    )

target_include_directories(core_tests
    PRIVATE ${CMAKE_SOURCE_DIR}/src/core
    private ${gtest_INCLUDE_DIRS}
    PRIVATE ${Qt5Core_INCLUDE_DIRS}
    )

target_compile_definitions(core_tests
    PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/"
    )

target_link_libraries(core_tests
    libappimage
    Qt5::Core

    ${gtest_LIBRARIES}
    pthread # this must be last else it fails at linking
    )

add_dependencies(core_tests gtest)

add_test(core_tests core_tests)