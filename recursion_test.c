#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iconv.h>
#include <locale.h>
#include <wchar.h>
#include "utility.h"
#define LEN 255

int fib(int i)
{
    if (i == 0)
        return 0;
    if (i == 1)
        return 1;
    int j = fib(i - 1) + fib(i - 2);
    return j;
}

int fib2(int i);
int fib3(int i);

int sum(int i)
{
    if (i == 0)
        return 0;
    return i + sum(i - 1);
}

int sum2(int i);

typedef struct Stack_tag
{
    int i[3];
    struct Stack_tag *next;
} Stack;

int stack_empty(Stack *stack)
{
    return stack == NULL;
}

Stack *stack_push(Stack *stack, int *i)
{
    Stack *new = (Stack *)malloc(sizeof(Stack));
    // new->i = i;
    // new->i = (int*)malloc(3 * sizeof(int));
    memcpy(new->i, i, 3 * sizeof(int));
    new->next = stack;
    return new;
}

Stack *stack_pop(Stack *stack)
{
    Stack *keep = stack->next;
    // free(stack->i);
    // stack->i = NULL;
    stack->next = NULL;
    free(stack);
    return keep;
}

int *stack_top(Stack *stack)
{
    return stack->i;
}

int main(int argc, char *argv[])
{
    printf("%d", fib2(30));
}

int sum2(int a)
{
    Stack *stack = NULL;
    while (a > 0)
    {
        stack = stack_push(stack, a);
        a--;
    }
    int i = 0;
    while (!stack_empty(stack))
    {
        i += stack_top(stack);
        stack = stack_pop(stack);
    }
    return i;
}

int fib2(int a)
{
    Stack *stack = NULL;
    int temp = -1;
    int i[3] = {a, -1, -1};
    stack = stack_push(stack, i);
    while(!stack_empty(stack))
    {
        int *top = stack_top(stack);
        if (temp != -1 && top[1] == -1)
        {
            top[1] = temp;
            temp = -1;
        }
        else if(temp != -1 && top[2] == -1)
        {
            top[2] = temp;
            temp = -1;
        }
        if (top[0] == 0)
        {
            stack = stack_pop(stack);
            temp = 0;
            continue;
        }
        else if(top[0] == 1)
        {
            stack = stack_pop(stack);
            temp = 1;
            continue;
        }
        else
        {
            int j[3] = {top[0], -1, -1};
            if (top[1] == -1)
            {
                j[0] = top[0] - 1;
                stack = stack_push(stack, j);
            }
            else if (top[2] == -1)
            {
                j[0] = top[0] - 2;                
                stack = stack_push(stack, j);
            }
            else
            {
                temp = top[1] + top[2];
                stack = stack_pop(stack);
            }
            continue;
        }
    }
    return temp;
}

int fib3(int n)
{
    int i, s;
    int s1 = 1, s2 = 1;
    for (i = 3; i <= n; ++i)
    {
        s = s1 + s2;
        s2 = s1;
        s1 = s;
    }
    return s;
}