//
// Created by ash on 23/07/23.
//

#include "webkit_applets.h"
#include "utils/logger.h"
#include "patcher/patcher.h"

void Patch_webkit_applets(uint32_t titleVer, uint64_t titleId, const rplinfo& rpls)
{
    if ((titleId == 0x00050010'1004B000 && titleVer == 65) ||
        (titleId == 0x00050010'1004B100 && titleVer == 65) ||
        (titleId == 0x00050010'1004B200 && titleVer == 65))
    {
        // libopenssl is identical between all regions
        auto rpx = FindRPL(rpls, "libopenssl.rpl");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected NNID Settings v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x0005c138), 0x40820020, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x0005c150), 0x38600000, 0x38600001);
    }
    else if ((titleId == 0x00050030'1001600A && titleVer == 113) ||
        (titleId == 0x00050030'1001610A && titleVer == 113) ||
        (titleId == 0x00050030'1001620A && titleVer == 113))
    {
        auto rpx = FindRPL(rpls, "libopenssl.rpl");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected Miiverse Applet v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x00043c80), 0x40820020, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x00043c98), 0x38600000, 0x38600001);
    }
    else if ((titleId == 0x00050030'1001400A && titleVer == 131) ||
        (titleId == 0x00050030'1001410A && titleVer == 131) ||
        (titleId == 0x00050030'1001420A && titleVer == 131))
    {
        auto rpx = FindRPL(rpls, "libopenssl.rpl");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected Nintendo eShop v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x00043c80), 0x40820020, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x00043c98), 0x38600000, 0x38600001);
    }
    else if ((titleId == 0x00050030'1001300A && titleVer == 81) ||
        (titleId == 0x00050030'1001310A && titleVer == 81) ||
        (titleId == 0x00050030'1001320A && titleVer == 81))
    {
        auto rpx = FindRPL(rpls, "libopenssl.rpl");
        if (!rpx) return;

        DEBUG_FUNCTION_LINE("Detected Nintendo TVii v%d - patching...", titleVer);
        // OpenSSL ssl_verify_cert_chain
        PatchInstruction((void*)(rpx->textAddr + 0x00042ee4), 0x40820020, 0x60000000);
        PatchInstruction((void*)(rpx->textAddr + 0x00042efc), 0x38600000, 0x38600001);
    }
}
