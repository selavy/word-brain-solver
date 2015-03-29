add_library(libdictionary Dictionary.h Dictionary.cpp UnixDictionary.cpp UnixDictionary.h)

target_include_directories(libdictionary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
