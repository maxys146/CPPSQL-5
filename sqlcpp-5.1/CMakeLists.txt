# CMakeList.txt: проект CMake для sqlcpp-5.1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(PostgreSQL_ADDITIONAL_VERSIONS "15")

add_executable (sqlcpp-5.1 "sqlcpp-5.1.cpp" "sqlcpp-5.1.h")

add_subdirectory(C:/Users/maxys/source/repos/libpqxx-7.7.4 libpqxx-build)

#target_compile_features(sqlcpp-5.1 PRIVATE cxx_std_17)
target_link_libraries(sqlcpp-5.1 pqxx)        

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sqlcpp-5.1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
