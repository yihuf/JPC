include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/poco/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../third/openssl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

aux_source_directory(. DIR_SRCS)
add_library(main OBJECT ${DIR_SRCS})