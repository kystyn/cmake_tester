# CMakeList.txt : CMake project for TestEnvironment, include source and define
# project specific logic here.
# see https://habr.com/ru/post/433822/
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
#add_executable (TestEnvironment "TestEnvironment.cpp" "TestEnvironment.h")

# here will be set(STUDPROJNAME ...)

set(STUDADDR "../../../student/build/${STUDPROJNAME}")

# TODO: Add tests and install targets if needed.
# Добавить тесты:

enable_testing()
SET (TestEnvironment_TIMEOUT 100)
add_test(Trivial_FirstTest ${PROJECT_NAME} Red ../ex1.png ${STUDADDR} res.png 10 30 2 0 1 1)
add_test(Normal_SecondTest ${PROJECT_NAME} Red ../ex1.png ${STUDADDR} res.png 1 3 2 0 1 1)

# Установить поведение тестов:
set_tests_properties(Trivial_FirstTest
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})

set_tests_properties(Trivial_FirstTest PROPERTIES
PASS_REGULAR_EXPRESSION "OK OK"
FAIL_REGULAR_EXPRESSION "BAD: Too many bad pixels: [d]{1,}")

set_tests_properties(Normal_SecondTest PROPERTIES
PASS_REGULAR_EXPRESSION "OK OK"
FAIL_REGULAR_EXPRESSION "BAD:Too many bad pixels: [d]{1,}")
