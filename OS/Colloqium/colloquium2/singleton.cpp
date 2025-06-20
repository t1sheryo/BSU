#include <mutex>
#include <iostream>

// Политика создания: создание через new
template <class T>
struct CreateUsingNew {
    static T* create() { return new T; }
    static void destroy(T* p) { delete p; }
};

// Политика хранения: статическая переменная
template <class T>
struct StaticStorage {
    static T*& value() {
        static T* s_value = nullptr;
        return s_value;
    }
};

// Модель однопоточности
struct SingleThreadedModel {
    struct Lock {
        Lock() = default;
        ~Lock() = default;
    };
    static Lock lock() { return Lock(); }
};

// Модель многопоточности
struct MultiThreadedModel {
    static std::mutex& getMutex() {
        static std::mutex mutex;
        return mutex;
    }
    struct Lock {
        explicit Lock(std::mutex& m) : guard(m) {}
        std::lock_guard<std::mutex> guard;
    };
    static Lock lock() { return Lock(getMutex()); }
};

// Шаблон Singleton
template <
    class T,
    class CreationPolicy = CreateUsingNew<T>,
    class StoragePolicy = StaticStorage<T>,
    class ThreadingModel = MultiThreadedModel
>
class Singleton {
public:
    static T& instance() {
        T*& instancePtr = StoragePolicy::value();
        if (!instancePtr) {
            typename ThreadingModel::Lock lock = ThreadingModel::lock();
            if (!instancePtr) {
                instancePtr = CreationPolicy::create();
            }
        }
        return *instancePtr;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() = default;
};

// Пример класса для демонстрации
class Example {
public:
    Example() { std::cout << "Example created\n"; }
    void use() const { std::cout << "Example used\n"; }
};

// Демонстрация использования
int main() {
    Singleton<Example>::instance().use();
    Singleton<Example>::instance().use();
    return 0;
}
