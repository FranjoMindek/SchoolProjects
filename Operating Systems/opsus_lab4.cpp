#include<set>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<iomanip>
#include<string>

//OLD NE DINAMICKO
//#define TOTAL_SIZE 100 // VELICINA POLJA JE OD 0 DO total_memory_size, znaci total_memory_size = 100 -----> 100 znakovnih polja
#define HIGHER_BOUND 30
#define LOWER_BOUND 5 //VELICINE MANJE OD 2 PRAVE PROBLEME S IPISOM!!!
int total_memory_size;
int free_space_size;

char randChar();

class Segment{
    private: //default  
    public:
        std::string values = "";
        int start;
        int end;
        int size; //easier later on
        bool memory; //1 is memory, 0 is free space
        Segment(int start, int end, bool memory){
            this->start = start;
            this->end = end;
            this->size = end-start;
            this->memory = memory;
            if(memory){
                for(int i = 0; i < this->size; i++){
                    this->values += randChar();
                }
                this->values[0] = '|';
                this->values[this->size - 1] = '|';
            }else{
                for(int i = 0; i < this->size; i++){
                    this->values += '-';
                }
            }
        }
        bool operator<(const Segment& rhs) const { return start < rhs.start; } //za set
};

void memorySort(std::set<Segment> &memory, std::set<Segment> &free_space);
void printMemory(std::set<Segment> &memory, std::set<Segment> &free_space);
std::ostream &operator<<(std::ostream &os, Segment const &m);

int main(){
    std::set<Segment> memory;
    std::set<Segment> free_space;
    std::cin >> total_memory_size;
    bool checked = 0;
    free_space_size = total_memory_size;
    Segment starting_space(0, total_memory_size, 0);
    free_space.insert(starting_space);
    srand(time(NULL));
    int counter = 0;
    while(1){
        counter++;
        checked = 0;
        if(counter%15 == 0){
            std::cout << "~~~Standard routine memory sort initiated!~~~" << std::endl;
            counter = 0;
            memorySort(memory, free_space);
        }
        printMemory(memory, free_space);
        //LOGIKA DODAVANJA I OSLOBADJANJA
        int memory_chance = rand()%101 + (1.f * free_space_size / total_memory_size)*40; //sto ima manje memorije veca sansa za memoriju
        if (memory_chance >= 60 || memory.size() == 0){
            //create new memory segment
            int size = rand()%(HIGHER_BOUND - LOWER_BOUND + 1) + LOWER_BOUND; //range 3-20
            allocationRetry:;
            auto fp_it = free_space.begin();
            int min = total_memory_size;
            for(; fp_it != free_space.end(); fp_it++){
                if(fp_it->size >= size && fp_it->size < min){
                    //postoji mjesta za njega, i trazimo najmanji takav
                    min = fp_it->size;
                }
            }
            for(fp_it = free_space.begin(); fp_it != free_space.end(); fp_it++){
                if(fp_it->size == min){
                    break;
                }
            }
            if(fp_it == free_space.end() && !checked){
                std::cout << "~~~Not enough space for newly created memory segment, memory sort initiated!~~~" << std::endl;
                memorySort(memory, free_space);
                checked = 1;
                counter = 0;
                goto allocationRetry;
            }else if(fp_it == free_space.end() && checked){
                fp_it--;
                std::cout << "~~~Failure, still not enough space!~~~ [" << size << "/" << fp_it->size << "]" << std::endl;
            }else {
                if(checked) std::cout << "~~~Success, newly created space is large enough!~~~" << std::endl;
                Segment new_memory(fp_it->start, fp_it->start + size, 1); //brise se stari slobodni prostor koji se sada dijeli na memoriju i novi slobodni prostor ako postoji
                free_space_size -= new_memory.size;
                memory.insert(new_memory);
                if(fp_it->size != size) { //znaci da je slobodni prostor sigurno veci od nove memorije, tj nastaje novi slobodni prostor
                    Segment new_free_space(fp_it->start + size, fp_it->end, 0);
                    free_space.insert(new_free_space);
                }
                free_space.erase(fp_it);
            }
        }else if(memory.size() >= 1){
            //create free space segment
            int which_memory = rand()%memory.size();
            auto m_it = memory.begin();
            for(int i = 0; i < which_memory; i++){
                m_it++;
            } //odredimo pointer na memoriju koju brisemo
            auto fp_it = free_space.begin(); //idemo pronaci jel postoji
            auto fp_helper_it = fp_it;
            for(; fp_it != free_space.end(); fp_it++){ 
                if(fp_it->start == m_it->end  || fp_it->end == m_it->start ){
                    break;
                }
                fp_helper_it++;
            }
            if(fp_it == free_space.end()){ //ne mozemo nigdje povezati free memoriju, samo stvaramo novu
                Segment new_free_space(m_it->start, m_it->end, 0);
                free_space_size += new_free_space.size;
                free_space.insert(new_free_space);
                memory.erase(m_it);
            }else{//povezujemo novonastale memorije
                fp_helper_it++;
                if(fp_helper_it->start == m_it->end && fp_it->end == m_it->start){// ZAUZETA MEMORIJE || FREE MEMORIJA => FREE MEMORIJA]
                    Segment new_free_space(fp_it->start, fp_helper_it->end, 0);
                    free_space_size += m_it->size;
                    free_space.erase(fp_helper_it);
                    free_space.erase(fp_it);
                    free_space.insert(new_free_space);
                    memory.erase(m_it);
                }
                else if(fp_it->start == m_it->end){// ZAUZETA MEMORIJE || FREE MEMORIJA => FREE MEMORIJA
                    Segment new_free_space(m_it->start, fp_it->end, 0);
                    free_space_size += m_it->size;
                    free_space.erase(fp_it);
                    free_space.insert(new_free_space);
                    memory.erase(m_it);
                }else{                        // FREE MEMORIJA || ZAUZETA MEMORIJA => FREE ME   MORIJA
                    Segment new_free_space(fp_it->start, m_it->end, 0);
                    free_space_size += m_it->size;
                    free_space.erase(fp_it);
                    free_space.insert(new_free_space);
                    memory.erase(m_it);
                }
            }
        }
        sleep(1);
    }
    return 0;
}

void memorySort(std::set<Segment> &memory, std::set<Segment> &free_space){
    //MEMORIJA
    std::set<Segment> new_memory_set;
    auto m_it = memory.begin();
    int start = 0;
    for(;m_it != memory.end(); m_it++){
        Segment new_memory(start, start + m_it->size, 1);
        new_memory.values = m_it->values;
        new_memory_set.insert(new_memory);
        start += m_it->size;
    }
    memory.clear();
    memory = new_memory_set;
    //FREE SPACE
    free_space.clear();
    Segment new_free_space(start, total_memory_size, 0);
    free_space.insert(new_free_space);
    return;
}

void printMemory(std::set<Segment> &memory, std::set<Segment> &free_space){
    auto m_it = memory.begin();
    auto fp_it = free_space.begin();
    
    std::cout << "Free_Memory=(" << std::setw(3) << free_space_size << "/" << std::setw(3) << total_memory_size <<") ";
    while(m_it != memory.end() || fp_it != free_space.end()){
        if(m_it != memory.end() && fp_it != free_space.end()){
            if(m_it->start < fp_it->start){
                std::cout << *m_it;
                m_it++;
            }
            else{
                std::cout << *fp_it;
                fp_it++;
            }
        }else if(m_it != memory.end() && fp_it == free_space.end()){
            std::cout << *m_it ;
            m_it++;   
        }else{
            std::cout << *fp_it;
            fp_it++;
        }
    }
    std::cout << std::endl;
    return;
}

char randChar(){
    int one_of_three = rand()%3;
    switch(one_of_three){
        case 0:
            return rand()%('z'-'a')+'a';
        case 1:
            return rand()%('Z'-'A')+'A';
        case 2:
            return rand()%('9'-'0')+'0';
    }
    return '?';
}

std::ostream &operator<<(std::ostream &os, Segment const &m) {
    //return os << m.size;
    return os << m.values;
}