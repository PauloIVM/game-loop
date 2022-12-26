#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

// Install lib on Makefile?
// sudo apt install libsdl2-dev
// gcc -Wall -std=c99 ./src/*.c -o game

int game_is_running = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int last_frame_time = 0;

struct ball {
    float x;
    float y;
    float width;
    float height;
} ball;

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error on init SDL. \n");
        return 0;
    }
    window = SDL_CreateWindow(
        "title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error on creating. \n");
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error on renderer. \n");
        return 0;
    }
    return 1;
}

void setup() {
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = 0;
            break;
    }
}

void update() {
    // TODO: Comparar uso de CPU com a linha 70-73 vs 74
    int time_to_wait = last_frame_time + FRAME_TARGET_TIME - SDL_GetTicks();
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(last_frame_time + FRAME_TARGET_TIME - SDL_GetTicks());
    }
    // while(!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();
    // Pixels per second, and not pixels per frame:
    ball.x += 20 * delta_time;
    ball.y += 20 * delta_time;
    // Fazer um teste, manter como nas linhas abaixo e testar para dois valores
    // distintos de FPS... deve mudar bastante:
    // ball.x += 2;
    // ball.y += 2;
    // Em seguida, usar o delta_time criado acima, e fazer um teste pra dois
    // valores de FPS. Deve manter parecido.
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Rect ball_rect = {
        (int) ball.x,
        (int) ball.y,
        (int) ball.width,
        (int) ball.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball_rect);
    SDL_RenderPresent(renderer);
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    game_is_running = initialize_window();

    setup();

    while(game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}
