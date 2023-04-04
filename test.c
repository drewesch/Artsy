#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

bool isOperator(char *ch) {
    if (*ch == '+' || *ch == '-' || *ch == '*' || *ch == '/')
        return true;
    return false;
}

int evaluatePrefix(char **exp, int n) {
    int i, first, second, temp;
    int top = -1;
    int stack[MAX_SIZE];

    for (i = n - 1; i >= 0; i--) {
        if (isOperator(exp[i])) {
            first = stack[top--];
            second = stack[top--];
            if (*exp[i] == '+') temp = first + second;
            else if (*exp[i] == '-') temp = first - second;
            else if (*exp[i] == '*') temp = first * second;
            else if (*exp[i] == '/') temp = first / second;
            stack[++top] = temp;
        } else {
            stack[++top] = atoi(exp[i]);
        }
    }
    return stack[top];
}

int main() {
    char *exp = "/ * + 5 6 3 11";
    char *token, **exp_arr;
    int i, n = 0, result;

    exp_arr = (char**)malloc(MAX_SIZE * sizeof(char*));
    token = strtok(exp, " ");
    while (token != NULL) {
        exp_arr[n++] = token;
        token = strtok(NULL, " ");
    }
    result = evaluatePrefix(exp_arr, n);
    printf("The Polish Notation is: %s\n", exp);
    printf("The Result after Evaluation is: %d\n", result);
    return 0;
}
