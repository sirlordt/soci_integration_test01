#add_subdirectory( src/modules/GUI )   # look in module_a subdirectory for CMakeLists.txt to process
#add_subdirectory(src/modules/b)   # look in module_a subdirectory for CMakeLists.txt to process

# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required( VERSION 3.11-3.18 )

project( main )

#UUID_v4 library require this
#To avoid wear error message like next
#inlining failed in call to ‘always_inline’ ‘__m256i _mm256_add_epi8(__m256i, __m256i)’: target specific option mismatch
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

#file( GLOB_RECURSE SOURCES "src/*.cpp" )
file( GLOB_RECURSE SOURCES "src/main_03.cpp" )
#file( GLOB_RECURSE SOURCES "src/main_02.cpp" )
file( GLOB_RECURSE MODULES_SOURCES "src/modules/*.cpp" )
file( GLOB_RECURSE MODULES_INCLUDES_H "src/modules/*.h" )
file( GLOB_RECURSE MODULES_INCLUDES_HPP "src/modules/*.hpp" )

file( GLOB_RECURSE CONFIGS "config/*.*" )

#configure_file( ${PROJECT_SOURCE_DIR}/config/test.json ${CMAKE_CURRENT_BINARY_DIR}/config/test.json COPYONLY )

#file(COPY ${PROJECT_SOURCE_DIR}/config/test.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/config )
#${PROJECT_SOURCE_DIR}/

file( COPY ${CONFIGS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/config )

#include(FetchContent)
#include( ExternalProject )

# FetchContent_Declare( soci
#     GIT_REPOSITORY https://github.com/SOCI/soci
#     GIT_TAG master

#     #CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/soci
#     #                  CMAKE_ARGS      -DSOCI_CXX11:BOOL=ON
#     #                  CMAKE_ARGS      -DWITH_MYSQL:BOOL=ON
# )

#ExternalProject_Add_Step( soci configure CMAKE -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/soci )

# FetchContent_Populate(soci
#                       GIT_REPOSITORY https://github.com/SOCI/soci
#                       GIT_TAG master )
#                      CONFIGURE_COMMAND "-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/soci" )

# FetchContent_Declare( soci
#     GIT_REPOSITORY https://github.com/SOCI/soci
#     GIT_TAG master
#     GIT_SHALLOW ON
#                      CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/soci
#                      CMAKE_ARGS      -DSOCI_CXX11:BOOL=ON
#                      CMAKE_ARGS      -DWITH_MYSQL:BOOL=ON
# )

# FetchContent_GetProperties(soci)
# if(NOT soci_POPULATED)
#     set(SOCI_CXX11 ON CACHE INTERNAL "")
#     set(SOCI_STATIC ON CACHE INTERNAL "")
#     set(SOCI_SHARED ON CACHE INTERNAL "")
#     set(SOCI_TESTS OFF CACHE INTERNAL "")
#     # set(SOCI_ASAN OFF)
#     #set(soci_SOCI_CXX11 ON)
#     set(SOCI_LIBDIR lib)
#     set(WITH_SQLITE3 ON CACHE INTERNAL "")
#     set(WITH_POSTGRESQL OFF CACHE INTERNAL "")
#     set(WITH_BOOST OFF CACHE INTERNAL "")
#     set(WITH_DB2 OFF CACHE INTERNAL "")
#     set(WITH_ODBC OFF CACHE INTERNAL "")
#     set(WITH_ORACLE OFF CACHE INTERNAL "")
#     set(WITH_MYSQL ON CACHE INTERNAL "")
#     set(SOCI_EMPTY ON CACHE INTERNAL "")
#     FetchContent_Populate(soci)
#     add_subdirectory(
#         ${soci_SOURCE_DIR}
#         ${soci_BINARY_DIR}
#         EXCLUDE_FROM_ALL)

# endif()

# set_directory_properties( PROPERTIES EP_UPDATE_DISCONNECTED true )

# include( ExternalProject )
# ExternalProject_Add( soci
#                      GIT_REPOSITORY https://github.com/SOCI/soci
#                      GIT_TAG master  # it's much better to use a specific Git revision or Git tag for reproducability
#                      #CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX} -DSOCI_CXX11:BOOL=ON
#                      #CMAKE_CACHE_ARGS -Dmyvar:STRING=${mylist}   # need variable type e.g. STRING for this
#                      CMAKE_ARGS      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/soci
#                      CMAKE_ARGS      -DSOCI_CXX11:BOOL=ON
#                      CMAKE_ARGS      -DWITH_MYSQL:BOOL=ON
#                      CONFIGURE_HANDLED_BY_BUILD ON
#                      BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/soci/lib/${CMAKE_STATIC_LIBRARY_PREFIX}soci_core${CMAKE_STATIC_LIBRARY_SUFFIX} )

#message(STATUS "CMAKE_STATIC_LIBRARY_PREFIX=${CMAKE_STATIC_LIBRARY_PREFIX}")
#message(STATUS "CMAKE_STATIC_LIBRARY_SUFFIX=${CMAKE_STATIC_LIBRARY_SUFFIX}")

#execute_process( COMMAND git clone https://github.com/SOCI/soci ${PROJECT_SOURCE_DIR}/soci )

# message(STATUS "MAIN_ROOT_SOURCE_DIR=${MAIN_ROOT_SOURCE_DIR}")

# #execute_process( COMMAND git clone https://github.com/SOCI/soci ${PROJECT_SOURCE_DIR}/soci )

# file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/soci_install )
# file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/soci_build )

# #-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/soci_install -DCD_NO_COLOR:BOOL=ON -Dcoloron:BOOL=OFF
# execute_process( COMMAND cmake ${MAIN_ROOT_SOURCE_DIR}/external/libraries/soci -DSOCI_CXX11:BOOL=ON -DSOCI_TESTS:BOOL=OFF -DWITH_MYSQL:BOOL=ON WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/soci_build )

# execute_process( COMMAND cmake --build ${CMAKE_CURRENT_BINARY_DIR}/soci_build )

# execute_process( COMMAND cmake --install ${CMAKE_CURRENT_BINARY_DIR}/soci_build --prefix "${CMAKE_CURRENT_BINARY_DIR}/soci_install" )

# #-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/soci_install -DSOCI_CXX11:BOOL=ON -DWITH_MYSQL:BOOL=ON )

# add_library( soci_core STATIC IMPORTED GLOBAL )
# set_target_properties( soci_core PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/soci_install/lib/libsoci_core.a )

# target_include_directories( soci_core INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/soci_install/include )

# add_library( soci_mysql STATIC IMPORTED GLOBAL )
# set_target_properties( soci_mysql PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/soci_install/lib/libsoci_mysql.a )

# target_include_directories( soci_mysql INTERFACE /usr/include/mysql )

# target_link_libraries( soci_mysql INTERFACE soci_core mysql_client mysql_services )

#message(STATUS "CONAN_INCLUDE_DIRS=${CONAN_INCLUDE_DIRS}")

#include_directories( ${CONAN_INCLUDE_DIRS} )

add_executable( main ${MODULES_SOURCES} ${MODULES_INCLUDES_H} ${MODULES_INCLUDES_HPP} ${SOURCES} )

#target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src/modules/GUI/include )
target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src/include )

# include(CMakePrintHelpers)

# cmake_print_properties(TARGETS raylib
#                        PROPERTIES
#                        LOCATION
#                        INTERFACE_INCLUDE_DIRECTORIES)

# cmake_print_properties(
#     TARGETS raylib
#     PROPERTIES ALL
# )

#find_package(fmt)

#target_link_options( ${PROJECT_NAME} PRIVATE -Wl,--gc-sections )

target_link_libraries( ${PROJECT_NAME} PRIVATE NANOJSON UUID_V4 mysql_client mysql_services soci_core soci_mysql ) # soci_core soci_mysql )

# ***************** Conan Integration ***************

target_link_libraries( ${PROJECT_NAME} PRIVATE PACKAGE_MANAGER_CONAN_LIBS )

# ***************** Conan Integration ***************

# -static-libgcc -static-libstdc++

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
target_compile_features( main PUBLIC cxx_std_20 )
