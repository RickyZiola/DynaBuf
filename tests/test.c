#include <stdio.h>
#include <assert.h>
#include "../dynabuf.h"  // Replace with the actual header file name

// Test function to check if a buffer is initialized correctly
void test_initialize_buffer() {
    DynamicByteBuffer* buf = newDynamicBuf(byte);
    assert(buf != NULL);
    initDynamicBuf(byte, buf);
    assert(buf->data == NULL);
    assert(buf->capacity == 0);
    freeDynamicBuf(byte, buf);
}

// Test function to check if a buffer can be grown
void test_grow_buffer() {
    DynamicByteBuffer* buf = newDynamicBuf(byte);
    initDynamicBuf(byte, buf);
    growDynamicBuf(byte, buf);
    assert(buf->capacity == 8);  // Initial capacity is 0, so it should grow to 8
    freeDynamicBuf(byte, buf);
}

// Test function to write and read from the buffer
void test_write_read_buffer() {
    DynamicByteBuffer* buf = newDynamicBuf(byte);
    initDynamicBuf(byte, buf);
    
    // Write and read a value
    writeDynamicBuf(byte, buf, 0, 42);
    byte val = readDynamicBuf(byte, buf, 0);
    assert(val == 42);

    // Try to read from an out-of-range address, should return 0
    val = readDynamicBuf(byte, buf, 100);
    assert(val == 0);

    freeDynamicBuf(byte, buf);
}

// Test function to clear the buffer
void test_clear_buffer() {
    DynamicByteBuffer* buf = newDynamicBuf(byte);
    initDynamicBuf(byte, buf);
    
    // Write a value and then clear the buffer
    writeDynamicBuf(byte, buf, 0, 42);
    clearDynamicBuf(byte, buf, 0);
    
    // Reading from the cleared buffer should return 0
    byte val = readDynamicBuf(byte, buf, 0);
    assert(val == 0);

    freeDynamicBuf(byte, buf);
}

int main() {
    // Run the test functions
    test_initialize_buffer();
    test_grow_buffer();
    test_write_read_buffer();
    test_clear_buffer();

    printf("All tests passed!\n");
    return 0;
}
