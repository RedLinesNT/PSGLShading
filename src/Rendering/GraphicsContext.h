#pragma once

#include "PSGL/psgl.h"

// ---------------------------------------------------
// Create, Dispose and Update the PSGL's
// environment used throughout the application's
// life-time.
// ---------------------------------------------------
class GraphicsContext {
public:
    GraphicsContext();

    // ---------------------------------------------------------------------------
    // Initialize and set up the Graphics Context
    // using PSGL.
    // ---------------------------------------------------------------------------
    // Parameters:
    //    - cellResolutionIDs
    //          A "priority-ordered" array of "CellVideoOutResolutionId"
    //          values wishing to use with the PSGL.
    //          Check "GraphicsContext::GetBestVideoOutputMode" for more details
    //          about the usage of both parameters.
    //    - numResolutions
    //          The number of elements in the array given.
    // ---------------------------------------------------------------------------
    //  Returns:
    //      False is something failed during the process.
    //      If the process failed, the error will be printed before returning.
    // ---------------------------------------------------------------------------
    bool Initialize(const unsigned int* cellResolutionIDs, unsigned int numResolutions);
    // ---------------------------------------------------------------------------
    // Destroy/Close the Graphics Context and associated 
    // object created for running PSGL.
    // ---------------------------------------------------------------------------
    void Dispose() const;

    // ---------------------------------------------------------------------------
    // Create the Context's viewport.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      Will only be done once at the Context's creation.
    // ---------------------------------------------------------------------------
    void CreateViewport();

    // ---------------------------------------------------------------------------
    // Prepare the Graphics Context for a new frame.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      "PreRender" is supposed to be called before any other
    //      graphics-related command.
    // ---------------------------------------------------------------------------
    void PreRender();
    // ---------------------------------------------------------------------------
    // Finishes up the current frame.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      "PostRender" is supposed to be called after every other
    //      graphics-related command.
    // ---------------------------------------------------------------------------
    void PostRender();

    // ---------------------------------------------------------------------------
    // The current GraphicsContext instance running.
    // ---------------------------------------------------------------------------
    static inline GraphicsContext* Get() { return instance; }
    // ---------------------------------------------------------------------------
    // Returns the width of the main viewport created.
    // ---------------------------------------------------------------------------
    static inline unsigned int GetViewportWidth() { return instance->viewportWidth; }
    // ---------------------------------------------------------------------------
    // Returns the height of the main viewport created.
    // ---------------------------------------------------------------------------
    static inline unsigned int GetViewportHeight() { return instance->viewportHeight; }

private:
    // ---------------------------------------------------------------------------
    //  Returns:
    //      True if the PlayStation3 output video is ready to be used.
    // ---------------------------------------------------------------------------
    static bool IsVideoOutputReady();
    // ---------------------------------------------------------------------------
    // Assign "width" and "height" proper values based on an ID
    // from the "CellVideoOutResolutionId" given.
    // ---------------------------------------------------------------------------
    // Parameters:
    //    - cellResolutionID
    //          The "CellVideoOutResolutionId" value to retrieve its
    //          width and height.
    // ---------------------------------------------------------------------------
    //  Returns:
    //      1 if the "cellResolutionID" given is value and "width" and "height"
    //      values have been affected.
    //      0 if not ("width" and "height" will remain unmodified).
    // ---------------------------------------------------------------------------
    static int GetResolutionFromCellResolutionID(unsigned int cellResolutionID, unsigned int& width, unsigned int& height);
    // ---------------------------------------------------------------------------
    // Takes up a "priority-ordered" array of "CellVideoOutResolutionId" values
    // and return the ID of the first value available and supported inside
    // the array given.
    // ---------------------------------------------------------------------------
    // Parameters:
    //    - cellResolutionID
    //          The "CellVideoOutResolutionId" value to retrieve its
    //          width and height.
    // ---------------------------------------------------------------------------
    //  Remarks:
    //      If a value like "CELL_VIDEO_OUT_RESOLUTION_0000x0000" is in
    //      the array given and is selected, there's a chance the application
    //      will be rendered at a lower resolution than the one currently setup
    //      and used across the PlayStation3 system. In this case, the PSGL will
    //      automatically stretch/upscale the final framebuffer to the current
    //      resolution used by the PlayStation3.
    // ---------------------------------------------------------------------------
    //  Example:
    //      My "top-priority" resolution is "1920x1080", and if not available,
    //      I'd like "1280x720" to be my fallback one, I should input:
    //          wantedCellResolutionIDs = {
    //              CELL_VIDEO_OUT_RESOLUTION_1080, //1080p
    //              CELL_VIDEO_OUT_RESOLUTION_720, //720p
    //          };
    //          wantedCellResolutionIDsCount = 2;
    // ---------------------------------------------------------------------------
    //  Returns:
    //      0 if nothing amongst the array given is currently available.
    //      Otherwise, the "CellVideoOutResolutionId" of the best available
    //      resolution.
    // ---------------------------------------------------------------------------
    static unsigned int GetBestVideoOutputMode(const unsigned int* wantedCellResolutionIDs, unsigned int wantedCellResolutionIDsCount);

private:
    // ---------------------------------------------------------------------------
    // The current GraphicsContext instance running.
    // ---------------------------------------------------------------------------
    static GraphicsContext* instance;
    
    PSGLcontext* psglContext;
    PSGLdevice* psglDevice;

    // ---------------------------------------------------------------------------
    // The width of the main viewport created.
    // ---------------------------------------------------------------------------
    unsigned int viewportWidth;
    // ---------------------------------------------------------------------------
    // The height of the main viewport created.
    // ---------------------------------------------------------------------------
    unsigned int viewportHeight;
};