#include <iostream>
#include <raylib.h>
#include "Mobs.hpp"
using namespace std;
float enemy_timer = 0;
Color color_gameover = {53, 59, 54, 100};
Player rocket;
Background backdrop;

int main()
{
    rocket.x = 10;
    rocket.y = 10;
    backdrop.x = 0;
    backdrop.y = 0;
    rocket.v = 10;

    InitWindow(1280, 720, "Rocket v1.2");
    InitAudioDevice();
    Music bg;
   
    
    bg = LoadMusicStream("resources/bgAudio.mp3");
    SetMusicVolume(bg,0.8f);
    PlayMusicStream(bg);
    SetTargetFPS(60);
    backdrop.init();
    rocket.init();

    while (!WindowShouldClose())
    {
        UpdateMusicStream(bg);
        if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT))
        {
            game_state = 0;
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            firingBullet(rocket.x, rocket.y, 30);
        }

        if (game_state == 0)
        {

            rocket.Update();
            for (auto &B : bulletsArr)
            {
                B.Update();
            }
            for (auto &E : enemiesArr)
            {
                E.Update();
            }
            enemy_timer++;
            if (enemy_timer > 42)
            {
                enemiesSpawn(1280, GetRandomValue(0, 720), 2);
                enemy_timer = 0;
            }
        }

       onCollision(rocket);

       
        BeginDrawing();
        backdrop.Draw();
        rocket.Draw();
        for (auto &B : bulletsArr)
        {
            B.Draw();
        }
        for (auto &E : enemiesArr)
        {
            E.Draw();
        }
        DrawText(TextFormat("%i", score), 400, 0, 30, WHITE);
        if (game_state == 1)
        {
            DrawText("GAME OVER", 500, 300, 50, WHITE);
            DrawText(TextFormat("%i", score), 800, 350, 35, WHITE);
            DrawText("HIGH SCORE:", 470, 350, 35, WHITE);
            DrawText("press Enter key to restart", 500, 400, 20, WHITE);
            DrawRectangle(0, 0, screen_w, screen_h, color_gameover);
        }
        if (game_state == 2)
        {
            Menue();
        }
        EndDrawing();
    }
    
    UnloadMusicStream(bg);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}