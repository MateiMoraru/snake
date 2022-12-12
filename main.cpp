#include <iostream>
#include <vector>
#include <cstdlib>
#include <Windows.h>
#include <ctime>
#include <queue>
using namespace std;

vector<vector<char>> make_map(int size)
{
    vector<vector<char>> map(size, vector<char>(size * 2, ' '));

    for(int x = 0; x < size * 2; x++)
    {
        map[0][x] = '#';
        map[size - 1][x] = '#';
    }

    for(int y = 0; y < size; y++)
    {
        map[y][0] = '#';
        map[y][size * 2 - 1] = '#';
    }

    return map;
}

void print_map(vector<vector<char>> map)
{
    system("clear");

    for(int i = 0; i < map.size(); i++)
    {
        for(int j = 0; j < map[i].size(); j++)
        {
            cout << map[i][j];
        }
        cout << '\n';
    }
}

vector<int> make_apple(vector<vector<char>> &map)
{
    // TODO: check if apple collides with snake

    vector<int> a(2);
    a[0] = rand() % 8 + 1;
    a[1] = rand() % 18 + 1;

    while(map[a[0]][a[1]] == '0')
    {
        a[0] = rand() % 8 + 1;
        a[1] = rand() % 18 + 1;
    }

    map[a[0]][a[1]] = '@';

    return a;
}

queue<pair<int, int>> make_snake(vector<vector<char>> &map)
{
    queue<pair<int, int>> snake;
    snake.push({5, 9});
    snake.push({5, 8});
    snake.push({5, 7});

    map[5][9] = map[5][8] = map[5][7] = '0';
    return snake;
}

vector<pair<int, int>> moves = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool update_map(vector<vector<char>> &map, queue<pair<int, int>> &snake, int direction, vector<int> &apple)
{
     if(apple[0] != snake.back().first || apple[1] != snake.back().second)
     {
         map[snake.front().first][snake.front().second] = ' ';
         snake.pop();
     }
     else
     {
         apple = make_apple(map);
     }

     pair<int, int> snake_head = snake.back();

     pair<int, int> next_head = snake_head;

     next_head.first += moves[direction].first;
     next_head.second += moves[direction].second;

    if(map[next_head.first][next_head.second] == '#')
    {
        if(direction == 0)
        {
            next_head.second = 1;
        }
        if(direction == 1)
        {
            next_head.first = 1;
        }
        if(direction == 2)
        {
            next_head.second = map[0].size() - 2;
        }
        if(direction == 3)
        {
            next_head.first = map.size() - 2;
        }
    }

     snake.push(next_head);

     if(map[next_head.first][next_head.second] == '0')
     {
         return false;
     }

     map[next_head.first][next_head.second] = '0';

     return true;
}


int main()
{
    srand(time(NULL));

    int direction = 3;
    vector<vector<char>> map = make_map(10);
    queue<pair<int, int>> snake = make_snake(map);
    vector<int> apple = make_apple(map);
    print_map(map);

    int time = 0;

    while(true) {

        Sleep(50);
        time += 50;

        if (GetKeyState(VK_DELETE) & 0x8000) {
            return 0;
        }

        if (GetKeyState(VK_LEFT) & 0x8000 && direction != 0) {
            direction = 2;
        }
        if (GetKeyState(VK_RIGHT) & 0x8000 && direction != 2) {
            direction = 0;
        }
        if (GetKeyState(VK_UP) & 0x8000 && direction != 1) {
            direction = 3;
        }
        if (GetKeyState(VK_DOWN) & 0x8000 && direction != 3) {
            direction = 1;
        }

        if (time == 500) {
            time = 0;

            if(!update_map(map, snake, direction, apple))
            {
                cout << "Lost game!!!!" << endl;
                return 0;
            }
            print_map(map);
        }
    }
}
