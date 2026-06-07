#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct p3 {
    float x, y, z;
} p3;

#define NUMPOINTS 40000
// Model array holds the original point cloud, Rotated holds
// the transformed points after applying rotation each frame.
p3 Model[NUMPOINTS];
p3 Rotated[NUMPOINTS];

// Zeroes the framebuffer.
void clear(SDL_Surface *surface) {
    int height = surface->h;
    int pitch = surface->pitch;
    uint8_t *fb = (uint8_t*)surface->pixels;
    memset(fb, 0, pitch * height);
}

// Subtracts 15 from every byte each frame, creating a motion
// trail effect instead of a hard clear.
void fade(SDL_Surface *surface) {
    int height = surface->h;
    int pitch = surface->pitch;
    uint8_t *fb = (uint8_t*)surface->pixels;
    int numbytes = pitch * height;
    for (int j = 0; j < numbytes; j++) {
        if (fb[j] > 15) {
            fb[j] -= 15;
        } else {
            fb[j] = 0;
        }
    }
}

// Model definition (range -150 to +150 on each axis).
void create_model(void) {
#if 0
    // Cube model.
    for (int j = 0; j < NUMPOINTS; j++) {
        Model[j].x = -75 + rand() % 150;
        Model[j].y = -75 + rand() % 150;
        Model[j].z = -75 + rand() % 150;
    }
#else
    // Waves model.
    int j = 0;
    for (float x = -50; x < 50; x += 0.5) {
        for (float z = -50; z <= 50; z += 0.5) {
            // Surface height from two overlapping sine/cosine waves along x and z.
            float y = 10+(sin(x/100*3.14*5) * 5)+(cos(z/100*3.14*5) * 5);
            // Scale from model units to world coordinates.
            Model[j].x = x * 4;
            Model[j].y = y * 4;
            Model[j].z = z * 4;
            j++;
            if (j == NUMPOINTS) return;
        }
    }
#endif
}

// Writes BGRA bytes directly into the SDL surface framebuffer,
// with bounds checking.
void pixel(SDL_Surface *surface, int x, int y, int r, int g, int b) {
    // Write pixels – fill with a horizontal RGB gradient
    int width = surface->w;
    int height = surface->h;
    if (x < 0 || x >= width) return;
    if (y < 0 || y >= height) return;

    int pitch = surface->pitch; // bytes per row
    uint8_t *fb = (uint8_t*)surface->pixels;

    fb[y * pitch + x * 4 + 0] = b;
    fb[y * pitch + x * 4 + 1] = g;
    fb[y * pitch + x * 4 + 2] = r;
    fb[y * pitch + x * 4 + 3] = 255;
}


// Applies Y axis rotation to all points using the standard
// rotation matrix. The angle increments each frame based on time.
void rotate(float time) {
    // Convert frame count to radians: full circle (2pi) over 60 frames, scaled by 0.05.
    float alpha = (time * ((3.14*2)/60)) * 0.05;
    for (int j = 0; j < NUMPOINTS; j++) {
        /*
         * Rotation along the y axis is:
         *
         * x' =  x cosθ + z sinθ
         * y' =  y
         * z' = -x sinθ + z cosθ
         */
        Rotated[j].x = Model[j].x * cos(alpha) + Model[j].z * sin(alpha);
        Rotated[j].y = Model[j].y;
        Rotated[j].z = -Model[j].x * sin(alpha) +  Model[j].z * cos(alpha);
    }
}

// Clears the screen, then projects each rotated point to 2D
// using a simple perspective division: x / (1 + z/300). Points
// farther away (larger z) shrink toward the center.
// All points are drawn white.
void draw(SDL_Surface *surface, float time) {
    int width = surface->w;
    int height = surface->h;

    float cx = (float)width / 2;
    float cy = (float)height / 2;

    rotate(time);

    //fade(surface);
    clear(surface);
    for (int j = 0; j < NUMPOINTS; j++) {
        // Perspective: objects farther away (larger z) appear smaller.
        float zfactor = 1 + (Rotated[j].z / 300);
        // Project 3D to 2D by dividing x,y by the depth factor.
        float x = Rotated[j].x / zfactor;
        float y = Rotated[j].y / zfactor;
        pixel(surface,round(cx+x),round(cy+y),255,255,255);
    }
}

// A 3D point cloud rotating around the Y axis, rendered
// with a simple perspective projection onto a 2D SDL window.
int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    // Initialize SDL video.
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // Create window.
    SDL_Window* window = SDL_CreateWindow("Pixel Framebuffer", 640, 480, 0);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Get the window's surface (the frame buffer).
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface) {
        SDL_Log("SDL_GetWindowSurface failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    clear(surface);
    create_model();
    int running = 1;
    float time = 0;
    while(running) {
        draw(surface,time);
        SDL_UpdateWindowSurface(window);
        time += 1;

        // Wait for quit event
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
