//
// Created by ash on 24/10/22.
//

#include "just_dance.h"
#include "utils/logger.h"
#include "patcher/patcher.h"

#include <cstdint>

void Patch_just_dance(uint32_t titleVer, uint64_t titleId, const rplinfo& rpls) {
    if (titleId == 0x00050000'101B9800 && titleVer == 32) {
        auto rpx = FindRPL(rpls, "wiiu_ua_engine_f.rpx");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected JD2016 EUR v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x0200907c), 0x40820020, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x02009094), 0x38600000, 0x38600001);
        // OpenSSL X509_verify_cert (just in case lol)
        PatchInstruction((void*)(rpx->textAddr + 0x0203ebfc), 0x9421ffb8, 0x38600001);
        PatchInstruction((void*)(rpx->textAddr + 0x0203ec00), 0xbe410010, 0x4e800020);
    } else if (titleId == 0x00050000'101EAA00 && titleVer == 32) {
        auto rpx = FindRPL(rpls, "wiiu_ua_engine_f.rpx");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected JD2017 EUR v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x025755d4), 0x40820024, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x025755f0), 0x38600000, 0x38600001);
        // OpenSSL X509_verify_cert (just in case lol)
        PatchInstruction((void*)(rpx->textAddr + 0x0253e1e4), 0x9421ffb8, 0x38600001);
        PatchInstruction((void*)(rpx->textAddr + 0x0253e1e8), 0xbe21000c, 0x4e800020);
    } else if (titleId == 0x00050000'10210C00 && titleVer == 0) {
        auto rpx = FindRPL(rpls, "wiiu_ua_engine_f.rpx");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected JD2018 EUR v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x024f8d08), 0x40820024, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x024f8d24), 0x38600000, 0x38600001);
        // OpenSSL X509_verify_cert (just in case lol)
        PatchInstruction((void*)(rpx->textAddr + 0x02537ca0), 0x9421ffb8, 0x38600001);
        PatchInstruction((void*)(rpx->textAddr + 0x02537ca4), 0xbe21000c, 0x4e800020);
    }
}
