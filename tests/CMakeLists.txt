function(ConfigureTest CMAKE_TEST_NAME)
  ADD_EXECUTABLE(${CMAKE_TEST_NAME} ${ARGN} ${FLEX_ScannerTarget_OUTPUTS})
  TARGET_LINK_LIBRARIES(${CMAKE_TEST_NAME} compilers ${DEPS} ${FLEX_LIBRARIES} gtest)
  ADD_TEST(NAME ${CMAKE_TEST_NAME} COMMAND ${CMAKE_TEST_NAME})
endfunction()

# https://cmake.org/cmake/help/latest/module/FindFLEX.html
FIND_PACKAGE(FLEX REQUIRED)

IF(FLEX_FOUND)
  FLEX_TARGET(ScannerTarget
    ${PROJECT_SOURCE_DIR}/compilers/scanner.l
    ${PROJECT_SOURCE_DIR}/compilers/scanner.cpp
  )
ENDIF()

INCLUDE_DIRECTORIES(../compilers)

ConfigureTest(validation_test
  validation_test.cpp
)
