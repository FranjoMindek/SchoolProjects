#include <iostream>
#include <string>
#include <string.h>
#include <set>
#include <vector>


template <typename Iterator, typename Predicate>
Iterator mymax(Iterator first, Iterator last, Predicate pred){
    Iterator max = first;
    while(first != last){
        if(pred(max, first) <= 0) max = first;
        first++;
    }
    return max;
}

template <typename Iterator> //radi u slucaju ako tip implementira Greater Than funkcionalnost
int gt_template(Iterator x, Iterator y){
    return *x > *y;
}

int main(){
    int arr_int[] = { 1, 3, 5, 7, 4, 6, 9, 2, 0 };
    std::string arr_string[] = {"Jedan", "Dva", "Tri", "zzZadnji", "Peti", "Sesti"};
    std::vector<std::string> vec_string = {"Jedan", "Dva", "Tri", "zzZadnji", "Peti", "Sesti"};
    std::set<std::string> set_string = {"Jedan", "Dva", "Tri", "zzZadnji", "Peti", "Sesti"};

    auto maxint = mymax(&arr_int[0], 
        &arr_int[sizeof(arr_int)/sizeof(*arr_int)], gt_template<typeof(&arr_int[0])>);
    auto maxstr1 = mymax(&arr_string[0], 
        &arr_string[sizeof(arr_string)/sizeof(*arr_string)], gt_template<typeof(&arr_string[0])>);
    auto maxstr2 = mymax(vec_string.cbegin(), 
        vec_string.cend(), gt_template<typeof(vec_string.cbegin())>);
    auto maxstr3 = mymax(set_string.cbegin(), 
        set_string.cend(), gt_template<typeof(set_string.cbegin())>);

    std::cout <<*maxint <<"\n";
    std::cout <<*maxstr1 <<"\n";
    std::cout <<*maxstr2 <<"\n";
    std::cout <<*maxstr3 <<"\n";

    return 0;
}