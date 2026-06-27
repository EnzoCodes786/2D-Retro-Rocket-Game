#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int score = 0;
int game_state = 2;
float screen_w = 1280;
float screen_h = 720;
Color neonCyan = { 0, 255, 255, 255 };
Color neonPurple = { 180, 90, 255, 255 };
Color electricBlue = { 80, 170, 255, 255 };
Color neonYellow = { 255, 230, 80, 255 };



float m_x1 = 420;
float m_y1 = 180; 
float m_x2 =540 ;
float m_y2 = 250;
float m_x3 =470 ;
float m_y3 =350 ;
class Player
{
public:
    float x, y, v;
    Image img;
    Texture2D tex;
    void init()
    {
        img = LoadImage("resources/rocket.png");
        ImageResize(&img, 64, 64);
        tex = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    void Update()
    {
        if (IsKeyDown(KEY_W))
        {
            y -= v;
        }
        else if (IsKeyDown(KEY_S))
        {
            y += v;
        }
        else if (IsKeyDown(KEY_A))
        {
            x -= v;
        }
        else if (IsKeyDown(KEY_D))
        {
            x += v;
        }

        x = Clamp(x, 10, screen_w - 10);
        y = Clamp(y, 10, screen_h - 10);
    }
    void Draw()
    {
        DrawTexture(tex, x, y, WHITE);
    }

    Rectangle GetRect() const
    {
        return {x, y, (float)tex.width, (float)tex.height};
    }
};

class Background
{

public:
    float x, y;
    Image backdrop;
    Texture2D tex;
    void init()
    {
        backdrop = LoadImage("resources/background.png");
        ImageResize(&backdrop, screen_w, screen_h);
        tex = LoadTextureFromImage(backdrop);
        UnloadImage(backdrop);
    }
    void Draw()
    {
        DrawTexture(tex, x, y, WHITE);
    }
};

class Bullets
{

public:
    float x, y, v;
    Image bullet;
    Texture2D tex1;
    //    Rectangle rec;

    void Update()
    {

        // rec = {x, y, (float)tex1.width, (float)tex1.height};
        x += v;
    }
    void init()
    {
        bullet = LoadImage("resources/bullet.png");
        ImageResize(&bullet, 20, 20);
        tex1 = LoadTextureFromImage(bullet);
        UnloadImage(bullet);

        //  rec = {x, y, (float)tex1.width, (float)tex1.height};
    }
    void Draw()
    {
        DrawTexture(tex1, x, y, WHITE);
    }
    Rectangle GetRect() const
    {
        return {x, y, (float)tex1.width, (float)tex1.height};
    }
};

class Enemies
{
public:
    float x, y, v;
    Image Enemy;
    Texture2D tex2;
    //   Rectangle rec;

    void init()
    {
        Enemy = LoadImage("resources/enemy.png");
        ImageResize(&Enemy, 40, 40);
        tex2 = LoadTextureFromImage(Enemy);
        UnloadImage(Enemy);
    }
    void Update()
    {

        x -= v;
    }
    void Draw()
    {
        DrawTexture(tex2, x, y, WHITE);
    }
    Rectangle GetRect() const
    {
        return {x, y, (float)tex2.width, (float)tex2.height};
    }
};


vector<Bullets> bulletsArr;
vector<Enemies> enemiesArr;

void firingBullet(float Posx, float Posy, float speed)
{
    Bullets B;
    B.init();
    B.x = Posx;
    B.y = Posy;
    B.v = speed;

    bulletsArr.push_back(B);
}

void enemiesSpawn(float Posx, float Posy, float speed)
{
    Enemies E;
    E.init();
    E.x = Posx;
    E.y = Posy;
    E.v = speed;

    enemiesArr.push_back(E);
}

void onCollision(Player &P)
{

    for (int i = 0; i < bulletsArr.size(); i++)
    {
        for (int j = 0; j < enemiesArr.size(); j++)
        {
            if (CheckCollisionRecs(bulletsArr[i].GetRect(), enemiesArr[j].GetRect()))
            {

                score++;
                
                bulletsArr.erase(bulletsArr.begin() + i);
                enemiesArr.erase(enemiesArr.begin() + j);
                i--;
                break;
            }
            if (CheckCollisionRecs(P.GetRect(), enemiesArr[j].GetRect()))
            {
                cout << "Game Over!!" << endl;
                game_state = 1;
                if (IsKeyPressed(KEY_ENTER))
                {
                    game_state = 0;
                    P.x = GetRandomValue(20, 50);
                    P.y = GetRandomValue(20, 600);
                    score = 0;
                }
            }
        }
    }
}

void Menue()
{
    Texture2D menu = LoadTexture("resources/menu.png");
    DrawTexture(menu, 0, 0, WHITE);
   
    DrawText("VOID RUNNER", m_x1+2, m_y1+2, 60, Fade(BLACK, 0.5f)); // shadow
    DrawText("VOID RUNNER", m_x1, m_y1, 60, electricBlue);             // main text
    
    DrawText("By Aryan Qayum", m_x2+2, m_y2+2, 40, Fade(BLACK, 0.5f)); // shadow
    DrawText("By Aryan Qayum", m_x2, m_y2, 40, neonCyan);             // main text

    DrawText("Press SHIFT to Start", m_x3+2, m_y3+2, 40, Fade(BLACK, 0.5f)); // shadow
    DrawText("Press SHIFT to Start", m_x3, m_y3, 40, neonYellow);             // main text

   

    
    
}
