#include "raylib.h"   // Librería principal de Raylib: ventanas, input, dibujo, texturas, etc.
#include "raymath.h"  // Librería de utilidades matemáticas para vectores (Vector2, operaciones, etc.)

int main()
{
    // Tamaño de la ventana del juego
    const int width = 800;
    const int height = 600;

    // Crea la ventana del programa con el tamaño especificado y el título
    InitWindow(width, height, "pantalla raylib");

    // Limita el juego a 60 frames por segundo
    // Esto hace que el juego tenga un ritmo constante de actualización
    SetTargetFPS(60);

    // Posición inicial del jugador en el mundo (coordenadas de pantalla)
    Vector2 position_player = {400, 600};

    // Punto de destino hacia el que el jugador se moverá
    // Inicialmente es la misma posición del jugador
    Vector2 target = position_player;

    // Guarda la última dirección en la que se movió el jugador
    // Esto permite que cuando el jugador se detenga siga mirando
    // hacia la última dirección de movimiento
    Vector2 lastDirection = {1.0f, 0.0f};

    // Carga la textura desde el archivo "VEMON.png"
    // Esta textura contiene un atlas de sprites (muchos frames en una sola imagen)
    Texture2D ship = LoadTexture("VEMON.png");

    // Número de columnas del atlas de sprites
    int totalCol = 9;

    // Número total de frames en el atlas
    int totalFrames = 72;

    // Tamaño de cada frame del atlas en píxeles
    int AnchoX = 202;
    int AnchoY = 202;

    // Velocidad del jugador en píxeles por segundo
    float speed = 300;

    // Variable para activar o desactivar invisibilidad
    bool invisible = false;

    // Rectángulo de destino donde se dibuja el sprite en pantalla
    // Define posición y tamaño final del sprite
    Rectangle destinoPlayer = {position_player.x, position_player.y, 202, 202};

    // Punto de origen del sprite para rotaciones o centrado
    // En este caso el centro del sprite (202 / 2 = 101)
    Vector2 originPlayer = {101, 101};

    // Bucle principal del juego
    // Se ejecuta continuamente hasta que el usuario cierre la ventana
    while (!WindowShouldClose())
    {
        // =========================
        // INPUT (entrada del usuario)
        // =========================

        // Si se presiona la tecla A se alterna la invisibilidad
        // !invisible invierte el valor (true → false, false → true)
        if (IsKeyPressed(KEY_A)) invisible = !invisible;

        // Si el botón izquierdo del ratón está presionado
        // se actualiza el punto de destino
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            // Obtiene la posición actual del ratón
            target = GetMousePosition();
        }

        // =========================
        // UPDATE MOVEMENT (lógica de movimiento)
        // =========================

        // Calcula el vector desde el jugador hasta el destino
        // target - position = dirección hacia el objetivo
        Vector2 direction = Vector2Subtract(target, position_player);

        // Calcula la distancia entre el jugador y el destino
        float distance = Vector2Length(direction);

        // Cuánto se puede mover el jugador en este frame
        // velocidad * tiempo del frame
        float step = speed * GetFrameTime();

        // Si la distancia al destino es mayor que el paso posible
        // el jugador sigue moviéndose
        if (distance > step)
        {
            // Convierte el vector dirección en un vector de longitud 1
            // Esto mantiene solo la dirección sin afectar la velocidad
            direction = Vector2Normalize(direction);

            // Guarda la última dirección válida de movimiento
            lastDirection = direction;

            // Actualiza la posición del jugador moviéndolo en esa dirección
            position_player.x += direction.x * step;
            position_player.y += direction.y * step;
        }
        else
        {
            // Si el jugador ya está muy cerca del destino
            // se coloca exactamente en el objetivo
            // Esto evita vibraciones o movimientos de corrección
            position_player = target;
        }

        // Actualiza la posición del rectángulo donde se dibuja el sprite
        destinoPlayer.x = position_player.x;
        destinoPlayer.y = position_player.y;

        // =========================
        // CÁLCULO DE ORIENTACIÓN DEL SPRITE
        // =========================

        // Calcula el ángulo de la última dirección de movimiento
        // atan2 calcula el ángulo de un vector en radianes
        float angulo = atan2f(lastDirection.y, lastDirection.x) * RAD2DEG;

        // Convierte el rango del ángulo a 0-360 grados
        if (angulo < 0) angulo += 360;

        // Cada frame del atlas representa una orientación
        // 360 grados / 72 frames = 5 grados por frame
        int frames_actual = (int)(((360.0f - angulo) / 5.0f) + 0.5f) % totalFrames;

        // Calcula la columna del frame dentro del atlas
        int col = frames_actual % totalCol;

        // Calcula la fila del frame dentro del atlas
        int file = frames_actual / totalCol;

        // Rectángulo fuente dentro del atlas
        // Indica qué parte de la textura se debe dibujar
        Rectangle fuente = {
            (float)(col * AnchoX),   // posición X del frame dentro del atlas
            (float)(file * AnchoY),  // posición Y del frame dentro del atlas
            202,                     // ancho del frame
            202                      // alto del frame
        };

        // =========================
        // DRAW (renderizado)
        // =========================

        // Comienza el proceso de dibujo del frame
        BeginDrawing();

        // Limpia la pantalla con color negro
        ClearBackground(BLACK);

        // Si el jugador es invisible se dibuja con transparencia
        if (invisible)
            DrawTexturePro(ship, fuente, destinoPlayer, originPlayer, 0, Fade(WHITE, 0.2f));
        else
            DrawTexturePro(ship, fuente, destinoPlayer, originPlayer, 0, WHITE);

        // Finaliza el dibujo del frame
        EndDrawing();
    }

    // Libera la memoria usada por la textura
    UnloadTexture(ship);

    // Cierra la ventana y termina el programa
    CloseWindow();
}
