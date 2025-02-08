#pragma once

#include <sysutil/sysutil_common.h>

// ---------------------------------------------------
// Handle some specific CELL's callbacks.
// ---------------------------------------------------
class CELLCallbackHelpers {
public:
    CELLCallbackHelpers() = delete;

    // ---------------------------------------------------------------------------
    // Bind and setup all callbacks handled by this class.
    // ---------------------------------------------------------------------------
    static void BindCallbacks();
    // ---------------------------------------------------------------------------
    // Unbind all callbacks handled by this class.
    // ---------------------------------------------------------------------------
    static void UnbindCallbacks();
    // ---------------------------------------------------------------------------
    // Check each ticks for incoming callbacks from the system.
    // ---------------------------------------------------------------------------
    static void CheckIncomingCallbacks();

    // ---------------------------------------------------------------------------
    // Has the "CELL_SYSUTIL_REQUEST_EXITGAME" callback been caught?
    // ---------------------------------------------------------------------------
    // Remarks:
    //      True if the application should stop running.
    // ---------------------------------------------------------------------------
    inline static bool HasReceivedCloseCallback() { return hasReceivedCloseCallback; }
    // ---------------------------------------------------------------------------
    // Is the XMB currently open?
    // ---------------------------------------------------------------------------
    inline static bool IsTheXMBOpen() { return isTheXMBOpen; }
    
private:
    // ---------------------------------------------------------------------------
    // Handle specifically the close callback.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      Can be triggered by the PlayStation3 itself for various reasons,
    //      such as the user wanting to close the application.
    // ---------------------------------------------------------------------------
    static void HandleCELLCloseCallback(uint64_t status, uint64_t param, void* userdata);
    // ---------------------------------------------------------------------------
    // Handle specifically the XMB being closed/opened.
    // ---------------------------------------------------------------------------
    static void HandleCELLXMBCallbacks(uint64_t status, uint64_t param, void* userdata);

private:
    // ---------------------------------------------------------------------------
    // Has the "CELL_SYSUTIL_REQUEST_EXITGAME" callback been caught?
    // ---------------------------------------------------------------------------
    // Remarks:
    //      True if the application should stop running.
    // ---------------------------------------------------------------------------
    static bool hasReceivedCloseCallback;
    // ---------------------------------------------------------------------------
    // Is the XMB currently open?
    // ---------------------------------------------------------------------------
    static bool isTheXMBOpen;
};
