/*  Copyright 2022 Pretendo Network contributors <pretendo.network>
    Copyright 2022 Ash Logan <ash@heyquark.com>

    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby
    granted, provided that the above copyright notice and this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
    INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
    IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
    PERFORMANCE OF THIS SOFTWARE.
*/

#include "rplinfo.h"

#include "utils/logger.h"
#include "patcher/patcher.h"

#include <kernel/kernel.h>

std::optional<std::vector<OSDynLoad_NotifyData>> TryGetRPLInfo() {
    int num_rpls = OSDynLoad_GetNumberOfRPLs();
    if (num_rpls == 0) {
        return std::nullopt;
    }

    DEBUG_FUNCTION_LINE("num_rpls: %d", num_rpls);

    std::vector<OSDynLoad_NotifyData> rpls;
    rpls.resize(num_rpls);

    bool ret = OSDynLoad_GetRPLInfo(0, num_rpls, rpls.data());
    if (!ret) {
        return std::nullopt;
    }

    return rpls;
}

bool PatchDynLoadFunctions() {
    uint32_t *patch1 = ((uint32_t *) &OSDynLoad_GetNumberOfRPLs) + 6;
    uint32_t *patch2 = ((uint32_t *) &OSDynLoad_GetRPLInfo) + 22;

    if (!PatchInstruction(patch1, 0x41820038 /* beq +38 */, 0x60000000 /*nop*/)) {
        return false;
    }
    if (!PatchInstruction(patch2, 0x41820100 /* beq +100 */, 0x60000000 /*nop*/)) {
        return false;
    }

    return true;
}
