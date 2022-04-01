# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(soci_core)

add_library(${PROJECT_NAME} STATIC IMPORTED GLOBAL)

set_target_properties(${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libsoci_core.a)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} INTERFACE pthread ssl crypto )

#set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES pthread)

# External project libraries system wide dependencies apt-get install libmysqlclient-dev

  #target_link_libraries(${PROJECT_NAME} INTERFACE mysql_client)

  #target_link_libraries(${PROJECT_NAME} INTERFACE mysql_services)

  # #apt-get install libssl-dev -> /usr/lib/x86_64-linux-gnu/libssl.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE ssl)
  # #libssl-dev -> /usr/lib/x86_64-linux-gnu/libcrypto.a
  #target_link_libraries(${PROJECT_NAME} INTERFACE crypto)
  # #apt-get install libc6-dev -> /usr/lib/x86_64-linux-gnu/libpthread.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE pthread)
  # #libc6-dev /usr/lib/x86_64-linux-gnu/libpthread.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE dl)
  #libc6-dev /usr/lib/x86_64-linux-gnu/libdl.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE m)
  # #apt-get install zlib1g-dev -> /usr/lib/x86_64-linux-gnu/libz.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE z)

project(soci_empty)

add_library(${PROJECT_NAME} STATIC IMPORTED GLOBAL)

set_target_properties(${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libsoci_empty.a)

project(soci_mysql)

add_library(${PROJECT_NAME} STATIC IMPORTED GLOBAL)

set_target_properties(${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libsoci_mysql.a)

target_include_directories( ${PROJECT_NAME} INTERFACE /usr/include/mysql )

#mysql_client/mysql_services come from [project_root]/external/libraries/mysql/CMakeLists.txt
target_link_libraries(${PROJECT_NAME} INTERFACE soci_core mysql_client mysql_services )

#set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES pthread)
#set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES ssl)
#set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES crypto)
#set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES soci_core)

  # target_link_libraries(${PROJECT_NAME} INTERFACE mysql_client)

  # target_link_libraries(${PROJECT_NAME} INTERFACE mysql_services)

  # target_link_libraries(${PROJECT_NAME} INTERFACE soci_core)

  # #apt-get install libssl-dev -> /usr/lib/x86_64-linux-gnu/libssl.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE ssl)
  # #libssl-dev -> /usr/lib/x86_64-linux-gnu/libcrypto.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE crypto)
  # #apt-get install libc6-dev -> /usr/lib/x86_64-linux-gnu/libpthread.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE pthread)
  # #libc6-dev /usr/lib/x86_64-linux-gnu/libpthread.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE dl)
  # #libc6-dev /usr/lib/x86_64-linux-gnu/libdl.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE m)
  # #apt-get install zlib1g-dev -> /usr/lib/x86_64-linux-gnu/libz.a
  # target_link_libraries(${PROJECT_NAME} INTERFACE z)

# project(soci_pgsql)

# add_library(${PROJECT_NAME} STATIC IMPORTED GLOBAL)

# set_target_properties(${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/static/libsoci_pgsql.a)


# External project libraries system wide dependencies apt-get install libpgclient-dev

#target_link_libraries(${PROJECT_NAME} INTERFACE pgsql_client)

#target_link_libraries(${PROJECT_NAME} INTERFACE pgsql_service)
