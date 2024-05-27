#include "SnakeGame.h"

void SnakeGame::Setup() {
    // Initialize game state
    isGameOver = false; // Game is not over
    score = 0; // Score starts at 0

    width = 20; // Width of game area
    height = 12; // Height of game area

    direction = STOP; // Start stopped
    snakeHeadX = width / 2; // Start in the middle
    snakeHeadY = height / 2; // Start in the middle

    // Randomize food location within game area
    srand(time(NULL));
    foodX = rand() % width;
    foodY = rand() % height;

    // Resize vector size to 100 for snake tail
    snakeTailX.resize(100);
    snakeTailY.resize(100);
}

void SnakeGame::Print() {
    system("cls"); // Clear screen

    // Print top border
    for (int i = 0; i < width + 2; i++)
        std::cout << "-";
    std::cout << std::endl;

    // Print game area
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if (j == 0)
                std::cout <<"!";
            
            if(i == snakeHeadY && j == snakeHeadX)
                std::cout<< "S"; // Print snake head
            else if(i == foodY && j == foodX)
                std::cout << "%"; // Print food
            else {
                // Check if current position is part of snake tail
                bool isSnakeTailCoord = false;
                for(int k = 0; k < snakeTailLength; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        std::cout << "s"; // Print snake tail
                        isSnakeTailCoord = true;
                    }
                }
                if(!isSnakeTailCoord)
                    std::cout << " "; // Empty space
            }
            if (j == width - 1)
                std::cout << "!";
        }
        std::cout << std::endl;
    }

    // Print bottom border
    for (int i = 0; i < width + 2; i++)
        std::cout << "-";
    std::cout << std::endl << std::endl;

    // Print score
    std::cout << "Score: " << score;
    std::cout << std::endl << std::endl;
}

void SnakeGame::Input() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'w':
                direction = UP; // Change direction to up
                break;
            case 'd':
                direction = RIGHT; // Change direction to right
                break;
            case 'a':
                direction = LEFT; // Change direction to left
                break;
            case 's':
                direction = DOWN; // Change direction to down
                break;
            case 27: // Esc button
                isGameOver = true; // End game
                break;
        }   
    }
}

void SnakeGame::Logic() {
    // Store previous position of first tail segment
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;

    // Update first tail segment with head position
    snakeTailX[0] = snakeHeadX;
    snakeTailY[0] = snakeHeadY;

    // Update positions of other tail segments
    for (int i = 1; i < snakeTailLength; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move snake head based on current direction
    switch (direction) {
        case LEFT:
            snakeHeadX--;
            break;
        case RIGHT:
            snakeHeadX++;
            break;
        case UP:
            snakeHeadY--;
            break;
        case DOWN:
            snakeHeadY++;
            break;
        default:
            break;
    }

    // Handle wrapping around edges of game area
    if (snakeHeadX >= width) 
        snakeHeadX = 0;
    else if (snakeHeadX < 0) 
        snakeHeadX = width - 1;
    
    if (snakeHeadY >= height)
        snakeHeadY = 0;
    else if (snakeHeadY < 0)
        snakeHeadY = height - 1;
    
    // Check for collision with snake tail
    for (int i = 0; i < snakeTailLength; i++) {
        if (snakeTailX[i] == snakeHeadX && snakeTailY[i] == snakeHeadY)
            isGameOver = true;
    }
    
    // Check for collision with food
    if (snakeHeadX == foodX && snakeHeadY == foodY) {
        // Increase snake length and score
        snakeTailLength++;
        score++;

        // Randomize new food location
        srand(time(NULL));
        foodX = rand() % width;
        foodY = rand() % height;
    }
}

int main() {
    // Initialize snake game
    SnakeGame snake;
    snake.Setup();

    // Game loop
    while(!snake.getIsGameOver()) {
        // Print game state
        snake.Print();
        // Handle user input
        snake.Input();
        // Update game logic
        snake.Logic();
        // Delay for smoother gameplay
        Sleep(150);
    }

    return 0;
}