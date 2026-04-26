#include <gtest/gtest.h>  // Подключаем GoogleTest
#include "queue.h"        // Подключаем интерфейс нашей очереди
#include <stdexcept>      // Для std::runtime_error

// ─── Мок-реализация очереди для тестирования ───────────────────────────────
// Так как Queue — абстрактный класс, создаём простую реализацию через std::queue
#include <queue>  // Стандартная очередь из STL для мок-реализации

// MockQueue — тестовая реализация интерфейса Queue на базе std::queue
template<typename Element>
class MockQueue : public Queue<Element> {
private:
    std::queue<Element> data;  // Внутреннее хранилище — стандартная очередь STL
public:
    // Реализация push: добавляем элемент в конец очереди
    void push(const Element& value) override {
        data.push(value);  // Делегируем в std::queue
    }

    // Реализация pop: удаляем и возвращаем первый элемент
    Element pop() override {
        if (data.empty())  // Проверяем, не пуста ли очередь
            throw std::runtime_error("Queue is empty");  // Бросаем исключение
        Element val = data.front();  // Сохраняем первый элемент
        data.pop();            // Удаляем его из очереди
        return val;            // Возвращаем сохранённое значение
    }

    // Реализация size: возвращаем количество элементов
    size_t size() const override { return data.size(); }

    // Реализация empty: возвращаем true если очередь пуста
    bool empty() const override { return data.empty(); }

    // Реализация front: возвращаем первый элемент без удаления
    Element front() const override {
        if (data.empty())  // Проверяем, не пуста ли очередь
            throw std::runtime_error("Queue is empty");
        return data.front();  // Возвращаем первый элемент
    }
};

// ─── Тесты для Queue ────────────────────────────────────────────────────────

// Тест 1: Новая очередь должна быть пустой
TEST(QueueTest, IsEmptyOnCreation) {
    MockQueue<int> queue;          // Создаём пустую очередь целых чисел
    EXPECT_TRUE(queue.empty());    // Ожидаем, что очередь пуста
    EXPECT_EQ(queue.size(), 0u);   // Ожидаем, что размер равен 0
}

// Тест 2: После одного push очередь не должна быть пустой
TEST(QueueTest, PushMakesQueueNonEmpty) {
    MockQueue<int> queue;          // Создаём пустую очередь
    queue.push(42);                // Добавляем элемент 42
    EXPECT_FALSE(queue.empty());   // Ожидаем, что очередь НЕ пуста
    EXPECT_EQ(queue.size(), 1u);   // Ожидаем размер 1
}

// Тест 3: push нескольких элементов — размер должен увеличиваться
TEST(QueueTest, PushIncreasesSize) {
    MockQueue<int> queue;
    queue.push(1);                 // Добавляем 1
    queue.push(2);                 // Добавляем 2
    queue.push(3);                 // Добавляем 3
    EXPECT_EQ(queue.size(), 3u);   // Ожидаем размер 3
}

// Тест 4: pop должен возвращать элементы в порядке FIFO
TEST(QueueTest, PopReturnsFIFOOrder) {
    MockQueue<int> queue;
    queue.push(10);                // Добавляем 10 первым
    queue.push(20);                // Добавляем 20 вторым
    queue.push(30);                // Добавляем 30 третьим
    EXPECT_EQ(queue.pop(), 10);    // Первым должен выйти 10
    EXPECT_EQ(queue.pop(), 20);    // Вторым — 20
    EXPECT_EQ(queue.pop(), 30);    // Третьим — 30
}

// Тест 5: pop уменьшает размер очереди
TEST(QueueTest, PopDecreasesSize) {
    MockQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.pop();                   // Удаляем один элемент
    EXPECT_EQ(queue.size(), 1u);   // Ожидаем, что осталось 1 элемент
}

// Тест 6: pop из пустой очереди должен бросать исключение
TEST(QueueTest, PopFromEmptyThrows) {
    MockQueue<int> queue;
    // EXPECT_THROW проверяет, что выражение бросает указанный тип исключения
    EXPECT_THROW(queue.pop(), std::runtime_error);
}

// Тест 7: front возвращает первый элемент без удаления
TEST(QueueTest, FrontReturnsFirstWithoutRemoving) {
    MockQueue<int> queue;
    queue.push(100);
    queue.push(200);
    EXPECT_EQ(queue.front(), 100); // Первый элемент — 100
    EXPECT_EQ(queue.size(), 2u);   // Размер не изменился
}

// Тест 8: front на пустой очереди должен бросать исключение
TEST(QueueTest, FrontOnEmptyThrows) {
    MockQueue<int> queue;
    EXPECT_THROW(queue.front(), std::runtime_error);
}

// Тест 9: после pop всех элементов очередь снова пуста
TEST(QueueTest, EmptyAfterPoppingAll) {
    MockQueue<int> queue;
    queue.push(5);
    queue.pop();
    EXPECT_TRUE(queue.empty());    // Очередь должна снова быть пустой
}

// Тест 10: работа со строками (проверяем шаблонность)
TEST(QueueTest, WorksWithStrings) {
    MockQueue<std::string> queue;
    queue.push("hello");           // Добавляем строку
    queue.push("world");
    EXPECT_EQ(queue.pop(), "hello"); // Ожидаем FIFO-порядок
}