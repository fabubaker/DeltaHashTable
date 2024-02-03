#pragma once

#include <cstdint>
#include "constants.h"

/*
 *                 hkey
 * --------------------------------------
 * bucket ID - Lslot ID - Fingerprint ID
 * --------------------------------------
 * N-1 N-2 N-3 ... ... ... ... ... 2 1 0
 *
 */

typedef uint64_t ukey[4]; // Assume ukey to be 32 bytes
typedef uint64_t payload[4]; // Assume payload to be 32 bytes
typedef uint64_t hkey[2];

struct hkey {
  uint64_t hkey[2];


};
