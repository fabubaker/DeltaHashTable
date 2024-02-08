#pragma once

#include "lslots.h"
#include "entries.h"
#include "constants.h"

struct Bucket {
  Lslots lslots;
  data *payloads[AVERAGE_NUM_ENTRIES_PER_BUCKET]; // One payload per entry

public:
  void insert(hkey hkey, data *payload);
  int get(hkey hkey); // Returns an offset into payloads array or -1
};
