# Коллоквиум 2

Этот каталог содержит реализацию шаблона Singleton с использованием ортогональных стратегий, как описано в книге "Modern C++ Design" Андрея Александреску ([Modern C++ Design](https://www.amazon.nl/-/en/Alexandrescu-Andrei/dp/0201704315)).

## Содержимое
- **singleton.cpp**: Код Singleton с политиками создания, хранения и синхронизации.
- **documentation.md**: Подробная документация.

## Инструкции по запуску
1. **Компиляция**:
   ```bash
   g++ -std=c++11 singleton.cpp -o singleton -pthread
   ```
2. **Запуск**:
   ```bash
   ./singleton
   ```
