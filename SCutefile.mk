project SortVisualizer
compile cxx g++
compile cxxflags -std=c++11 -mwindows -Wall
compile cxxlibs graphics64 gdiplus64 imm32 msimg32 ole32 oleaut32 winmm uuid
compile c gcc

SortVisualizer.path build
SortVisualizer {
	src/DataLine.cpp
	src/SortVisualizer.cpp
	src/SortView.cpp
}
