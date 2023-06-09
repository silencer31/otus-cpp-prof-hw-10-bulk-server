cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk_server VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h)

#Main target 
add_executable(bulk_server main.cpp)
add_library(lib_bulk_server lib.cpp)

set_target_properties(bulk_server lib_bulk_server PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib_bulk_server 
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(bulk_server PRIVATE
    lib_bulk_server
)

if (MSVC)
    target_compile_options(bulk_server PRIVATE
        /W4
    )
    target_compile_options(lib_bulk_server PRIVATE
        /W4
    )
else ()
    target_compile_options(bulk_server PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lib_bulk_server PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()