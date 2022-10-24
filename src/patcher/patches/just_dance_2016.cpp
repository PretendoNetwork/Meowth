//
// Created by ash on 24/10/22.
//

#include "just_dance_2016.h"
#include "utils/logger.h"
#include "patcher/patcher.h"

#include <cstdint>

void Patch_just_dance_2016(uint32_t titleVer, uint64_t titleId, const rplinfo& rpls) {
    if (titleId == 0x00050000101B9800 && titleVer == 32) {
        auto rpx = FindRPL(rpls, "wiiu_ua_engine_f.rpx");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected JD2016 EUR v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x0200907c), 0x40820020, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x02009094), 0x38600000, 0x38600001);
        // OpenSSL X509_verify_cert (just in case lol)
        PatchInstruction((void*)(rpx->textAddr + 0x0203ebfc), 0x9421ffb8, 0x38600001);
        PatchInstruction((void*)(rpx->textAddr + 0x0203ec00), 0xbe410010, 0x4e800020);
    }
}
