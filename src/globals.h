#define HKEY_BITS (128) // In the paper, hkeys are 16 bytes

#define BUCKET_BITS (8)
#define LSLOT_BITS (8)
#define FINGERPRINT_BITS (HKEY_BITS - BUCKET_BITS - LSLOT_BITS)

#define NUM_BUCKETS (1UL << BUCKET_BITS)
#define NUM_LSLOTS (1UL << LSLOT_BITS)

#define ALLOTTED_BITS_PER_ENTRY (4)
#define AVERAGE_NUM_ENTRIES_PER_LSLOT (1)
#define AVERAGE_NUM_ENTRIES_PER_BUCKET (AVERAGE_NUM_ENTRIES_PER_LSLOT * NUM_LSLOTS)

/* For eg, say we have:
 * - ALLOTTED_BITS_PER_ENTRY = 4
 * - AVERAGE_NUM_ENTRIES_PER_LSLOT = 1
 * - NUM_LSLOTS = 1024
 *
 * Then:
 * - BUCKET_SIZE = 4 * 1 * 1024 = 4096
 */
#define BUCKET_SIZE (ALLOTTED_BITS_PER_ENTRY * AVERAGE_NUM_ENTRIES_PER_LSLOT * NUM_LSLOTS)
#define MAX_LSLOT_SIZE (BUCKET_SIZE) // Since an lslot can technically occupy a whole bucket

