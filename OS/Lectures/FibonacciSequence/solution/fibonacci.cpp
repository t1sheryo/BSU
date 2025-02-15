#include "fibonacci.h"
#include <iostream>
#include <limits>

void InitializeSizeOfSequence(int& n) {
    while (true) {
        std::cout << "Enter an amount of Fibonacci sequence numbers: ";
        if (std::cin >> n) {
            if (n < 2) {
                std::cout << "Incorrect amount! You should enter number >1\n";
            }
            else break;
        }
        else {
            std::cout << "Invalid input! Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::vector<int> CalculateFibonacciSequence(int n) {
    std::vector<int> dp(n);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i < n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp;
}

void PrintFibonacciSequence(const std::vector<int>& seq) {
    std::cout << "\nFirst " << seq.size() << " of Fibonacci sequence:\n";

    for (int num : seq) {
        std::cout << num << '\n';
    }
}
