add_library(
  bucket OBJECT
  bucket.h bucket.cpp
  entries.h entries.cpp
  lslots.h lslots.cpp
  bitvector.h bitvector.cpp
)

target_compile_options(bucket PRIVATE "-mbmi2")
