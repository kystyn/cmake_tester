# CMakeList.txt : CMake project for TestEnvironment, include source and define
# project specific logic here.
# see https://habr.com/ru/post/433822/
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
#add_executable (TestEnvironment "TestEnvironment.cpp" "TestEnvironment.h")

# here will be set(STUDPROJNAME ...)

set(STUDADDR "../../../student/build/${STUDPROJNAME}")

# TODO: Add tests and install targets if needed.

# toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE top left bottom right

enable_testing()
SET (TestEnvironment_TIMEOUT 100)
add_test(Trivial_Run ${PROJECT_NAME} ../config.txt ../ex.png ref.png ${STUDADDR} stud.png)
add_test(Trivial_Red1 ${PROJECT_NAME} Red ref.png stud.png 10 30 2 0 1 1)
add_test(Normal_Red2  ${PROJECT_NAME} Red ref.png stud.png 1 3 2 0 1 1)
add_test(Normal_Threshold1 ${PROJECT_NAME} Threshold ref.png stud.png 6000 0.15 0 0 2 2)
add_test(Hard_Threshold2   ${PROJECT_NAME} Threshold ref.png stud.png  500 0.01 0 0 2 2)

# Установить поведение тестов:

#Run
set_tests_properties(Trivial_Run
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})
set_tests_properties(Trivial_Run PROPERTIES
PASS_REGULAR_EXPRESSION "OK")

#Red
set_tests_properties(Trivial_Red1
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})

set_tests_properties(Normal_Red2
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})

set_tests_properties(Trivial_Red1 PROPERTIES
PASS_REGULAR_EXPRESSION "OK OK"
FAIL_REGULAR_EXPRESSION "BAD: Too many bad pixels: [d]{1,}")

set_tests_properties(Normal_Red2 PROPERTIES
PASS_REGULAR_EXPRESSION "OK OK"
FAIL_REGULAR_EXPRESSION "BAD:Too many bad pixels: [d]{1,}")

#Threshold
set_tests_properties(Normal_Threshold1
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})

set_tests_properties(Hard_Threshold2
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})

set_tests_properties(Normal_Threshold1 PROPERTIES
PASS_REGULAR_EXPRESSION "OK OK"
FAIL_REGULAR_EXPRESSION "BAD: Too many bad pixels: [d]{1,}")

set_tests_properties(Hard_Threshold2 PROPERTIES
PASS_REGULAR_EXPRESSION "OK OK"
FAIL_REGULAR_EXPRESSION "BAD:Too many bad pixels: [d]{1,}")
