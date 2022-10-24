#include "patcher.h"

#include "utils/logger.h"

#include <kernel/kernel.h>
#include <coreinit/memorymap.h>
#include <coreinit/cache.h>

bool replace_string(uint32_t start, uint32_t size, const char* original_val, size_t original_val_sz, const char* new_val, size_t new_val_sz) {
    for (uint32_t addr = start; addr < start + size - original_val_sz; addr++) {
        int ret = memcmp(original_val, (void*)addr, original_val_sz);
        if (ret == 0) {
            DEBUG_FUNCTION_LINE("found str @%08x: %s", addr, (const char*)addr);
            KernelCopyData(OSEffectiveToPhysical(addr), OSEffectiveToPhysical((uint32_t)new_val), new_val_sz);
            DEBUG_FUNCTION_LINE("new str   @%08x: %s", addr, (const char*)addr);
            return true;
        }
    }

    return false;
}

bool PatchInstruction(void* instr, uint32_t original, uint32_t replacement) {
    uint32_t current = *(uint32_t*)instr;
    if (current != original) {
        DEBUG_FUNCTION_LINE("Was given wrong instruction %08x, found %08x!", original, current);
        return current == replacement;
    }

    KernelCopyData(OSEffectiveToPhysical((uint32_t)instr), OSEffectiveToPhysical((uint32_t)&replacement), sizeof(replacement));
    //Only works on AROMA! WUPS 0.1's KernelCopyData is uncached, needs DCInvalidate here instead
    DCFlushRange(instr, 4);
    ICInvalidateRange(instr, 4);

    current = *(uint32_t*)instr;
    DEBUG_FUNCTION_LINE("patched instruction %08x -> %08x", original, current);

    return true;
}
