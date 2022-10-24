#ifndef INKAY_PATCHER_H
#define INKAY_PATCHER_H

#include <cstdint>
#include <cstdlib>

bool replace_string(uint32_t start, uint32_t size, const char* original_val, size_t original_val_sz, const char* new_val, size_t new_val_sz);

bool PatchInstruction(void* instr, uint32_t original, uint32_t replacement);

#endif //INKAY_PATCHER_H
