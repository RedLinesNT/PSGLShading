﻿#include "GraphicsContext.h"
#include "Core/Core.h"

GraphicsContext::GraphicsContext() {
    psglContext = nullptr;
    psglDevice = nullptr;
    viewportWidth = 0;
    viewportHeight = 0;
    isVSyncEnabled = false;
}

GraphicsContext::~GraphicsContext() = default;

bool GraphicsContext::Initialize(const unsigned int* cellResolutionIDs, unsigned int numResolutions) {
    // Wait for the PlayStation3's video output to be ready...
    if (!IsVideoOutputReady()) DEBUG_PRINT("[Renderer] System's video output not available, waiting...\n")
    while (!IsVideoOutputReady()) {} //Wait...
    DEBUG_PRINT("[Renderer] System's video output ready.\n")

    PSGLinitOptions glInitOptions;
    glInitOptions.enable = PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS | PSGL_INIT_HOST_MEMORY_SIZE; //Options we'd like to tweak
    glInitOptions.maxSPUs = 1; //Raw SPU for "large" PSGL operations
    glInitOptions.initializeSPUs = false; //Already previously initialized
#if _DEBUG
    glInitOptions.enable |= PSGL_INIT_ERROR_CONSOLE;
    glInitOptions.errorConsole = 1;
#endif
    //Retail consoles have 256MB of memory, REFERENCE STATIONS have 512MB
    glInitOptions.hostMemorySize = 128 * 1024*1024; //128MB usage for PSGL

    psglInit(&glInitOptions); //Initialize PSGL

    //Find the best resolution available from what we have
    unsigned int bestResolutionID = GetBestVideoOutputMode(cellResolutionIDs, numResolutions);
    if (bestResolutionID == 0) {
        DEBUG_PRINT("[Renderer] Unable to find any video mode available amongst the '%u' modes given!\n", numResolutions)
        return false;
    }

    //The target rendering resolution
    unsigned int targetWidth = 0;
    unsigned int targetHeight = 0;
    GetResolutionFromCellResolutionID(bestResolutionID, targetWidth, targetHeight);
    DEBUG_PRINT("[Renderer] Target resolution '%ux%u'.\n", targetWidth, targetHeight)

    //Create the PSGLDevice initialization parameters
    PSGLdeviceParameters params;
    params.enable = PSGL_DEVICE_PARAMETERS_COLOR_FORMAT | PSGL_DEVICE_PARAMETERS_DEPTH_FORMAT |
                    PSGL_DEVICE_PARAMETERS_MULTISAMPLING_MODE | PSGL_DEVICE_PARAMETERS_WIDTH_HEIGHT; //Options we'd like to tweak
    params.width = targetWidth;
    params.height = targetHeight;
    params.colorFormat = GL_ARGB_SCE;
    params.depthFormat = GL_DEPTH_COMPONENT24;
    params.multisamplingMode = GL_MULTISAMPLING_4X_SQUARE_CENTERED_SCE;

    psglDevice = psglCreateDeviceExtended(&params);
    psglContext = psglCreateContext();

    psglMakeCurrent(psglContext, psglDevice);
    psglResetCurrentContext();

    //Everything is created, set up the Viewport
    CreateViewport();

    //The PSGL doesn't clear up the screen after being initialized, do it now
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //Grey
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    psglSwap();
    
    return true;
}

void GraphicsContext::Dispose() const {
    psglDestroyContext(psglContext);
    psglDestroyDevice(psglDevice);
    psglExit();
}

void GraphicsContext::PreRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    if (isVSyncEnabled) glEnable(GL_VSYNC_SCE);
    else glDisable(GL_VSYNC_SCE);
}

void GraphicsContext::PostRender() {
    psglSwap();
}

void GraphicsContext::CreateViewport() {
    //Retrieve the target buffer's dimensions (rendering dimensions)
    psglGetRenderBufferDimensions(psglDevice, &viewportWidth, &viewportHeight);

    //Set the viewport
    glViewport(0, 0, (GLsizei)viewportWidth, (GLsizei)viewportHeight);
    glScissor(0, 0, (GLsizei)viewportWidth, (GLsizei)viewportHeight);
}

bool GraphicsContext::IsVideoOutputReady() {
    //Retrieve the current video state
    CellVideoOutState currVideoState;
    cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &currVideoState);

    return currVideoState.state == CELL_VIDEO_OUT_OUTPUT_STATE_ENABLED;
}

int GraphicsContext::GetResolutionFromCellResolutionID(unsigned int cellResolutionID, unsigned int& width, unsigned int& height){
    switch (cellResolutionID) {
        //Standard resolution modes
        case CELL_VIDEO_OUT_RESOLUTION_480: width=720; height=480; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_576: width=720; height=576; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_720: width=1280; height=720; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_1080: width=1920; height=1080; return 1;

        //Lower rendering resolution, buffer (hardware) upscaled to 1080p
        case CELL_VIDEO_OUT_RESOLUTION_1600x1080: width=1600; height=1080; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_1440x1080: width=1440; height=1080; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_1280x1080: width=1280; height=1080; return 1;
        case CELL_VIDEO_OUT_RESOLUTION_960x1080: width=960;  height=1080; return 1;
        
        default: break;
    }

    DEBUG_PRINT("[Renderer] CellVideoOutResolutionId '%u' is invalid or unsupported!\n'", cellResolutionID)
    return 0;
}

unsigned int GraphicsContext::GetBestVideoOutputMode(const unsigned int* wantedCellResolutionIDs, const unsigned int wantedCellResolutionIDsCount) {
    for (unsigned int i=0; i<wantedCellResolutionIDsCount; i++) {
        if (cellVideoOutGetResolutionAvailability(CELL_VIDEO_OUT_PRIMARY, wantedCellResolutionIDs[i], CELL_VIDEO_OUT_ASPECT_AUTO, 0)) {
            return wantedCellResolutionIDs[i]; //Yay! a wanted resolution is available!
        }
    }

    return 0; //Nothing is available :(
}