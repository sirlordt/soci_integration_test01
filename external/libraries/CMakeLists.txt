# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required( VERSION 3.11 )

project( MAIN_EXTERNAL_LIBRARIES
         VERSION 0.1
         DESCRIPTION "Main External Libraries" )

# # ******* mysql ********
add_subdirectory( ${PROJECT_SOURCE_DIR}/mysql )  # look in mysql subdirectory for CMakeLists.txt to process
# # ******* mysql ********

# ******* nanojson ********
add_subdirectory( ${PROJECT_SOURCE_DIR}/nanojson )  # look in nanojson subdirectory for CMakeLists.txt to process
# ******* nanojson ********

# ******* soci ********

add_subdirectory( ${PROJECT_SOURCE_DIR}/soci )  # look in soci subdirectory for CMakeLists.txt to process

#add_subdirectory( ${PROJECT_SOURCE_DIR}/soci_manual_static )  # look in soci subdirectory for CMakeLists.txt to process

#include(soci/soci.cmake)

# project(soci_full)

# file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/soci_full/src/core/*.cpp ${PROJECT_SOURCE_DIR}/soci_full/src/backends/mysql/*.cpp)
# file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/soci_full/include/*.h ${PROJECT_SOURCE_DIR}/soci_full/include/mysql/*.h ${PROJECT_SOURCE_DIR}/soci_full/include/private)

# message(STATUS "soci_SOURCES=${SOURCES}")
# message(STATUS "soci_HEADERS=${HEADERS}")

# add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# #message(STATUS "module_GUI=${PROJECT_SOURCE_DIR}")

# # PUBLIC needed to make both lib_a.h and lib_a library available elsewhere in project
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/soci_full/include /usr/include/mysql)


#add_subdirectory( ${PROJECT_SOURCE_DIR}/soci_manual_static )  # look in nanojson subdirectory for CMakeLists.txt to process

# # # All compile options need to be set before the SOCI directory gets included.
# # # The backend you want to use needs to be enabled here.
# set(SOCI_STATIC ON)
# set(SOCI_SHARED OFF)
# set(SOCI_TESTS OFF)
# # set(SOCI_ASAN OFF)
# set(SOCI_CXX11 ON)
# set(SOCI_LIBDIR lib)
# set(WITH_SQLITE3 ON)
# set(WITH_POSTGRESQL ON)
# set(WITH_BOOST OFF)
# set(WITH_DB2 OFF)
# set(WITH_ODBC OFF)
# set(WITH_ORACLE OFF)
# set(WITH_MYSQL OFF)
# set(SOCI_EMPTY OFF)

# include_directories( ${PROJECT_SOURCE_DIR}/soci_full/include )

# add_subdirectory(${PROJECT_SOURCE_DIR}/soci_full)

# set(SOCI_STATIC ON)
# set(SOCI_EMPTY ON)
# set(SOCI_TESTS OFF)
# set(WITH_MYSQL ON)
# set(SOCI_CXX11 ON)

# set(SOCI_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/soci)

# # #include_directories( ${SOCI_BINARY_DIR}/soci/include )

# add_subdirectory(${PROJECT_SOURCE_DIR}/soci ${SOCI_BINARY_DIR})


# set_property(TARGET soci_mysql APPEND PROPERTY
#    INTERFACE_INCLUDE_DIRECTORIES
#     $<BUILD_INTERFACE:${SOCI_BINARY_DIR}/include>
# )

# set_property(TARGET soci_mysql APPEND PROPERTY
#    INTERFACE_INCLUDE_DIRECTORIES
#    /usr/include/mysql
#    # $<BUILD_INTERFACE:${SOCI_MYSQL_INCLUDE_DIRECTORIES}>
# )

#add_library( soci_config INTERFACE )


#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. ${SOCI_BINARY_DIR})

#external/libraries/soci/include/soci/soci-config.h
#external/libraries/soci/include/soci/soci-platform.h
#external/libraries/soci/include/soci/mysql/soci-mysql.h

# include(FetchContent)

# FetchContent_Declare(
#   soci
#   GIT_REPOSITORY https://github.com/SOCI/soci.git
#   CONFIGURE_COMMAND "-DSOCI_STATIC"
# )

# FetchContent_GetProperties(soci)
# if(NOT soci_POPULATED)
#   # Fetch the content using previously declared details
#   FetchContent_Populate(soci)

#   # Set custom variables, policies, etc.
#   # ...

#   # Bring the populated content into the build
#   add_subdirectory(${soci_SOURCE_DIR} ${soci_BINARY_DIR})

#   include_directories( ${soci_BINARY_DIR}/include )

#   include_directories( ${SOCI_MYSQL_INCLUDE_DIRECTORIES} )

#   message(STATUS "soci_BINARY_DIR=${soci_BINARY_DIR}")

# endif()

# add_subdirectory( ${PROJECT_SOURCE_DIR}/soci )  # look in soci subdirectory for CMakeLists.txt to process
# include_directories( ${PROJECT_SOURCE_DIR}/soci/include )
# ******* soci ********

#target_link_libraries( ${PROJECT_NAME} INTERFACE soci_core soci_mysql )

# # ******* conan package manager ********

# #set(CONAN_DISABLE_CHECK_COMPILER TRUE)

# # Download automatically, you can also just copy the conan.cmake file
# if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
#    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
#    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
#                   "${CMAKE_BINARY_DIR}/conan.cmake")
# endif()

# set(CONAN_DISABLE_CHECK_COMPILER True CACHE BOOL "" FORCE )

# include(${CMAKE_BINARY_DIR}/conan.cmake)

# conan_cmake_run(REQUIRES restinio/0.6.14
#                 BASIC_SETUP
#                 BUILD missing )

# # conan_cmake_run(REQUIRES mongo-cxx-driver/3.6.6
# #                 BASIC_SETUP
# #                 BUILD missing )

# # conan_cmake_run(REQUIRES nlohmann_json/3.10.4
# #                 BASIC_SETUP)

# conan_cmake_run(REQUIRES fmt/8.0.1
#                 BASIC_SETUP
# #                SETTINGS compiler.version=9.3;
#                 BUILD missing)

# # conan_cmake_run(REQUIRES rapidjson/cci.20211112
# #                 BASIC_SETUP )

# # conan_cmake_run(REQUIRES spdlog/1.9.2
# #                 BASIC_SETUP
# #                 BUILD missing )

# add_library(${PROJECT_NAME} INTERFACE)

# message(STATUS "CONAN_INCLUDE_DIRS=${CONAN_INCLUDE_DIRS}")

# target_include_directories( ${PROJECT_NAME} INTERFACE ${CONAN_INCLUDE_DIRS} )

# # ******* conan package manager ********
