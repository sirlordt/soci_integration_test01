cmake_minimum_required(VERSION 3.11)

message(STATUS "Extern: SOCI from github repo")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare( soci
    GIT_REPOSITORY https://github.com/SOCI/soci
    GIT_TAG master
    GIT_SHALLOW ON
)
FetchContent_GetProperties(soci)
if(NOT soci_POPULATED)
    set(SOCI_CXX11 ON CACHE INTERNAL "")
    set(SOCI_STATIC ON CACHE INTERNAL "")
    set(SOCI_SHARED ON CACHE INTERNAL "")
    set(SOCI_TESTS OFF CACHE INTERNAL "")
    # set(SOCI_ASAN OFF)
    #set(soci_SOCI_CXX11 ON)
    set(SOCI_LIBDIR lib)
    set(WITH_SQLITE3 ON CACHE INTERNAL "")
    set(WITH_POSTGRESQL OFF CACHE INTERNAL "")
    set(WITH_BOOST OFF CACHE INTERNAL "")
    set(WITH_DB2 OFF CACHE INTERNAL "")
    set(WITH_ODBC OFF CACHE INTERNAL "")
    set(WITH_ORACLE OFF CACHE INTERNAL "")
    set(WITH_MYSQL ON CACHE INTERNAL "")
    set(SOCI_EMPTY ON CACHE INTERNAL "")
    FetchContent_Populate(soci)
    add_subdirectory(
        ${soci_SOURCE_DIR}
        ${soci_BINARY_DIR})

    set_property(TARGET soci_core APPEND PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${soci_BINARY_DIR}/include>
    )

    set_property(TARGET soci_mysql APPEND PROPERTY
      INTERFACE_INCLUDE_DIRECTORIES
        /usr/include/mysql
    )

endif()

