# C++ Unit Testing с GoogleTest

Проект на языке **C++** с настроенным модульным тестированием на основе фреймворка **GoogleTest** и системы сборки **CMake**.

---

## О проекте

Проект демонстрирует, как подключить и использовать **GoogleTest** для написания unit-тестов в C++ приложении. Фреймворк автоматически загружается и собирается с помощью модуля `FetchContent` в CMake — никаких ручных установок не требуется.

---

## Требования

- **CMake** версии `3.14` и выше
- **Компилятор:** GCC, MinGW или MSVC
- **Git** (для клонирования и загрузки зависимостей)
- **VS Code** *(опционально, настройки уже включены)*

---

## Установка и запуск

**1. Клонируй репозиторий:**
```bash
git clone https://github.com/makson029/googletest_project.git
cd googletest_project
```

**2. Создай папку сборки:**
```bash
mkdir build
cd build
```

**3. Сгенерируй проект через CMake:**
```bash
cmake ..
```

**4. Собери проект:**
```bash
cmake --build .
```

**5. Запусти тесты:**
```bash
ctest --output-on-failure
    или
cmake --build . --target test
```

## Демонстрация процесса

[![asciicast](https://asciinema.org/a/yFnqpVP5jbg76Lje.svg)](https://asciinema.org/a/yFnqpVP5jbg76Lje)

## Структура проекта

```CMake
googletest_project/
├──.vscode                # Настройки VS Code
├── src/                  # Исходный код приложения
│   └── binary_tree.h
│   └── heap.h
│   └── queue.h
├── tests/                # Файлы с тестами
│   └── test_binary_tree.cpp
│   └── test_heap.cpp
│   └── test_queue.cpp
└── CMakeLists.txt        # Конфигурация CMake
```

## Как добавить новый тест
1. Создай новый файл в папке tests/, например my_test.cpp
2. Напиши тесты, используя макросы GoogleTest (TEST, EXPECT_EQ, ASSERT_TRUE и т.д.). Например:
```C++
    #include &lt;gtest gtest.h&gt;

    int Add(int a, int b) { return a + b; }

    TEST(MathTest, AddPositiveNumbers) {
        EXPECT_EQ(Add(2, 3), 5);
    }

    TEST(MathTest, AddNegativeNumbers) {
        EPECT_EQ(Add(5, 5), 10);
    }
```
3. Добавьте линк на ваш файл в tests/CMakeLists.txt 
```CMake
    add_executable(
        ...
        my_test.cpp                  # Мои тесты
    )
```
4. Пересобери проект:
```Bash
    cmake --build .
```
5. Запустите теcт
```Bash
    ctest --output-on-failure
        или
    cmake --build . --target test
```