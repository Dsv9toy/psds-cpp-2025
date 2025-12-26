#include <vector>

#include <stack>
/*
//очередь работает по принципу FIFO. 
//Нельзя `std::queue`, `std::deque`, `std::list`
// Методы определяем вне класса
//Была идея использовать algorithm, но оттуда чисто один метод нужен был, проше уж самому реализовать через цикл, а не тащить целую библиотеку
//необходима реализация в зависимости от конструктора. 
//Добавил строгости в преобразовании. запрет на неявность. explicit
*/



class Queue {
public:
    //Конструкторы
    Queue() = default;
    explicit Queue(size_t capacity);
    explicit Queue(const std::vector<int>& vec);
    Queue(std::initializer_list<int> init);
    explicit Queue(const std::stack<int>& stack);
    //Методы
    void Push(int value);
    void Clear();
    void Swap(Queue& otherQueue);
    
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    
    bool Pop();
    bool Empty() const;
    size_t Size() const;
    
    bool operator==(const Queue& otherQueue) const;
    bool operator!=(const Queue& otherQueue) const;

private:
    std::vector<int> inputDat;
    std::vector<int> outputDat;
    
    void MoveInputToOutput() {
        while (!inputDat.empty()) {
            outputDat.push_back(inputDat.back());
            inputDat.pop_back();
        }
    }
};

// Реализации конструкторов
Queue::Queue(size_t capacity) {
    inputDat.reserve(capacity / 2 + 1);
    outputDat.reserve(capacity / 2 + 1);
}

Queue::Queue(const std::vector<int>& vec) : inputDat(vec) {}

Queue::Queue(std::initializer_list<int> initList) : inputDat(initList) {}

Queue::Queue(const std::stack<int>& stack) {
    std::stack<int> temp = stack;
    // Извлекаем элементы из стека в обратном порядке
    while (!temp.empty()) {
        inputDat.insert(inputDat.begin(), temp.top());
        temp.pop();
    }
}

// Реализации методов
void Queue::Push(int value) {
    inputDat.push_back(value);
}

void Queue::Clear() {
    inputDat.clear();
    outputDat.clear();
}

void Queue::Swap(Queue& otherQueue) {
    inputDat.swap(otherQueue.inputDat);
    outputDat.swap(otherQueue.outputDat);
}

int& Queue::Front() {
    if (outputDat.empty()) {
        MoveInputToOutput();
    }
    return outputDat.back();
}

const int& Queue::Front() const {
    if (outputDat.empty()) {
        // Создаем временные копии
        std::vector<int> tempInput = inputDat;
        std::vector<int> tempOutput = outputDat;
        
        // Перекладываем элементы
        while (!tempInput.empty()) {
            tempOutput.push_back(tempInput.back());
            tempInput.pop_back();
        }

        static int returnZero = 0;
        if (!tempOutput.empty()) {
            returnZero = tempOutput.back();
        }
        return returnZero;
    }
    return outputDat.back();
}

int& Queue::Back() {
    if (!inputDat.empty()) return inputDat.back();
    if (!outputDat.empty()) return outputDat.front();

    static int returnZero = 0;
    return returnZero;
}

const int& Queue::Back() const {
    if (!inputDat.empty()) return inputDat.back();
    if (!outputDat.empty()) return outputDat.front();

    static int returnZero = 0;
    return returnZero;
}

bool Queue::Pop() {
    if (Empty()) {
        return false;
    }
    
    if (outputDat.empty()) {
        MoveInputToOutput();
    }
    
    outputDat.pop_back();
    return true;
}

bool Queue::Empty() const {
    return inputDat.empty() && outputDat.empty();
}

size_t Queue::Size() const {
    return inputDat.size() + outputDat.size();
}

bool Queue::operator==(const Queue& otherQueue) const {
    if (Size() != otherQueue.Size()) return false;
    if (Empty()) return true;

//Для одной очереди
    std::vector<int> temp1;

    if (!outputDat.empty()) {
        for (size_t i = outputDat.size(); i > 0; --i) {
            temp1.push_back(outputDat[i - 1]);
        }
    }
    for (size_t i = 0; i < inputDat.size(); ++i) {
        temp1.push_back(inputDat[i]);
    }

//Для второй очереди
    std::vector<int> temp2;
    if (!otherQueue.outputDat.empty()) {
        for (size_t i = otherQueue.outputDat.size(); i > 0; --i) {
            temp2.push_back(otherQueue.outputDat[i - 1]);
        }
    }
    for (size_t i = 0; i < otherQueue.inputDat.size(); ++i) {
        temp2.push_back(otherQueue.inputDat[i]);
    }
    return temp1 == temp2;
}

bool Queue::operator!=(const Queue& otherQueue) const {
    return !(*this == otherQueue);
}
