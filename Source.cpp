#include <iostream>
#include "SFML/Graphics.hpp"
#include "globals.h"
#include "ghost.h"
using namespace std;
using namespace sf;


int main() {
    //game set up (you'll need these lines in every game)
    RenderWindow screen(VideoMode(896, 992), "pac man"); //set up screen
    Event event; //set up event queue
    Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    Texture block;
    block.loadFromFile("block.png");
    Sprite wall;
    wall.setTexture(block);
    Texture bg;
    bg.loadFromFile("bg.png");
    Sprite background;
    background.setTexture(bg);
    Texture pacman;
    pacman.loadFromFile("pac.png");
    IntRect pac(0, 0, 40, 40);
    Sprite playerImg(pacman, pac);
    int ticker = 0;
    int frameNum = 0;
    int rowNum = 0;

    sf::Color Red = sf::Color(253, 37, 0);
    sf::Color Pink = sf::Color(253, 177, 177);
    sf::Color Cyan = sf::Color(0, 222, 225);
    sf::Color Orange = sf::Color(253, 159, 2);

    int map[31][29] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
        1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,
        1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,
        1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
        1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,
        1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,
        1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,
        1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,
        1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,
        2,2,2,2,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,2,2,2,2,0,
        1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,
        1,1,1,1,1,1,0,1,1,0,1,2,2,2,2,2,2,1,0,1,1,0,1,1,1,1,1,1,1,
        2,2,2,2,2,2,0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0,2,2,2,2,2,2,2,
        1,1,1,1,1,1,0,1,1,0,1,2,2,2,2,2,2,1,0,1,1,0,1,1,1,1,1,1,1,
        1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,
        2,2,2,2,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,2,2,2,2,0,
        1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,
        1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
        1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,
        1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,
        1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,
        1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,
        1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,
        1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,
        1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,
        1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
    };

    //player setup
    int xpos = 32;
    int ypos = 443;
    int vx = 0;
    int vy = 0;
    CircleShape player(16);
    player.setFillColor(Color(5, 111, 1)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };
    int score = 0;
    sf::RectangleShape grid(sf::Vector2f(32, 32));
    grid.setOutlineColor(sf::Color::White);
    grid.setFillColor(sf::Color::Transparent);
    grid.setOutlineThickness(1);
    bool gridMode = false;

    CircleShape dot(3);
    dot.setFillColor(Color(240, 240, 240));

    ghost Blinky;
    Blinky.initGhost(448, 496, 1, 0, 3, Red);
    ghost Inky;
    Inky.initGhost(468, 496, 1, 0, 3, Cyan);
    ghost Pinky;
    Pinky.initGhost(488, 496, 1, 0, 3, Pink);
    ghost Clyde;
    Clyde.initGhost(508, 496, 1, 0, 5, Orange);
    
    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP ###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT 
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

            if (Keyboard::isKeyPressed(Keyboard::G)) {
                gridMode = true;
            }
            else gridMode = false;

        }//end event loop---------------------------------------------------------------


        //move Mr. Pac
        if (keys[LEFT] == true) {
            vx = -3;
        }
        else if (keys[RIGHT] == true) {
            vx = 3;
        }
        if (keys[UP] == true) {
            vy = -3;
        }
        else if (keys[DOWN] == true) {
            vy = 3;
        }
        cout << vx << " , " << vy << endl;

        //collision
        //right
        if (vx > 0 && (map[(ypos + 5) / 32][(xpos + 16 * 2 + 5) / 32] == 1 || map[(ypos + 16 * 2 - 5) / 32][(xpos + 16 * 2 + 5) / 32] == 1))
            vx = 0;

        //left
        if (vx < 0 && (map[(ypos + 5) / 32][(xpos - 5) / 32] == 1 || map[(ypos + 16 * 2 - 5) / 32][(xpos - 5) / 32] == 1))
            vx = 0;

        //down, so positive
        if (vy > 0 && (map[(ypos + 16 * 2 + 5) / 32][(xpos + 5) / 32] == 1 || map[(ypos + 16 * 2 + 5) / 32][(xpos + 16 * 2 - 5) / 32] == 1))
            vy = 0;

        //up, so negative
        if (vy < 0 && (map[(ypos - 5) / 32][(xpos + 16 * 2 - 5) / 32] == 1 || map[(ypos - 5) / 32][(xpos + 5) / 32] == 1))
            vy = 0;

        xpos += vx;
        ypos += vy;

        if (vx != 0 || vy != 0) {
            ticker += 1;
            if (ticker % 10 == 0)
                frameNum += 1;
            if (frameNum > 5)
                frameNum = 0;
        }
        pac = sf::IntRect(0, frameNum * 40, 40, 40);
        sf::Sprite playerImg(pacman, pac);
        player.setPosition(xpos - 4, ypos - 4);
        playerImg.setPosition(xpos - 4, ypos - 4);

        if (vx == -3) { //left
            playerImg.setRotation(180.f);
            playerImg.setPosition(xpos + 40, ypos + 40); // offset to keep the image where colission circle is
        }
        if (vx == 3) { //right
            playerImg.setRotation(0.f);
        }
        if (vy == 3) { //down
            playerImg.setRotation(90.f);
            playerImg.setPosition(xpos + 40, ypos);
        }
        if (vy == -3) { //up
            playerImg.setRotation(270.f);
            playerImg.setPosition(xpos, ypos + 40);
        }

        if (vx == 0) {
            xpos = ((xpos + PACSIZE) / WALLSIZE) * WALLSIZE;
        }

        if (vy == 0) {
            ypos = ((ypos + PACSIZE) / WALLSIZE) * WALLSIZE;
        }

        if (xpos < -20) {
            xpos = 880;
        }
        if (xpos > 880) {
            xpos = -20;
        }

        if (map[(ypos + 20) / 32][(xpos + 20) / 32] == 0) {
            map[(ypos + 20) / 32][(xpos + 20) / 32] = 2;
            score += 100;
        }


        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << "Score: " << "\n" << score << "\n\n\n\n\n\n\n";

        if (score == 100) Blinky.leave();
        if (score == 2500) Inky.leave();
        if (score == 5000) Pinky.leave();
        if (score == 28000) Clyde.leave();


        Blinky.chase1(xpos, ypos, map);
        Inky.chase2(xpos, ypos, map);
        Pinky.chase3(xpos, ypos, map);
        Clyde.chase4(xpos, ypos, map);

        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear
        for (int rows = 0; rows < 31; rows++)
            for (int cols = 0; cols < 28; cols++) {
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 32, rows * 32);
                    screen.draw(wall);
                }
            }
        for (int rows = 0; rows < 31; rows++)
            for (int cols = 0; cols < 28; cols++) {
                if (map[rows][cols] <= 0 or map[rows][cols] == 2) {
                    background.setPosition(cols * 32 - 14, rows * 32 - 14);
                    screen.draw(background);
                }
            }
        for (int rows = 0; rows < 31; rows++)
            for (int cols = 0; cols < 28; cols++) {
                if (map[rows][cols] == 0) {
                    dot.setPosition(cols * 32 + 13.5, rows * 32 + 13.5);
                    screen.draw(dot);
                }
            }
        if (gridMode == true) {
            for (int rows = 0; rows < 31; rows++)
                for (int cols = 0; cols < 28; cols++) {
                    grid.setPosition(cols * 32, rows * 32);
                    screen.draw(grid);
                }
        }

        screen.draw(playerImg); //draw player
        Blinky.drawGhost(screen);
        Inky.drawGhost(screen);
        Pinky.drawGhost(screen);
        Clyde.drawGhost(screen);
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main