#include "entries.h"
#include "constants.h"
#include "bitvector.h"

/*
 * Defines the basic Lslot structure.
 * NOTE: Lslots do not interleave structure and indices like in the paper.
 */

struct Lslots {
  BitVector bits; // Lslots are a bunch of bits anyways...

  /*
   * Returns the immediate index after the lslot at 'start'
   */
  position_t skip_lslot(position_t start);

  /*
   * @param lslot_id The lslot id to retrieve
   */
  position_t get_lslot_start(count_t lslot_id);

  /*
   * @param fp The fingerprint to match within the lslot
   * @param start The starting position of the lslot in the bitvector
   */
  uint32_t get_lslot_offset(__uint128_t fp, position_t start);
};
