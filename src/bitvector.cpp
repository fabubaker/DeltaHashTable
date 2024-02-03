#include "bitvector.h"
#include <cstdint>

template <uint32_t numBits>
std::vector<uint8_t> BitVector<numBits>::get_bits_in_range(uint32_t start, uint32_t end) {
  uint32_t output_size = bits_to_bytes(end - start);

  // Create a vector to hold the output
  std::vector<uint8_t> output(output_size);

  // Calculate the start and end byte relative to array indexing
  // (leftmost is 0, rightmost is size() - 1)
  uint32_t start_byte_index = (size() - 1) - (start / 8);
  uint32_t end_byte_index = (size() - 1) - (end / 8);

  // Calculate the start and end bit relative to byte indexing
  // (leftmost is 7, rightmost is 0)
  uint32_t start_bit_index = start % 8;
  uint32_t end_bit_index = end % 8;

  if (start_byte_index == end_byte_index) {
    // Extract the desired bits from the same byte
    uint8_t byte = data[start_byte_index];

    byte <<= (7 - end_bit_index + 1); // Remember, end is not inclusive
    byte >>= (7 - end_bit_index + 1) + start_bit_index;

    output[0] = byte; // output consists of only one byte...
  } else {
    uint32_t output_byte_index = output_size - 1;

    // Extract the desired bits from the start byte
    uint32_t current_byte_index = start_byte_index;
    uint8_t current_byte = data[current_byte_index];
    current_byte >>= start_bit_index;
    uint32_t remaining_bits = (8 - start_bit_index) % 8;

    // Extract the remaining bits from the next byte
    uint32_t next_byte_index = start_byte_index - 1;
    uint32_t next_byte = data[next_byte_index];
    next_byte <<= remaining_bits;

    // Merge data from both bytes
    output[current_byte_index] = next_byte | current_byte;

    current_byte_index = next_byte_index;
    next_byte_index = next_byte_index - 1;

    // Careful, we're looping in reverse here due to array indexing...
  }

  return output;
}
