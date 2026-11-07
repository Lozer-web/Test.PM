#include <iostream>
#include <Windows.h>
#include <cmath> 
#include <string>

// структура для хранения состояния корзины
struct Cart {
    int apple = 0;
    int orange = 0;
    int apricos = 0;
    int pear = 0;
    int tomato = 0;
    int onion = 0;
    int cucumber = 0;
    int garlic = 0;
    int parsley = 0;
    int boya = 0;
};

double calculateTotal(const Cart& cart, double& outParsleyPrice, int& outOnionGift) {
    int onionsale = cart.onion - (cart.onion / 4);
    double onionprice = onionsale * 100.0;
    outOnionGift = cart.onion / 4;

    double parsleyprice = cart.parsley * 90.0;
    if (cart.parsley >= 3) {
        double parsleysale = parsleyprice * 0.05;
        parsleyprice -= parsleysale;
    }
    outParsleyPrice = parsleyprice;

    double summa = (cart.apple * 100.0) + (cart.orange * 120.0) + (cart.apricos * 90.0) +
        (cart.pear * 67.0) + (cart.tomato * 130.0) + onionprice +
        (cart.cucumber * 150.0) + (cart.garlic * 80.0) + parsleyprice + (cart.boya * 100.0);

    if (summa >= 2500.0) {
        double skidka = summa * 0.13;
        summa -= skidka;
    }

    return summa;
}


void runUnitTests() {
    std::cout << "=========================================\n";
    std::cout << "       Запуск тестов      \n";
    std::cout << "=========================================\n";

    int passed = 0;
    int failed = 0;

    
    auto assertNear = [&](const std::string& testName, double actual, double expected, double epsilon = 1e-5) {
        if (std::abs(actual - expected) < epsilon) {
            std::cout << "[ Успешно ] " << testName << " | Ожидал: " << expected << " , Получил: " << actual << "\n";
            passed++;
        }
        else {
            std::cout << "[  Не успешно ] " << testName << " | Ожидал: " << expected << " , Получил: " << actual << " !!!\n";
            failed++;
        }
        };

    // TC-01
    {
        Cart cart; cart.apple = 1; cart.orange = 1;
        double pPrice = 0; int oGifts = 0;
        assertNear("TC-01: Базовый расчет чисел", calculateTotal(cart, pPrice, oGifts), 220.0);
    }

    // TC-02
    {
        Cart cart;
        double pPrice = 0; int oGifts = 0;
        assertNear("TC-02: Пустая корзина", calculateTotal(cart, pPrice, oGifts), 0.0);
    }

    // TC-03
    {
        Cart cart; cart.onion = 3;
        double pPrice = 0; int oGifts = 0;
        assertNear("TC-03: Лук без скидки (<4L)", calculateTotal(cart, pPrice, oGifts), 300.0);
    }

    // TC-04
    {
        Cart cart; cart.onion = 4;
        double pPrice = 0; int oGifts = 0;
        assertNear("TC-04: Лук со скидкой (4л по цене 3)", calculateTotal(cart, pPrice, oGifts), 300.0);
    }

    // TC-05
    {
        Cart cart; cart.parsley = 3;
        double pPrice = 0; int oGifts = 0;
        assertNear("TC-05: Скидка на Петрушевый чай", calculateTotal(cart, pPrice, oGifts), 256.5);
    }

    // TC-06 
    {
        Cart cart; cart.tomato = 20;
        double pPrice = 0; int oGifts = 0;
        assertNear("TC-06: Скидка на всю корзину 13%", calculateTotal(cart, pPrice, oGifts), 2262.0);
    }

    // TC-07
    {
        Cart cart; cart.tomato = 10;
        double pPrice = 0; int oGifts = 0;
        assertNear("TC-07: Без скидки на всю корзину (<2500)", calculateTotal(cart, pPrice, oGifts), 1300.0);
    }

    std::cout << "=========================================\n";
    std::cout << "Успешных: " << passed << " | Не успешных: " << failed << "\n";
    std::cout << "=========================================\n\n";
    std::cout << "Нажмите Enter для перехода к магазину...";
    std::cin.ignore();
    std::cin.get();
}


int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

   
    runUnitTests();

    Cart cart;
    int choose = 0, choose1 = 0, choose2 = 0, choose3 = 0, choose5 = 0;

    while (true)
    {
        system("cls");
        std::cout << "\t|Магазин  \"Соки Александра\"\n";
        std::cout << "\t|Категории:\n\n";
        std::cout << "\t|1 - Фруктовые соки\n";
        std::cout << "\t|2 - Овощные соки\n";
        std::cout << "\t|3 - Чаи!!\n";
        std::cout << "\t|4 - Настойки\n";
        std::cout << "\t|5 - Корзина\n";
        std::cout << "\t|Все напитки по литру!!\n\n";
        std::cout << "\t|Выберите вашу категорию товара: ";
        std::cin >> choose;

        int totalfrukt = cart.apple + cart.orange + cart.pear + cart.apricos;

        if (choose == 1)
        {
            system("cls");
            std::cout << "Вид Фруктового сока:\n";
            std::cout << "1 - Яблочный - 100\n";
            std::cout << "2 - Апельсиновый - 120\n";
            std::cout << "3 - Абрикосовый - 90\n";
            std::cout << "4 - Грушевый - 67\n";
            std::cout << "Напишите номер товара который хотите приобрести: ";
            std::cin >> choose1;

            int litrs = 0;
            if (choose1 == 1)
            {
                system("cls");
                std::cout << "Вы выбрали яблочный сок. Укажите сколько литров хотите " << cart.apple << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> litrs;
                cart.apple += litrs;
                if (cart.apple < 0) cart.apple = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.apple << " л.\n";
                Sleep(3000);
            }
            else if (choose1 == 2)
            {
                system("cls");
                std::cout << "Вы выбрали апельсиновый сок. Укажите сколько литров хотите " << cart.orange << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> litrs;
                cart.orange += litrs;
                if (cart.orange < 0) cart.orange = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.orange << " л.\n";
                Sleep(3000);
            }
            else if (choose1 == 3)
            {
                system("cls");
                std::cout << "Вы выбрали абрикосовый сок. Укажите сколько литров хотите " << cart.apricos << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> litrs;
                cart.apricos += litrs;
                if (cart.apricos < 0) cart.apricos = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.apricos << " л.\n";
                Sleep(3000);
            }
            else if (choose1 == 4)
            {
                system("cls");
                std::cout << "Вы выбрали грушевый сок. Укажите сколько литров хотите " << cart.pear << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> litrs;
                cart.pear += litrs;
                if (cart.pear < 0) cart.pear = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.pear << " л.\n";
                Sleep(3000);
            }

            if (cart.apple > 0 || cart.orange > 0 || cart.apricos > 0 || cart.pear > 0)
            {
                if (cart.boya > 0)
                {
                    system("cls");
                    cart.boya = 0;
                    std::cout << "Прошу внимание! Ваша покупка настойки боярышника аннулирована из вашей корзины из за покупки фруктового сока!!!\n";
                    std::cout << "Теперь вы не можете купить настойку боярышника!!!!! ";
                    Sleep(6500);
                }
            }
        }
        else if (choose == 2)
        {
            system("cls");
            std::cout << "Виды овощного сока:\n";
            std::cout << "1 - Томатный - 130\n";
            std::cout << "2 - Луковый - 100\n";
            std::cout << "3 - Огуречный - 150\n";
            std::cout << "Напишите номер товара, который вы хотите приобрести: ";
            std::cin >> choose2;

            int liters = 0;
            if (choose2 == 1)
            {
                system("cls");
                std::cout << "Вы выбрали томатный сок. Укажите сколько литров хотите " << cart.tomato << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> liters;
                cart.tomato += liters;
                if (cart.tomato < 0) cart.tomato = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.tomato << " л.\n";
                Sleep(3000);
            }
            else if (choose2 == 2)
            {
                system("cls");
                std::cout << "Вы выбрали луковый сок. Укажите сколько литров хотите " << cart.onion << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> liters;
                cart.onion += liters;
                if (cart.onion < 0) cart.onion = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.onion << " л.\n";
                Sleep(3000);
            }
            else if (choose2 == 3)
            {
                system("cls");
                std::cout << "Вы выбрали огуречный сок. Укажите сколько литров хотите " << cart.cucumber << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> liters;
                cart.cucumber += liters;
                if (cart.cucumber < 0) cart.cucumber = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.cucumber << " л.\n";
                Sleep(3000);
            }
        }
        else if (choose == 3)
        {
            system("cls");
            std::cout << "Виды чая:\n";
            std::cout << "1 - Чесночный - 80\n";
            std::cout << "2 - Петрушевый - 90\n";
            std::cout << "Напишите название товара, который хотите приобрести: ";
            std::cin >> choose3;
            int litr = 0;
            if (choose3 == 1)
            {
                system("cls");
                std::cout << "Вы выбрали чесночный чай. Укажите сколько литров хотите " << cart.garlic << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> litr;
                cart.garlic += litr;
                if (cart.garlic < 0) cart.garlic = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.garlic << " л.\n";
                Sleep(3000);
            }
            else if (choose3 == 2)
            {
                system("cls");
                std::cout << "Вы выбрали Петрушевый чай. Укажите сколько литров хотите " << cart.parsley << " л.\n";
                std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                std::cin >> litr;
                cart.parsley += litr;
                if (cart.parsley < 0) cart.parsley = 0;
                std::cout << "Корзина обновлена! Литров: " << cart.parsley << " л.\n";
                Sleep(3000);
            }
        }
        else if (choose == 4)
        {
            if (totalfrukt > 0)
            {
                system("cls");
                std::cout << "Блокировка, вы уже купили фруктовый сок, а эти миксы запрещены!!!!!";
                Sleep(2500);
            }
            else
            {
                system("cls");
                std::cout << "Виды настоек:\n";
                std::cout << "1 - Боярышник - 100\n";
                std::cin >> choose5;
                int latr = 0;
                if (choose5 == 1)
                {
                    system("cls");
                    std::cout << "Вы выбрали настойку боярышника. Укажите сколько литров хотите " << cart.boya << " л.\n";
                    std::cout << "Введите сколько литров хотите добавить(с минусом если хотите вычесть): ";
                    std::cin >> latr;
                    cart.boya += latr;
                    if (cart.boya < 0) cart.boya = 0;
                    std::cout << "Корзина обновлена! Литров: " << cart.boya << " л.\n";
                    Sleep(3000);
                }
            }
        }
        else if (choose == 5)
        {
            system("cls");
            std::cout << "Ваша Корзина:\n";
            std::cout << "Яблочный сок - " << cart.apple * 100 << " руб\n";
            std::cout << "Апельсиновый сок - " << cart.orange * 120 << " руб\n";
            std::cout << "Абрикосовый сок - " << cart.apricos * 90 << " руб\n";
            std::cout << "Грушевый сок - " << cart.pear * 67 << " руб\n";
            std::cout << "Томатный сок - " << cart.tomato * 130 << " руб\n";
            std::cout << "Луковый сок - " << cart.onion * 100 << " руб\n";
            std::cout << "Огуречный чай - " << cart.cucumber * 150 << " руб\n";
            std::cout << "Чесночный чай - " << cart.garlic * 80 << " руб\n";
            std::cout << "Петрушевый чай - " << cart.parsley * 90 << " руб\n";
            std::cout << "Настойка боярышника - " << cart.boya * 100 << " руб\n\n";
            double currentParsleyPrice = 0;
            int onionGifts = 0;
            double totalSumma = calculateTotal(cart, currentParsleyPrice, onionGifts);
            if (cart.onion > 0) {
                std::cout << "Луковый сок - " << cart.onion << " л. ";
                if (cart.onion >= 4) {
                    std::cout << "из них в подарок " << onionGifts << " л.\n";
                }
                else {
                    std::cout << "\n";
                }
            }
            if (cart.parsley >= 3) {
                std::cout << "Введена скидка на петрушевый чай, ваша цена: " << currentParsleyPrice << " руб\n";
            }
            if ((cart.apple * 100) + (cart.orange * 120) + (cart.apricos * 90) + (cart.pear * 67) +
                (cart.tomato * 130) + ((cart.onion - onionGifts) * 100) + (cart.cucumber * 150) +
                (cart.garlic * 80) + currentParsleyPrice + (cart.boya * 100) >= 2500) {
                std::cout << "Применена общая скидка 13% за заказ от 2500 руб!\n";
            }
            std::cout << "-------------------------------------------\n";
            std::cout << "ОБЩАЯ СУММА К ОПЛАТЕ: " << totalSumma << " руб\n\n";
            std::cout << "Нажмите любую клавишу для возврата в меню...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}