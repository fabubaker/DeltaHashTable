include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Add test targets
add_executable(bucket_tests bucket_tests.cpp)
target_include_directories(bucket_tests PRIVATE ../src)
target_link_libraries(bucket_tests PRIVATE GTest::gtest_main $<TARGET_OBJECTS:bucket>)
gtest_discover_tests(bucket_tests)

add_executable(entries_tests entries_tests.cpp)
target_include_directories(entries_tests PRIVATE ../src)
target_link_libraries(entries_tests PRIVATE GTest::gtest_main $<TARGET_OBJECTS:bucket>)
gtest_discover_tests(entries_tests)

add_executable(lslots_tests lslots_tests.cpp)
target_include_directories(lslots_tests PRIVATE ../src)
target_link_libraries(lslots_tests PRIVATE GTest::gtest_main $<TARGET_OBJECTS:bucket>)
gtest_discover_tests(lslots_tests)

add_executable(bitvector_tests bitvector_tests.cpp)
target_include_directories(bitvector_tests PRIVATE ../src)
target_link_libraries(bitvector_tests PRIVATE GTest::gtest_main $<TARGET_OBJECTS:bucket>)
gtest_discover_tests(bitvector_tests)
