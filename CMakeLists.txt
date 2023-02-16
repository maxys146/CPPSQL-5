# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("CPPSQL-5")

# Включите подпроекты.
add_subdirectory ("sqlcpp-5.1")
