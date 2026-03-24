cmake_minimum_required(VERSION 4.0.3)

# ---- Project Definition ----
project(lumberjack 
    VERSION 1.0.0
    LANGUAGES CXX
)

# ---------------------------------------------------------------
#   Compiler and build settings
# ---------------------------------------------------------------
option(LUMBERJACK_BUILD_TESTS "Build unit tests" OFF)
option(ENABLE_CLANG_TIDY "Enable clang-tidy analysis" OFF)
option(LUMBERJACK_ENABLE_ASAN "Enable AddressSanitizer" OFF)
set(CMAKE_GENERATOR "Ninja")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # Disable compiler-specific extensions (like gnu++20)

# ---------------------------------------------------------------
#   Clang Tidy "Linter" Settings
# ---------------------------------------------------------------
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE clang-tidy)
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy enabled")
        set(CMAKE_CXX_CLANG_TIDY
            ${CLANG_TIDY_EXE};
            --quiet
        )
    else()
        message(WARNING "clang-tidy requested but not found")
    endif()
endif()

# ---------------------------------------------------------------
#   ASan Scanner Settings
# ---------------------------------------------------------------
if(LUMBERJACK_ENABLE_ASAN)
    message(STATUS "AddressSanitizer enabled")
    
    target_compile_options(library_integration_tests PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
        -g
    )

    target_link_options(library_integration_tests PRIVATE
        -fsanitize=address
    )    
endif()

# ---------------------------------------------------------------
#   Library target
# ---------------------------------------------------------------
# Specify the source directories to include
file(GLOB SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/format/*.cpp
    src/format/builder/*.cpp
    src/writer/*.cpp
    src/time/*.cpp
    src/configuration/*.cpp
)

add_library(lumberjack STATIC ${SOURCES})

# Public headers - Available to consumers of this library
target_include_directories(lumberjack 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Defined C++ standard
target_compile_features(lumberjack 
    PUBLIC 
        cxx_std_17
)

# Version properties
set_target_properties(lumberjack PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME lumberjack
)

# Namespace alias for cleaner linking - Lumberjack::lumberjack
add_library(Lumberjack::lumberjack ALIAS lumberjack)

if(LUMBERJACK_BUILD_TESTS)
    # ---------------------------------------------------------------
    #   Testing Setup with GoogleTest
    # ---------------------------------------------------------------
    include(FetchContent)
  
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    # ---------------------------------------------------------------
    #   Test target definitions
    # ---------------------------------------------------------------
    # All tests
    file(GLOB_RECURSE ALL_TEST_SOURCES CONFIGURE_DEPENDS
        tests/*.cpp
    )

    # Integration tests
    file(GLOB_RECURSE INTEGRATION_TEST_SOURCES CONFIGURE_DEPENDS
        tests/integration/*.cpp
    )

    set(UNIT_TEST_SOURCES ${ALL_TEST_SOURCES})

    foreach(integration_file ${INTEGRATION_TEST_SOURCES})
        list(REMOVE_ITEM UNIT_TEST_SOURCES ${integration_file})
    endforeach()

    # ---------------------------------------------------------------
    #   Executable definitions
    # ---------------------------------------------------------------
    # --- Unit Test Executable
    add_executable(lumberjack_unit_tests 
        ${UNIT_TEST_SOURCES}
    )

    # Link the test executable against this library and GoogleTest
    target_link_libraries(lumberjack_unit_tests PRIVATE
        lumberjack
        GTest::gtest_main
        GTest::gmock_main
    )

    # --- Integration Test Executable (ASan-enabled)
    add_executable(lumberjack_integration_tests
        ${INTEGRATION_TEST_SOURCES}
    )

    target_link_libraries(lumberjack_integration_tests PRIVATE
        lumberjack
        GTest::gtest_main
        GTest::gmock_main
    )
    # ---------------------------------------------------------------

    # Register the test with CTest
    add_test(NAME lumberjack_unit_tests COMMAND lumberjack_unit_tests)

    include(GoogleTest)
    gtest_discover_tests(lumberjack_unit_tests)
    if (NOT ENABLE_ASAN)
        gtest_discover_tests(lumberjack_integration_tests)
    endif()
endif()
