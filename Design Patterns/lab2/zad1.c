#include<stdio.h>
#include<string.h>

const void* mymax(const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int gt_int(const void* x, const void* y);
int gt_char(const void* x, const void* y);
int gt_str(const void* x, const void* y);

int main(){

    int arr_int[] = { 1, 3, 5, 7, 4, 6, 9, 2, 0 };
    char arr_char[]="Suncana strana ulice";
    const char* arr_str[] = {
        "Gle", "malu", "vocku", "poslije", "kise",
        "Puna", "je", "kapi", "pa", "ih", "njise"
    };

    int int_test_res = gt_int(&arr_int[1], &arr_int[0]); //treba biti 1
    int char_test_res = gt_char(&arr_char[1], &arr_char[0]); //treba biti 1
    int str_test_res = gt_str(&arr_str[2], &arr_str[0]); // treba biti >0

    int max_int = *((int*)mymax(arr_int, 9, sizeof(int), gt_int));
    char max_char = *((char*)mymax(arr_char, 21, sizeof(char), gt_char));
    const char* max_str = *((const char**)mymax(arr_str, 11, sizeof(char*) , gt_str));

    //printf("Test: Int = %d, Char = %d, Str = %d \n", int_test_res, char_test_res, str_test_res);
    printf("Max in arr: Int = %d, Char = %c, Str = %s\n", max_int, max_char, max_str);

    return 0;
}

int gt_int(const void* x, const void* y){
    return *((int*)x) > *((int*)y) ? 1 : 0;
}

int gt_char(const void* x, const void* y){ //FIXME: mala velika slova ? ako je zahtjev nisam siguran
    return *((char*)x) > *((char*)y) ? 1 : 0;
}

int gt_str(const void* x, const void* y){
    return strcmp((*(const char**)x), (*(const char**)y));
}

// pointer na prvi clan, broj clanova, velicina jednog clana, funkcija usporedbe
const void* mymax(const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)){
    const void* max = base;
    for(int i = 1; i<nmemb; i++){
        const void* other = base + i*size;
        //printf("%d ", compar(max, other));
        if(compar(max, other) <= 0) max = other; //u slucaju =0 kod strcmp strings su jednaki pa je svejedno
    } 
    //printf("\n");
    return max;

}

