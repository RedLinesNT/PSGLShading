#pragma once

#include <list>
#include "Context/GraphicsContext.h"

class Camera; //To stop the compiler from bitching

// ---------------------------------------------------
// Handle and give context-free access
// to multiple methods regarding the rendering
// process of the application as a whole.
// ---------------------------------------------------
class Renderer {
    friend class Camera;
    
public:
    Renderer() = delete;

    // ---------------------------------------------------------------------------
    // Initialize the Renderer and associated components.
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
    static bool Initialize(const unsigned int* cellResolutionIDs, unsigned int numResolutions);
    // ---------------------------------------------------------------------------
    // Shutdown the Renderer and associated components.
    // ---------------------------------------------------------------------------
    static void Shutdown();
    
    // ---------------------------------------------------------------------------
    // Prepare the Graphics Context for a new frame.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      "PreRender" is supposed to be called before any other
    //      graphics-related command.
    // ---------------------------------------------------------------------------
    static void PreRender();
    // ---------------------------------------------------------------------------
    // Update the Renderer and associated components.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      Should be called in between of "PreRender" and "PostRender".
    // ---------------------------------------------------------------------------
    static void Render(float deltaTime);
    // ---------------------------------------------------------------------------
    // Finishes up the current frame.
    // ---------------------------------------------------------------------------
    // Remarks:
    //      "PostRender" is supposed to be called after every other
    //      graphics-related command.
    // ---------------------------------------------------------------------------
    static void PostRender();
    
    // ---------------------------------------------------------------------------
    // Returns the width of the main viewport created.
    // ---------------------------------------------------------------------------
    static inline unsigned int GetViewportWidth() { return context->viewportWidth; }
    // ---------------------------------------------------------------------------
    // Returns the height of the main viewport created.
    // ---------------------------------------------------------------------------
    static inline unsigned int GetViewportHeight() { return context->viewportHeight; }
    // ---------------------------------------------------------------------------
    // Returns the aspect ratio of the main viewport created.
    // ---------------------------------------------------------------------------
    static inline GLfloat GetAspectRatio() { return context->aspectRatio; }
    // ---------------------------------------------------------------------------
    // Is the V-Sync (Vertical Synchronization) active?
    // ---------------------------------------------------------------------------
    static inline bool IsVSyncEnabled() { return context->isVSyncEnabled; }
    // ---------------------------------------------------------------------------
    // Enable/Disable the V-Sync (Vertical Synchronization).
    // ---------------------------------------------------------------------------
    static inline void SetVSync(bool value) { context->isVSyncEnabled = value; }
    
private:
    static GraphicsContext* context;
};
