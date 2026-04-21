#include <stdio.h>
#include "stars.h"
#include <time.h> //подключаем библиотеку для работы с текущей датой (функции time(),localtime())

// Функция определяет високосный ли год
// Возвращает 1 если високосный
int isLeapYear(int year){  
    if ((year % 4 == 0 && year % 100 != 0)||( year % 400 == 0))
    {
        return 1;
    } 
    else 
    {
        return 0;
    }
}

// Функция по формуле Целлера определяет день недели
// Возвращает число от 0 до 6
int getDayOfTheWeek(int day, int month, int year) {
    // Если январь(1) или февраль(2) - считаем их как 13 и 14 месяцы прошлого года
    if (month < 3)  {
        month += 12; // Январь == 13 или февраль == 14
        year -=1; // Отнимаем год
    }

    int k = year % 100; // Последние две цифры года
    int j = year / 100; // Первые две цифры года

    // Сама формула Целлера
    int h = (day + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) + 5 * j) % 7;

    return h; // 0 == сб, 1 == вск, ... ,  6 == пт
}

int getAge(int birthDay,int birthMonth, int birthYear){
//узнаем текущую дату
    time_t t; // переменная t для хранения времени
    time(&t); // записываем в нее текущее время в секундах
    struct tm *today = localtime(&t); // переводим в структуру tm из библиотеки
    //time.h (день, месяц, год, ...)

    int curDay = today->tm_mday; // получаем число месяца из localtime()
    //и структуры тм, сохраняем в curDay
    int curMonth = today->tm_mon +1; //получаем номер месяца +1 для сдвига (0-11 +1)
    int curYear = today->tm_year +1900; //получаем год начиная от 1900 и добавляем + 1900
    int age = curYear - birthYear; // высчитываем возраст как разницу значений текущий - год рождения

    //если день рождения в этот год еще не наступил
    if (curMonth < birthMonth || (curMonth == birthMonth && curDay < birthDay)){
        age--; // то вычитаем 1 год
    }
    
    return age; // возращаем готовый возраст
}

int main() {

    int day, month, year;

    // Запрашиваем данные у пользователя   
    do{
    printf("Year: ");
    if (scanf("%d", &year) != 1) {  // если ввели не число
        while (getchar() != '\n');   // очищаем буфер
        year = 0;                    // делаем год невалидным
    }
    if (year < 1900 || year > 2026)
        printf("Error: year value must be between 1900 and 2026\nplease try again:\n");
	}
	while (year < 1900 || year > 2026);
    
    do{
    printf("Month: ");
    if (scanf("%d", &month) != 1) {
        while (getchar() != '\n');
        month = 0;
    }
    if (month < 1 || month > 12)
        printf("Error: month value must be between 1 and 12\nplease try again:\n");
}
	while(month < 1 || month > 12);
    

    int dayValid = 0; // считаем что дата некорректна изначально
    do{
        printf("Day : ");
    if (scanf("%d", &day) != 1) {
        while (getchar() != '\n');
        day = 0;
    }

        if (day < 1 || day > 31) { // ограничение по максимальному и минимальному значению
        printf("Error: day must be 1-31\n");
    }
    else if (month == 2) // ограничение дней в феврале
    {
        int maxDays = isLeapYear(year) ? 29 : 28; // високосный ли февраль
        if (day > maxDays){
        printf("Error: %ds February has %d days\n", year, maxDays);
        }else {
        dayValid = 1;
        }
    }
    //ограничения по месяцам где максимум 30 дней
    else if ((month == 4 || month == 6 || month == 9 || month == 11 ) && day > 30){
        printf("Error: %d month has only 30 days in it\n", month);
    }
    else {
        dayValid = 1;
    }
    }
    while (dayValid != 1);
 
    
    




    // Выводим полученную дату
    printf("\nBirthday is : %02d.%02d.%d\n", day,month,year);

    // Проверяем високосный ли год и выводим результат
    if (isLeapYear(year)) {
        printf("Year is a leap year\n");
    } else {
        printf("Year is not a leap year\n");
    }

    // Получаем день недели (число от 0 до 6)
    int weekday = getDayOfTheWeek(day, month, year);

    // Массив названий дней (начиная от 0 == суббота)
    char *days[] = {"Saturday", "Sunday" , "Monday" , "Tuesday" , "Wednesday" , "Thursday" , "Friday"};

    int age = getAge(day,month,year); // вызов функции передаем день месяц и год рождения

    printf("Your age: %d years\n", age); // выводим возраст пользователя




    //выводим даты звездочками
    printf("\nDate in stars:\n\n");

    // Каждая цифра состоит из 5 строк (0, 1, 2, 3, 4)
    // Нам нужно напечатать все 5 строк для дня, месяца и года
    // Для этого используем цикл: row меняется от 0 до 4
    for (int row = 0; row < 5; row++) {
        // Печатаем день (две цифры) в текущей строке row
        // Например, если day = 15 и row = 0, напечатает верхние строки цифр 1 и 5
        printTwoDigits(day, row);

        // Печатаем три пробела между днём и месяцем (разделитель)
        printf("   ");

         // Печатаем месяц (две цифры) в текущей строке row
        printTwoDigits(month, row);

        // Печатаем три пробела между месяцем и годом
        printf("   ");

        // Печатаем год (четыре цифры) в текущей строке row
        printYear(year, row);

        // После того как напечатали строку дня, месяца и года
        // переходим на следующую строку (к следующему row)
        printf("\n");

        // Цикл повторяется для row = 0,1,2,3,4
        // После row = 4 цикл заканчивается
    }

    printf("press 'Enter' to close the program;\n"); //пауза перед тем как программа закроется
    getchar();
    getchar();


    return 0;
}


