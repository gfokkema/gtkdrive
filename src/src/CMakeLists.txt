# Use PkgConfig to find GTKMM
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories (${GTKMM_INCLUDE_DIRS})
include_directories (${DRIVE_SOURCE_DIR}/include)
link_directories (${GTKMM_LIBRARY_DIRS})
link_directories (${DRIVE_SOURCE_DIR}/lib)

add_executable (drive auth_wrapper.cpp drive_wrapper.cpp wizard-mm.cpp main.cpp)

target_link_libraries(drive ${GTKMM_LIBRARIES})

target_link_libraries(drive google_drive_api)

target_link_libraries(drive googleapis_oauth2)
target_link_libraries(drive googleapis_curl_http)
target_link_libraries(drive googleapis_http)
target_link_libraries(drive googleapis_jsoncpp)
target_link_libraries(drive googleapis_json)
target_link_libraries(drive googleapis_openssl_codec)
target_link_libraries(drive googleapis_utils)
target_link_libraries(drive googleapis_internal)

target_link_libraries(drive curl)
target_link_libraries(drive crypto)
target_link_libraries(drive glog)
target_link_libraries(drive jsoncpp)
target_link_libraries(drive pthread)


# Use PkgConfig to find GTK+
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Add GTK+ to include and link directories
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable (wizard wizard.c)

target_link_libraries(wizard ${GTK3_LIBRARIES})
