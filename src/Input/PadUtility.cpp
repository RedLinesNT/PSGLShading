#include "PadUtility.h"

#include "Core/Core.h"

std::list<Pad*> PadUtility::pads;

void PadUtility::Initialize(uint8_t maxPads) {
    if (cellPadInit(maxPads) != CELL_OK) {
        DEBUG_PRINT("[PadUtility] Failed to initialize!\n")
    }

    for (int i=0; i < maxPads; i++) {
        Pad* pad = new Pad((uint8_t)i);
        pads.push_back(pad);
    }

    DEBUG_PRINT("[PadUtility] Initialized for '%i' pads!\n", (maxPads+1))
}

void PadUtility::Update() {
    CellPadData padData;

    for (Pad* pad : pads) {
        cellPadGetData(pad->portID, &padData);
        pad->Update(padData);
    }
}

void PadUtility::Dispose() {
    cellPadEnd();

    for (Pad* pad : pads) {
        delete pad;
    }

    DEBUG_PRINT("[PadUtility] Disposed!\n")
}

void PadUtility::ClearPadBuffers() {
    for (Pad* pad : pads) {
        if (!pad->ClearPadBuffer()) {
            DEBUG_PRINT("[PadUtility] Failed to 'cellPadClearBuf' on controller '%u'!\n", pad->portID)
        }
    }
}

Pad& PadUtility::GetPad(uint8_t portID) {
    for (Pad* pad : pads) {
        if (pad->portID ==  portID) return *pad;
    }

    return *pads.front();
}
