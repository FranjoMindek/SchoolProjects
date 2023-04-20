#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Unary_Function{
    const struct Unary_Function_vtable *vtable;
    int lower_bound;
    int upper_bound;
    void (*tabulate)(struct Unary_Function *);
} Unary_Function;

static bool same_functions_for_ints(Unary_Function *f1, Unary_Function *f2, double tolerance);

typedef struct Linear{
    Unary_Function super;
    //novi dio
    double a;
    double b;
} Linear;

typedef struct Square{
    Unary_Function super;
    //novi dio
} Square;

struct Unary_Function_vtable{
    double (*value_at)(Unary_Function*, double);
    double (*negative_value_at)(Unary_Function*, double);
};

void Unary_Function_tabulate(Unary_Function *self);

double value_at_square(Unary_Function* object, double x);
double value_at_linear(Unary_Function* object, double x);
double negative_value_at_square(Unary_Function* object, double x);
double negative_value_at_linear(Unary_Function* object, double x);

const struct Unary_Function_vtable square_vtable = {value_at_square, negative_value_at_square};
const struct Unary_Function_vtable linear_vtable = {value_at_linear, negative_value_at_linear};

Unary_Function* createSquare(int lb, int ub);
Unary_Function* createLinear(int lb, int ub, double a_coef, double b_coef);

void constructSquare(Square* memory, int lb, int ub);
void constructLinear(Linear* memory, int lb, int ub, double a_coef, double b_coef);

int main(){
    Unary_Function *f1 = createSquare(-2, 2);
    f1->tabulate(f1);
    Unary_Function *f2 = createLinear(-2, 2, 5, -2);
    f2->tabulate(f2);
    printf("f1==f2: %s\n", same_functions_for_ints(f1, f2, 1E-6) ? "DA" : "NE");
    printf("neg_val f2(1) = %lf\n", f2->vtable->negative_value_at(f2, 1.0));
    free(f1);
    free(f2);
    return 0;
}

static bool same_functions_for_ints(Unary_Function *f1, Unary_Function *f2, double tolerance){
    if(f1->lower_bound != f2->lower_bound) return false;
    if(f1->upper_bound != f2->upper_bound) return false;
    for(int x = f1->lower_bound; x<= f1->upper_bound; x++){
        double delta = f1->vtable->value_at(f1, x) - f2->vtable->value_at(f2, x);
        if(delta < 0) delta = -delta;
        if(delta > tolerance) return false;
    }
    return true;
}

void Unary_Function_tabulate(Unary_Function *self){
    for(int x = self->lower_bound; x <= self->upper_bound; x++){
        printf("f(%d)=%lf\n", x, self->vtable->value_at(self, x));
    }
}

double value_at_linear(Unary_Function* object, double x){
    Linear* downcast = (Linear*) object;
    return downcast->a * x + downcast->b;
}

double negative_value_at_linear(Unary_Function* object, double x){
    return -value_at_linear(object, x);
}

double value_at_square(Unary_Function* object, double x){
    return x*x;
}

double negative_value_at_square(Unary_Function* object, double x){
    return -value_at_square(object, x);
}

Unary_Function* createSquare(int lb, int ub){
    Square *memory = (Square*) malloc(sizeof(Square));
    constructSquare(memory, lb, ub);
    return (Unary_Function*) memory;
}

void constructSquare(Square* memory, int lb, int ub){
    memory->super.lower_bound = lb;
    memory->super.upper_bound = ub;
    memory->super.vtable = &square_vtable;
    memory->super.tabulate = Unary_Function_tabulate;
}

Unary_Function* createLinear(int lb, int ub, double a_coef, double b_coef){
    Linear *memory = (Linear*) malloc(sizeof(Linear));
    constructLinear(memory, lb, ub, a_coef, b_coef);
    return (Unary_Function*) memory;
}

void constructLinear(Linear* memory, int lb, int ub, double a_coef, double b_coef){
    memory->super.lower_bound = lb;
    memory->super.upper_bound = ub;
    memory->super.vtable = &linear_vtable;
    memory->super.tabulate = Unary_Function_tabulate;
    memory->a = a_coef;
    memory->b = b_coef;
}


//
// Created by mindek on 10. 03. 2022..
//

