#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

std::vector<std::vector<int>> readMazeFromFile(const std::string& filename);
void dijkstra(const std::vector<std::vector<int>>& maze, const std::pair<int,int>& start, std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& prev);
std::vector<std::pair<int,int>> shortestPath(const std::vector<std::vector<int>>& maze, const std::pair<int,int>& start, const std::pair<int,int>& end);

class Izgara{
public:

     int  endX, endY,ROW,COL;
     std::vector<std::vector<int>>  mazeolustur(string filename){
    std::vector<std::vector<int>> maze = readMazeFromFile(filename);
      ROW = maze.size();
      COL = maze[0].size();

     return maze;
    }

};

int main()
{
    srand(time(0));
   string filename= "C://Users//Sezer//Desktop//labirent1.txt";
std::vector<std::vector<int>> maze = readMazeFromFile(filename);



   Izgara mazeo;
    maze = mazeo.mazeolustur(filename);

    int startX, startY,ROW,COL;

    ROW=mazeo.ROW;
    COL=mazeo.COL;
    startX = 0;
    startY = 1;



    std::vector<std::vector<int>> dist(ROW, std::vector<int>(COL, INF));
    std::vector<std::vector<int>> prev(ROW, std::vector<int>(COL, -1));
    dijkstra(maze, {startX, startY}, dist, prev);

    int endX, endY, minDist = INF;
    for (int i = 0; i < ROW; ++i) {
        if (maze[i][0] == 0 && dist[i][0] < minDist) {
            endX = i;
            endY = 0;
            minDist = dist[i][0];
        }
        if (maze[i][COL-1] == 0 && dist[i][COL-1] < minDist) {
            endX = i;
            endY = COL-1;
            minDist = dist[i][COL-1];
        }
    }
    for (int j = 0; j < COL; ++j) {
        if (maze[0][j] == 0 && dist[0][j] < minDist) {
            endX = 0;
            endY = j;
            minDist = dist[0][j];
        }
        if (maze[ROW-1][j] == 0 && dist[ROW-1][j] < minDist) {
            endX = ROW-1;
            endY = j;
            minDist = dist[ROW-1][j];
        }
    }


    std::vector<std::pair<int,int>> path = shortestPath(maze, {startX, startY}, {endX, endY});


    sf::RenderWindow window(sf::VideoMode(COL*40, ROW*40), "Maze");

    sf::RectangleShape block(sf::Vector2f(40, 40));
    block.setOutlineThickness(2);
    block.setOutlineColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();


       for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                if (maze[i][j] == 0) {
                    block.setFillColor(sf::Color::White);
                    block.setPosition(j * 40, i * 40);
                    window.draw(block);
                } else if (maze[i][j] == 1) {
                    block.setFillColor(sf::Color::Black);
                    block.setPosition(j * 40, i * 40);
                    window.draw(block);
                } else if (maze[i][j] == 2) {
                    block.setFillColor(sf::Color::Black);

                    block.setPosition(j * 40, i * 40);
                    window.draw(block);
                } else if (maze[i][j] == 3) {
                    block.setFillColor(sf::Color::Black);
                    block.setPosition(j * 40, i * 40);
                    window.draw(block);
                }
            }
        }

        for (int i = 0; i < path.size(); ++i) {
            int x = path[i].second;
            int y = path[i].first;
            block.setFillColor(sf::Color::Yellow);
            block.setPosition(x*40, y*40);
            window.draw(block);
        }

        block.setFillColor(sf::Color::Green);
        block.setPosition(startY*40, startX*40);
        window.draw(block);

        window.display();
    }

    return 0;
}

std::vector<std::vector<int>> readMazeFromFile(const std::string& filename){
   std::ifstream inputFile(filename);
    std::vector<std::vector<int>> maze;
    std::vector<int> row;

    char c;
    while (inputFile.get(c))
    {
        if (c == ' ' || c == '\n' || c == '\r')
        {
            if (!row.empty())
            {
                maze.push_back(row);
                row.clear();
            }
        }
        else if (c >= '0' && c <= '9')
        {
            int val = c - '0';
            row.push_back(val);
        }
        else
        {
            throw std::runtime_error("Invalid character in file ");
        }
    }

    if (!row.empty())
    {
        maze.push_back(row);
    }


    return maze;
}

void dijkstra(const std::vector<std::vector<int>>& maze, const std::pair<int,int>& start,
              std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& prev) {
    int ROW = maze.size();
    int COL = maze[0].size();

    std::vector<std::pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    std::priority_queue<std::pair<int,std::pair<int,int>>, std::vector<std::pair<int,std::pair<int,int>>>,
        std::greater<std::pair<int,std::pair<int,int>>>> pq;
    pq.push({0, start});
    dist[start.first][start.second] = 0;


    while (!pq.empty()) {
        std::pair<int,std::pair<int,int>> top = pq.top();

        pq.pop();

        int x = top.second.first;
        int y = top.second.second;
        int d = top.first;

        if (d > dist[x][y]) continue;

        for (int i = 0; i < directions.size(); ++i) {
            int nx = x + directions[i].first;
            int ny = y + directions[i].second;
            if (nx >= 0 && nx < ROW && ny >= 0 && ny < COL && maze[nx][ny] == 0) {
                int nd = d + 1;
                if (nd < dist[nx][ny]) {
                    dist[nx][ny] = nd;
                    prev[nx][ny] = x * COL + y;
                    pq.push({nd, {nx, ny}});
                }
            }
        }
    }
}

std::vector<std::pair<int,int>> shortestPath(const std::vector<std::vector<int>>& maze,
    const std::pair<int,int>& start, const std::pair<int,int>& end) {
    int ROW = maze.size();
    int COL = maze[0].size();

    std::vector<std::pair<int,int>> path;
    std::vector<std::vector<int>> dist(ROW, std::vector<int>(COL, INF));
    std::vector<std::vector<int>> prev(ROW, std::vector<int>(COL, -1));
    dijkstra(maze, start, dist, prev);

    if (dist[end.first][end.second] == INF) {
        return path;
    }

    int cur = end.first * COL + end.second;
    while (cur != -1) {
        int x = cur / COL;
        int y = cur % COL;
        path.push_back({x, y});
        cur = prev[x][y];
    }

    std::reverse(path.begin(), path.end());
    return path;
}
