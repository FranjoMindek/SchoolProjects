#include <iostream>
#include <vector>

struct Point{
    int x, y;
};

class Shape{
    public:
        virtual ~Shape(){}
        virtual void move(int x, int y) =0;
        virtual void draw() =0;
};

class Circle : public Shape{
    public:
        void move(int x, int y) {center_.x += x; center_.y += y;}
        void draw() {std::cerr <<"in drawCircle\n";}
    private:
        Point center_;    
};

class Square : public Shape{
    public:
        void move(int x, int y) {center_.x += x; center_.y += y;}
        void draw() {std::cerr <<"in drawSquare\n";}
    private:
        Point center_;    
};

class Rhomb : public Shape{
    public:
        void move(int x, int y) {center_.x += x; center_.y += y;}
        void draw() {std::cerr <<"in drawRhomb\n";}
    private:
        Point center_;    
};



int main(){
    
    Shape* prvi = new Circle();
    Shape* drugi = new Square();
    Shape* treci = new Circle();
    Shape* cetvrti = new Rhomb();
    std::vector<Shape*> vec = {prvi, drugi, treci, cetvrti};

    for(auto shape : vec){
        shape->draw();
    }
    
    for(auto shape : vec){
        shape->move(3,3);
    }
    
    return 0;
}