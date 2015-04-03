add_executable (word_brain_solver main.cpp)
target_link_libraries (word_brain_solver LINK_PUBLIC libtimer libreader libdictionary libboard)
target_link_libraries (word_brain_solver LINK_PUBLIC ${Boost_LIBRARIES})
