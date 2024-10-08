# This top-level micropython.cmake is responsible for listing
# the individual modules we want to include.
# Paths are absolute, and ${CMAKE_CURRENT_LIST_DIR} can be
# used to prefix subdirectories.

# Add the C example.
include(${CMAKE_CURRENT_LIST_DIR}/cexample/micropython.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/led/micropython.cmake)
# include(${CMAKE_CURRENT_LIST_DIR}/ssd1306/micropython.cmake)
