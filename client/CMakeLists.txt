add_executable(client main.cpp)

target_link_libraries(client PRIVATE network_lib fmt::fmt)
