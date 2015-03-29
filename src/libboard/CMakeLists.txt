add_library (libboard Board.cpp Board.h Tile.cpp Tile.h)

target_include_directories (libboard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
