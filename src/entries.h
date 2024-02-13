#pragma once

#include <cstdint>
#include "constants.h"

/*
 *                 hkey
 * --------------------------------------
 * bucket ID - Lslot ID - Fingerprint
 * --------------------------------------
 * N-1 N-2 N-3 ... ... ... ... ... 2 1 0
 *
 */

typedef uint64_t ukey[4]; // Assume ukey to be 32 bytes

struct hkey {
  __uint128_t hkey; // hkeys are defined to be 16 bytes

  uint32_t get_bucket_id();
  uint32_t get_lslot_id();
  __uint128_t get_fingerprint();
};

/*
 * Simulate storing data entries on disk.
 * For now, keep them in memory.
 * Thus, payloads are just pointers to data structs.
 */
struct data {
  ukey user_key;
  hkey hash_key;
  int value;
};

uint32_t inline get_bit_at_index(__uint128_t fp, uint32_t idx) {
  return 0x1 & (fp << idx >> 127);
}
