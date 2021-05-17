_group = {
  {
    group_size = 3,
    pattern = "LLS",
    opcodes = "MOVUPS,MOVUPS,MOVUPS,",
    offsets = "0,0,0,",
    addresses = "0x13a8,0x13ae,0x13ca,",
    stride_status = "Success",
    stride = 16,
    memory_status = "Success",
    accessed_memory = 48,
    accessed_memory_nooverlap = 16,
    accessed_memory_overlap = 32,
    span = 16,
    head = 16,
    unroll_factor = 1,
  },
  {
    group_size = 2,
    pattern = "LL",
    opcodes = "PADDD,PADDD,",
    offsets = "3249,3257,",
    addresses = "0x13b7,0x13bf,",
    stride_status = "RIP based value",
    stride = 0,
    memory_status = "Success",
    accessed_memory = 32,
    accessed_memory_nooverlap = 24,
    accessed_memory_overlap = 8,
    span = 24,
    head = 0,
    unroll_factor = 2,
  },
}