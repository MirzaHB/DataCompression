#include "compression.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    uint8_t dataPtr[] = {
        0x03, 0x74, 0x04, 0x04, 0x04, 0x35, 0x35, 0x64,
        0x64, 0x64, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x56, 0x45, 0x56, 0x56, 0x56, 0x09, 0x09, 0x09};
    uint32_t dataSize = sizeof(dataPtr) / sizeof(dataPtr[0]);

    // print the original data in the buffer
    printDataArray("Original Data", dataPtr, dataSize);

    // compress the data
    uint32_t compressedSize = byteCompress(dataPtr, dataSize);

    // print the compressed data
    printDataArray("Compressed Data", dataPtr, compressedSize);

    // decompress the data
    uint32_t decompressedSize = 0;
    uint8_t *decompressedData = byteDecompress(dataPtr, compressedSize, &decompressedSize);

    if (decompressedData == NULL)
    {
        printf("Error: Decompression failed.\n");
        return 1;
    }

    // print decompressed data array
    printDataArray("Decompressed Data", decompressedData, decompressedSize);

    // free the memory on the heap
    free(decompressedData);

    return 0;
}