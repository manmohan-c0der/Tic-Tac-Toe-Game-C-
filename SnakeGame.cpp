#include <iostream>
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;
#define MAX_LENGHT 1000

//  Directions define global
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_RIGHT = 'R';
const char DIR_LEFT = 'L';

// Define console width and height
int consoleWidth, consoleHeight;

void DisplayScreen()
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hconsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
struct Point
{
    int xCoord;
    int yCoord;
    Point()
    {
    }
    Point(int x, int y)
    {
        xCoord = x;
        yCoord = y;
    }
};

class Snake
{
    int length;
    char direction;

public:
    Point body[MAX_LENGHT];
    Snake(int x, int y)
    {
        length = 1;
        body[0] = Point(x, y);
        direction = DIR_LEFT;
    }
    // ~Snake()
    // {
    //     delete[] body;
    // }
    int getLenght()
    {
        return length;
    }
    void changeDirection(char newDirection)
    {
        if (newDirection == DIR_UP && direction != DIR_DOWN)
        {
            direction = newDirection;
        }
        else if (newDirection == DIR_DOWN && direction != DIR_UP)
        {
            direction = newDirection;
        }
        else if (newDirection == DIR_LEFT && direction != DIR_RIGHT)
        {
            direction = newDirection;
        }
        else if (newDirection == DIR_RIGHT && direction != DIR_LEFT)
        {
            direction = newDirection;
        }
    }
    bool SnakeMove(Point food)
    {
        for (int i = length - 1; i > 0; i--)
        {
            body[i] = body[i - 1];
        }
        switch (direction)
        {
            int val;
        case DIR_UP:
            val = body[0].yCoord;
            body[0].yCoord = val -1;
            break;
        case DIR_DOWN:
            val = body[0].yCoord;
            body[0].yCoord = val + 1;
            break;
        case DIR_LEFT:
            val = body[0].xCoord;
            body[0].xCoord = val - 1;
            break;
        case DIR_RIGHT:
            val = body[0].xCoord;
            body[0].xCoord = val + 1;
            break;
        default:
            break;
        }
        //  snake bites itself
        for (int i = 1; i < length; i++)
        {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord)
            {
                return false;
            }
        }
        //  Snake eats food
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord)
        {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length++;
        }
        return true;
    }
};
class Board
{
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;

public:
    Board()
    {
        spawanFood();
        snake = new Snake(10, 10);
        score = 0;
    }
    ~Board()
    {
        delete snake;
    }
    int getScore()
    {
        return score;
    }
    void spawanFood()
    {
        int x = rand() % consoleHeight;
        int y = rand() % consoleWidth;
        food = Point(x, y);
    }
    void DisplayCurrentScore()
    {
        gotxy(consoleWidth / 2, 0);
        cout << "Current Score : " << score;
    }
    void gotxy(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void draw()
    {
        system("cls");
        for (int i = 0; i < snake->getLenght(); i++)
        {
            gotxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }
        gotxy(food.xCoord, food.yCoord);
        cout << FOOD;
        DisplayCurrentScore();
    }

    bool update()
    {
        bool isAlive = snake->SnakeMove(food);
        if (isAlive == false)
        {
            return false;
        }
        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord)
        {
            score++;
            spawanFood();
        }
        return true;
    }
    void getInput()
    {
        if (kbhit())
        {
            char key = getch();
            if (key == 'w' || key == 'W')
            {
                snake->changeDirection(DIR_UP);
            }
            else if (key == 'd' || key == 'D')
            {
                snake->changeDirection(DIR_LEFT);
            }
            else if (key == 'a' || key == 'A')
            {
                snake->changeDirection(DIR_RIGHT);
            }
            else if (key == 's' || key == 'S')
            {
                snake->changeDirection(DIR_DOWN);
            }
        }
    }
};

int main()
{
    srand(time(0));
    DisplayScreen();
    Board *board = new Board();
    while (board->update())
    {
        board->getInput();
        board->draw();
        Sleep(1000);
    }
    cout << "Game Over !" << endl;
    cout << "Final Score is : " << board->getScore();
    return 0;
}