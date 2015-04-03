add_library (liblogger Logger.h Logger.cpp)
target_include_directories (liblogger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (liblogger ${Boost_LIBRARIES})
