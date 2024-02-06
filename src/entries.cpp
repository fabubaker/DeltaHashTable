#include <cstdint>
#include <cstdlib>
#include "constants.h"
#include "entries.h"

/*
 * get_lslot_id() parses and returns the lslot id bits.
 * Since it returns a uint32_t, this means that lslot id bits can
 * technically only be up to 32 bits...
 */
uint32_t hkey::get_lslot_id() {
  // First, find which half of the hkey the lslot bits are in
  uint32_t lslot_pos = (BUCKET_BITS + LSLOT_BITS) <= 64 ? 0 : 1;

  if (lslot_pos == 1) {
    // The lslot id is in the 2nd half, crash for now...
    abort();
  }

  uint64_t lslot_id = hkey[lslot_pos];

  // Get rid of the fingerprint bits in this half
  lslot_id >>= (64 - (BUCKET_BITS + LSLOT_BITS));

  // Grab only the LSLOT_BITS
  uint64_t lslot_mask = (0x1 << LSLOT_BITS) - 1;
  lslot_id &= lslot_mask;

  return lslot_id;
}
