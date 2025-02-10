#pragma once

#include <list>
#include <cell/pad/libpad.h>
#include <cell/pad/error.h>

#include "Pad.h"

#define CELL_USBPAD_AUTO_PARSE

#define PAD_PLAYER_ONE (0)
#define PAD_PLAYER_TWO (1)
#define PAD_PLAYER_THREE (2)
#define PAD_PLAYER_FOUR (3)
#define PAD_PLAYER_FIVE (4)
#define PAD_PLAYER_SIX (5)
#define PAD_PLAYER_SEVEN (6)
#define PAD_PLAYER_EIGHT (7)

// ---------------------------------------------------
// Manage PlayStation3's controllers throughout the
// application.
// ---------------------------------------------------
class PadUtility {
public:
    PadUtility() = delete;

    // ---------------------------------------------------------------------------
    // Initialize the "PadUtility" class as well of each pad requested
    // to initialize.
    // ---------------------------------------------------------------------------
    static void Initialize(uint8_t maxPads);
    // ---------------------------------------------------------------------------
    // Update each pad.
    // ---------------------------------------------------------------------------
    static void Update();
    // ---------------------------------------------------------------------------
    // Cleans up and dispose the pads created as well of the "PadUtility" class.
    // ---------------------------------------------------------------------------
    static void Dispose();
    static void ClearPadBuffers();
    
    static Pad& GetPad(uint8_t portID);

private:
    static std::list<Pad*> pads;
};