# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TICTACTOE_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TICTACTOE_autogen.dir\\ParseCache.txt"
  "TICTACTOE_autogen"
  )
endif()
