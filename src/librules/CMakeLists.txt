add_library (librules Rules.cpp Rules.h)

target_include_directories (librules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (librules LINK_PUBLIC libboard liblogger libtimer libdictionary)
