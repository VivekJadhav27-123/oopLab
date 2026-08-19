#include <stdio.h>

int main() {
    int arr[4], sum = 0;

    printf("Enter 4 numbers:\n");
    for(int i = 0; i < 4; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    printf("Sum of array elements = %d\n", sum);
    return 0;
}