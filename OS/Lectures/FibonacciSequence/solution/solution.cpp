#include "fibonacci.h"
#include <iostream>

int main() {
    int n = 0;

    InitializeSizeOfSequence(n);
    std::vector<int> sequence = CalculateFibonacciSequence(n);
    PrintFibonacciSequence(sequence);

    // Clearing buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Waiting for user to press ENTER
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
