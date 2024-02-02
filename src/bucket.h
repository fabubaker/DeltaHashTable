#include "entries.h"
#include "globals.h"

struct Bucket {
  char lslot_bits[BUCKET_SIZE / 8];
  payload payloads[AVERAGE_NUM_ENTRIES_PER_BUCKET]; // One payload per entry

  void insert(hkey hkey, payload payload);
  int get(hkey hkey); // Returns an offset into payloads array or -1
};
