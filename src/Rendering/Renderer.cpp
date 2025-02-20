#include "Renderer.h"

#include "Camera/PerspectiveCamera.h"
#include "Core/Core.hpp"

GraphicsContext* Renderer::context = nullptr;
std::list<Camera*> Renderer::cameraStack;

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

    DEBUG_PRINT("[Renderer] Disposed!\n")
}

void Renderer::PreRender() {
    context->PreRender();
}

float* vertices = new float[12] {
    15.0f, 15.0f, 0.0f, //01 - Top Right
    15.0f, -15.0f, 0.0f, //02 - Bottom Right
    -15.0f, -15.0f, 0.0f, // 03 - Bottom Left
    -15.0f, 15.0f, 0.0f, //04 - Top Left
};

float* colors = new float[16] {
    1.0f, 0.0f, 0.0f, 1.0f, //RED
    0.0f, 1.0f, 0.0f, 1.0f, //GREEN
    0.0f, 0.0f, 1.0f, 1.0f, //BLUE
    1.0f, 1.0f, 0.0f, 1.0f, //YELLOW
};

void Renderer::Render(float deltaTime) {
    //I'll be using "gl"-easy methods rather than doing it
    //all by myself from scratch.
    //Why? I know that PSGL use an SPE, but I don't know (at least I hope)
    //if those "glMatrixMode" methods are actually using SPU code to quicker
    //calculate matrices and stuff to delegate this type of "heavy" workload
    //from the CELL Broadband Engine.
    
    for (Camera* camera : cameraStack) { //Loop throughout every camera created
        if (camera->NeedRecalculateProjectMatrix()) { //Something modified?
            camera->RecalculateProjectionMatrix();
        }

        //Update the current camera first
        camera->GetTransform().Update();
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();

            //Load and push the camera's transform so that every
            //matrice that'll be pushed will be related to the camera's one
            //(I kinda forgot how that work ngl)
            glLoadIdentity();
            glLoadMatrixf((GLfloat*)&camera->GetTransform().GetLocalToWorld());
            glPushMatrix();
        
        //TODO: KMS
        //glMatrixMode(GL_MODELVIEW); //TODO: Should probably remove matrix stuff from here
        //glLoadIdentity();
        //glPushMatrix();

        glMultMatrixf((GLfloat*)&Matrix4::identity); //Object's Matrix4
        
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glCullFace(GL_FRONT_AND_BACK);
    
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(4, GL_FLOAT, 0, colors);
        glDrawArrays(GL_QUADS, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        

        //TODO: for loop something here
        //TODO: Update registered Render-able objects?

        glPopMatrix(); //Pop the camera's transform matrix
    }
    
}

void Renderer::PostRender() {
    context->PostRender();
}

void Renderer::AddCamera(Camera* camera) {
    cameraStack.push_back(camera);
    DEBUG_PRINT("[Renderer] Added a new Camera into the stack.\n")
}
