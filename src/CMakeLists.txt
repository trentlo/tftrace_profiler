add_executable (TFTProfiler main.cpp parser.cpp analyzer.cpp)

target_include_directories (TFTProfiler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

