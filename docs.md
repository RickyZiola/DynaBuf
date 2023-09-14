# DynaBuf documentation

## `DynamicBuffer(tp)`
Creates a new DynamicBuffer type.
### Parameters:
- `tp`: The data type to use in the buffer. 

### Return value:
A `struct` type for a dynamic buffer holding type `tp`

## `newDynamicBuf(tp)`
Allocates space for a new dynamic buffer.
### Parameters:
- `tp`: The data type to use with the buffer. This should match the data type of the variable you are assigning this pointer to.

### Return value:
A pointer to a new DynamicBuffer(tp)

## `initDynamicBuf(tp, buf)`
Initialize a dynamic buffer, making it empty with capacity 0.
### Parameters:
- `tp`: The type of the buffer data
- `buf`: A pointer to the buffer to initialize

### Return value:
A `DynabufErr`, this is always `ERR_OK` as nothing can go wrong in this function.

## `growDynamicBuf(tp, buf)`
Increase the capacity of a `DynamicBuffer(tp)`.  
This sets the capacity to 8 if the buffer is emtpy and doubles it otherwise.
### Parameters:
- `tp`: The type of the buffer data
- `buf`: A pointer to the buffer to grow

### Return value:
A `DynabufErr`, `ERR_OK` if the buffer grew succesfully or `ERR_INSUFFICIENT_MEM` or the allocation failed

## `writeDynamicBuf(tp, buf, addr, val)`
Write to a slot of a dynamic buffer.  
This automatically increases the capacity of the buffer if necessary.
### Parameters:
- `tp`: The type of the buffer data
- `buf`: A pointer to the buffer to write to
- `addr`: The index into `buf->data` to write to
- `val`: The value to write

### Return value:
A `DynabufErr`, `ERR_OK` if the write was succesful, `ERR_WRITE_FAILED` if the write fails, or `ERR_INSUFFICIENT_MEM` if there's an allocation error.

## `readDynamicBuf(tp, buf, addr)`
Read from a slot of a dynamic buffer.
### Parameters:
- `tp`: The type of the buffer data
- `buf`: A pointer to the buffer to read from
- `addr`: The index into `buf->data` to read from

### Return value:
The value (type `tp`) at `buf->data[addr]` or `0` if `addr > buf->capacity`

## `clearDynamicBuf(tp, buf, val)`
Sets all slots in a dynamic buffer to a value
### Parameters:
- `tp`: The type of the buffer data
- `buf`: A pointer to the buffer to clear
- `val`: The value to write to the buffer.
### Return value:
A `DynabufErr`, ERR_OK or the error from `writeDynamicBuf`