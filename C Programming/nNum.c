#include <stdio.h>

int main() {
    int n, i, num, sum = 0;

    printf("How many numbers do you want to add? ");
    scanf("%d", &n);

    printf("Enter %d numbers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &num);
        sum = sum + num;
    }

    printf("Sum = %d\n", sum);

    return 0;
}