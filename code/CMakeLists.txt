project(jpc)

add_subdirectory(source)

add_executable(http_server)

target_link_libraries(
    http
    main
    )