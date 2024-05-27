#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

class SnakeGame {
private:
    bool isGameOver;                // Check if the player is playing
    int width, height;              // Dimensions of box

    int snakeHeadX, snakeHeadY;     // Location of head in X,Y plot
    int foodX, foodY;               // X,Y loation of food
    int score;

    std:: vector<int> snakeTailX, snakeTailY;
    int snakeTailLength;

    enum eDirection {
        STOP = 0,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    eDirection direction;

public:
    bool getIsGameOver() {return isGameOver;}

    void Setup();
    void Print();
    void Input();
    void Logic();
};
