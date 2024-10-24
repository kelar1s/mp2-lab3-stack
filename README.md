# mp2-lab3-stack

# Лабораторная работа №3. Вычисление арифметических выражений.

## Цель работы

Разработать программу, выполняющую вычисление арифметического выражения. Выражение в качестве операндов может содержать переменные и вещественные числа. Допустимые операции: +, -, /, *. Допускается также наличие знака "-" в начале выражения или после открывающей скобки. Опционально - наличие математических функций (sin, соs, ln, exp, и т.д.) Программа должна выполнять предварительную проверку корректности выражения и сообщать пользователю вид ошибки и номера символов строки, в которых были найдены ошибки.

## Этапы выполнения работы

1. Разработка шаблонного класса TStack с использованием массива
2. Разработка класса TCalculator, в котором была бы реализована:
- проверка правильности расстановки скобок (с использованием стека для хранения индексов скобок).
- проверка правильности расстановки операндов и операций
- проверка корректности ввода выражения (недопустимые символы)
- перевод выражения в постфиксную (польскую) запись
- вычисление выражения по постфиксной записи
3. Разработка простого консольного приложения (ввод и вычисление выражения)
4. Разработка системы тестов для классов  TStack и TCalculator; тестирование классов.
5. Создание приложения с графическим интерфейсом, которое обеспечивало бы:
- ввод и вычисление выражения (базовый вариант)
- построение графика функции одной переменной (опционально)
6. Подготовка отчета.
