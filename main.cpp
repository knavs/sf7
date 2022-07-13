#include "intarray.h"
#include "arrayexception.h"

using namespace std;

namespace test {
int ASize = 10;

IntArray init(int size = ASize) {
    IntArray array(size);
    for (int i = 0; i < size; i++) {
        array[i] = rand()%size;
    }
    return array;

}

void ok() {
    std::cout << "OK"; // выведется только если не будет выброшен exception
}

void out_of_range_up() {
    auto array = test::init();

    try {
        array[ASize];
        test::ok();
    } catch(BadRange& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "Exceptions!";
    }
}

void out_of_range_down() {
    auto array = test::init();

    try {
        array[-1];
        test::ok();
    } catch(BadRange& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "Exceptions!";
    }
}

void resize_to_zero() {
    auto array = test::init();

    try {
        array.resize(0);
        test::ok();

    } catch(BadSize& e) {
        std::cout << e.what();

    } catch (...) {
        std::cout << "Exceptions!";
    }

}

void resize_to_negative() {
    auto array = test::init();

    try {
        array.resize(-2);
        test::ok();

    } catch(BadSize& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "Exceptions!";
    }

}

}


int main()
{
    setlocale(LC_ALL, "");
    IntArray array;

    std::cout << "1. Создать контейнер и заполнить случайными числами" << std::endl;
    int asize = 5;
    IntArray arr1(asize);
    for (int i = 0; i < asize; i++) {
        arr1[i] = rand()%asize;
    }
    std::cout << "arr1=" << arr1 << std::endl << std::endl;

    //
    std::cout << "2. Скопировать контейнер" << std::endl;
    IntArray arr2 = IntArray(arr1);
    std::cout << "Оригинал: arr1=" << arr1 << std::endl;
    std::cout << "Копия: arr2=" << arr2 << std::endl << std::endl;


    std::cout << "3. Получить доступ к любому элементу контейнера по индексу" << std::endl;
    std::cout << "arr1 = "<< arr1 << std::endl;
    std::cout << "arr1[0] = "<< arr1[0] << std::endl;
    std::cout << "arr1[1] = "<< arr1[1] << std::endl;
    std::cout << "arr1[2] = "<< arr1[2] << std::endl;
    std::cout << "arr1[3] = "<< arr1[3] << std::endl;
    std::cout << "arr1[4] = "<< arr1[4] << std::endl << std::endl;

    std::cout << "4. Изменить размер контейнера" << std::endl;
    arr1.resize(6);
    std::cout << "(размер +1) arr1 = "<< arr1 << std::endl;
    arr1.resize(4);
    std::cout << "(размер -1) arr1 = "<< arr1 << std::endl;
    arr1.resize(1);
    std::cout << "(размер =1) arr1 = "<< arr1 << std::endl << std::endl;



    std::cout << "4. Вставить элемент в контейнер по месту / в начало / в конец" << std::endl;
    arr2.insertAtBeginning(13);
    std::cout << "13 в начало: arr2="<< arr2 << std::endl;
    arr2.insertAtEnd(88);
    std::cout << "88 в конец: arr2="<< arr2 << std::endl;
    arr2.insertBefore(777, 1);
    std::cout << "777 перед 1-м: arr2="<< arr2 << std::endl << std::endl;

    std::cout << "5. Удалить элемент из контейнера" << std::endl;
    std::cout << "arr2 = " << arr2 << std::endl;
    arr2.remove(7);
    std::cout << "удаляем 7-й: "<<  arr2 << std::endl;
    arr2.remove(1);
    std::cout << "удаляем 1-й: "<<  arr2 << std::endl;
    arr2.remove(0);
    std::cout << "удаляем 0-й: "<<  arr2 << std::endl << std::endl;


    std::cout << "6. Поиск по индексу" << std::endl;
    std::cout << arr2 << std::endl;
    std::cout << "Результат поиска (" << arr2[3] << "): " << arr2.index(arr2[3]) << " позиция";


    std::cout << std::endl << std::endl <<
                "ТЕСТИРОВАНИЕ"
             << std::endl;

    std::cout << "Тест1: ";
    test::out_of_range_up();
    std::cout << endl;

    std::cout << "Тест2: ";
    test::out_of_range_down();
    std::cout << endl;


    std::cout << "Тест3: ";
    test::resize_to_negative();
    std::cout << endl;


    std::cout << "Тест4: ";
    test::resize_to_zero();
    std::cout << endl;

    return 0;
}
