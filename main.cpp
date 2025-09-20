#include <stdlib.h>
#include <stdio.h>

#include "GLFW/glfw3.h"

#define SK_GANESH
#define SK_GL
#include "include/gpu/ganesh/GrBackendSurface.h"
#include "include/gpu/ganesh/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLInterface.h"
#include "include/gpu/ganesh/gl/GrGLAssembleInterface.h"
#include "include/gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkSurface.h"

#define ERROR(message, ...)                                \
    fprintf(stderr, "%s:%i: error: ", __FILE__, __LINE__); \
    fprintf(stderr, message, ##__VA_ARGS__)

GrDirectContext* context = nullptr;
SkSurface* surface = nullptr;

void init_skia(int window_width, int window_height) {
    sk_sp<const GrGLInterface> interface = GrGLMakeNativeInterface();
    if (interface == nullptr) {
        interface = GrGLMakeAssembledInterface(nullptr, (GrGLGetProc) * [](void*, const char* p) -> void* { return (void*) glfwGetProcAddress(p); });
    }
    context = GrDirectContexts::MakeGL(interface).release();

    GrGLFramebufferInfo frame_buffer_info;
    frame_buffer_info.fFBOID = 0;
    frame_buffer_info.fFormat = GL_RGBA8;

    GrBackendRenderTarget backend_render_target = GrBackendRenderTargets::MakeGL(window_width, window_height, 0, 0, frame_buffer_info);
    surface = SkSurfaces::WrapBackendRenderTarget(context, backend_render_target, kBottomLeft_GrSurfaceOrigin, SkColorType::kRGBA_8888_SkColorType, SkColorSpace::MakeSRGB(), nullptr, nullptr).release();

    if (surface == nullptr) abort();
}

void cleanup_skia() {
    delete surface;
    delete context;
}

static void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    if (!glfwInit()) {
        ERROR("failed to initialize glfw\n");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_STENCIL_BITS, 0);
    glfwWindowHint(GLFW_DEPTH_BITS, 0);

    const int window_width = 800;
    const int window_height = 600;
    const char* window_title = "OpenGL";

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        ERROR("failed to create glfw window\n");
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    init_skia(window_width, window_height);
    SkCanvas* canvas = surface->getCanvas();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        process_input(window);

        SkPaint paint;
        paint.setColor(SK_ColorBLACK);
        canvas->drawPaint(paint);
        paint.setColor(SK_ColorBLUE);
        canvas->drawRect({100, 200, 300, 500}, paint);
        context->flush();

        glfwSwapBuffers(window);
    }

    cleanup_skia();
    glfwTerminate();
    return EXIT_SUCCESS;
}
