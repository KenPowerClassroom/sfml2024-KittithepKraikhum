#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

//Magic number
const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 533;
const float GRAVITY = 0.2f;
const float JUMP_FORCE = -10.f;
const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 70;

const int PLATFORM_WIDTH = 68;
const int PLATFORM_HEIGHT = 14;
const int PLAYER_LEFT_OFFSET = 20;

const int PLATFORM_COUNT = 10;

const int PLAYER_SPEED = 3;

const int FALL_LIMIT = 500;

const int CAMERA_HEIGHT = 200;




struct point
{ int x,y;};

//Extract collision into its own function
bool isColliding(int x, int y, float dy, const point& plat)
{
    bool xOverlap = (x + PLAYER_WIDTH > plat.x) &&
        (x + PLAYER_LEFT_OFFSET < plat.x + PLATFORM_WIDTH);

    bool yOverlap = (y + PLAYER_HEIGHT > plat.y) &&
        (y + PLAYER_HEIGHT < plat.y + PLATFORM_HEIGHT);

    return xOverlap && yOverlap && (dy > 0);
}

//Split platform creation into functions
void generatePlatforms(point plat[], int count)
{
    for (int i = 0; i < count; i++)
    {
        plat[i].x = rand() % WINDOW_WIDTH;
        plat[i].y = rand() % WINDOW_HEIGHT;
    }
}



int doodle_jump()
{
    srand(time(0));

    RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Doodle Game!");
    app.setFramerateLimit(60);

    Texture t1,t2,t3;
    t1.loadFromFile("images/doodle_jump/background.png");
    t2.loadFromFile("images/doodle_jump/platform.png");
    t3.loadFromFile("images/doodle_jump/doodle.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    point plat[PLATFORM_COUNT];

    generatePlatforms(plat, PLATFORM_COUNT);

    int x = 100, y = 100;
    float dx=0,dy=0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) x+= PLAYER_SPEED;
    if (Keyboard::isKeyPressed(Keyboard::Left)) x-=PLAYER_SPEED;

    dy+= GRAVITY;
    y+=dy;
    if (y> FALL_LIMIT)  dy= JUMP_FORCE;

    if (y< CAMERA_HEIGHT)
    for (int i=0;i< PLATFORM_COUNT;i++)
    {
      y= CAMERA_HEIGHT;
      plat[i].y=plat[i].y-dy;
      if (plat[i].y> WINDOW_HEIGHT) {plat[i].y=0; plat[i].x=rand()% WINDOW_WIDTH;}
    }

    for (int i=0;i<10;i++)
        if (isColliding(x, y, dy, plat[i]))
        {
            dy = JUMP_FORCE;
        }

    sPers.setPosition(x,y);

    app.draw(sBackground);
    app.draw(sPers);
    for (int i=0;i< PLATFORM_COUNT;i++)
    {
    sPlat.setPosition(plat[i].x,plat[i].y);
    app.draw(sPlat);
    }

    app.display();
}

    return 0;
}
