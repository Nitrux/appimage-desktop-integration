add_library(appimage_dektop_integration OBJECT
    Registry.h
    Registry.cpp
    Validator.h
    Validator.cpp
    Deployer.h
    Deployer.cpp
    Executor.h
    Executor.cpp
    )

target_compile_options(appimage_dektop_integration PUBLIC -fPIC -fexceptions)
target_include_directories(appimage_dektop_integration PUBLIC
    ${libappimage_INCLUDE_DIRECTORIES}
    ${Qt5Core_INCLUDE_DIRS} )

add_subdirectory(test)