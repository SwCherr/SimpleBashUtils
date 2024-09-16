# Simple Bash Utils

В этом проекте предсталена собственная версия реализации утилит Bash по работе с текстом, в рамках учебного проекта "School 21".
В этом проекте представлена реализация базовых утилиты Bash (cat и grep) по работе с текстами на языке программирования Си. 
Программы представляют собой исполняемый файл с аргументами командной строки.

- Программы разработаны на языке Си стандарта C11 с использованием компилятора gcc 
- Код программ cat и grep находится в ветке develop в папках src/cat/ и src/grep/ соответственно
- Сборка программ настроена с помощью Makefile с соответствующими целями: s21_cat, s21_grep в директоряих src/cat/ и src/grep/ соответственно
- Итоговые исполняемые файлы после сборки будут располагаться в соответсвующих директориях


### Формат использования утилиты cat

`cat [OPTION] [FILE]...`

### cat флаги
Список реализованных флагов и их описание для утилиты cat:

| № | Опции | Описание |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | нумерует только непустые строки |
| 2 | -e предполагает и -v (GNU only: -E то же самое, но без применения -v) | также отображает символы конца строки как $  |
| 3 | -n (GNU: --number) | нумерует все выходные строки |
| 4 | -s (GNU: --squeeze-blank) | сжимает несколько смежных пустых строк |
| 5 | -t предполагает и -v (GNU: -T то же самое, но без применения -v) | также отображает табы как ^I |


### Формат использования утилиты grep

`grep [options] template [file_name]`

### grep Опции
Список реализованных флагов и их описание для утилиты grep:

| № | Опции | Описание |
| ------ | ------ | ------ |
| 1 | -e | Шаблон |
| 2 | -i | Игнорирует различия регистра.  |
| 3 | -v | Инвертирует смысл поиска соответствий. |
| 4 | -c | Выводит только количество совпадающих строк. |
| 5 | -l | Выводит только совпадающие файлы.  |
| 6 | -n | Предваряет каждую строку вывода номером строки из файла ввода. |
| 7 | -h | Выводит совпадающие строки, не предваряя их именами файлов. |
| 8 | -s | Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах. |
| 9 | -f file | Получает регулярные выражения из файла. |
| 10 | -o | Печатает только совпадающие (непустые) части совпавшей строки. |


Поддерживается парные комбинации флагов.