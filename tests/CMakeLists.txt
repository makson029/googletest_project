# Создаём исполняемый файл для тестов, объединяя все тестовые файлы
add_executable(
  all_tests                    # Имя исполняемого файла с тестами
  test_queue.cpp               # Тесты для очереди
  test_heap.cpp                # Тесты для кучи
  test_binary_tree.cpp         # Тесты для бинарного дерева
)

# Указываем пути к заголовочным файлам проекта (папка src)
target_include_directories(all_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Линкуем наш тестовый файл с библиотеками GoogleTest
# gtest_main — содержит функцию main(), запускающую все тесты
target_link_libraries(
  all_tests
  gtest_main  # Основная библиотека GoogleTest со встроенной функцией main
)

# Регистрируем тесты в системе CMake (позволяет запускать через ctest)
include(GoogleTest)
gtest_discover_tests(all_tests)