#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


void Print(int *sample, int size){
    for(int i=0; i<size; i++){
        printf("%d ", sample[i]);
    }
}

int calculate_steps(int steps, int size){
    if(steps > size)
        calculate_steps(steps - size, size);

    return steps;
}

void left(int *sample, int steps, int size){
    steps = calculate_steps(steps, size);
    if(steps == size) return;

    int tmp[size];

    memset(tmp, 0, size);
    memcpy(tmp, sample, (steps * sizeof(int) ));

    int cnt = 0;
    for(int i=steps; i<size; i++) {
        sample[cnt++] = sample[i];
    }

    int padding = size - steps;
    cnt = 0;
    for(int i=padding; i<size; i++){
        sample[i] = tmp[cnt++];
    }


   // printf("Testing!! --> steps %d\n", steps);
    Print(sample, size);

}

int main() {
    int size=0, steps = 0;

    scanf("%d %d", &size, &steps);


    int matrix[size];
    int cnt = 0;

    while(1){
        
        scanf("%d", &matrix[cnt++]);
        if(cnt == size)
            break;
    }

    for(int i =0; i<size; i++){
       // printf("%d ", matrix[i]);
    }

    left(matrix, steps, size);

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
