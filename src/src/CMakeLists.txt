include_directories (${CALENDAR_SOURCE_DIR}/include)
link_directories (${CALENDAR_SOURCE_DIR}/lib)

add_executable (calendar auth_wrapper.cpp)

target_link_libraries(calendar google_drive_api)

target_link_libraries(calendar googleapis_oauth2)
target_link_libraries(calendar googleapis_curl_http)
target_link_libraries(calendar googleapis_http)
target_link_libraries(calendar googleapis_jsoncpp)
target_link_libraries(calendar googleapis_json)
target_link_libraries(calendar googleapis_openssl_codec)
target_link_libraries(calendar googleapis_utils)
target_link_libraries(calendar googleapis_internal)

target_link_libraries(calendar curl)
target_link_libraries(calendar crypto)
target_link_libraries(calendar glog)
target_link_libraries(calendar jsoncpp)
target_link_libraries(calendar pthread)
