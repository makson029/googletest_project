# Минимальная версия CMake, необходимая для сборки проекта
cmake_minimum_required(VERSION 3.14)

# Название проекта и язык программирования
project(GoogleTestProject CXX)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)

# Подключаем FetchContent — встроенный модуль CMake для загрузки зависимостей
include(FetchContent)

# Объявляем зависимость: GoogleTest будет скачан с GitHub
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Отключаем установку GoogleTest вместе с нашим проектом (нам это не нужно)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# Фактически скачиваем и подготавливаем GoogleTest
FetchContent_MakeAvailable(googletest)

# Включаем поддержку тестирования в CMake
enable_testing()

# Подключаем подпапку tests, где лежат наши тесты
add_subdirectory(tests)