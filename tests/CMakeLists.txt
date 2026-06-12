find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Sql Core)

add_executable(voyager_tests
    tst_voyage.cpp
)
target_link_libraries(voyager_tests PRIVATE
    voyager_core
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Core
)

add_test(NAME voyager_tests COMMAND voyager_tests)
# Headless: run the GUI-less test binary on the offscreen platform.
set_tests_properties(voyager_tests PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
