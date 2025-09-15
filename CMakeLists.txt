cmake_minimum_required(VERSION 4.0.3)

# ---- Project Definition ----
project(Logger++ 
    VERSION 0.1.0
    LANGUAGES CXX
)

# Options
option(LOGGER_BUILD_TESTS "Build unit tests" ON)
set(CMAKE_GENERATOR "Ninja")

# ---- Logging library ----
add_library(logger STATIC
        src/StandardOutputLogger.cpp
)

# Public headers
target_include_directories(logger 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Defined C++ standard
target_compile_features(logger 
    PUBLIC 
        cxx_std_17
)

# Version properties
set_target_properties(logger PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME logger
)

# Namespace alias (preferred consumption)
add_library(Logger::logger ALIAS logger)

# ---- Tests ----
if(LOGGER_BUILD_TESTS)

    include(FetchContent)
  
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(logger_tests tests/test_StandardOutputLogger.cpp)
    target_link_libraries(logger_tests PRIVATE
        Logger::logger
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(logger_tests)
endif()

