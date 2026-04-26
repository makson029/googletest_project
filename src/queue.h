#pragma once  // Защита от повторного включения заголовочного файла
#include <stdexcept>  // Для std::runtime_error — исключений при ошибках

// Шаблонный класс Queue — очередь (FIFO)
template<typename Element>
class Queue {
public:
    // Виртуальный деструктор — позволяет корректно удалять объекты через указатель на базовый класс
    virtual ~Queue() = default;

    // push — добавляет элемент в конец очереди
    // value — значение, которое нужно добавить
    virtual void push(const Element& value) = 0;

    // pop — удаляет и возвращает элемент из начала очереди
    // Должен бросать std::runtime_error, если очередь пуста
    virtual Element pop() = 0;

    // size — возвращает текущее количество элементов в очереди
    virtual size_t size() const = 0;

    // empty — возвращает true, если очередь пуста
    virtual bool empty() const = 0;

    // front — возвращает первый элемент БЕЗ удаления
    // Должен бросать std::runtime_error, если очередь пуста
    virtual Element front() const = 0;
};