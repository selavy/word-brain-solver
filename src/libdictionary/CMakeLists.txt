add_library(libdictionary Dictionary.h UnixDictionary.cpp UnixDictionary.h Trie.h TrieUnixDictionary.cpp TrieUnixDictionary.h)

target_include_directories(libdictionary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (libdictionary LINK_PUBLIC liblogger libtimer)
