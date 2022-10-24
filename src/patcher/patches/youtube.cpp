//
// Created by ash on 24/10/22.
//

#include "youtube.h"
#include "utils/logger.h"
#include "patcher/patcher.h"

#include <cstdint>

void Patch_youtube(uint32_t titleVer, uint64_t titleId, const rplinfo& rpls) {
    if (titleId == 0x0005000010105700 && titleVer == 193) {
        auto rpx = FindRPL(rpls, "lb_shell.rpx");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected YouTube ALL v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x8dfdbc), 0x40820020, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x8dfdd4), 0x38600000, 0x38600001);
        // OpenSSL X509_verify_cert (called by cert_verify_proc_openssl.cc)
        PatchInstruction((void*)(rpx->textAddr + 0x9208e8), 0x9421ffb8, 0x38600001);
        PatchInstruction((void*)(rpx->textAddr + 0x9208ec), 0xbe410010, 0x4e800020);
    }
}
