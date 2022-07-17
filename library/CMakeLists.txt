add_library(
  network_lib
  STATIC
  include/lib/request_header.hpp
  include/lib/request.hpp
  include/lib/response.hpp
  include/lib/response_header.hpp
  include/lib/port.hpp
  include/lib/socket_read.hpp
  src/lib/request_header.cpp
  src/lib/request.cpp 
  src/lib/response.cpp 
  src/lib/response_header.cpp 
  src/lib/socket_read.cpp)

target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(network_lib PUBLIC NOMINMAX)

target_link_libraries(network_lib PUBLIC Poco::Net CppPhil::philslib)
