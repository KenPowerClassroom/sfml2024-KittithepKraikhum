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


struct point
{ int x,y;};

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

    point plat[20];

    for (int i=0;i<10;i++)
      {
       plat[i].x=rand()% WINDOW_WIDTH;
       plat[i].y=rand()% WINDOW_HEIGHT;
      }

    int x=100,y=100,h=200;
    float dx=0,dy=0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left)) x-=3;

    dy+=0.2;
    y+=dy;
    if (y>500)  dy=-10;

    if (y<h)
    for (int i=0;i<10;i++)
    {
      y=h;
      plat[i].y=plat[i].y-dy;
      if (plat[i].y> WINDOW_HEIGHT) {plat[i].y=0; plat[i].x=rand()% WINDOW_WIDTH;}
    }

    for (int i=0;i<10;i++)
     if ((x+ PLAYER_WIDTH >plat[i].x) && (x+20<plat[i].x+ PLATFORM_WIDTH)
      && (y+ PLAYER_HEIGHT >plat[i].y) && (y+ PLAYER_HEIGHT <plat[i].y+ PLATFORM_HEIGHT) && (dy>0))  dy=JUMP_FORCE;

    sPers.setPosition(x,y);

    app.draw(sBackground);
    app.draw(sPers);
    for (int i=0;i<10;i++)
    {
    sPlat.setPosition(plat[i].x,plat[i].y);
    app.draw(sPlat);
    }

    app.display();
}

    return 0;
}
