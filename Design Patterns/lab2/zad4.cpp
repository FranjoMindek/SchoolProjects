#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <time.h>

class Percentile{
public:
    virtual void print(std::vector<int>* numbers) =0;
};

class NearestRankPercentile : public Percentile{
public:
    void print(std::vector<int>* numbers) override{
        for(int i=10; i<=90; i+=10){
            int index = (int)(1.0*i*numbers->size()/100 + 0.5)-1; //-1 jer je od 1 do N umjesto od 0 do N-1
            if(index < 0) index = 0;
            std::cout << i << " percentile is " << numbers->at(index) << std::endl;
        }
    }
};

class InterpolatedPercentile : public Percentile{
public:
    void print(std::vector<int>* numbers) override{
        std::vector<int> percentiles;
        int n = numbers->size();
        for(int i=1; i<=n; i++){
            percentiles.push_back((int)(100*(i-0.5)/n)); //+1 jer je od 1 do N umjesto od 0 do N-1 -> ubaceno kao da pocinje od 1
        }
        int start = percentiles[0];
        int end = percentiles[n-1];
        for(int i=10; i<=90; i+=10){
            if(i < start){
                std::cout << i << " percentile is " << start << std::endl;
                continue;
            }else if(i > end){
                std::cout << i << " percentile is " << start << std::endl;
                continue;
            }
            for(int j=0; j<n; j++){
                if(i == percentiles[j]){
                    std::cout << i << " percentile is " << numbers->at(j) << std::endl;
                    break;
                }else if(i < percentiles[j]){
                    int value = numbers->at(j-1) + n*(numbers->at(j) - numbers->at(j-1))*(i - percentiles[j-1])/100;
                    std::cout << i << " percentile is " << value << std::endl;
                    break;
                }
            }
        }
    }
};

class Generator{
public:
    virtual std::vector<int>* generate() =0;
};

class SequentialGenerator : public Generator{
public:
    SequentialGenerator(int left, int right, int step){
        this->left = left;
        this->right = right;
        this->step = step;
    }
    // void setParameters(int left, int right, int step){
    //     this->left = left;
    //     this->right = right;
    //     this->step = step;
    // }
private:
    int left, right, step;

    std::vector<int>* generate() override{
        std::vector<int>* numbers = new std::vector<int>;
        int i = left;
        while(i <= right){
            numbers->push_back(i);
            i+=step;
        }
        return numbers;
    }
};

class RandomGenerator : public Generator{
public:
    RandomGenerator(int mean, int std_dev, int number_of){
        this->mean = mean;
        this->std_dev = std_dev;
        this->number_of = number_of;
    }
    // void setParameters(int mean, int std_dev, int number_of){
    //     this->mean = mean;
    //     this->std_dev = std_dev;
    //     this->number_of = number_of;
    // }
private:
    int mean, std_dev, number_of;
    std::vector<int>* generate() override{
        std::vector<int>* numbers = new std::vector<int>;
        std::default_random_engine generator;
        generator.seed(time(NULL));
        std::normal_distribution<double> distribution(mean, std_dev);
        for(int i=0; i<number_of; i++)
            numbers->push_back((int)distribution(generator));
        std::make_heap(numbers->begin(), numbers->end());
        std::sort_heap(numbers->begin(), numbers->end());
        return numbers;
    }
};

class FibonacciGenerator : public Generator{
public:
    FibonacciGenerator(int number_of){
        this->number_of = number_of;
    }
    // void setParameters(int number_of){
    //     this->number_of = number_of;
    // }
private:
    int number_of;
    std::vector<int>* generate() override{
        std::vector<int>* numbers = new std::vector<int> {0, 1};
        int t1 = 0;
        int t2 = 1;
        int next;
        for(int i=0; i< number_of; i++){
            next = t1 + t2;
            t1 = t2;
            t2 = next;
            numbers->push_back(t2);
        }
        return numbers;
    }
};

class DistributionTester{
private:
    Generator* generator;
    Percentile* percentile;

public:
    ~DistributionTester(){
        delete this->generator;
        delete this->percentile;
    }
    DistributionTester(Generator* gen, Percentile* per){
        this->generator = gen;
        this->percentile = per;
    };

    void setGeneratorType(Generator* gen){
        delete this->generator;
        this->generator = gen;
    }

    void setPercentileType(Percentile* per){
        delete this->percentile;
        this->percentile = per;
    }

    std::vector<int>* generate(){
        std::cout << "Generating numbers" << std::endl;
        std::vector<int>* numbers = generator->generate();
        for(int x : *numbers)
            std::cout << x << " ";
        std::cout << std::endl;
        std::cout << "Numbers are generated" << std::endl;
        std::cout << "Printing percentiles" << std::endl;
        percentile->print(numbers);
        std::cout << "Percentiles are printed" << std::endl;
        std::cout << std::endl;
        return numbers;
    }
};

int main(){

    DistributionTester dt(new SequentialGenerator(1, 10, 2), new NearestRankPercentile());
    
    //takodjer vraca vektor ....
    dt.generate();
    dt.setPercentileType(new InterpolatedPercentile());
    dt.generate();
    dt.setGeneratorType(new RandomGenerator(10, 4, 50));
    dt.generate();
    dt.setGeneratorType(new FibonacciGenerator(10));
    dt.generate();
    dt.setGeneratorType(new FibonacciGenerator(14));
    dt.generate();
    dt.setPercentileType(new NearestRankPercentile());
    dt.generate();  
    //u dekonstruktoru zadnji generator i percentiles se obrisu..
}