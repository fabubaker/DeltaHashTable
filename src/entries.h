#pragma once

#include "bitvector.h"
#include "globals.h"

/*
 *                 hkey
 * --------------------------------------
 * bucket ID - Lslot ID - Fingerprint ID
 * --------------------------------------
 * N-1 N-2 N-3 ... ... ... ... ... 2 1 0
 *
 */

typedef BitVector<32> ukey; // Assume ukey to be 32 bytes
typedef BitVector<32> payload; // Assume payload to be 32 bytes
typedef BitVector<HKEY_BITS> hkey;
