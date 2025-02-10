#pragma once

#include <list>

#include "cell/pad/pad_codes.h"

// ---------------------------------------------------
// Enum containing each button of a PlayStation3
// DualSock3/SIXAXIS controller.
// ---------------------------------------------------
enum E_PAD_BUTTONS {
    SELECT = 0,
    L3 = 1,
    R3 = 2,
    START = 3,

    DPAD_UP = 4,
    DPAD_RIGHT = 5,
    DPAD_DOWN = 6,
    DPAD_LEFT = 7,

    L2 = 8,
    R2 = 9,
    L1 = 10,
    R1 = 11,

    TRIANGLE = 12,
    CIRCLE = 13,
    CROSS = 14,
    SQUARE = 15,

    PAD_BUTTONS_MAX,
};

typedef void (*InputFunc)();

// ---------------------------------------------------
// Simple and primitive implementation of
// the PlayStation3's controllers.
// ---------------------------------------------------
// Remarks:
//      There's currently no support for
//      "pressure-sensitive" buttons, such as the
//      triggers and joysticks.
// ---------------------------------------------------
class Pad {
    friend class PadUtility;
    
public:
    Pad(uint8_t portID);
    ~Pad() = default;

    // ---------------------------------------------------------------------------
    // Bind a void method and invoke it when a specific defined button
    // of this pad is pressed.
    // ---------------------------------------------------------------------------
    void SetPressedFunc(E_PAD_BUTTONS targetButton, InputFunc func);
    // ---------------------------------------------------------------------------
    // Unbind a void method from being invoked when a specific defined button
    // of this pad is released.
    // ---------------------------------------------------------------------------
    void RemovePressedFunc(E_PAD_BUTTONS targetButton, InputFunc func);
    
private:
    // ---------------------------------------------------------------------------
    // Update this pad, and invoke "callbacks" if needed.
    // ---------------------------------------------------------------------------
    void Update(const CellPadData& data) const;
    // ---------------------------------------------------------------------------
    // Clear the data buffer of this pad.
    // ---------------------------------------------------------------------------
    // Returns:
    //      True if the buffer was successfully cleared.
    // ---------------------------------------------------------------------------
    bool ClearPadBuffer() const;
    
private:
    // ---------------------------------------------------------------------------
    // The identifier of this pad.
    // ---------------------------------------------------------------------------
    const uint8_t portID;
    // ---------------------------------------------------------------------------
    // The "button pressed" callbacks methods.
    // ---------------------------------------------------------------------------
    InputFunc pressedCallbacks[PAD_BUTTONS_MAX];
};
