include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/poco/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/openssl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

add_subdirectory(http)
add_subdirectory(main)