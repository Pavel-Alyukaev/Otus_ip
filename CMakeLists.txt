cmake_minimum_required(VERSION 3.2)

################################
# Версионность
################################

if(PROJECT_VERSION_PATCH GREATER 0)
    set(CUR_VERSION $ENV{PROJECT_VERSION_PATCH})
    project(IpFilter VERSION 0.0.${CUR_VERSION})
else()
    project(IpFilter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER} )
endif()

add_executable(IpFilter_cli main.cpp)
add_library(IpFilter IpFilter.cpp)

set_target_properties(IpFilter_cli IpFilter  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(IpFilter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(IpFilter_cli PRIVATE
    IpFilter 
)


if (MSVC)
    target_compile_options(IpFilter_cli PRIVATE
        /W4
    )
    target_compile_options(IpFilter PRIVATE
        /W4
    )
else ()
    target_compile_options(IpFilter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(IpFilter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS IpFilter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
