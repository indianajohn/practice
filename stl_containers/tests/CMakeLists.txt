function(prepare_test test_name source_file)
  add_executable(${test_name} ${source_file})
  target_link_libraries(${test_name} stl_containers)
  add_test(${test_name} ${test_name})
endfunction()

prepare_test(framework test_framework.cpp)
