#include "entries.h"
#include "constants.h"
#include "bitvector.h"

/*
 * Defines the basic Lslot structure.
 * NOTE: Lslots do not interleave structure and indices like in the paper.
 */

struct Lslots {
  BitVector<BUCKET_SIZE> bits; // Lslots are a bunch of bits anyways...

  /*
   * @param fp The fingerprint to match within the lslot
   * @param start The starting position of the lslot in the bitvector
   */
  uint32_t get_lslot_offset(__uint128_t fp, position_t start);
};
