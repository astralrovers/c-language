#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define INIT_STACK_POS -1

struct simple_stack
{
    int *stack;
    int stack_len;
    int stack_top_pos;
};

static bool is_stack_full(const struct simple_stack *stack);
static bool is_stack_empty(const struct simple_stack *stack);
static int get_stack_top_pos(const struct simple_stack *stack);
static int get_stack_size(const struct simple_stack *stack);
static bool get_top(const struct simple_stack *stack, int *data);
static bool _pop(struct simple_stack *stack, int *data);
static void _push(struct simple_stack *stack, int *data);

static bool is_stack_full(const struct simple_stack *stack)
{
    // TODO stack is NULL

    return stack->stack_len == stack->stack_top_pos + 1;
}

static bool is_stack_empty(const struct simple_stack *stack)
{
    // TODO stack is NULL

    return stack->stack_top_pos == INIT_STACK_POS;
}

static int get_stack_top_pos(const struct simple_stack *stack)
{
    // TODO stack is NULL

    return stack->stack_top_pos;
}

static int get_stack_size(const struct simple_stack *stack)
{
    // TODO stack is NULL

    return stack->stack_len;
}

static bool get_top(const struct simple_stack *stack, int *data)
{
    // TODO stack is NULL

    if (is_stack_empty(stack))
    {
        return false;
    }

    *data = stack->stack[stack->stack_top_pos];

    return true;
}

static bool _pop(struct simple_stack *stack, int *data)
{
    // TODO stack is NULL

    if (is_stack_empty(stack))
    {
        return false;
    }

    *data = stack->stack[stack->stack_top_pos];
    stack->stack_top_pos--;

    return true;
}

static void _push(struct simple_stack *stack, int *data)
{
    // TODO stack is NULL

    if (is_stack_full(stack))
    {
        return (void)0;
    }

    stack->stack_top_pos++;
    stack->stack[stack->stack_top_pos] = *data;

    return (void)0;
}

static struct simple_stack *create_simple_stack(int len)
{
    struct simple_stack *stack = (struct simple_stack*)malloc(sizeof(struct simple_stack));
    // if stack == NULL return NULL
    stack->stack = (int *)malloc(sizeof(int) * len);
    // if stack->stack == NULL return NULL

    memset(stack->stack, 0, sizeof(int) * len);
    stack->stack_len = len;
    stack->stack_top_pos = INIT_STACK_POS;

    return stack;
}

static void _drop_simple_stack(struct simple_stack *stack)
{
    // if NULL == stack return

    free(stack->stack);
    stack->stack = NULL;

    free(stack);
    stack = NULL;

    return (void)0;
}

void print_stack(const struct simple_stack *stack)
{
    for (int i = 0; i <= stack->stack_top_pos; i++)
    {
        printf("stack[%d] = %d\n", i, stack->stack[i]);
    }

    return (void)0;
}

int main(void)
{
    struct simple_stack *stack = create_simple_stack(MAX_STACK_SIZE);

    int input_data[] = {3, 51, 20, 3, 1, 6, 8, 89, 34, 23};
    int ret = 0;

    for (int i = 0; i < sizeof(input_data)/sizeof(int); i++)
    {
        _push(stack, &input_data[i]);
    }

    print_stack(stack);

    printf("stack len = %d\n", get_stack_size(stack));
    printf("stack top_pos = %d\n", get_stack_top_pos(stack));

    get_top(stack, &ret);
    printf("stack top = %d\n", ret);

    printf("stack empty : %s\n", is_stack_empty(stack) ? "true" : "false");
    printf("stack full : %s\n", is_stack_full(stack) ? "true" : "false");

    _pop(stack, &ret);
    printf("stack pop = %d\n", ret);
    printf("stack top_pos = %d\n", get_stack_top_pos(stack));

    ret = 100;
    _push(stack, &ret);
    get_top(stack, &ret);
    printf("stack top = %d\n", ret);
    printf("stack top_pos = %d\n", get_stack_top_pos(stack));

    _drop_simple_stack(stack);

    return 0;
}
