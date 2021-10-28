#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;


typedef struct
{
    int x, y;
    Texture tex;
    Sprite spr;
} Person;

bool isCollide(Sprite s1, Sprite s2)
{
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int main()
{
    srand(time(NULL));
    RenderWindow app(VideoMode(400, 530), "DDF");
    app.setFramerateLimit(60);

    std::vector<Person> pers(3);
    Person player;
    Person bg;

    bg.tex.loadFromFile("images/bga.png");
    bg.spr.setTexture(bg.tex);

    player.tex.loadFromFile("images/m.png");
    player.spr.setTexture(player.tex);
    player.x = 200;
    player.y = 250;

    for (unsigned int i = 0; i < pers.size(); i++)
    {
        pers[i].tex.loadFromFile("images/pl.png");
        pers[i].spr.setTexture(pers[i].tex);
        pers[i].x = rand() % 400;
        pers[i].y = rand() % 500;

    }


    Event e;

    while(app.isOpen())
    {
        while(app.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                app.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            player.x -= 3;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            player.x += 3;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player.y += 3;
        }

        player.spr.setPosition(player.x, player.y);

        int h = 300;
        float dx = 0, dy = 0;


        dy -= 1.0;
        player.y += dy;

        if (player.y < h)
        {
            dy -= 5;

            for (unsigned int i = 0; i < pers.size(); i++)
            {
                player.y = h;
                pers[i].y = pers[i].y - dy;

                if (pers[i].y > 533)
                {
                    pers[i].y = 0;
                    pers[i].x = rand() % 400;
                }
            }

        }


        app.clear();

        app.draw(bg.spr);
        app.draw(player.spr);


        for (unsigned int i = 0; i < pers.size(); i++)
        {

            if (isCollide(player.spr, pers[i].spr)) {

                player.y += 50;
            }
                        app.draw(pers[i].spr);
            pers[i].spr.setPosition(pers[i].x, pers[i].y);
        }

        for(unsigned int i = 0; i < pers.size(); i++)
        {
            if ((player.x + 50 > pers[i].x)
                && (player.x + 20 < pers[i].x + 68)
                && (player.y + 70 > pers[i].y)
                && (player.y + 70 < pers[i].y + 14)
                && (dy > 0))
            {
                dy = -10;
            }
        }


        app.display();
    }

    return 0;
}

