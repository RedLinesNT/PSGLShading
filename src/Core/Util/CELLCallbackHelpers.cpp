#include "CELLCallbackHelpers.h"
#include "Core/Core.hpp"

enum E_CELL_CALLBACKS_ACTION_SLOTS : int {
    CELL_CLOSE_CALLBACK_HANDLER_SLOT = 0, //Shutdown
    CELL_XMB_CALLBACK_HANDLER_SLOT = 1, //PS3's XMB has been closed/opened
};

bool CELLCallbackHelpers::hasReceivedCloseCallback = false;
bool CELLCallbackHelpers::isTheXMBOpen = false;

void CELLCallbackHelpers::BindCallbacks() {
    cellSysutilRegisterCallback(CELL_CLOSE_CALLBACK_HANDLER_SLOT, HandleCELLCloseCallback, nullptr);
    cellSysutilRegisterCallback(CELL_XMB_CALLBACK_HANDLER_SLOT, HandleCELLXMBCallbacks, nullptr);
}

void CELLCallbackHelpers::UnbindCallbacks() {
    cellSysutilUnregisterCallback(CELL_CLOSE_CALLBACK_HANDLER_SLOT);
    cellSysutilUnregisterCallback(CELL_XMB_CALLBACK_HANDLER_SLOT);
}

void CELLCallbackHelpers::CheckIncomingCallbacks() {
    cellSysutilCheckCallback();
}

void CELLCallbackHelpers::HandleCELLCloseCallback(uint64_t status, uint64_t param, void* userdata) {
    (void)param;
    (void)userdata;

    if (status == CELL_SYSUTIL_REQUEST_EXITGAME) {
        hasReceivedCloseCallback = true;
        DEBUG_PRINT("[CallbacksHandler] CELL_SYSUTIL_REQUEST_EXITGAME Callback received!\n")
    }
}

void CELLCallbackHelpers::HandleCELLXMBCallbacks(uint64_t status, uint64_t param, void* userdata) {
    (void)param;
    (void)userdata;

    if (status == CELL_SYSUTIL_SYSTEM_MENU_OPEN) {
        isTheXMBOpen = true;
        DEBUG_PRINT("[CallbacksHandler] CELL_SYSUTIL_SYSTEM_MENU_OPEN Callback received!\n")
    } else if (status == CELL_SYSUTIL_SYSTEM_MENU_CLOSE) {
        isTheXMBOpen = false;
        DEBUG_PRINT("[CallbacksHandler] CELL_SYSUTIL_SYSTEM_MENU_CLOSE Callback received!\n")
    }
}
