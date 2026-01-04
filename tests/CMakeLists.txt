add_executable(unit_tests
    test_employee.cpp
    test_fileutils.cpp
    test_process.cpp
)

target_link_libraries(unit_tests
    PRIVATE
        MyLib
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)