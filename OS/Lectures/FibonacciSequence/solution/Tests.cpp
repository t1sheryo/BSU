//#include "fibonacci.h"
//#include <gtest/gtest.h>
//#include <iostream>
//#include <sstream>
//
//// Test for CalculateFibonacciSequence
//TEST(FibonacciTest, CalculateFibonacciSequence) {
//    // Test for n = 5
//    std::vector<int> expected = { 0, 1, 1, 2, 3 };
//    EXPECT_EQ(CalculateFibonacciSequence(5), expected);
//
//    // Test for n = 10
//    expected = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
//    EXPECT_EQ(CalculateFibonacciSequence(10), expected);
//
//    // Test for n = 2
//    expected = { 0, 1 };
//    EXPECT_EQ(CalculateFibonacciSequence(2), expected);
//}
//
//// Test for InitializeSizeOfSequence
//TEST(FibonacciTest, InitializeSizeOfSequence) {
//    int n = 0;
//
//    // Test with correct input
//    std::istringstream input1("5\n");
//    std::cin.rdbuf(input1.rdbuf());
//    InitializeSizeOfSequence(n);
//    EXPECT_EQ(n, 5);
//
//    // Test with incorrect input(number is less than 2)
//    std::istringstream input2("1\n3\n");
//    std::cin.rdbuf(input2.rdbuf());
//    InitializeSizeOfSequence(n);
//    EXPECT_EQ(n, 3);
//
//    // Test with incorrect input (not valid value)
//    std::istringstream input3("abc\n4\n");
//    std::cin.rdbuf(input3.rdbuf());
//    InitializeSizeOfSequence(n);
//    EXPECT_EQ(n, 4);
//}
//
//// Test for PrintFibonacciSequence
//TEST(FibonacciTest, PrintFibonacciSequence) {
//    std::vector<int> sequence = { 0, 1, 1, 2, 3 };
//
//    // Перенаправляем вывод std::cout в строку
//    std::stringstream buffer;
//    std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
//
//    // Вызываем тестируемую функцию
//    PrintFibonacciSequence(sequence);
//
//    // Восстанавливаем старый буфер std::cout
//    std::cout.rdbuf(oldCoutBuffer);
//
//    std::string expectedOutput =
//        "\nFirst 5 of Fibonacci sequence:\n"
//        "0\n"
//        "1\n"
//        "1\n"
//        "2\n"
//        "3\n";
//
//    EXPECT_EQ(buffer.str(), expectedOutput);
//}
//
//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//
//    // Запуск тестов
//    int testResult = RUN_ALL_TESTS();
//
//    // Очистка буфера ввода
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//    // Ожидание нажатия Enter
//    std::cout << "Press Enter to exit...";
//    std::cin.get();
//
//    return testResult;
//}
