cmake_minimum_required(VERSION 2.8)

project(jpc)

add_subdirectory(source)

add_executable(http_server
    $<TARGET_OBJECTS:http>
    $<TARGET_OBJECTS:main> 
)

message(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/poco/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/openssl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries(
    PocoJSON
    PocoJSONd
    PocoFoundation
    PocoFoundationd
    PocoNet
    PocoNetd
    PocoUtil
    PocoUtild
)