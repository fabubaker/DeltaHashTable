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

uint32_t Lslots::get_lslot_offset(__uint128_t fp, position_t start) {
  position_t cur_idx = start;


}
