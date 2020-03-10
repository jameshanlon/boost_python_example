cmake_minimum_required(VERSION 3.12.0)
project(boost_python_example)

# Target Boost::<library> already has an imported location + link errors
# https://stackoverflow.com/questions/58081084/target-boostlibrary-already-has-an-imported-location-link-errors
set(Boost_USE_MULTITHREADED TRUE)

find_package(Python REQUIRED COMPONENTS
	     Interpreter
	     Development)
find_package(Boost 1.72.0 REQUIRED COMPONENTS
	     python)

message(STATUS "PYTHON_LIBRARIES    = ${Python_LIBRARIES}")
message(STATUS "PYTHON_EXECUTABLE   = ${Python_EXECUTABLE}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${Python_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES     = ${Boost_LIBRARIES}")

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${Boost_INCLUDE_DIR}
		    ${Python_INCLUDE_DIRS})

# The hello library
add_library(hello hello.cpp)
target_link_libraries(hello
  ${Boost_LIBRARIES})

# The hello library Python wrapper
add_library(wrapper MODULE wrapper.cpp)
target_link_libraries(wrapper
  ${Boost_LIBRARIES}
  ${Python_LIBRARIES}
  hello)
set_target_properties(wrapper PROPERTIES PREFIX "")

# Test it
file(COPY test_wrapper.py
     DESTINATION .)
add_test(NAME test_wrapper
	 COMMAND ${Python_EXECUTABLE} test_wrapper.py)
