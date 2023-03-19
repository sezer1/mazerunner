#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

std::vector<std::vector<int>> readMazeFromFile(const std::string& filename);

struct Node {
    int x, y, distance;
};

bool operator<(const Node& lhs, const Node& rhs) {
    return lhs.distance > rhs.distance;
}

int shortestPath(const std::vector<std::vector<int>>& maze, int startX, int startY, int endX, int endY, std::vector<std::vector<int>>& pathNum) {
    const int ROW = maze.size();
    const int COL = maze[0].size();

    std::vector<std::vector<int>> distance(ROW, std::vector<int>(COL, std::numeric_limits<int>::max()));
    std::vector<std::vector<Node>> parent(ROW, std::vector<Node>(COL));
    std::priority_queue<Node> pq;

    pq.push({startX, startY, 0});
    distance[startX][startY] = 0;

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.x == endX && curr.y == endY) {
            // Backtrack to find the path
            while (curr.x != startX || curr.y != startY) {
                pathNum[curr.x][curr.y] = 0;
                curr = parent[curr.x][curr.y];
            }
            pathNum[curr.x][curr.y] = 0;
            return distance[endX][endY];
        }

        if (distance[curr.x][curr.y] < curr.distance) {
            continue;
        }

        // Check neighbors
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int nextX = curr.x + dx[i];
            int nextY = curr.y + dy[i];

            if (nextX >= 0 && nextX < ROW && nextY >= 0 && nextY < COL && maze[nextX][nextY] == 0) {
                int dist = curr.distance + 1;

                if (dist < distance[nextX][nextY]) {
                    distance[nextX][nextY] = dist;
                    parent[nextX][nextY] = curr;
                    pq.push({nextX, nextY, dist});
                }
            }
        }
    }
}

void drawMaze(sf::RenderWindow& window, const std::vector<std::vector<int>>& maze) {
    const int ROW = maze.size();
    const int COL = maze[0].size();

    // Create rectangle shapes for each cell in the maze
    std::vector<std::vector<sf::RectangleShape>> cells(ROW, std::vector<sf::RectangleShape>(COL));
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cells[i][j].setSize(sf::Vector2f(40.f, 40.f));
            cells[i][j].setPosition(j * 40.f, i * 40.f);
            cells[i][j].setOutlineThickness(1.f);
            cells[i][j].setOutlineColor(sf::Color::Black);

            // Color cells based on their value in the maze
            switch (maze[i][j]) {
                case 0:
                    cells[i][j].setFillColor(sf::Color::White);
                    break;
                case 1:
                    cells[i][j].setFillColor(sf::Color::Black);
                    break;
                case 2:
                    cells[i][j].setFillColor(sf::Color::Red);
                    break;
                case 3:
                    cells[i][j].setFillColor(sf::Color::Green);
                    break;
                default:
                    cells[i][j].setFillColor(sf::Color::White);
                    break;
            }

            window.draw(cells[i][j]);
        }
    }

    // Add number labels to cells with distance value
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Error: Font not found!" << endl;
        return;
    }

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (maze[i][j] >= 4) {
                // Convert distance value to string and create text object
                std::stringstream ss;
                ss << maze[i][j] - 3;
                sf::Text text(ss.str(), font, 20);
                text.setFillColor(sf::Color::Black);
                text.setStyle(sf::Text::Bold);
                text.setPosition(j * 40.f + 10.f, i * 40.f + 5.f);

                window.draw(text);
            }
        }
    }
}

int main() {
    srand(time(0));

    string filename = "C://Users//Sezer//Desktop//labirent1.txt";
    std::vector<std::vector<int>> maze = readMazeFromFile(filename);
    int ROW = maze.size();
    int COL = maze[0].size();

    int startX, startY, endX, endY;

    startX = rand() % ROW;
    startY = rand() % COL;

    do {
        endX = rand() % ROW;
        endY = rand() % COL;
    } while (maze[endX][endY] != 0 || (startX == endX && startY == endY));

    cout << "Start: (" << startX << ", " << startY << ")" << endl;
    cout << "End: (" << endX << ", " << endY << ")" << endl;

    int shortestDist = shortestPath(maze, startX, startY, endX, endY,maze);
    if (shortestDist == -1) {
        cout << "No path found!" << endl;
    } else {
        cout << "Shortest distance: " << shortestDist << endl;
sf::RenderWindow window(sf::VideoMode(ROW *40, COL*40), "Maze");


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


  // Draw maze
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

    // Draw start and end points
    block.setFillColor(sf::Color::Green);
    block.setPosition(startY * 40, startX * 40);
    window.draw(block);

    // Draw shortest path
    if (shortestDist != -1) {
        int currX = endX;
        int currY = endY;
        while (currX != startX || currY != startY) {
            block.setFillColor(sf::Color::Yellow);
            block.setPosition(currY * 40, currX * 40);
            window.draw(block);
            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, 1, 0, -1};
            for (int i = 0; i < 4; ++i) {
                int nextX = currX + dx[i];
                int nextY = currY + dy[i];
                if (nextX >= 0 && nextX < ROW && nextY >= 0 && nextY < COL && maze[nextX][nextY] == 0 && shortestPath(maze, startX, startY, nextX, nextY,maze) == shortestDist - 1) {
                    currX = nextX;
                    currY = nextY;
                    break;
                }
            }
            shortestDist--;
        }
    }

    block.setFillColor(sf::Color::Red);
    block.setPosition(endY * 40, endX * 40);
    window.draw(block);


    // Display window
    window.display();


}

return 0;
}
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

