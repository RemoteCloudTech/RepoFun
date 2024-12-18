cmake_minimum_required(VERSION 3.10)

# Project name
project(MidiReader)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(MidiReader realtimeMIDI.cpp)

# Specify the path to the RtMidi library
set(RTMIDI_DIR "C:/Users/Remot/Documents/github/rtmidi")
set(RTMIDI_OUTDIR ${RTMIDI_DIR}/out/build/x64-Debug/)

# Include directories
include_directories(MidiReader ${RTMIDI_DIR})

# Link directories
link_directories(MidiReader ${RTMIDI_OUTDIR})

# Link the RtMidi library
target_link_libraries(MidiReader ${RTMIDI_OUTDIR}rtmidi.lib)

# Copy the RtMidi DLL to the output directory
add_custom_command(TARGET MidiReader POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${RTMIDI_OUTDIR}rtmidi.dll $<TARGET_FILE_DIR:MidiReader>
)
