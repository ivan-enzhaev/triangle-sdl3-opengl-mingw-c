#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPosition;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPosition, 1.0);\n"
    "}\n";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "precision mediump float;\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "    fragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n";

// Global application state to persist data between callbacks
struct AppState {
    SDL_Window *window;
    SDL_GLContext glContext;
    unsigned int shaderProgram;
    unsigned int VAO, VBO;
} state;

// Initialization callback
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        return SDL_APP_FAILURE;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    state.window = SDL_CreateWindow("SDL3 OpenGL Triangle", 380, 380, SDL_WINDOW_OPENGL);
    if (!state.window)
        return SDL_APP_FAILURE;

    state.glContext = SDL_GL_CreateContext(state.window);
    if (!state.glContext)
        return SDL_APP_FAILURE;

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        return SDL_APP_FAILURE;

    SDL_GL_SetSwapInterval(1); // Turn on vertical sync

    // Simple Shader Compilation
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    state.shaderProgram = glCreateProgram();
    glAttachShader(state.shaderProgram, vertexShader);
    glAttachShader(state.shaderProgram, fragmentShader);
    glLinkProgram(state.shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    glGenVertexArrays(1, &state.VAO);
    glGenBuffers(1, &state.VBO);
    glBindVertexArray(state.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, state.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    return SDL_APP_CONTINUE;
}

// Event handling callback (called automatically per event by SDL3)
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // Stops the application cleanly
    }
    return SDL_APP_CONTINUE;
}

// Main loop iteration callback (called repeatedly)
SDL_AppResult SDL_AppIterate(void *appstate)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(state.shaderProgram);
    glBindVertexArray(state.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(state.window);

    return SDL_APP_CONTINUE;
}

// Cleanup callback (called automatically when application exits)
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    glDeleteVertexArrays(1, &state.VAO);
    glDeleteBuffers(1, &state.VBO);
    glDeleteProgram(state.shaderProgram);
    SDL_GL_DestroyContext(state.glContext);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}
