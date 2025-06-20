#include "crow_all.h"
#include "catch.hpp"
#include <vector>
#include <string>
#include <stdexcept>

// Структура для узла связного списка
struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ~ListNode() = default;
};

// Генерация первых n чисел Фибоначчи
std::vector<int> fibonacci(int n) {
    if (n < 0) {
        throw std::invalid_argument("n must be non-negative");
    }
    std::vector<int> fib(n);
    if (n == 0) return fib;
    fib[0] = 0;
    if (n == 1) return fib;
    fib[1] = 1;
    for (int i = 2; i < n; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    return fib;
}

// Проверка, является ли число палиндромом
bool isPalindrome(int x) {
    if (x < 0) return false;
    long reversed = 0;
    int original = x;
    while (x > 0) {
        int digit = x % 10;
        reversed = reversed * 10 + digit;
        x /= 10;
    }
    return original == reversed;
}

// Итеративный разворот связного списка
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextTemp = current->next;
        current->next = prev;
        prev = current;
        current = nextTemp;
    }
    return prev;
}

// Вспомогательная функция: вектор в список
ListNode* vectorToList(const std::vector<int>& vec) {
    if (vec.empty()) return nullptr;
    ListNode* head = new ListNode(vec[0]);
    ListNode* current = head;
    for (size_t i = 1; i < vec.size(); ++i) {
        current->next = new ListNode(vec[i]);
        current = current->next;
    }
    return head;
}

// Вспомогательная функция: список в вектор с освобождением памяти
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> result;
    ListNode* current = head;
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    return result;
}

// Юнит-тесты
TEST_CASE("Fibonacci Tests", "[fibonacci]") {
    REQUIRE_THROWS_AS(fibonacci(-1), std::invalid_argument);
    REQUIRE(fibonacci(0).empty());
    REQUIRE(fibonacci(1) == std::vector<int>{0});
    REQUIRE(fibonacci(2) == std::vector<int>{0,1});
    REQUIRE(fibonacci(5) == std::vector<int>{0,1,1,2,3});
    REQUIRE(fibonacci(10) == std::vector<int>{0,1,1,2,3,5,8,13,21,34});
}

TEST_CASE("Palindrome Tests", "[palindrome]") {
    REQUIRE(isPalindrome(121) == true);
    REQUIRE(isPalindrome(-121) == false);
    REQUIRE(isPalindrome(0) == true);
    REQUIRE(isPalindrome(12321) == true);
    REQUIRE(isPalindrome(12345) == false);
}

TEST_CASE("Reverse List Tests", "[reverse_list]") {
    REQUIRE(reverseList(nullptr) == nullptr);
    ListNode* single = new ListNode(1);
    ListNode* reversed = reverseList(single);
    REQUIRE(reversed->val == 1);
    REQUIRE(reversed->next == nullptr);
    delete reversed;
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    ListNode* rev = reverseList(head);
    REQUIRE(rev->val == 3);
    REQUIRE(rev->next->val == 2);
    REQUIRE(rev->next->next->val == 1);
    REQUIRE(rev->next->next->next == nullptr);
    while (rev) {
        ListNode* temp = rev;
        rev = rev->next;
        delete temp;
    }
}

// REST-сервис
int main(int argc, char* argv[]) {
    // Запуск тестов, если передан флаг --test
    if (argc > 1 && std::string(argv[1]) == "--test") {
        return Catch::Session().run(argc, argv);
    }

    crow::SimpleApp app;

    // Эндпоинт для чисел Фибоначчи
    CROW_ROUTE(app, "/fibonacci")([] (const crow::request& req) {
        try {
            auto n_str = req.url_params.get("n");
            if (!n_str) return crow::response(400, "Missing parameter n");
            int n = std::stoi(n_str);
            auto fib = fibonacci(n);
            crow::json::wvalue result;
            result["fibonacci"] = fib;
            return crow::response(result);
        } catch (const std::invalid_argument& e) {
            return crow::response(400, "Invalid parameter n");
        } catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
    });

    // Эндпоинт для проверки палиндрома
    CROW_ROUTE(app, "/palindrome")([] (const crow::request& req) {
        try {
            auto num_str = req.url_params.get("num");
            if (!num_str) return crow::response(400, "Missing parameter num");
            int num = std::stoi(num_str);
            bool result = isPalindrome(num);
            crow::json::wvalue response;
            response["is_palindrome"] = result;
            return crow::response(response);
        } catch (const std::exception& e) {
            return crow::response(400, "Invalid parameter num");
        }
    });

    // Эндпоинт для разворота списка
    CROW_ROUTE(app, "/reverse_list").methods("POST"_method)([] (const crow::request& req) {
        try {
            auto json = crow::json::load(req.body);
            if (!json || !json.has("list")) return crow::response(400, "Invalid or missing list");
            std::vector<int> input;
            for (const auto& item : json["list"]) {
                input.push_back(item.i());
            }
            ListNode* head = vectorToList(input);
            ListNode* reversed = reverseList(head);
            auto output = listToVector(reversed);
            crow::json::wvalue result;
            result["reversed"] = output;
            return crow::response(result);
        } catch (const std::exception& e) {
            return crow::response(400, e.what());
        }
    });

    app.port(18080).multithreaded().run();
    return 0;
}
