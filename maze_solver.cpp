#include <iostream>
#include <fstream>
#include <stack>
#include <SFML/Graphics.hpp>

/* note: to compile "g++ -o maze_solver maze_solver.cpp -lsfml-graphics -lsfml-window -lsfml-system" */

using namespace std;

const int MAX_SIZE = 10;

struct cell
{
    int row;
    int col;
};

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

bool isValid(int row, int col, char maze[MAX_SIZE][MAX_SIZE], int r, int c)
{
    return (row >= 0 && row < r && col >= 0 && col < c && maze[row][col] != '#');
}

bool solveMaze(char maze[MAX_SIZE][MAX_SIZE], int r, int c, int sr, int sc)
{
    stack<cell> stack;
    cell start = {sr, sc};
    stack.push(start);
    while (!stack.empty())
    {
        cell current = stack.top();
        stack.pop();
        if (maze[current.row][current.col] == 'E')
        {
            maze[current.row][current.col] = 'X';
            return true;
        }
        else if (maze[current.row][current.col] == 'S')
        {
            maze[current.row][current.col] = 'S';
        }
        else
        {
            maze[current.row][current.col] = 'V';
        }
        for (int i = 0; i < 4; i++)
        {
            int newrow = current.row + dr[i];
            int newcol = current.col + dc[i];
            if (isValid(newrow, newcol, maze, r, c) && maze[newrow][newcol] != 'V')
            {
                stack.push({newrow, newcol});
            }
        }
    }
    return false;
}

void drawMaze(char maze[MAX_SIZE][MAX_SIZE], int r, int c)
{
    sf::RenderWindow window(sf::VideoMode(c * 40, r * 40), "Maze Solver");
    window.setFramerateLimit(60);

    sf::RectangleShape cellShape(sf::Vector2f(40, 40));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                switch (maze[i][j])
                {
                case 'S':
                    cellShape.setFillColor(sf::Color::Blue);
                    break;
                case 'E':
                    cellShape.setFillColor(sf::Color::Red);
                    break;
                case '#':
                    cellShape.setFillColor(sf::Color(139, 69, 19));
                    break;
                case 'V':
                    cellShape.setFillColor(sf::Color::Green);
                    break;
                case 'X':
                    cellShape.setFillColor(sf::Color::Red);
                    break;
                default:
                    cellShape.setFillColor(sf::Color::White);
                    break;
                }

                cellShape.setPosition(j * 40, i * 40);
                window.draw(cellShape);
            }
        }

        window.display();
    }
}

int main()
{
    int r = 5, c = 5;
    char maze[MAX_SIZE][MAX_SIZE] = {{'#', '#', '#', '#', '#'},
                                     {'S', ' ', '#', '#', '#'},
                                     {'#', ' ', '#', '#', '#'},
                                     {'#', ' ', ' ', ' ', '#'},
                                     {'#', '#', '#', 'E', '#'}};

    cout << "Maze before solving: " << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    if (solveMaze(maze, r, c, 1, 0))
    {
        cout << "Maze after solving: " << endl;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
        drawMaze(maze, r, c);
    }
    else
    {
        cout << "Couldn't solve the maze" << endl;
    }

    return 0;
}
