#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <vector>

void InitializeSizeOfSequence(int& n);
std::vector<int> CalculateFibonacciSequence(int n);
void PrintFibonacciSequence(const std::vector<int>& seq);

#endif // FIBONACCI_H
