#ifndef RINGBUF_H
#define RINGBUF_H
#include <stdint.h>
#define BUFFER_SIZE 8
#define RINGBUF_OK     0
#define RINGBUF_ERROR -1
void ringbuf_init(void);
int ringbuf_write(uint8_t data);
int ringbuf_read(uint8_t *data);
uint8_t ringbuf_count(void);
int ringbuf_is_full(void);
int ringbuf_is_empty(void);
#endif
