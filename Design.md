## Running the program
- To Compile the program ```make```
- To run the program ```./compressProgram```
- To clean up object files and executable ```make clean```

## Given Details
- Values in the data buffer from 0-127
- the values in the data array are all 1 byte (8 bits)
- data buffer is to be modified so all the data in it is compressed
  
## Things I assumed

- The most significant bit (MSB) in all the values of the data array are not used
- the types of values in the data buffer are all unsigned 8 bit integers
- the size of the data buffer can not grow (wouldnt make sense anyways)

## Compression algorithm
- If the value in the data buffer is repeated than make the values MSB 1 to indicate the value is repeated in series more than once
- if the MSB of a value is 1, it means there is a relationship between the current value and the very next one
  - if MSB of value is 1 the very next byte will hold the number of times the value (stored in the lower 7 bits) is repeated in series
- if the value is not repeated, than it is kept as is

#### Edge cases
A Value is repeated more than 255 times in series:
- a new entry is created, so the value with the MSB is copied over and the number of times it repeated after the 255 times is stored in the next byte

Ex:
- 0x00 is repeated 510 times:
  - four 8 bit unsigned integer entries are used to compress the 0x00 value which was repeated 510 times
  - When compressed the four values would be 0x80,0xFF,0x80,0xFF

## Decompression Algorithm
- function takes in:
  - pointer to the array with the compressed data
  - size of the array with the compressed data
  - a pointer to an unsigned integer to be set to how big the decompressed data is at the end
- first calculate how big the data will be when decompressed
- allocate that ammount of memory onto the heap just once
  - knowing the ammount of memory to allocate on the heap from the start will allow us to avoid extra system calls by not having to reallocate more memory as we decompress the data
- decompress the data:
  - if the current value has 1 as the MSB, write the value stored in the lower 7 bits x many times where x is the value stored in the very next byte
  - if the MSB of the current value is 0 then copy the value as is
- set the size of the decompressed data
- returns a pointer to the array on the heap with the decompressed data

## Extra details
- size of all values must be 1 byte
- worst case scenario: Data is not able to be decompressed and the size remains the same (when every entry is not repeated in series)
- best case scenario: 1 value is repeated 255 times (2 bytes to compress it all) 
