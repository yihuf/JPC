cmake_minimum_required(VERSION 2.8)

project(jpc)

add_subdirectory(source)

message(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/poco/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/openssl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/poco/lib64
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/openssl/lib64
)

add_executable(http_server
    $<TARGET_OBJECTS:http>
    $<TARGET_OBJECTS:main> 
)

target_link_libraries(http_server
    crypto
    ssl
    PocoJSON
    PocoJSONd
    PocoFoundation
    PocoFoundationd
    PocoNet
    PocoNetd
    PocoUtil
    PocoUtild
)

