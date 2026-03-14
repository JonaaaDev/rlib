#include "raylib.h"

int main(){
  
    const int width = 800;
    const int height = 600;

    InitWindow(width, height, "pantalla raylib");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }
    
    CloseWindow();
}
