#include "funcs.hpp"
#include "funcs.cpp"

using std::cout;

int main(void){
    srand(time(NULL));
    Wolf wf = Wolf();
    Hare hr = Hare();
    Carrot cr = Carrot();

    int **arr = (int**)malloc(sizeof(int*) * HEIGHT);
    for(int i = 0; i < WIDTH; i++){
        arr[i] = (int*)malloc(sizeof(int) * WIDTH);
    }

    init_world(arr, wf, hr, cr);
    for(int i = 0; i < WIDTH; i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}