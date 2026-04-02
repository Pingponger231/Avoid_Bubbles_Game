#include "raylib.h"
#include <cstdlib>
#include <ctime>
struct Enemy
{
    int x,y;
    int speed = 3;
    int size;
    char direction = 'L';
};
struct Player
{
    int x = 0,y = 0;
    int speed = 5;
    int size;
    Color color;
};
struct Powerup
{
    int x,y;
    int size = 40;
    enum Type{Point, Life, Speed, Shield}type;
};
void EnemyBasicPosition(Enemy &Enemy, const int ScreenHeight, const int ScreenWidth, int points)
{
    if(rand() % 2 == 0)
    {
        Enemy.x = 0;
        Enemy.direction = 'P';
    }
    else
    {
        Enemy.x = ScreenWidth;
        Enemy.direction = 'L';
    }
    Enemy.y = rand() % (ScreenHeight - Enemy.size);
}
void PlayerBasicPosition(Player &Player,const int ScreenHeight, const int ScreenWidth)
{
    Player.x = ScreenWidth/2;
    Player.y = ScreenHeight/2;
    Player.color = RED;
    Player.speed = 5;
}
void PowerupBasicPosition (Powerup &powerup,const int ScreenHeight, const int ScreenWidth)
{
    powerup.x = rand() % ScreenWidth-powerup.size;
    powerup.y = rand() % ScreenHeight-powerup.size;
    if (powerup.x < 0) powerup.x += ScreenWidth/2;
    if (powerup.y < 0) powerup.y += ScreenHeight/2;
    if (powerup.x > ScreenWidth) powerup.x -= ScreenWidth/2;
    if (powerup.y > ScreenHeight) powerup.y -= ScreenHeight/2;
    int ChooseType = 0;
    ChooseType = rand() % 10 + 1;
    if (ChooseType < 5)
    {
        powerup.type = Powerup::Point;
    }
    if (ChooseType >= 5 && ChooseType < 8 )
    {
         powerup.type = Powerup::Life;
    }
    if (ChooseType == 8 ||ChooseType == 9)
    {
         powerup.type = Powerup::Speed;
    }
    if (ChooseType == 10)
    {
        powerup.type = Powerup::Shield;
    }
}
void EnemyMove(Enemy &Enemy,const int ScreenHeight, const int ScreenWidth, int &points)
{
    if (Enemy.direction == 'P')
    {
        Enemy.x += Enemy.speed + points/8;
        if(Enemy.x > ScreenWidth)
        {
            EnemyBasicPosition(Enemy,ScreenHeight,ScreenWidth, points);
            points++;
        }
    }
    if (Enemy.direction == 'L')
    {
        Enemy.x -= Enemy.speed + points/8;
        if(Enemy.x < 0)
        {
            EnemyBasicPosition(Enemy,ScreenHeight,ScreenWidth, points);
            points++;
        }
    }
    Enemy.y += rand() % 10 - 5;
    if (Enemy.y > ScreenHeight - Enemy.size) Enemy.y = ScreenHeight - Enemy.size;
    if (Enemy.y < 0) Enemy.y = 0;
}
void PlayerMove(Player &Player, const int ScreenHeight, const int ScreenWidth)
{
    if (IsKeyDown(KEY_RIGHT)) Player.x += Player.speed;
    if (IsKeyDown(KEY_LEFT)) Player.x -= Player.speed;
    if (IsKeyDown(KEY_UP)) Player.y -= Player.speed;
    if (IsKeyDown(KEY_DOWN)) Player.y += Player.speed;
    if (Player.x < 0) Player.x = 0;
    if (Player.y < 0) Player.y = 0;
    if (Player.x > ScreenWidth - Player.size) Player.x = ScreenWidth - Player.size;
    if (Player.y > ScreenHeight - Player.size) Player.y = ScreenHeight - Player.size;
}
void PowerupSet (Rectangle p,Player &player, Powerup &powerup, const int ScreenHeight, const int ScreenWidth, float &timer,float &timerSec,bool &shield, Sound powerupsound, int &points, int &lifes, Texture point, Texture life, Texture speed, Texture shieldImage)
{
    Rectangle PowerupRect = {powerup.x, powerup.y, 40, 40};
    if (powerup.type == Powerup::Point)
    {
        point.width = 40;
        point.height = 40;
        DrawTexture(point, powerup.x,powerup.y,BLUE);
    }
    if (powerup.type == Powerup::Life)
    {
        life.width = 40;
        life.height = 40;
        DrawTexture(life, powerup.x,powerup.y,BLUE);
    }
    if (powerup.type == Powerup::Speed && timer<=0.0)
    {
        speed.width = 40;
        speed.height = 40;
        DrawTexture(speed, powerup.x,powerup.y,BLUE);
    }
    if (powerup.type == Powerup::Shield && timer<=0.0)
    {
        shieldImage.width = 40;
        shieldImage.height = 40;
        DrawTexture(shieldImage, powerup.x,powerup.y,BLUE);
    }
    if (CheckCollisionRecs(p, PowerupRect))
    {
        if (powerup.type == Powerup::Point)
        {
            points += 5;
            PlaySound(powerupsound);
            PowerupBasicPosition (powerup,ScreenHeight, ScreenWidth);
        }
         else if (powerup.type == Powerup::Life)
        {
            lifes++;
            PlaySound(powerupsound);
            PowerupBasicPosition (powerup,ScreenHeight, ScreenWidth);
        }
         else if (powerup.type == Powerup::Speed && timer <= 0.0 && timerSec <= 0.0)
        {
            timer = 6.0;
            PlaySound(powerupsound);
            player.speed = 12;
            player.color = BLUE;
            PowerupBasicPosition (powerup,ScreenHeight, ScreenWidth);
        }
         else if (powerup.type == Powerup::Shield)
        {
            timerSec = 3.0;
            PlaySound(powerupsound);
            shield = true;
            player.color = WHITE;
            PowerupBasicPosition (powerup,ScreenHeight, ScreenWidth);
        }
    }
}

void ResetGame (Player &Player, Enemy &Enemy,Powerup &powerup, const int ScreenHeight, const int ScreenWidth, int &points, int&lifes)
{
    EnemyBasicPosition(Enemy,ScreenHeight,ScreenWidth, points);
    PlayerBasicPosition(Player, ScreenHeight, ScreenWidth);
    PowerupBasicPosition (powerup,ScreenHeight, ScreenWidth);
    lifes = 3;
    points = 0;
}
void StartGame(Player &Player, Enemy &Enemy,Powerup &powerup, const int ScreenHeight, const int ScreenWidth, int &points, int&lifes, bool &start)
{
    start = false;
    if(!start)
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawText("Avoid Bubbles game", 140, 100, 50, RED);
        DrawText("Press Space to start", 180, 350, 40, BLACK);
        EndDrawing();
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        EndDrawing();
        start = true;
        ResetGame (Player,Enemy, powerup,ScreenHeight, ScreenWidth,points,lifes);
    }
}
void GameOver (Player &Player, Enemy &Enemy,Powerup &powerup, const int ScreenHeight, const int ScreenWidth, int &points, int&lifes, bool&gameover)
{
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawText("Game over", 100, 100, 100, RED);
    DrawText(TextFormat("Total Score: %d", points), 270, 250, 30, BROWN);
    DrawText("Press R to restart", 250, 380, 40, BLACK);
    EndDrawing();
    if (IsKeyPressed(KEY_R))
    {
        ResetGame(Player,Enemy,powerup,ScreenHeight, ScreenWidth,points,lifes);
        gameover = false;
    }
}
void SetGame(Player &player, Powerup &powerup, Enemy enemies[], Enemy bigEnemies[], const int ScreenHeight, const int ScreenWidth, int NormalEnemy, int BigEnemy, int &points, int &lifes, bool &shield, Sound &hitSound, Sound powerupsound, Texture point, Texture life, Texture speed, Texture shieldImage, float &timer, float &timerSec)
{
    player.size = 50;
    for (int i = 0; i < BigEnemy + points/10; i++)
    {
        bigEnemies[i].size = 60;
    }
    Rectangle p = {player.x, player.y, player.size, player.size};
    Rectangle e[20];
    Rectangle eBig[10];
    for (int i = 0; i < NormalEnemy; i++)
    {
        enemies[i].size = 20;
        e[i] = {enemies[i].x, enemies[i].y, enemies[i].size, enemies[i].size};
    }
    for (int i = 0; i < BigEnemy; i++)
    {
        bigEnemies[i].size = 60;
        eBig[i] = {bigEnemies[i].x, bigEnemies[i].y, bigEnemies[i].size, bigEnemies[i].size};
    }
    PlayerMove(player, ScreenHeight,ScreenWidth);
    PowerupSet ( p,player,powerup,ScreenHeight,ScreenWidth,timer,timerSec,shield,powerupsound,points,lifes, point,life,speed,shieldImage);
    for (int i = 0; i < NormalEnemy; i++)
    {
        EnemyMove(enemies[i], ScreenHeight, ScreenWidth, points);
        if (CheckCollisionRecs(p, e[i]) && !shield)
        {
            lifes--;
            PlaySound(hitSound);
            for (int j = 0; j < NormalEnemy; j++)
            {
                EnemyBasicPosition(enemies[j], ScreenHeight, ScreenWidth,points);
            }
        }
    }
    for (int i = 0; i < BigEnemy; i++)
    {
        EnemyMove(bigEnemies[i], ScreenHeight, ScreenWidth, points);
        if (CheckCollisionRecs(p, eBig[i]) && !shield)
        {
            lifes--;
            PlaySound(hitSound);
            for (int j = 0; j < BigEnemy; j++)
            {
                EnemyBasicPosition(bigEnemies[j], ScreenHeight, ScreenWidth, points);
            }
        }
    }
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    for ( int  i = 0; i < NormalEnemy; i++) DrawRectangleRec(e[i], DARKGREEN);
    for ( int  i = 0; i < BigEnemy; i++) DrawRectangleRec(eBig[i], YELLOW);
    DrawRectangleRec(p, player.color);
    DrawText(TextFormat("Lifes: %d", lifes), 50, 10, 30, BLUE);
    DrawText(TextFormat("Score: %d", points), 300, 10, 30, BLUE);
    //DrawText(TextFormat("Best Score: %d", record), 550, 10, 30, BLUE);
    EndDrawing();
}
int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetTargetFPS(60);
    InitWindow(screenWidth, screenHeight, "Avoid Bubbles Game 1.02 (update)");
    InitAudioDevice();
    Music music = LoadMusicStream("gamemusic.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.22f);
    Sound hitSound = LoadSound("failsound.mp3");
    SetSoundVolume(hitSound, 0.5f);
    Sound powerupsound = LoadSound("1upsound.mp3");
    SetSoundVolume(powerupsound, 0.5f);
    Texture2D point = LoadTexture("point.png");
    Texture2D life = LoadTexture("lifeMushroom.png");
    Texture2D speed = LoadTexture("speed.png");
    Texture2D shieldImage = LoadTexture("shield.png");
    srand(time(NULL));
    bool shield = false;
    float timer = 0.0;
    float timerSec = 0.0;
    int points = 0, lifes = 3, record = 0;
    bool start = false, gameover = false;
    Player player;
    Enemy enemies[20];
    Enemy bigEnemies[10];
    Powerup powerup;
    int EnemyCount = 3;
    int BigEnemyCount = 1;
    int NormalEnemy = EnemyCount + points/6;
    int BigEnemy = BigEnemyCount + points/10;
    PlayerBasicPosition(player, screenHeight, screenWidth);
    for (int i = 0; i < NormalEnemy; i++)
        EnemyBasicPosition(enemies[i], screenHeight, screenWidth, points);
    for (int i = 0; i < BigEnemy; i++)
        EnemyBasicPosition(bigEnemies[i], screenHeight, screenWidth, points);
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        if (!start)StartGame(player, enemies[0],powerup, screenHeight, screenWidth, points, lifes, start);
        if (start && !gameover) SetGame(player,powerup, enemies, bigEnemies, screenHeight, screenWidth, NormalEnemy, BigEnemy, points, lifes, shield, hitSound,powerupsound, point,life,speed,shieldImage,timer, timerSec);
        NormalEnemy = EnemyCount + points/25;
        BigEnemy = BigEnemyCount + points/40;
        float delta = GetFrameTime();
        if (timer <= 0.0)
        {
            player.speed = 5;
        }
        else timer -= delta;
        if (timerSec <= 0.0)
        {
            shield = false;
        }
        else timerSec -= delta;
        if (shield) player.color = WHITE;
        else if (timer > 0.0) player.color = BLUE;
        else player.color = RED;
        if (lifes <= 0) gameover = true;
        if (gameover) GameOver(player, enemies[0],powerup, screenHeight, screenWidth, points, lifes, gameover);
    }
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

