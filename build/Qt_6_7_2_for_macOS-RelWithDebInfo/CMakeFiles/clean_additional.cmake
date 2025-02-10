# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles/New_dash_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/New_dash_autogen.dir/ParseCache.txt"
  "New_dash_autogen"
  )
endif()
