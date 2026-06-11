#include <stdio.h>
#include <stdint.h>
#include "ringbuf.h"
int main(void)
{
    uint8_t data;
    uint8_t write_data[] =
    {
        0x41, 0x42, 0x43, 0x44,
        0x45, 0x46, 0x47, 0x48
    };

    int i;

    ringbuf_init();

    printf("=== Ring Buffer Demo ===\n\n");

    for (i = 0; i < 8; i++)
    {
        if (ringbuf_write(write_data[i]) == RINGBUF_OK)
        {
            printf("[WRITE] 0x%02X -> OK (count=%u)\n",
                   write_data[i],
                   ringbuf_count());
        }
    }

    if (ringbuf_is_full())
    {
        printf("Buffer FULL\n");
    }

    if (ringbuf_write(0x99) == RINGBUF_ERROR)
    {
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");
    }

    for (i = 0; i < 3; i++)
    {
        if (ringbuf_read(&data) == RINGBUF_OK)
        {
            printf("[READ ] -> 0x%02X (count=%u)\n",
                   data,
                   ringbuf_count());
        }
    }

    if (ringbuf_write(0x49) == RINGBUF_OK)
    {
        printf("[WRITE] 0x49 -> OK (count=%u)\n",
               ringbuf_count());
    }

    if (ringbuf_write(0x4A) == RINGBUF_OK)
    {
        printf("[WRITE] 0x4A -> OK (count=%u)\n",
               ringbuf_count());
    }

    if (ringbuf_write(0x4B) == RINGBUF_OK)
    {
        printf("[WRITE] 0x4B -> OK (count=%u)\n",
               ringbuf_count());
    }

    while (!ringbuf_is_empty())
    {
        ringbuf_read(&data);

        printf("[READ ] -> 0x%02X (count=%u)\n",
               data,
               ringbuf_count());
    }

    if (ringbuf_read(&data) == RINGBUF_ERROR)
    {
        printf("[READ ] EMPTY -> FAIL (buffer empty)\n");
    }

    return 0;
}
