# Тесты для лабораторной работы №1 (Длинная арифметика)

## Входные данные
-нет-

## Выходные данные
-вывод информации о фильмах на экран-

# Позитивные тесты: 
- 01 - Тест на целочисленное деление (50/10)
- 02 - Тест на округление (1/6)
- 03 - Тест на нулевой результат (0/10)
- 04 - Тест на деление на число с точкой (1/9.24)
- 05 - Тест на удаление лишних нулей (0007/0.007000)
- 06 - Тест на деление на число без целой части (1/.33)
- 07 - Тест на деление на число без дробной части (1/33.)
- 08 - Тест на деление на экспоненту (5/1Е-10)
- 09 - Тест на увеличение порядка + ввод максимального кол-ва цифр (9х40/0.00000001)
- 10 - Тест на временный выход за границы порядка (12345/1E99999)
- 11 - Тест на деление двух одинаковых чисел
- 12 - Тест на неизменность порядка (1024/50 - порядок частного 2)
- 13 - Тест на перемену порядка (9024/50 порядок частного 3)

# Негативные тесты:
- 01 - Пустой файл
- 02 - Указано только первое число
- 03 - Первое число - не целое
- 04 - Указано не число
- 05 - Вместо второго числа введена точка
- 06 - Вместо второго числа введена E
- 07 - Второе число - ноль
- 08 - Превышение длины мантиссы
- 09 - Превышение длины порядка
- 10 - В ходе деление получилось число, выходящее за границы
- 11 - -
- 12 - -
- 13 - -