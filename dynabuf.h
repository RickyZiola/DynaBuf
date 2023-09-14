#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "errcode.h"

/**

 * Creates a new DynamicBuffer type. This can hold up to 4294967296 slots of data.
 *
 * @param tp The type to use for the data in the buffer.
 * 
 * @retval A struct representing the buffer type.

 */
#define DynamicBuffer(tp) \
struct {                  \
    tp *data;             \
    uint32_t capacity; }

typedef DynamicBuffer(uint8_t)   DynamicByteBuffer;
typedef DynamicBuffer(uint16_t) DynamicShortBuffer;

typedef uint8_t byte;

/**
 
 * Allocates space for a new dynamic buffer
 *
 * @param tp The type of the buffer data
 * 
 * @retval A pointer to the buffer

 */
#define newDynamicBuf(tp) ((DynamicBuffer(tp))malloc(sizeof(DynamicBuffer(tp))))

/**

 * Sets up the fields of a new dynamic buffer
 *
 * @param tp The type of the buffer data
 * @param buf A pointer to the buffer to be initialized
 * 
 * @retval ERR_OK, there is no possible error in this function

 */
#define initDynamicBuf(tp, buf) ({               \
    (buf)->data = NULL;                          \
    (buf)->capacity = 0; ERR_OK; })


/**

 * Expands the capacity of a dynamic buffer. If the buffer's capacity is 0 (empty) it allocates 8 slots. Otherwise, it doubles the number of allocated slots.
 *
 * @param tp The type of the buffer data
 * @param buf A pointer to the buffer to be grown
 * 
 * @retval A DynabufErr, ERR_OK or ERR_INSUFFICIENT_MEM

 */
#define growDynamicBuf(tp, buf) ({                                        \
    (buf)->capacity = ((buf)->capacity == 0) ? 8 : (2 * (buf)->capacity); \
    ((((buf)->data = realloc((buf)->data, (buf)->capacity * sizeof(tp))) == NULL) ? ERR_INSUFFICIENT_MEM : ERR_OK); })


/**

 * Write to a slot of a dynamic buffer. This automatically grows the buffer if `addr` is out of the buffer's range
 *
 * @warning Writing to a high address may cause allocation of large amounts of memory.
 * 
 * @param tp The type of the buffer data
 * @param buf A pointer to the buffer to write to
 * @param addr The index into `buf->data` to write to
 * @param vad The value to write
 * 
 * @retval A DynabufErr, ERR_OK or the allocation error from `growDynamicBuf`

 */
#define writeDynamicBuf(tp, buf, addr, val) ({    \
    DynabufErr allocErr = ERR_OK;               \
    while ((addr) >= (buf)->capacity) {           \
        allocErr = growDynamicBuf(tp, buf);       \
        if (allocErr != ERR_OK) break;            \
    }                                             \
    DynabufErr finalErr = ERR_OK;               \
    if (allocErr == ERR_OK) {                     \
        (buf)->data[addr] = (tp)(val);            \
        if ((tp)((buf)->data[addr]) != (tp)(val)) \
            finalErr = ERR_FAILED_WRITE;          \
    } else {                                      \
        finalErr = allocErr;                      \
    } finalErr; })

/**

 * Read from a slot of a dynamic buffer.
 *
 * @param tp The type of the buffer data
 * @param buf A pointer to the buffer to read from
 * @param addr The index into `buf->data` to write to
 * 
 * @retval The data at `buf->data[addr]` or 0 if `addr` is greater than `buf->capacity`

 */
#define readDynamicBuf(tp, buf, addr) (((addr) >= (buf)->capacity) ? ((tp) 0) : ((tp) ((buf)->data[addr])))

/**

 * Sets all slots of a dynamic buffer to a value
 *
 * @param tp The type of the buffer data
 * @param buf A pointer to the buffer to clear
 * @param val The value to write to `buf`
 * 
 * @retval ERR_OK or a write error from `writeDynamicBuf`

 */
#define clearDynamicBuf(tp, buf, val) ({                      \
    DynabufErr err = ERR_OK;                                \
    for (int addr = 0; addr < (buf)->capacity; ++addr) {      \
        if ((err = writeDynamicBuf(tp, buf, addr, val)) \
            != ERR_OK) break;                                 \
    } err; })
