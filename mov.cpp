#include "raylib.h"
#include "raymath.h" 
#include <vector>

struct Ship
{
    Texture2D ship_disagne;
    int TotalFrames;
    int totalCol;
    float sizeX;
    float sizeY;
    int pixelMargen;
};



int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Mi primera ventana con raylib");
    // 1. Inicialización
    
    std::vector<Ship> listaDeNaves;

    
    Ship nave_bigboy;
    nave_bigboy.ship_disagne = LoadTexture("BigBoy.png");
    nave_bigboy.TotalFrames = 32;
    nave_bigboy.totalCol = 5;
    nave_bigboy.sizeX = 203;
    nave_bigboy.sizeY = 143;
    nave_bigboy.pixelMargen = 0;

    listaDeNaves.push_back(nave_bigboy);

    
    Ship nave_venom;
    nave_venom.ship_disagne = LoadTexture("VEMON.png");
    nave_venom.TotalFrames = 72;
    nave_venom.totalCol = 9;
    nave_venom.sizeX = 202;
    nave_venom.sizeY = 202;
    nave_venom.pixelMargen = 0;

    listaDeNaves.push_back(nave_venom);

    Vector2 ship_position = { screenWidth / 2.0f, screenHeight / 2.0f };
    int nave_selecionada = 0;

    SetTargetFPS(60); // Limitamos a 60 fotogramas por segundo

    // 2. Bucle de juego principal
    while (!WindowShouldClose()) {    // Detecta si se pulsa ESC o el botón de cerrar

        Ship &nave_actual = listaDeNaves[nave_selecionada];
        float gradosPorFrame = 360.0f / nave_actual.TotalFrames;

        Rectangle destino = { ship_position.x, ship_position.y, nave_actual.sizeX, nave_actual.sizeY};
        Vector2 origenGiro = { nave_actual.sizeX / 2.0f, nave_actual.sizeY / 2.0f };


        if (IsKeyPressed(KEY_A)) nave_selecionada = 0;
        if (IsKeyPressed(KEY_B)) nave_selecionada = 1;

        Vector2 mouse_pisition = GetMousePosition();
        // --- AQUÍ IRÍA LA LÓGICA DE ACTUALIZACIÓN ---

        float angulo = atan2f(mouse_pisition.y - ship_position.y, mouse_pisition.x - ship_position.x ) * RAD2DEG;


        if (angulo < 0) angulo += 360;

        int framesActual = (int)(((360.0f - angulo) / gradosPorFrame) + 0.5f) % nave_actual.TotalFrames;

        int col = framesActual % nave_actual.totalCol;
        int file = framesActual / nave_actual.totalCol;


        Rectangle fuente = {

            (float)(col * nave_actual.sizeX) + nave_actual.pixelMargen,
            (float)(file * nave_actual.sizeY) + nave_actual.pixelMargen,
            nave_actual.sizeX,
            nave_actual.sizeY

        };

        // 3. Dibujado
        BeginDrawing();

            ClearBackground(RAYWHITE); // Limpia la pantalla con un color

            DrawTexturePro(nave_actual.ship_disagne, fuente, destino, origenGiro, 0, WHITE);

        EndDrawing();
    }
    UnloadTexture(nave_bigboy.ship_disagne);
    // 4. Desinicialización
    CloseWindow();        // Cierra la ventana y el contexto de OpenGL

    return 0;
}
