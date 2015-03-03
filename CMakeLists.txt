cmake_minimum_required(VERSION 3.0)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

project(yandex_contest_invoker_compat_common)

find_package(BunsanCMake CONFIG REQUIRED)

bunsan_add_shared_library(${PROJECT_NAME}
    src/empty.cpp
)
bunsan_use_bunsan_package(${PROJECT_NAME} yandex_contest_invoker yandex_contest_invoker)

bunsan_install_headers()
bunsan_install_targets(${PROJECT_NAME})
bunsan_install_project()

bunsan_include_tests()
