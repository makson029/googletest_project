#pragma once  // Защита от повторного включения заголовочного файла
#include <stdexcept>  // Для std::runtime_error

// Шаблонный класс Heap — двоичная куча (по умолчанию — max-heap)
// Max-heap: наибольший элемент всегда на вершине
template<typename Element>
class Heap {
public:
    // Виртуальный деструктор для безопасного наследования
    virtual ~Heap() = default;

    // push — добавляет элемент в кучу с сохранением свойства кучи
    // value — добавляемое значение
    virtual void push(const Element& value) = 0;

    // pop — удаляет и возвращает наибольший элемент (наибольший элемент кучи)
    // Должен бросать std::runtime_error, если куча пуста
    virtual Element pop() = 0;

    // top — возвращает наибольший элемент БЕЗ удаления
    // Должен бросать std::runtime_error, если куча пуста
    virtual Element top() const = 0;

    // size — возвращает количество элементов в куче
    virtual size_t size() const = 0;

    // empty — возвращает true, если куча пуста
    virtual bool empty() const = 0;
};