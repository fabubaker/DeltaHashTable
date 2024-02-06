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
  __uint128_t lslot_id = hkey;

  // Get rid of fingerprint bits
  lslot_id >>= (128 - (BUCKET_BITS + LSLOT_BITS));

  // Grab only the LSLOT_BITS
  uint64_t lslot_mask = (0x1 << LSLOT_BITS) - 1;
  lslot_id &= lslot_mask;

  return lslot_id;
}
