#include <iostream>
#include <iomanip>
#include <iterator>
#include <locale>
#include <sstream>

using namespace std;

void appeal() { 
    cout << "Какую валюту Вы хотите конвертировать?" << 
    endl << "1 - Рубли" <<
    endl << "2 - Доллары" <<
    endl << "3 - Евро" <<
    endl << "4 - Иены" << 
    endl << "5 - Закончить операцию" << endl;
};

void rubles () {
    cout << "Введите сумму для конвертации в рублях" << endl;
    long double money_;
    //cin.imbue(std::locale("ru_RU.utf8"));
    cin >> std::get_money(money_, false);
    cout << "В какую валюту Вы хотите конвертировать?" << 
    endl << "1 - Доллары" <<
    endl << "2 - Евро" <<
    endl << "3 - Иены" << 
    endl << "4 - Закончить операцию" << endl;
    int _num;
    cin >> _num;
    switch (_num) {
            case 1: { 
                money_ = money_/73.4;
                std::cout.imbue(std::locale("en_US.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 2: {
                money_ = money_/80.2;
                std::cout.imbue(std::locale("de_De.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 3: {
                money_ = money_*1.48;
                std::cout.imbue(std::locale("ja_JP.UTF-8"));
                std::cout << "ja_JP: " << std::put_money(money_) << endl;
                break;
            };
            case 4: {break;};
            default:
            {cout << "Выбран отсутствующий вариант. Попробуйте ещё раз." << endl;
            break;}
    }
};

void dollars () {
    cout << "Введите сумму для конвертации в долларах" << endl;
    long double money_;
    //cin.imbue(std::locale("en_US.utf8"));
    cin >> std::get_money(money_, false);
    cout << "В какую валюту Вы хотите конвертировать?" << 
    endl << "1 - Рубли" <<
    endl << "2 - Евро" <<
    endl << "3 - Иены" << 
    endl << "4 - Закончить операцию" << endl;
    int _num;
    cin >> _num;
    switch (_num) {
            case 1: { 
                money_ = money_*73.4;
                std::cout.imbue(std::locale("ru_RU.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 2: {
                money_ = money_/1.2;
                std::cout.imbue(std::locale("de_LI.UTF-8"));
                std::cout << std::showbase << std::put_money(money_, true) << endl;
                break;
            };
            case 3: {
                money_ = money_*108.54;
                std::cout.imbue(std::locale("ja_JP.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 4: {break;};
            default:
            {cout << "Выбран отсутствующий вариант. Попробуйте ещё раз." << endl;
            break;}
    }
};

void euros () {
    cout << "Введите сумму для конвертации в евро" << endl;
    long double money_;
    //cin.imbue(std::locale("de_DE.utf8"));
    cin >> std::get_money(money_, false);

    cout << "В какую валюту Вы хотите конвертировать?" << 
    endl << "1 - Доллары" <<
    endl << "2 - Рубли" <<
    endl << "3 - Иены" << 
    endl << "4 - Закончить операцию" << endl;
    int _num;
    cin >> _num;

    switch (_num) {
            case 1: { 
                money_ = money_*1.2;
                std::cout.imbue(std::locale("en_US.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 2: {
                money_ = money_*80.2;
                std::cout.imbue(std::locale("ru_RU.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 3: {
                money_ = money_*130.05;
                std::cout.imbue(std::locale("ja_JP.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 4: {break;};
            default:
            {cout << "Выбран отсутствующий вариант. Попробуйте ещё раз." << endl;
            break;}
    }
};

void yens () {
    cout << "Введите сумму для конвертации в иенах" << endl;
    long double money_;
    //cin.imbue(std::locale("ja_JP.utf8"));
    cin >> std::get_money(money_);
    cout << " " << endl;
    cout << "В какую валюту Вы хотите конвертировать?" << 
    endl << "1 - Доллары" <<
    endl << "2 - Евро" <<
    endl << "3 - Рубли" << 
    endl << "4 - Закончить операцию" << endl;
    int _num;
    cin >> _num;
    switch (_num) {
            case 1: { 
                money_ = money_/108.54;
                std::cout.imbue(std::locale("en_US.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 2: {
                money_ = money_/130.05;
                std::cout.imbue(std::locale("de_DE.utf8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 3: {
                money_ = money_/1.48;
                std::cout.imbue(std::locale("ru_RU.UTF-8"));
                std::cout << std::showbase << std::put_money(money_) << endl;
                break;
            };
            case 4: {break;};
            default:
            {cout << "Выбран отсутствующий вариант. Попробуйте ещё раз." << endl;
            break;}
    }
};

int main()

{ 	
    int n = 0;
    do {
        appeal();
        int number;
        cin >> number;
        n = number;
        switch (number) {
            case 1: { 
                rubles();
                break;
            };
            case 2: {
                dollars();
                break;
            };
            case 3: {
                euros();
                break;
            };
            case 4: {
                yens();
                break;
            };
            case 5: {break;};
            default:
            {cout << "Выбран отсутствующий вариант. Попробуйте ещё раз." << endl;
            break;}
        }
    } while (n != 5);

return 0;

}