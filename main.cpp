#include "raylib.h"
#include <cstdlib>
#include <ctime>

void ResetGame(int &a, int &b, int&c, int&d, int&e, int&f, int&g, int&h, int&x, int&y, int&lifes, int&points,int &Gameover, int&powerup)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    x = screenWidth / 2;
    y = screenHeight / 2;

    a = rand() % 430 + 1; b = 780;
    c = rand() % 430 + 1; d = 780;
    e = rand() % 430 + 1; f = 0;
    g = rand() % 430 + 1; h = 0;

    lifes = 3;
    points = 0;
    Gameover = 0;
    powerup = 0;
}


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Avoid Bubbles Game 1.01 (update)");
    InitAudioDevice();
    Music music = LoadMusicStream("gamemusic.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.22f);
    Sound hitSound = LoadSound("failsound.mp3");
    SetSoundVolume(hitSound, 0.5f);
    Sound lifesound = LoadSound("1upsound.mp3");
    SetSoundVolume(lifesound, 0.5f);
    int x = screenWidth/2;
    int y = screenHeight/2;
    int speed = 5;
    srand(time(NULL));
    int a = rand() % 430 + 1;
    int b = 780;
    int c = rand() % 430 + 1;
int d = 780;
    int e = rand() % 430 + 1;
    int f = 0;
    int g = rand() % 430 + 1;
    int h = 0;
    int points = 0, lifes = 3, record = 0, powerup = 0;
    int Gameover = 0;
    int start = 0, restart = 1;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
       if (start == 0)
       {
            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawText("Avoid Bubbles game", 140, 100, 50, RED);
            DrawText("Press Space to start", 180, 350, 40, BLACK);
            EndDrawing();
       }
        if (IsKeyDown(KEY_SPACE))
        {
            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            EndDrawing();
            start = 1;
        }
            if (Gameover == 0 && start == 1)
            {
                Rectangle player = {x, y, 50, 50};
                Rectangle opponent = {b, a, 20, 20};
                Rectangle opponentSec = {d, c, 20, 20};
                Rectangle opponentThird = {f, e, 20, 20};
                Rectangle opponentBig = {h, g, 60, 60};
                if (IsKeyDown(KEY_RIGHT)) x += speed;
                if (IsKeyDown(KEY_LEFT)) x -= speed;
                if (IsKeyDown(KEY_UP)) y -= speed;
                if (IsKeyDown(KEY_DOWN)) y += speed;

                if (x < 0) x += speed;
                if (x > 750) x -= speed;
                if (y < 0) y += speed;
                if (y > 400) y -= speed;
                if (CheckCollisionRecs(player,opponent) || CheckCollisionRecs(player,opponentSec) || CheckCollisionRecs(player,opponentThird) || CheckCollisionRecs(player,opponentBig))
                {
                        lifes--;
                    b = 780;
                    d = 780;
                    f = 0;
                    h = 0;
                    PlaySound(hitSound);
                }
                if (lifes == 0) Gameover = 1;
                BeginDrawing();
                ClearBackground(LIGHTGRAY);
                DrawRectangleRec(opponent, DARKGREEN);
                DrawRectangleRec(opponentSec, DARKGREEN);
                DrawRectangleRec(opponentThird, DARKGREEN);
                DrawRectangleRec(opponentBig, YELLOW);
                b -= 3 + points/2;
                a += rand() % 10 - 5;
                d -= 3 + points/2;
                c += rand() % 10 - 5;
                f += 3 + points/2;
                e -= rand() % 10 - 5;
                h += 3 + points/2;
                g -= rand() % 10 - 5;
                if (a < 0) a+=10;
                if (a>380) a-= 10;
                if (c < 0) c+=10;
                if (c>380) c-= 10;
                if (e < 0) e+=10;
                if (e > 380) e-= 10;
                if (g < 0) g+=10;
                if (g > 380) g-= 10;
                if (b < 0)
                {
                    points++;
                    b = 780;
                    a = rand() % 430 + 1;
                }
                if (d < 0)
                {
                    d = 780;
                    c = rand() % 430 + 1;
                }
                if (f > 780)
                {
                    f = 0;
                    e = rand() % 430 + 1;
                }
                if (h > 780)
                {
                    h = 0;
                    g = rand() % 430 + 1;
                }
                if (points > record)
                {
                    record = points;
                }
                if (points % 5 == 0)
                {
                    if (powerup == 1 )
                    {
                        lifes++;
                        powerup = 0;
                        PlaySound(lifesound);
                    }
                }
                else powerup = 1;
                DrawRectangleRec(player, RED);
                DrawText(TextFormat("Lifes: %d", lifes), 50, 10, 30, BLUE);
                DrawText(TextFormat("Score: %d", points), 300, 10, 30, BLUE);
                DrawText(TextFormat("Best Score: %d", record), 550, 10, 30, BLUE);
                EndDrawing();
        }
        if(Gameover == 1)
                {
                    BeginDrawing();
                    ClearBackground(LIGHTGRAY);
                    DrawText("Game over", 100, 100, 100, RED);
                    DrawText(TextFormat("Total Score: %d", points), 270, 250, 30, BROWN);
                    DrawText("Press R to restart", 250, 380, 40, BLACK);
                    EndDrawing();
                    if (IsKeyDown(KEY_R))
                    {
                        ResetGame(a, b, c, d, e, f, g, h, x, y, lifes, points, Gameover, powerup);
                    }
                }
    }
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}


