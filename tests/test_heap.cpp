#include <gtest/gtest.h>  // Подключаем GoogleTest
#include "heap.h"         // Подключаем интерфейс нашей кучи
#include <stdexcept>      // Для std::runtime_error
#include <vector>         // Для хранения данных кучи
#include <algorithm>      // Для std::make_heap, push_heap, pop_heap

// ─── Мок-реализация кучи для тестирования ──────────────────────────────────

// MockHeap — тестовая реализация Max-Heap (наибольший элемент)
template<typename Element>
class MockHeap : public Heap<Element> {
private:
    std::vector<Element> data;  // Вектор для хранения элементов кучи
public:
    // Реализация push: добавляем элемент и восстанавливаем свойство кучи
    void push(const Element& value) override {
        data.push_back(value);                // Добавляем в конец вектора
        std::push_heap(data.begin(), data.end()); // Восстанавливаем heap-свойство
    }

    // Реализация pop: удаляем наибольший элемент
    Element pop() override {
        if (data.empty())
            throw std::runtime_error("Heap is empty");
        std::pop_heap(data.begin(), data.end()); // Перемещаем максимум в конец
        Element val = data.back();  // Сохраняем максимальный элемент
        data.pop_back();      // Удаляем его из вектора
        return val;           // Возвращаем
    }

    // Реализация top: возвращаем наибольший элемент кучи без удаления
    Element top() const override {
        if (data.empty())
            throw std::runtime_error("Heap is empty");
        return data.front();  // В max-heap максимум всегда на позиции [0]
    }

    // Реализация size: количество элементов
    size_t size() const override { return data.size(); }

    // Реализация empty: пуста ли куча
    bool empty() const override { return data.empty(); }
};

// ─── Тесты для Heap ─────────────────────────────────────────────────────────

// Тест 1: Новая куча пуста
TEST(HeapTest, IsEmptyOnCreation) {
    MockHeap<int> heap;
    EXPECT_TRUE(heap.empty());   // Ожидаем пустую кучу
    EXPECT_EQ(heap.size(), 0u);  // Размер равен 0
}

// Тест 2: После push куча не пуста
TEST(HeapTest, PushMakesHeapNonEmpty) {
    MockHeap<int> heap;
    heap.push(5);
    EXPECT_FALSE(heap.empty());  // Куча не пуста
    EXPECT_EQ(heap.size(), 1u);  // Размер равен 1
}

// Тест 3: top возвращает максимальный элемент
TEST(HeapTest, TopReturnsMaxElement) {
    MockHeap<int> heap;
    heap.push(3);   // Добавляем 3
    heap.push(10);  // Добавляем 10 — теперь это наибольший элемент
    heap.push(1);   // Добавляем 1
    EXPECT_EQ(heap.top(), 10);  // Ожидаем наибольший элемент
}

// Тест 4: pop возвращает наибольший элемент
TEST(HeapTest, PopReturnsMaxElement) {
    MockHeap<int> heap;
    heap.push(7);
    heap.push(2);
    heap.push(15);  // Максимум
    EXPECT_EQ(heap.pop(), 15);  // pop должен вернуть 15
}

// Тест 5: После pop наибольший элемент становится следующий по величине элемент
TEST(HeapTest, AfterPopNewMaxIsOnTop) {
    MockHeap<int> heap;
    heap.push(5);
    heap.push(20);  // Максимум
    heap.push(10);
    heap.pop();     // Удаляем 20
    EXPECT_EQ(heap.top(), 10);  // Теперь наибольший элемент — 10
}

// Тест 6: pop уменьшает размер кучи
TEST(HeapTest, PopDecreasesSize) {
    MockHeap<int> heap;
    heap.push(1);
    heap.push(2);
    heap.pop();
    EXPECT_EQ(heap.size(), 1u);  // Остался 1 элемент
}

// Тест 7: pop из пустой кучи бросает исключение
TEST(HeapTest, PopFromEmptyThrows) {
    MockHeap<int> heap;
    EXPECT_THROW(heap.pop(), std::runtime_error);
}

// Тест 8: top на пустой куче бросает исключение
TEST(HeapTest, TopOnEmptyThrows) {
    MockHeap<int> heap;
    EXPECT_THROW(heap.top(), std::runtime_error);
}

// Тест 9: Несколько pop подряд возвращают элементы в убывающем порядке
TEST(HeapTest, MultiplePopReturnsDescendingOrder) {
    MockHeap<int> heap;
    heap.push(4);
    heap.push(8);
    heap.push(2);
    heap.push(6);
    EXPECT_EQ(heap.pop(), 8);  // Сначала наибольший
    EXPECT_EQ(heap.pop(), 6);
    EXPECT_EQ(heap.pop(), 4);
    EXPECT_EQ(heap.pop(), 2);  // В конце наименьший
}

// Тест 10: top не удаляет элемент (размер не меняется)
TEST(HeapTest, TopDoesNotChangeSize) {
    MockHeap<int> heap;
    heap.push(42);
    heap.top();               // Вызываем top
    EXPECT_EQ(heap.size(), 1u); // Размер всё ещё 1
}