include_directories (${DRIVE_SOURCE_DIR}/include)
link_directories (${DRIVE_SOURCE_DIR}/lib)

add_executable (drive auth_wrapper.cpp drive_wrapper.cpp main.cpp)

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
