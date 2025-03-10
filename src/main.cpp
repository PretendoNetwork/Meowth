/*  Copyright 2022 Pretendo Network contributors <pretendo.network>
    Copyright 2022 Ash Logan <ash@heyquark.com>
    Copyright 2019 Maschell

    Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby
    granted, provided that the above copyright notice and this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
    INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
    IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
    PERFORMANCE OF THIS SOFTWARE.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wups.h>
#include <coreinit/mcp.h>
#include <utils/logger.h>
#include "patcher/ingame.h"

/**
    Mandatory plugin information.
    If not set correctly, the loader will refuse to use the plugin.
**/
WUPS_PLUGIN_NAME("Meowth");
WUPS_PLUGIN_DESCRIPTION("SSL Patcher");
WUPS_PLUGIN_VERSION("v0.1");
WUPS_PLUGIN_AUTHOR("quarky + Pretendo contributors");
WUPS_PLUGIN_LICENSE("ISC");

#include <kernel/kernel.h>
#include <mocha/mocha.h>

static bool is555(MCPSystemVersion version) {
    return (version.major == 5) && (version.minor == 5) && (version.patch >= 5);
}

INITIALIZE_PLUGIN() {
    WHBLogUdpInit();
    WHBLogCafeInit();

    auto res = Mocha_InitLibrary();

    if (res != MOCHA_RESULT_SUCCESS) {
        DEBUG_FUNCTION_LINE("Mocha init failed with code %d!", res);
        return;
    }

    //get os version
    MCPSystemVersion os_version;
    int mcp = MCP_Open();
    int ret = MCP_GetSystemVersion(mcp, &os_version);
    if (ret < 0) {
        DEBUG_FUNCTION_LINE("getting system version failed (%d/%d)!", mcp, ret);
        os_version = (MCPSystemVersion) {
                .major = 5, .minor = 5, .patch = 5, .region = 'E'
        };
    }
    DEBUG_FUNCTION_LINE("Running on %d.%d.%d%c",
        os_version.major, os_version.minor, os_version.patch, os_version.region
    );

    // IOS-NSEC SSL patch
    if (is555(os_version)) {
        Mocha_IOSUKernelWrite32(0xE1019F78, 0xE3A00001); // mov r0, #1
    } else {
        Mocha_IOSUKernelWrite32(0xE1019E84, 0xE3A00001); // mov r0, #1
    }

    MCP_Close(mcp);
}
DEINITIALIZE_PLUGIN() {
    WHBLogUdpDeinit();
    Mocha_DeInitLibrary();
}

ON_APPLICATION_START() {
    WHBLogUdpInit();
    WHBLogCafeInit();
    RunPatcher();
}

// Try to hook the webkit applets fairly early - wish there was a better way to do this...

DECL_FUNCTION(int, FSOpenFile_miiverse, FSClient *client, FSCmdBlock *block, const char *path, const char *mode, uint32_t *handle, int errorMask) {
    const char *oma = "vol/content/preload.oma";

    if (strcmp(oma, path) == 0)
    {
        WHBLogUdpInit();
        RunPatcher();
    }

    return real_FSOpenFile_miiverse(client, block, path, mode, handle, errorMask);
}
WUPS_MUST_REPLACE_FOR_PROCESS(FSOpenFile_miiverse, WUPS_LOADER_LIBRARY_COREINIT, FSOpenFile, WUPS_FP_TARGET_PROCESS_MIIVERSE);

DECL_FUNCTION(int, FSOpenFile_tvii, FSClient *client, FSCmdBlock *block, const char *path, const char *mode, uint32_t *handle, int errorMask) {
    const char *oma = "/vol/content/skin/Skin.dat";

    if (strcmp(oma, path) == 0)
    {
        WHBLogUdpInit();
        RunPatcher();
    }

    return real_FSOpenFile_tvii(client, block, path, mode, handle, errorMask);
}
WUPS_MUST_REPLACE_FOR_PROCESS(FSOpenFile_tvii, WUPS_LOADER_LIBRARY_COREINIT, FSOpenFile, WUPS_FP_TARGET_PROCESS_TVII);

DECL_FUNCTION(int, FSOpenFile_eshop, FSClient *client, FSCmdBlock *block, const char *path, const char *mode, uint32_t *handle, int errorMask) {
    const char *oma = "vol/content/preload.oma";

    if (strcmp(oma, path) == 0)
    {
        WHBLogUdpInit();
        RunPatcher();
    }

    return real_FSOpenFile_eshop(client, block, path, mode, handle, errorMask);
}
WUPS_MUST_REPLACE_FOR_PROCESS(FSOpenFile_eshop, WUPS_LOADER_LIBRARY_COREINIT, FSOpenFile, WUPS_FP_TARGET_PROCESS_ESHOP);
