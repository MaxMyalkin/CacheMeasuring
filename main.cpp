#include <iostream>
#include <ctime>
#include <chrono>
#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include <sys/time.h>
#include <iomanip>

#define START_NUMBER 8 * 1024 // начнем с 8 кб
#define REPEAT_QUANTITY 30
#define CYCLES_NUMBER 10000 // сколько раз будет проходить по массиву для замера времени.
#define ELEMENTS_NUMBER CYCLES_NUMBER * 32 // сколько элементов проходит при измерении
#define END_NUMBER 10 * 1024 * 1024 //10МБ
#define DEBUG

using namespace std;


class cache_element {
public:
    cache_element * next;
    cache_element():next(NULL){}
};


vector<int> get_indexes(unsigned long n) {
    vector<int> indexes;
    for(int i = 0; i < n ; i++) {
        indexes.push_back(i);
    }
    return indexes;
}

double measure_time(cache_element *element) {
    clock_t start = clock();
    for(int i = 0 ; i < CYCLES_NUMBER; i++) {
        element = element->next; // проходим по 16 элементов
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;


        element = element->next; // проходим по 16 элементов
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
        element = element->next;
    }
    clock_t end = clock();
    double time_per_op =  ((double)(end - start)/ ELEMENTS_NUMBER);
    return time_per_op;
}


double measure_middle_time(cache_element *elements) {
    vector<double> times;
    for(int i = 0; i < REPEAT_QUANTITY; i++) {
        times.push_back(measure_time(elements));
    }

    double time = 0;
    for(auto iterator = times.begin(); iterator != times.end(); iterator++) {
        time += *iterator;
    }
    time /= times.size();
    return time;
}


void make_list(cache_element *elements, vector<int> indexes) {
    auto iterator = indexes.begin();
    for(auto iterator2 = iterator + 1; iterator2 != indexes.end(); iterator++, iterator2++) {
        elements[*iterator].next = &elements[*iterator2];
    }
    elements[*iterator].next = &elements[*indexes.begin()];
}

int main() {
    vector<int> indexes;
    cache_element element;
    const int size_width = 10;
    const int time_width = 10;

    for(unsigned long n = START_NUMBER; n < END_NUMBER; n*= 1.2) {
        unsigned long elements_quantity = n/ sizeof(cache_element);
        cout<< setw(size_width)<<left<< (double)n/1000;
        indexes = get_indexes(elements_quantity);
        cache_element* elements = new cache_element[elements_quantity];
        make_list(elements, indexes);
        //cout<< setw(time_width)<<left<< measure_middle_time(elements);
        auto engine = default_random_engine{};
        shuffle(indexes.begin(), indexes.end(), engine);
        make_list(elements, indexes);
        cout<< setw(time_width)<<left<< measure_middle_time(elements)<<endl;
        delete [] elements;
    }
    return 0;
}