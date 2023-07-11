//
// Created by rambo on 11/07/23.
//

#include "watch_dogs.h"
#include "utils/logger.h"
#include "patcher/patcher.h"

#include <cstdint>

void Patch_watch_dogs(uint32_t titleVer, uint64_t titleId, const rplinfo& rpls) {
    if (titleId == 0x00050000'10140500 && titleVer == 0) {
        auto rpx = FindRPL(rpls, "duniademo.rpx");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected WATCH_DOGS EUR v%d - patching...", titleVer);
        // Disable Proxy CURL settings (use current connection settings)
        PatchInstruction((void*)(rpx->textAddr + 0x04A3B4EC), 0x7C0802A6, 0x38600001);
        PatchInstruction((void*)(rpx->textAddr + 0x04A3B4F0), 0x9421FFE8, 0x4E800020);
        // Disable NSSL verify nlibcurl
        PatchInstruction((void*)(rpx->textAddr + 0x04A3B8F8), 0x38000007, 0x38000000);
    }
}
