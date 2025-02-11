#include "Renderer.h"

#include "Core/Core.h"

GraphicsContext* Renderer::context = nullptr;

bool Renderer::Initialize(const unsigned int* cellResolutionIDs, unsigned int numResolutions) {
    if (context != nullptr) { //Already been initialized!
        DEBUG_PRINT("[Renderer] Already been previously initialized! Restarting...");
        Shutdown();
    }

    context = new GraphicsContext();
    if (!context->Initialize(cellResolutionIDs, numResolutions)) {
        DEBUG_PRINT("[Renderer] Unable to setup the GraphicsContext!\n")
        return false;
    }

    DEBUG_PRINT("[Renderer] Initialized!\n")
    
    return true;
}

void Renderer::Shutdown() {
    context->Dispose();
    delete context;

    DEBUG_PRINT("[Renderer] Disposed!\n");
}

void Renderer::PreRender() {
    context->PreRender();
}

void Renderer::Render(float deltaTime) {
    //TODO: Update registered Render-able objects?
}

void Renderer::PostRender() {
    context->PostRender();
}
