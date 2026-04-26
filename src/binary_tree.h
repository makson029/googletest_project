#pragma once  // Защита от повторного включения заголовочного файла
#include <stdexcept>  // Для std::runtime_error

// Шаблонный класс BinaryTree — бинарное дерево поиска (BST)
// Свойство BST: левый потомок < узел < правый потомок
template<typename Element>
class BinaryTree {
public:
    // Виртуальный деструктор для безопасного наследования
    virtual ~BinaryTree() = default;

    // push — вставляет новый элемент в дерево с сохранением свойства BST
    // value — вставляемое значение
    virtual void push(const Element& value) = 0;

    // pop — удаляет элемент из дерева
    // value — значение, которое нужно удалить
    // Должен бросать std::runtime_error, если элемент не найден
    virtual void pop(const Element& value) = 0;

    // search — ищет элемент в дереве
    // value — искомое значение
    // Возвращает true, если элемент найден, иначе false
    virtual bool search(const Element& value) const = 0;

    // size — возвращает количество узлов в дереве
    virtual size_t size() const = 0;

    // empty — возвращает true, если дерево пусто
    virtual bool empty() const = 0;
};