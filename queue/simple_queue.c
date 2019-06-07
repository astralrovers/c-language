#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100
#define INIT_QUEUE_POS 0

struct simple_queue
{
    int *queue;
    int queue_len;
    int queue_front;
    int queue_rear;
};

static bool is_queue_full(const struct simple_queue *queue);
static bool is_queue_empty(const struct simple_queue *queue);
static int get_queue_size(const struct simple_queue *queue);
static bool _en_queue(struct simple_queue *queue, int *data);
static void _de_queue(struct simple_queue *queue, int *data);
static void _clear_queue(struct simple_queue *queue);

static bool is_queue_full(const struct simple_queue *queue)
{
    // TODO queue is NULL

    return queue->queue_front == (queue->queue_rear + 1) % queue->queue_len;
}

static bool is_queue_empty(const struct simple_queue *queue)
{
    // TODO queue is NULL

    return queue->queue_front == queue->queue_rear;
}

static int get_queue_size(const struct simple_queue *queue)
{
    // TODO queue is NULL

    return queue->queue_len;
}

static void _de_queue(struct simple_queue *queue, int *data)
{
    // TODO queue is NULL

    if (is_queue_empty(queue))
    {
        return (void)0;
    }

    *data = queue->queue[queue->queue_front];
    queue->queue_front = (queue->queue_front + 1) % queue->queue_len;

    return (void)0;
}

static bool _en_queue(struct simple_queue *queue, int *data)
{
    // TODO queue is NULL

    if (is_queue_full(queue))
    {
        return false;
    }

    queue->queue[queue->queue_rear] = *data;
    queue->queue_rear = (queue->queue_rear + 1) % queue->queue_len;

    return true;
}

static struct simple_queue *create_simple_queue(int len)
{
    struct simple_queue *queue = (struct simple_queue*)malloc(sizeof(struct simple_queue));
    // if queue == NULL return NULL
    queue->queue = (int *)malloc(sizeof(int) * len);
    // if queue->queue == NULL return NULL

    memset(queue->queue, 0, sizeof(int) * len);
    queue->queue_len = len;
    queue->queue_front = INIT_QUEUE_POS;
    queue->queue_rear = INIT_QUEUE_POS;

    return queue;
}

static void _drop_simple_queue(struct simple_queue *queue)
{
    // if NULL == queue return

    free(queue->queue);
    queue->queue = NULL;

    free(queue);
    queue = NULL;

    return (void)0;
}

static void _clear_queue(struct simple_queue *queue)
{
    queue->queue_rear = INIT_QUEUE_POS;
    queue->queue_front = INIT_QUEUE_POS;

    return (void)0;
}

void print_queue(const struct simple_queue *queue)
{
    for (int i = queue->queue_front; i < queue->queue_rear; i++)
    {
        printf("queue[%d] = %d\n", i, queue->queue[i]);
    }

    return (void)0;
}

int main(void)
{
    struct simple_queue *queue = create_simple_queue(MAX_QUEUE_SIZE);

    int input_data[] = {3, 51, 20, 3, 1, 6, 8, 89, 34, 23};
    int ret = 0;

    for (int i = 0; i < sizeof(input_data)/sizeof(int); i++)
    {
        _en_queue(queue, &input_data[i]);
    }

    print_queue(queue);

    printf("queue len = %d\n", get_queue_size(queue));

    printf("queue is full = %s\n", is_queue_full(queue) ? "true" : "false");

    ret = 100;
    _en_queue(queue, &ret);
    print_queue(queue);

    _de_queue(queue, &ret);
    printf("out queue = %d\n", ret);
    print_queue(queue);

    _clear_queue(queue);
    printf("queue is empty = %s\n", is_queue_empty(queue) ? "true" : "false");

    _drop_simple_queue(queue);

    return 0;
}
