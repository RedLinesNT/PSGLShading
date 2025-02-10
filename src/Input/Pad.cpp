#include "Pad.h"
#include <cell/pad/libpad.h>
#include <sys/return_code.h>

Pad::Pad(uint8_t portID) : portID(portID), pressedCallbacks{} {
    
}

void Pad::SetPressedFunc(E_PAD_BUTTONS targetButton, InputFunc func) {
    pressedCallbacks[targetButton] = func;
}

void Pad::RemovePressedFunc(E_PAD_BUTTONS targetButton, InputFunc func) {
    if (pressedCallbacks[targetButton] != func) return;
    pressedCallbacks[targetButton] = nullptr;
}

void Pad::Update(const CellPadData& data) const {
    if (data.len <= 0) return; //Nothing to update

    //Layout:
    //  data.button[2] -> Digital buttons
    //  data.button[3] -> More digital buttons
    //  data.button[4] -> Right JoyStick X
    //  data.button[5] -> Right JoyStick Y
    //  data.button[6] -> Left JoyStick X
    //  data.button[7] -> Left JoyStick Y
    //  data.button[8 <-> 19] -> "Pressure-Sensitive" buttons (Require "cellPadSetPortSetting" to handle)
    //  data.button[20 <-> 13] -> SIXAXIS (X,Y,Z) values (Require "cellPadSetPortSetting" to handle)
    
    if (data.button[2]) {
        for (int i=0; i<PAD_BUTTONS_MAX / 2; i++) {
            if (data.button[2] & (1 << i)) {
                if (pressedCallbacks[i]) pressedCallbacks[i](); //We got something, invoke!
            }
        }
    }

    if (data.button[3]) {
        for (int i=0; i<PAD_BUTTONS_MAX / 2; i++) {
            if (data.button[3] & (1 << i)) {
                if (pressedCallbacks[PAD_BUTTONS_MAX/2 + i]) pressedCallbacks[PAD_BUTTONS_MAX/2 + i](); //We got something, invoke!
            }
        }
    }
}

bool Pad::ClearPadBuffer() const {
    return cellPadClearBuf(portID) == CELL_OK;
}
