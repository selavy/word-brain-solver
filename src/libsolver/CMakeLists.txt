add_library (libsolver Rules.cpp Rules.h)

target_include_directories (libsolver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (libsolver LINK_PUBLIC libboard liblogger libtimer libdictionary)
