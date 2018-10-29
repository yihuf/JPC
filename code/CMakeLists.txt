cmake_minimum_required(VERSION 2.8)

project(jpc)

add_subdirectory(source)

add_executable(http_server
    $<TARGET_NAME:http>
    $<TARGET_NAME:main> 
)


)

#target_link_libraries(
#    http
#    main
#    )