add_library(user_apps_monitor_core OBJECT
    Registry.h
    Registry.cpp
    Validator.h
    Validator.cpp
    Deployer.h
    Deployer.cpp
    Executor.h
    Executor.cpp
    )

target_compile_options(user_apps_monitor_core PUBLIC -fPIC -fexceptions)
target_include_directories(user_apps_monitor_core PUBLIC
    ${libappimage_INCLUDE_DIRECTORIES}
    ${Qt5Core_INCLUDE_DIRS} )
