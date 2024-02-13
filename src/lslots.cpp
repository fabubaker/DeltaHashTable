#include "lslots.h"

position_t Lslots::skip_lslot(position_t start) {
  position_t offset = start;
  count_t len = bits.parse_unary(start);

  offset += len + 1; // Skip over 'tenancy' bits
  offset += 2 * (len - 2); // Skip over 'structure' bits
  offset = bits.skip_indices_field(offset, len - 1);

  return offset;
}

position_t Lslots::get_lslot_start(count_t lslot_id) {
  position_t start = 0;

  for (count_t cur_lslot_id = 0; cur_lslot_id < lslot_id; cur_lslot_id++) {
    start = skip_lslot(start);
  }

  return start;
}

int32_t Lslots::get_lslot_offset(__uint128_t fp, position_t start) {
  count_t size = bits.parse_unary(start);

  if (size == 0) return -1;

  uint32_t skip = 0;
  uint32_t offset = 0;
  int32_t index = -1;
  bool found = false;

  position_t structure_pos = start + (size + 1);
  position_t indices_pos = structure_pos + 2 * (size - 2);

  for (uint32_t i = 0; i < size - 1; i++) {
    count_t structure = (i == size - 2) ? 0b00 : bits.parse_two_structure_bits(structure_pos);
    count_t index_delta = bits.parse_unary(indices_pos);

    structure_pos += 2;
    indices_pos += index_delta + 1;

    if (skip == 0 && !found) {
      index += index_delta + 1;

      if (get_bit_at_index(fp, index) == 1) {
        if (structure == 0b11 || structure == 0b10) {
          skip++;
        } else if (structure == 0b01) {
          offset++;
        } else if (structure == 0b00) {
          offset++;
          found = true;
        }
      } else {
        if (structure == 0b01 || structure == 0b00) {
          found = true;
        }
      }
    } else if (skip > 0 && !found) {
      skip--;

      if (structure == 0b11) {
        skip += 2;
      } else if (structure == 0b01 || structure == 0b10) {
        offset++;
        skip++;
      } else if (structure == 0b00) {
        offset += 2;
      }
    }
  }

  return offset;
}
