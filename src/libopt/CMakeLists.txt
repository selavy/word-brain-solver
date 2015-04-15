add_library (libopt Opt.h Opt.cpp)
target_include_directories (libopt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (libopt LINK_PUBLIC ${Boost_LIBRARIES})
