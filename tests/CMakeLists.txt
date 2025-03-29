# Add unit tests
file(GLOB UNIT_TESTS unit/*.cpp)
file(GLOB PERF_TESTS utils/*.cpp)

foreach(test_file ${UNIT_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_include_directories(${test_name} PRIVATE ../src)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

foreach(test_file ${PERF_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_include_directories(${test_name} PRIVATE ../src)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
