#include "compression.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t byteCompress(uint8_t *dataPtr, uint32_t dataSize)
{
    uint32_t readIndex = 0;
    uint32_t writeIndex = 0;

    while (readIndex < dataSize)
    {
        uint8_t currentValue = dataPtr[readIndex] & 0x7F; // make sure MSB is 0
        uint32_t count = 1;

        // count the number of times the value is repeated
        while ((readIndex + count < dataSize) &&
               (dataPtr[readIndex + count] == currentValue) &&
               (count < 255))
        {
            count++;
        }

        if (count > 1)
        {
            // MSB becomes 1 due to repitition of value
            dataPtr[writeIndex++] = currentValue | 0x80;
            dataPtr[writeIndex++] = (uint8_t)count;
            readIndex += count;
        }
        else
        {
            // value not repeated, keep value as is
            dataPtr[writeIndex++] = currentValue;
            readIndex++;
        }
    }
    return writeIndex;
}

uint8_t *byteDecompress(const uint8_t *dataPtr, uint32_t dataSize, uint32_t *decompressedSize)
{
    uint32_t readIndex = 0;
    uint32_t size = 0;

    // first pass is to calculate ammount of space to allocate on heap
    while (readIndex < dataSize)
    {
        uint8_t currentValue = dataPtr[readIndex];
        // if MSB is 1, increment the size by what the next value is
        if (currentValue & 0x80)
        {
            uint8_t count = dataPtr[readIndex + 1];
            size += count;
            readIndex += 2;
        }
        else
        {
            size += 1;
            readIndex += 1;
        }
    }

    // allocate memory on the heap for the decompressed data
    uint8_t *outputPtr = (uint8_t *)malloc(size * sizeof(uint8_t));

    // for the rare chance the memory allocation fails
    if (outputPtr == NULL)
    {
        *decompressedSize = 0;
        return NULL;
    }

    // decompress the data into the allocated buffer
    readIndex = 0;
    uint32_t writeIndex = 0;

    while (readIndex < dataSize)
    {
        uint8_t currentValue = dataPtr[readIndex];
        // if MSB is 1, the value is repeated
        if (currentValue & 0x80)
        {
            // write the value for the ammount of times its repeated
            uint8_t value = currentValue & 0x7F;
            uint8_t count = dataPtr[readIndex + 1];
            for (uint8_t i = 0; i < count; i++)
            {
                outputPtr[writeIndex++] = value;
            }
            readIndex += 2;
        }
        else
        {
            // MSB was 0 so write value only once to the buffer
            outputPtr[writeIndex++] = currentValue;
            readIndex += 1;
        }
    }

    *decompressedSize = size;
    return outputPtr;
}

void printDataArray(const char *message, const uint8_t *data, uint32_t size)
{
    printf("%s (Size: %u bytes):\n", message, size);
    for (uint32_t i = 0; i < size; i++)
    {
        printf("0x%02X ", data[i]);
        // 16 values per line for readability
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n");
}