#include <stdio.h>
#include <stdbool.h>
#include <string.h>
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}
void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}
char pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return '\0';
}
bool areParenthesesBalanced(char* exp) {
    struct Stack* stack = createStack(strlen(exp));

    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
            push(stack, exp[i]);
        } else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
            if (isEmpty(stack)) {
                return false; 
            }
            char popped = pop(stack);
            if ((exp[i] == ')' && popped != '(') ||
                (exp[i] == ']' && popped != '[') ||
                (exp[i] == '}' && popped != '{')) {
                return false; 
            }
        }
    }

    return isEmpty(stack); 
}

int main() {
    char expression[100];

    printf("Enter a sequence of parentheses: ");
    scanf("%s", expression);

    if (areParenthesesBalanced(expression)) {
        printf("Parentheses are balanced it is a valid stack.\n");
    } else {
        printf("Parentheses are not balanced it is not a valid stack.\n");
    }

    return 0;
}
