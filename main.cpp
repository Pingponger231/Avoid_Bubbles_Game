#include "raylib.h"
#include <cstdlib>
#include <ctime>


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Pierwsza gra");
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
    int points = 0, lifes = 3;
    int Gameover = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (Gameover == 0)
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
            }
            if (lifes == 0) Gameover = 1;
            BeginDrawing();
            ClearBackground(LIGHTGRAY);
            DrawRectangleRec(opponent, DARKGREEN);
            DrawRectangleRec(opponentSec, DARKGREEN);
            DrawRectangleRec(opponentThird, DARKGREEN);
            DrawRectangleRec(opponentBig, YELLOW);
            b -= 3 + points/4;
            a += rand() % 10 - 5;
            d -= 3 + points/4;
            c += rand() % 10 - 5;
            f += 3 + points/4;
            e -= rand() % 10 - 5;
            h += 3 + points/4;
            g -= rand() % 10 - 5;
            if (a < 0) a+=10;
            if (a>380) a-= 10;
            if (c < 0) c+=10;
            if (c>380) c-= 10;
            if (e < 0) e+=10;
            if (e > 380) e-= 10;
            if (g < 0) e+=10;
            if (g > 380) e-= 10;
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
            DrawRectangleRec(player, RED);
            DrawText(TextFormat("Lifes: %d", lifes), 50, 10, 30, BLUE);
            DrawText(TextFormat("Score: %d", points), 300, 10, 30, BLUE);
            EndDrawing();
        }
        if(Gameover == 1)
        {
            ClearBackground(LIGHTGRAY);
            DrawText("Game over", 100, 100, 100, RED);
            EndDrawing();
        }
    }
    CloseWindow();
    return 0;
}

