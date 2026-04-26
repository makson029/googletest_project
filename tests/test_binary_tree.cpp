#include <gtest/gtest.h>   // Подключаем GoogleTest
#include "binary_tree.h"   // Подключаем интерфейс бинарного дерева
#include <stdexcept>       // Для std::runtime_error
#include <memory>          // Для std::unique_ptr (умные указатели)

// ─── Мок-реализация бинарного дерева поиска ────────────────────────────────

template<typename Element>
class MockBinaryTree : public BinaryTree<Element> {
private:
    // Структура узла дерева
    struct Node {
        Element value;                        // Значение узла
        std::unique_ptr<Node> left;     // Левый потомок (умный указатель)
        std::unique_ptr<Node> right;    // Правый потомок (умный указатель)

        // Конструктор узла
        explicit Node(const Element& val) : value(val), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;  // Корень дерева
    size_t count = 0;            // Счётчик количества узлов

    // Вспомогательная рекурсивная функция вставки
    void insertNode(std::unique_ptr<Node>& node, const Element& value) {
        if (!node) {  // Если узел пуст — создаём новый
            node = std::make_unique<Node>(value);
            ++count;  // Увеличиваем счётчик
        } else if (value < node->value) {  // Идём влево, если меньше
            insertNode(node->left, value);
        } else if (value > node->value) {  // Идём вправо, если больше
            insertNode(node->right, value);
        }
        // Если равно — дубликаты не добавляем
    }

    // Вспомогательная рекурсивная функция поиска
    bool searchNode(const Node* node, const Element& value) const {
        if (!node) return false;           // Не нашли
        if (value == node->value) return true; // Нашли
        if (value < node->value)               // Идём влево
            return searchNode(node->left.get(), value);
        return searchNode(node->right.get(), value); // Идём вправо
    }

    // Находит минимальный узел в поддереве (для удаления)
    Node* findMin(Node* node) const {
        while (node->left) node = node->left.get();
        return node;
    }

    // Вспомогательная рекурсивная функция удаления
    bool deleteNode(std::unique_ptr<Node>& node, const Element& value) {
        if (!node) return false;  // Элемент не найден

        if (value < node->value) {
            return deleteNode(node->left, value);   // Ищем в левом поддереве
        } else if (value > node->value) {
            return deleteNode(node->right, value);  // Ищем в правом поддереве
        } else {
            // Нашли удаляемый узел
            if (!node->left) {
                // Нет левого потомка — заменяем правым
                node = std::move(node->right);
            } else if (!node->right) {
                // Нет правого потомка — заменяем левым
                node = std::move(node->left);
            } else {
                // Есть оба потомка: находим минимум правого поддерева
                Node* minNode = findMin(node->right.get());
                node->value = minNode->value;  // Копируем значение
                deleteNode(node->right, minNode->value);  // Удаляем минимум
                return true;  // Счётчик уже уменьшится рекурсивно
            }
            --count;  // Уменьшаем счётчик
            return true;
        }
    }

public:
    // Публичная функция вставки
    void push(const Element& value) override {
        insertNode(root, value);
    }

    // Публичная функция удаления
    void pop(const Element& value) override {
        if (!deleteNode(root, value))
            throw std::runtime_error("Element not found");
    }

    // Публичная функция поиска
    bool search(const Element& value) const override {
        return searchNode(root.get(), value);
    }

    // Размер дерева
    size_t size() const override { return count; }

    // Проверка на пустоту
    bool empty() const override { return count == 0; }
};

// ─── Тесты для BinaryTree ───────────────────────────────────────────────────

// Тест 1: Новое дерево пустое
TEST(BinaryTreeTest, IsEmptyOnCreation) {
    MockBinaryTree<int> tree;
    EXPECT_TRUE(tree.empty());   // Дерево пусто
    EXPECT_EQ(tree.size(), 0u);  // Размер 0
}

// Тест 2: После push дерево не пустое
TEST(BinaryTreeTest, PushMakesTreeNonEmpty) {
    MockBinaryTree<int> tree;
    tree.push(10);
    EXPECT_FALSE(tree.empty()); // Дерево не пусто
    EXPECT_EQ(tree.size(), 1u); // Размер 1
}

// Тест 3: search находит добавленный элемент
TEST(BinaryTreeTest, SearchFindsExistingElement) {
    MockBinaryTree<int> tree;
    tree.push(5);
    tree.push(3);
    tree.push(7);
    EXPECT_TRUE(tree.search(5));  // Корень
    EXPECT_TRUE(tree.search(3));  // Левый потомок
    EXPECT_TRUE(tree.search(7));  // Правый потомок
}

// Тест 4: search возвращает false для отсутствующего элемента
TEST(BinaryTreeTest, SearchReturnsFalseForMissing) {
    MockBinaryTree<int> tree;
    tree.push(10);
    EXPECT_FALSE(tree.search(99));  // 99 не добавляли
}

// Тест 5: search на пустом дереве возвращает false
TEST(BinaryTreeTest, SearchOnEmptyReturnsFalse) {
    MockBinaryTree<int> tree;
    EXPECT_FALSE(tree.search(1));  // Дерево пусто
}

// Тест 6: pop удаляет элемент
TEST(BinaryTreeTest, PopRemovesElement) {
    MockBinaryTree<int> tree;
    tree.push(10);
    tree.push(5);
    tree.pop(5);               // Удаляем 5
    EXPECT_FALSE(tree.search(5)); // 5 больше не должен находиться
}

// Тест 7: pop уменьшает размер дерева
TEST(BinaryTreeTest, PopDecreasesSize) {
    MockBinaryTree<int> tree;
    tree.push(10);
    tree.push(20);
    tree.pop(20);
    EXPECT_EQ(tree.size(), 1u);  // Остался 1 элемент
}

// Тест 8: pop несуществующего элемента бросает исключение
TEST(BinaryTreeTest, PopNonExistentThrows) {
    MockBinaryTree<int> tree;
    tree.push(10);
    EXPECT_THROW(tree.pop(99), std::runtime_error);
}

// Тест 9: pop из пустого дерева бросает исключение
TEST(BinaryTreeTest, PopFromEmptyThrows) {
    MockBinaryTree<int> tree;
    EXPECT_THROW(tree.pop(1), std::runtime_error);
}

// Тест 10: Дубликаты не добавляются
TEST(BinaryTreeTest, DuplicatesNotInserted) {
    MockBinaryTree<int> tree;
    tree.push(10);
    tree.push(10);  // Дубликат
    EXPECT_EQ(tree.size(), 1u);  // Размер всё равно 1
}

// Тест 11: pop корневого узла (у него есть оба потомка)
TEST(BinaryTreeTest, PopRootWithTwoChildren) {
    MockBinaryTree<int> tree;
    tree.push(10);  // Корень
    tree.push(5);   // Левый потомок
    tree.push(15);  // Правый потомок
    tree.pop(10);   // Удаляем корень
    EXPECT_FALSE(tree.search(10)); // Корень удалён
    EXPECT_TRUE(tree.search(5));   // Левый потомок остался
    EXPECT_TRUE(tree.search(15));  // Правый потомок остался
}

// Тест 12: Последовательные операции push и pop
TEST(BinaryTreeTest, PushAndPopSequence) {
    MockBinaryTree<int> tree;
    tree.push(50);
    tree.push(30);
    tree.push(70);
    tree.push(20);
    tree.pop(30);              // Удаляем узел с одним потомком
    EXPECT_EQ(tree.size(), 3u);
    EXPECT_FALSE(tree.search(30));
    EXPECT_TRUE(tree.search(20));
}