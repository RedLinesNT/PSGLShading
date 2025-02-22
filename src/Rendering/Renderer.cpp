#include "Renderer.h"

#include "Camera/PerspectiveCamera.h"
#include "Core/Core.hpp"

GraphicsContext* Renderer::context = nullptr;

bool Renderer::Initialize(const unsigned int* cellResolutionIDs, unsigned int numResolutions) {
    if (context != nullptr) { //Already been initialized!
        DEBUG_PRINT("[Renderer] Already been previously initialized! Restarting...")
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

    DEBUG_PRINT("[Renderer] Disposed!\n")
}

void Renderer::PreRender() {
    context->PreRender();
}

float* vertices = new float[12] {
    1.0f, 1.0f, 0.0f, //01 - Top Right
    1.0f, -1.0f, 0.0f, //02 - Bottom Right
    -1.0f, -1.0f, 0.0f, // 03 - Bottom Left
    -1.0f, 1.0f, 0.0f, //04 - Top Left
};

float* colors = new float[16] {
    1.0f, 0.0f, 0.0f, 1.0f, //RED
    0.0f, 1.0f, 0.0f, 1.0f, //GREEN
    0.0f, 0.0f, 1.0f, 1.0f, //BLUE
    1.0f, 1.0f, 0.0f, 1.0f, //YELLOW
};

Transform* testObjTrans = new Transform();

void Renderer::Render(float deltaTime) {
    if (Camera::GetMainCamera() == nullptr) return;
    
    //I'll be using "gl"-easy methods rather than doing it
    //all by myself from scratch.
    //Why? I know that PSGL use an SPE, but I don't know (at least I hope)
    //if those "glMatrixMode" methods are actually using SPU code to quicker
    //calculate matrices and stuff to delegate this type of "heavy" workload
    //from the CELL Broadband Engine.
    
    if (Camera::GetMainCamera()->NeedRecalculateProjectionMatrix()) { //Something modified?
        Camera::GetMainCamera()->RecalculateProjectionMatrix();
    }

    //Update the main camera first
    Camera::GetMainCamera()->GetTransform().Update();

    //Retrieve the camera's matrices
    Matrix4 projMatrix = Camera::GetMainCamera()->GetProjectionMatrix();
    Matrix4 viewMatrix = -Camera::GetMainCamera()->GetViewMatrix();

    //TODO: REMOVE ONLY USED TO TEST A QUAD HERE
    testObjTrans->Rotation[0] += 1.0f * deltaTime;
    testObjTrans->Rotation[1] += 1.0f * deltaTime;
    testObjTrans->Rotation[2] += 1.0f * deltaTime;
    testObjTrans->Update();

    //Projection Matrix (Camera)
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((GLfloat*)&projMatrix);

    //View Matrix (Camera)
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf((GLfloat*)&viewMatrix);

    //Model Transform (of the test quad in this case)
    glMultMatrixf((GLfloat*)&testObjTrans->GetLocalToWorld());
        
    glDisable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);

    //TODO: REMOVE ONLY USED TO TEST A QUAD HERE
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(4, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
        

    //TODO: for loop something here
    //TODO: Update registered Render-able objects?

    glPopMatrix();
}

void Renderer::PostRender() {
    context->PostRender();
}