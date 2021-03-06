cmake_minimum_required(VERSION 2.8)

project(jpc)

message(${PROJECT_SOURCE_DIR})
message("you are building a ${CMAKE_BUILD_TYPE} version")

set(CMAKE_CXX_FLAGS  -std=c++11)

add_definitions(-D__HELP__)


include_directories(
    ${PROJECT_SOURCE_DIR}/../third/poco/include
    ${PROJECT_SOURCE_DIR}/../third/openssl/include
    ${PROJECT_SOURCE_DIR}/include/
)

add_subdirectory(source)

link_directories(
    ${PROJECT_SOURCE_DIR}/../third/poco/lib64
    ${PROJECT_SOURCE_DIR}/../third/openssl/lib64
)

add_executable(http_server
    $<TARGET_OBJECTS:http>
    $<TARGET_OBJECTS:main> 
)

target_link_libraries(http_server
    crypto
    ssl
    PocoJSON
    PocoFoundation
    PocoNet
    PocoUtil
    PocoXML
)

