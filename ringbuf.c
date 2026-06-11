#include "ringbuf.h"

static uint8_t buffer[BUFFER_SIZE];
static uint8_t head;
static uint8_t tail;
static uint8_t count;

void ringbuf_init(void)
{
    head = 0;
    tail = 0;
    count = 0;
}

int ringbuf_write(uint8_t data)
{
    if (ringbuf_is_full())
    {
        return RINGBUF_ERROR;
    }

    buffer[head] = data;

    head = (head + 1) & (BUFFER_SIZE - 1);

    count++;

    return RINGBUF_OK;
}

int ringbuf_read(uint8_t *data)
{
    if (ringbuf_is_empty())
    {
        return RINGBUF_ERROR;
    }

    *data = buffer[tail];
    tail = (tail + 1) & (BUFFER_SIZE - 1);

    count--;

    return RINGBUF_OK;
}

uint8_t ringbuf_count(void)
{
    return count;
}

int ringbuf_is_full(void)
{
    return (count == BUFFER_SIZE);
}

int ringbuf_is_empty(void)
{
    return (count == 0);
}
