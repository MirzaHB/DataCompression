#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>

uint32_t byteCompress(uint8_t *dataPtr, uint32_t dataSize);
uint8_t *byteDecompress(const uint8_t *dataPtr, uint32_t dataSize, uint32_t *decompressedSize);
void printDataArray(const char *message, const uint8_t *data, uint32_t size);

#endif
