include(FetchContent)

FetchContent_Declare(avr-libstdcpp
  GIT_REPOSITORY https://github.com/modm-io/avr-libstdcpp
  GIT_TAG        master
)
FetchContent_MakeAvailable(avr-libstdcpp)

file(GLOB_RECURSE avr-libstdcpp_SOURCES ${avr-libstdcpp_SOURCE_DIR}/src/**.cc)
add_library(avr-libstdcpp ${avr-libstdcpp_SOURCES})
target_include_directories(avr-libstdcpp PUBLIC ${avr-libstdcpp_SOURCE_DIR}/include)