#include <iostream>
#include <random>
#include <vector>
#include <string>

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
    sort_analisys = {};
    int length = mas.size();

    for (int i = 0; i < length; i++) {
        int min = mas[i];
        int index_min = i;
        sort_analisys.iter_directSelection++;
        for (int j = i; j < length; j++) {
            sort_analisys.srav_Selection++;
            if (mas[j] <= min && mas[j]%3 == 0) {
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
        if (mas[i] % 3 == 0) 
        {
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
}

// Сортировка пузырьком
void sortBubble(std::vector<int> mas) {
    sort_analisys = {};
    int length = mas.size();

    for (int i = 0; i < length - 1; i++) {
        sort_analisys.iter_Bubble++;
        for (int j = 0; j < length - i - 1; j++) {
            sort_analisys.srav_Bubble++;
            if (mas[j] % 3 == 0 && mas[j + 1] % 3 == 0) 
            {
                if (mas[j] > mas[j + 1]) {
                    std::swap(mas[j], mas[j + 1]);
                    sort_analisys.swap_Bubble++;
                }
            }
        }
    }
}

void sortQuick(std::vector<int>& mas, int low, int high) {
    sort_analisys.iter_directExchange++;
    if (low < high) {
        int pi = -1;
        for (int k = low; k <= high; ++k) {
            if (mas[k] % 3 == 0) {
                pi = k;
                break;
            }
        }

        if (pi == -1) {
            return;
        }

        int i = low - 1;

        for (int j = low; j <= high; j++) {
            sort_analisys.srav_directExchange++;
            if (mas[j] % 3 == 0 && mas[j] < mas[pi]) {
                i++;
                std::swap(mas[i], mas[j]);
                sort_analisys.swap_directExchange++;
            }
        }
        
        int pi_index = high;
        for (int k = low; k < high; k++) {
            if (mas[k] % 3 != 0) {
                pi_index = k;
                break;
            }
            else {
                pi_index = k + 1;
            }

        }
        if (mas[high] % 3 == 0) {
            std::swap(mas[i + 1], mas[pi]);
            pi_index = i + 1;
            sort_analisys.swap_directExchange++;
        }



        sortQuick(mas, low, pi_index - 1);
        sortQuick(mas, pi_index + 1, high);
    }
}

std::string spacesIndentation(int val, int length) {
    std::string str = std::to_string(val);
    //std::cout << (length - str.size()) << "&" << std::endl;
    int size = length - str.size();
    for (int i = 0; i < size; i++) {
        str += " ";
       // std::cout << str <<" " <<i <<  std::endl;
    }
    return str;
}

void printTable(std::vector<int> mas)
{
    std::cout << "\n+ ------------------+--------+--------------+--------------+------------+" << std::endl;
    std::cout << "| Метод сортировки  | Размер | Итерации     | Сравнения    | Обмены     |" << std::endl;
    std::cout << "+-------------------+--------+--------------+--------------+------------+" << std::endl;
    std::vector<float> percent_sortings = { 0, 0.25, 0.5, 0.75, 1 };
    for (float percent : percent_sortings) {
        std::vector<int> copy_mas = mas;
        std::sort(begin(copy_mas), begin(copy_mas) + (copy_mas.size() * percent));
        std::vector<int> masSelection = copy_mas;
        std::vector<int> masInsertion = copy_mas;
        std::vector<int> masBubble = copy_mas;
        std::vector<int> masQuick = copy_mas;
        // Сортировка выбором
        sortDirectSelection(masSelection);
        std::cout << "| Selection Sort    |" << spacesIndentation(mas.size(),8) << "|" << spacesIndentation(sort_analisys.iter_directSelection, 14)  << "|" << spacesIndentation(sort_analisys.srav_Selection, 14) << "|" << spacesIndentation(sort_analisys.swap_Selection,12) << "|" << std::endl;

        // Сортировка вставками
        sortDirectInc(masInsertion);
        std::cout << "| Insertion Sort    |" << spacesIndentation(mas.size(),8) << "|" << spacesIndentation(sort_analisys.iter_directInc,14) << "|" << spacesIndentation(sort_analisys.srav_Inc,14) << "|" << spacesIndentation(sort_analisys.swap_Inc,12) << "|" << std::endl;

        // Сортировка пузырьком
        sortBubble(masBubble);
        std::cout << "| Bubble Sort       |" << spacesIndentation(mas.size(),8) << "|" << spacesIndentation(sort_analisys.iter_Bubble,14) << "|" << spacesIndentation(sort_analisys.srav_Bubble,14) << "|" << spacesIndentation(sort_analisys.swap_Bubble,12) << "|" << std::endl;

        // Быстрая сортировка
        sort_analisys = {};
       // sortQuick(masQuick, 0, masQuick.size() - 1);
        //std::cout << "| Quick Sort       | " << mas.size() << "     | "<< sort_analisys.iter_directExchange <<"     | " << sort_analisys.srav_directExchange << "     | " << sort_analisys.swap_directExchange << "     | " << std::endl;

        std::cout << "+-------------------+--------+--------------+--------------+------------+" << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(0));
    std::vector<int> original20 = createMassiv(20);
    printTable(original20);
    std::vector<int> original500 = createMassiv(500);
    printTable(original500);
    std::vector<int> original1000 = createMassiv(1000);
    printTable(original1000);
    std::vector<int> original10000 = createMassiv(10000);
    printTable(original10000);
    

    return 0;
}
