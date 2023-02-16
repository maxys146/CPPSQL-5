# CMakeList.txt: проект CMake для sqlcpp-5.1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (sqlcpp-5.1 "sqlcpp-5.1.cpp" "sqlcpp-5.1.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sqlcpp-5.1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
