#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

struct SortAnalisys {
    int iter_directSelection = 0;
    int iter_directInc = 0;
    int iter_Bubble = 0;
    int iter_directExchange = 0;
    int srav_Selection = 0;
    int srav_Inc = 0;
    int srav_Bubble = 0;
    int srav_directExchange = 0;
    int swap_Selection = 0;
    int swap_Inc = 0;
    int swap_Bubble = 0;
    int swap_directExchange = 0;
};

SortAnalisys sort_analisys;

// Заполение массива случайными числами
std::vector<int> createMassiv(int count) {
    int start = 0;
    int end = 100;

    std::vector<int> mas;

    for (int i = 0; i < count; i++) {
        int el = rand() % (end - start + 1);
        mas.push_back(el);
    }

    return mas;
}

// Вывод массива
void printMas(const std::vector<int> mas) {
    for (int element : mas) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Сортировка прямого выбора
void sortDirectSelection(std::vector<int> mas) {
    sort_analisys = {}; // Сброс статистики перед каждой сортировкой
    int length = mas.size();

    for (int i = 0; i < length; i++) {
        int min = mas[i];
        int index_min = i;
        sort_analisys.iter_directSelection++;
        for (int j = i; j < length; j++) {
            sort_analisys.srav_Selection++;
            if (mas[j] <= min) {
                min = mas[j];
                index_min = j;
            }
        }
        if (index_min != i) {
            std::swap(mas[index_min], mas[i]);
            sort_analisys.swap_Selection++;
        }
    }
}

// Сортировка прямого включения (вставками)
void sortDirectInc(std::vector<int> mas) {
    sort_analisys = {};
    int length = mas.size();

    for (int i = 1; i < length; i++) {
        sort_analisys.iter_directInc++;
        int temp = mas[i];
        int j = i;
        while (j > 0 && temp < mas[j - 1]) {
            sort_analisys.srav_Inc++;
            mas[j] = mas[j - 1];
            j--;
            sort_analisys.swap_Inc++;
        }
        mas[j] = temp;
    }
}

// Сортировка пузырьком
void sortBubble(std::vector<int> mas) {
    sort_analisys = {}; // Сброс статистики перед каждой сортировкой
    int length = mas.size();

    for (int i = 0; i < length - 1; i++) {
        sort_analisys.iter_Bubble++;
        for (int j = 0; j < length - i - 1; j++) {
            sort_analisys.srav_Bubble++;
            if (mas[j] > mas[j + 1]) {
                std::swap(mas[j], mas[j + 1]);
                sort_analisys.swap_Bubble++;
            }
        }
    }
}

void sortQuick(std::vector<int> mas, int low, int high) {
    if (low < high) {
        int pi = (low + high) / 2; // Simple pivot selection
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            sort_analisys.srav_directExchange++;
            if (mas[j] < mas[pi]) {
                i++;
                std::swap(mas[i], mas[j]);
                sort_analisys.swap_directExchange++;
            }
        }
        std::swap(mas[i + 1], mas[high]);
        sort_analisys.swap_directExchange++;
        int pivotIndex = i + 1;

        sortQuick(mas, low, pivotIndex - 1);
        sortQuick(mas, pivotIndex + 1, high);
    }
}


int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0));

    std::vector<int> sizes = { 20, 500, 1000, 3000, 5000, 10000 };

    std::cout << "\n+ ------------------ + -------- + -------------- + -------------- + ------------ +" << std::endl;
    std::cout << "| Метод сортировки  | Размер | Итерации     | Сравнения    | Обмены     |" << std::endl;
    std::cout << "+------------------+--------+--------------+--------------+------------+" << std::endl;

    for (int size : sizes) {
        std::vector<int> original = createMassiv(size);
        std::vector<int> masSelection = original;
        std::vector<int> masInsertion = original;
        std::vector<int> masBubble = original;
        std::vector<int> masQuick = original;

        // Сортировка выбором
        sortDirectSelection(masSelection);
        std::cout << "| Selection Sort   | " << size << "     | " << sort_analisys.iter_directSelection << "      | " << sort_analisys.srav_Selection << "     | " << sort_analisys.swap_Selection << "   |" << std::endl;

        // Сортировка вставками
        sortDirectInc(masInsertion);
        std::cout << "| Insertion Sort   | " << size << "     | " << sort_analisys.iter_directInc << "      | " << sort_analisys.srav_Inc << "     | " << sort_analisys.swap_Inc << "   |" << std::endl;

        // Сортировка пузырьком
        sortBubble(masBubble);
        std::cout << "| Bubble Sort      | " << size << "     | " << sort_analisys.iter_Bubble << "      | " << sort_analisys.srav_Bubble << "     | " << sort_analisys.swap_Bubble << "   |" << std::endl;

        // Быстрая сортировка
        sort_analisys = {};
        sortQuick(masQuick, 0, masQuick.size() - 1);
        std::cout << "| Quick Sort       | " << size << "     | N/A          | " << sort_analisys.srav_directExchange << "     | " << sort_analisys.swap_directExchange << "   |" << std::endl;

        std::cout << "+------------------+--------+--------------+--------------+------------+" << std::endl;
    }

    return 0;
}