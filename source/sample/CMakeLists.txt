
set(Clue_Sample_SOURCES
	Sample.cpp
	Sample.rdef
	)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

haiku_add_executable(SampleApp ${Clue_Sample_SOURCES})

target_link_libraries(SampleApp "be" "tracker" "translation" "stdc++" "clue")
