/*Создайте приложение для работыавтосалона. Необходимо 
хранить информацию о продаваемых автомобилях (название, год выпуска, объем двигателя, цену). Реализуйте 
интерфейс для добавления данных, удаления данных, 
отображения данных, сортировке данных по различным 
параметрам, поиску данных по различным параметрам. 
При реализации используйте контейнеры, функторы и 
алгоритмы.*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits> // Для проверки некорректного ввода

struct Car {
    std::string name;
    int year;
    double engineVolume;
    double price;

    // Перегрузим оператор вывода для удобства
    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << "Название: " << car.name
            << ", Год выпуска: " << car.year
            << ", Объем двигателя: " << car.engineVolume
            << " л, Цена: " << car.price << " руб.";
        return os;
    }
};

class CarShowroom {
private:
    std::vector<Car> cars;

public:
    // Добавление нового автомобиля
    void addCar(const std::string& name, int year, double engineVolume, double price) {
        auto it = std::find_if(cars.begin(), cars.end(), [&name](const Car& car) {
            return car.name == name;
            });

        if (it != cars.end()) {
            std::cout << "Автомобиль с названием \"" << name << "\" уже существует.\n";
        }
        else {
            cars.push_back({ name, year, engineVolume, price });
            std::cout << "Автомобиль \"" << name << "\" успешно добавлен!\n";
            std::cout << "Текущее количество автомобилей: " << cars.size() << "\n";
        }
    }

    // Удаление автомобиля по названию
    void removeCar(const std::string& name) {
        auto it = std::remove_if(cars.begin(), cars.end(), [&name](const Car& car) {
            return car.name == name;
            });

        if (it != cars.end()) {
            cars.erase(it, cars.end());
            std::cout << "Автомобиль \"" << name << "\" успешно удален.\n";
            std::cout << "Текущее количество автомобилей: " << cars.size() << "\n";
        }
        else {
            std::cout << "Автомобиль \"" << name << "\" не найден.\n";
        }
    }

    // Отображение всех автомобилей
    void displayCars() const {
        if (cars.empty()) {
            std::cout << "На данный момент в автосалоне нет автомобилей.\n";
        }
        else {
            std::cout << "\nСписок автомобилей в автосалоне:\n";
            for (const auto& car : cars) {
                std::cout << car << "\n";
            }
            std::cout << "\nВсего автомобилей: " << cars.size() << "\n";
        }
    }

    // Сортировка по году выпуска
    void sortByYear() {
        std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return a.year < b.year;
            });
        std::cout << "Автомобили отсортированы по году выпуска.\n";
    }

    // Сортировка по цене
    void sortByPrice() {
        std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
            return a.price < b.price;
            });
        std::cout << "Автомобили отсортированы по цене.\n";
    }

    // Поиск автомобиля по названию
    void searchByName(const std::string& name) const {
        auto it = std::find_if(cars.begin(), cars.end(), [&name](const Car& car) {
            return car.name == name;
            });

        if (it != cars.end()) {
            std::cout << "\nНайден автомобиль:\n" << *it << "\n";
        }
        else {
            std::cout << "Автомобиль с названием \"" << name << "\" не найден.\n";
        }
    }

    // Поиск автомобиля по объему двигателя
    void searchByEngineVolume(double engineVolume) const {
        auto it = std::find_if(cars.begin(), cars.end(), [engineVolume](const Car& car) {
            return car.engineVolume == engineVolume;
            });

        if (it != cars.end()) {
            std::cout << "\nНайден автомобиль:\n" << *it << "\n";
        }
        else {
            std::cout << "Автомобиль с объемом двигателя " << engineVolume << " л не найден.\n";
        }
    }

    // Поиск автомобилей в диапазоне цен
    void searchByPriceRange(double minPrice, double maxPrice) const {
        std::cout << "\nАвтомобили в диапазоне цен от " << minPrice << " до " << maxPrice << " руб:\n";
        auto count = std::count_if(cars.begin(), cars.end(), [minPrice, maxPrice](const Car& car) {
            return car.price >= minPrice && car.price <= maxPrice;
            });

        if (count > 0) {
            for (const auto& car : cars) {
                if (car.price >= minPrice && car.price <= maxPrice) {
                    std::cout << car << "\n";
                }
            }
        }
        else {
            std::cout << "Нет автомобилей в указанном диапазоне цен.\n";
        }
    }

    // Поиск автомобилей в диапазоне объема двигателя
    void searchByEngineVolumeRange(double minVolume, double maxVolume) const {
        std::cout << "\nАвтомобили с объемом двигателя от " << minVolume << " л до " << maxVolume << " л:\n";
        auto count = std::count_if(cars.begin(), cars.end(), [minVolume, maxVolume](const Car& car) {
            return car.engineVolume >= minVolume && car.engineVolume <= maxVolume;
            });

        if (count > 0) {
            for (const auto& car : cars) {
                if (car.engineVolume >= minVolume && car.engineVolume <= maxVolume) {
                    std::cout << car << "\n";
                }
            }
        }
        else {
            std::cout << "Нет автомобилей в указанном диапазоне объема двигателя.\n";
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    CarShowroom showroom;
    int choice;

    while (true) {
        std::cout << "\n===== Меню автосалона =====\n"
            << "1. Добавить автомобиль\n"
            << "2. Удалить автомобиль\n"
            << "3. Показать все автомобили\n"
            << "4. Сортировать автомобили по году выпуска\n"
            << "5. Сортировать автомобили по цене\n"
            << "6. Найти автомобиль по названию\n"
            << "7. Найти автомобиль по объему двигателя\n"
            << "8. Поиск автомобилей по диапазону цен\n"
            << "9. Поиск автомобилей по диапазону объема двигателя\n"
            << "0. Выйти из программы\n"
            << "===========================\n"
            << "Введите номер действия: ";
        std::cin >> choice;

        // Обработка некорректного ввода
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Пожалуйста, введите номер действия от 0 до 9.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Завершение работы программы.\n";
            break;
        }

        std::string name;
        int year;
        double engineVolume, price, minValue, maxValue;

        switch (choice) {
        case 1:
            std::cout << "\nВведите название автомобиля: ";
            std::cin >> name;
            std::cout << "Введите год выпуска: ";
            std::cin >> year;
            std::cout << "Введите объем двигателя (л): ";
            std::cin >> engineVolume;
            std::cout << "Введите цену (руб): ";
            std::cin >> price;
            showroom.addCar(name, year, engineVolume, price);
            break;

        case 2:
            std::cout << "\nВведите название автомобиля для удаления: ";
            std::cin >> name;
            showroom.removeCar(name);
            break;

        case 3:
            showroom.displayCars();
            break;

        case 4:
            showroom.sortByYear();
            break;

        case 5:
            showroom.sortByPrice();
            break;

        case 6:
            std::cout << "\nВведите название автомобиля для поиска: ";
            std::cin >> name;
            showroom.searchByName(name);
            break;

        case 7:
            std::cout << "\nВведите объем двигателя для поиска: ";
            std::cin >> engineVolume;
            showroom.searchByEngineVolume(engineVolume);
            break;

        case 8:
            std::cout << "\nВведите минимальную цену: ";
            std::cin >> minValue;
            std::cout << "Введите максимальную цену: ";
            std::cin >> maxValue;
            showroom.searchByPriceRange(minValue, maxValue);
            break;

        case 9:
            std::cout << "\nВведите минимальный объем двигателя (л): ";
            std::cin >> minValue;
            std::cout << "Введите максимальный объем двигателя (л): ";
            std::cin >> maxValue;
            showroom.searchByEngineVolumeRange(minValue, maxValue);
            break;

        default:
            std::cout << "Некорректный выбор. Пожалуйста, введите число от 0 до 9.\n";
            break;
        }
    }

    return 0;
}
