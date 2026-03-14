#include "raylib.h"
#include "raymath.h"
#include <vector>

struct Ship
{
    Texture2D ship_design;
    int TotalFrames;
    int totalCol;
    float sizeX;
    float sizeY;
    int margin;
    int spacing;
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Mi primera ventana con raylib");

    std::vector<Ship> listaDeNaves;

    // BIG BOY
    Ship nave_bigboy{};
    nave_bigboy.ship_design = LoadTexture("BigBoy.png");
    nave_bigboy.TotalFrames = 32;
    nave_bigboy.totalCol = 5;
    nave_bigboy.sizeX = 203;
    nave_bigboy.sizeY = 143;
    nave_bigboy.margin = 0;
    nave_bigboy.spacing = 0;
    listaDeNaves.push_back(nave_bigboy);

    // VENOM
    Ship nave_venom{};
    nave_venom.ship_design = LoadTexture("VEMON.png");
    nave_venom.TotalFrames = 72;
    nave_venom.totalCol = 9;
    nave_venom.sizeX = 202;
    nave_venom.sizeY = 202;
    nave_venom.margin = 0;
    nave_venom.spacing = 0;
    listaDeNaves.push_back(nave_venom);

    // SENTINEL
    Ship nave_sentinel{};
    nave_sentinel.ship_design = LoadTexture("ship100.png");
    nave_sentinel.TotalFrames = 70;
    nave_sentinel.totalCol = 18;
    nave_sentinel.sizeX = 225;
    nave_sentinel.sizeY = 225;
    nave_sentinel.margin = 2;
    nave_sentinel.spacing = 2;
    listaDeNaves.push_back(nave_sentinel);

    Vector2 ship_position = { screenWidth / 2.0f, screenHeight / 2.0f };
    int nave_selecionada = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mouse_position = GetMousePosition();

        if (IsKeyPressed(KEY_A)) nave_selecionada = 0;
        if (IsKeyPressed(KEY_B)) nave_selecionada = 1;
        if (IsKeyPressed(KEY_C)) nave_selecionada = 2;

        Ship& nave_actual = listaDeNaves[nave_selecionada];

        float gradosPorFrame = 360.0f / nave_actual.TotalFrames;

        float angulo = atan2f(
            mouse_position.y - ship_position.y,
            mouse_position.x - ship_position.x
        ) * RAD2DEG;

        if (angulo < 0) angulo += 360;

        int frameActual = (int)(((360.0f - angulo) / gradosPorFrame) + 0.5f) % nave_actual.TotalFrames;

        int col = frameActual % nave_actual.totalCol;
        int row = frameActual / nave_actual.totalCol;

        float pasoX = nave_actual.sizeX + nave_actual.spacing;
        float pasoY = nave_actual.sizeY + nave_actual.spacing;

        Rectangle fuente = {
            nave_actual.margin + col * pasoX,
            nave_actual.margin + row * pasoY,
            nave_actual.sizeX,
            nave_actual.sizeY
        };

        Rectangle destino = {
            ship_position.x,
            ship_position.y,
            nave_actual.sizeX,
            nave_actual.sizeY
        };

        Vector2 origenGiro = {
            nave_actual.sizeX / 2.0f,
            nave_actual.sizeY / 2.0f
        };

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Frame: %d", frameActual), 10, 10, 20, BLACK);
        DrawTexturePro(
            nave_actual.ship_design,
            fuente,
            destino,
            origenGiro,
            0,
            WHITE
        );

        EndDrawing();
    }

    for (auto& nave : listaDeNaves)
    {
        UnloadTexture(nave.ship_design);
    }

    CloseWindow();
    return 0;
}
