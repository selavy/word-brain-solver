add_library (libboard Board.cpp Board.h Tile.cpp Tile.h)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (libboard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
