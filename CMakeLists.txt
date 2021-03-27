cmake_minimum_required (VERSION 3.8)

set(THIS printus)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${THIS} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${THIS} VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)
include_directories(src)

add_executable(otus_print src/main.cpp lib/printus.h)
set_target_properties(otus_print PROPERTIES CMAKE_CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(otus_print PRIVATE "${CMAKE_BINARY_DIR}")


if (MSVC)
    target_compile_options(otus_print PRIVATE
            /W4
            )
else ()
    target_compile_options(otus_print PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()



install(TARGETS otus_print RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)