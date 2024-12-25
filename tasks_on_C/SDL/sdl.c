//#include "/opt/homebrew/include/SDL2/SDL.h"
//#include "/opt/homebrew/include/SDL2/SDL_image.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <time.h>



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_SNOWFLAKES 1000

typedef struct {
    float x, y;
    float speed;
    float size;
    float rotation;
    SDL_Texture* texture;
} Snowflake;

Snowflake* snowflakes[MAX_SNOWFLAKES];
int snowflake_count = 0;

void add_snowflake(SDL_Renderer* renderer) {
    if (snowflake_count >= MAX_SNOWFLAKES) return;

    Snowflake* flake = malloc(sizeof(Snowflake));
    flake->x = rand() % WINDOW_WIDTH;
    flake->y = -(rand() % 100);
    flake->speed = 1 + rand() % 3;
    flake->size = 10 + rand() % 20;
    flake->rotation = 0;

    SDL_Surface* surface = IMG_Load("snowflake.png");
    flake->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    snowflakes[snowflake_count++] = flake;
}

void update_snowflakes(float delta_time) {
    for (int i = 0; i < snowflake_count; ++i) {
        Snowflake* flake = snowflakes[i];
        flake->y += flake->speed * delta_time;
        flake->rotation += delta_time * 50; 

        if (flake->y > WINDOW_HEIGHT) {
            SDL_DestroyTexture(flake->texture);
            free(flake);
            snowflakes[i] = snowflakes[--snowflake_count];
            --i;
        }
    }
}

void render_snowflakes(SDL_Renderer* renderer) {
    for (int i = 0; i < snowflake_count; ++i) {
        Snowflake* flake = snowflakes[i];
        SDL_Rect dest_rect = {flake->x, flake->y, flake->size, flake->size};
        SDL_RenderCopyEx(renderer, flake->texture, NULL, &dest_rect, flake->rotation, NULL, SDL_FLIP_NONE);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Snowfall", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    int running = 1;
    Uint32 last_time = SDL_GetTicks();

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                add_snowflake(renderer);
            }
        }

        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        update_snowflakes(delta_time);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        render_snowflakes(renderer);

        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < snowflake_count; ++i) {
        SDL_DestroyTexture(snowflakes[i]->texture);
        free(snowflakes[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
