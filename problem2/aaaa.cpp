#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <chrono>

using namespace std;

std::vector<std::vector<int>> readMazeFromFile(const std::string& filename);

struct Node {
    int x, y, distance;
};

bool operator<(const Node& lhs, const Node& rhs) {
    return lhs.distance > rhs.distance;
}

int shortestPath(const std::vector<std::vector<int>>& maze, int startX, int startY, int endX, int endY) {
    const int ROW = maze.size();
    const int COL = maze[0].size();

    std::vector<std::vector<int>> distance(ROW, std::vector<int>(COL, std::numeric_limits<int>::max()));
    std::priority_queue<Node> pq;

    pq.push({startX, startY, 0});
    distance[startX][startY] = 0;

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.x == endX && curr.y == endY) {
            return curr.distance;
        }

        if (distance[curr.x][curr.y] < curr.distance) {
            continue;
        }

        // Komşular
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int nextX = curr.x + dx[i];
            int nextY = curr.y + dy[i];

            if (nextX >= 0 && nextX < ROW && nextY >= 0 && nextY < COL && maze[nextX][nextY] == 0) {
                int dist = curr.distance + 1;

                if (dist < distance[nextX][nextY]) {
                    distance[nextX][nextY] = dist;
                    pq.push({nextX, nextY, dist});
                }
            }
        }
    }

    return -1;
}

class Engeller {
public:
     static sf::Color White(){return sf::Color::White; }
     static sf::Color Black() { return sf::Color::Black; }
    static sf::Color Yellow() { return sf::Color::Yellow; }
    static sf::Color Magenta() { return sf::Color::Magenta; }
    static sf::Color Cyan() { return sf::Color::Cyan; }
    static sf::Color Transparent() { return sf::Color::Transparent; }

};

class Izgara{
public:

     int  endX, endY,ROW,COL;


     std::vector<std::vector<int>>  mazeolustur(string filename){
    std::vector<std::vector<int>> maze = readMazeFromFile(filename);
      ROW = maze.size();
      COL = maze[0].size();
      do {
        endX = rand() % ROW;
        endY = rand() % COL;
    } while (maze[endX][endY] != 0 );
     return maze;
    }


};



int main() {
   auto start = std::chrono::high_resolution_clock::now();
    clock_t baslangic, bitis;
    double sure;
     baslangic = clock();

    srand(time(0));

int sayi=0;

sf::Color color0 =  Engeller::White();
sf::Color color1 =  Engeller::Black();
sf::Color color2 =  Engeller::Yellow();
sf::Color color3 =  Engeller::Magenta();
sf::Color color4 =  Engeller::Cyan();
sf::Color color5 =  Engeller::Transparent();

std::vector<std::vector<sf::Color>> cellColors(20, std::vector<sf::Color>(20));

    string filename = "C://Users//Sezer//Desktop//labirent2.txt";
std::vector<std::vector<int>> maze;

    Izgara mazeo;
    maze = mazeo.mazeolustur(filename);
    int startX, startY, endX, endY, ROW,COL;

        endX=mazeo.endX;
    endY=mazeo.endY;
    ROW=mazeo.ROW;
    COL=mazeo.COL;

        startX = rand() % ROW;
    startY = rand() % COL;




    cout << "Start: (" << startX << ", " << startY << ")" << endl;
    cout << "End: (" << endX << ", " << endY << ")" << endl;


    int shortestDist = shortestPath(maze, startX, startY, endX, endY);
    if (shortestDist == -1) {
        cout << "No path found!" << endl;
    } else {
        cout << "Shortest distance: " << shortestDist << endl;
    }



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

        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\Sezer\\Desktop\\arge\\codeblocksprojects\\deneme1\\rpsexample\\LucidaBrightRegular.ttf")) { // Yazı tipi yükleniyor
        return EXIT_FAILURE;
        }
       sf::Text text;
       text.setFont(font);
       sf::Text text1;
      sf::Text text2;
      sf::Text text3;


    for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                if (maze[i][j] == 0) {
                    block.setFillColor(sf::Color::White);
                    block.setPosition(j * 40, i * 40);
                    cellColors[i][j]=color0;

                    window.draw(block);
                    sayi++;

                } else if (maze[i][j] == 1) {
                    block.setFillColor(sf::Color::Magenta);
                    block.setPosition(j * 40, i * 40);
                    cellColors[i][j]=color3;
                    window.draw(block);

                } else if (maze[i][j] == 2) {
                    block.setFillColor(sf::Color::Cyan);
                    block.setPosition(j * 40, i * 40);
                    cellColors[i][j]=color4;

                    window.draw(block);
                } else if (maze[i][j] == 3) {
                    block.setFillColor(sf::Color::Black);
                    block.setPosition(j * 40, i * 40);
                    cellColors[i][j]=color1;
                    window.draw(block);
                }
            }
        }

    block.setFillColor(sf::Color::Green);
    block.setPosition(startY * 40, startX * 40);
    window.draw(block);

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
               cellColors[currX][currY]=color2;
                int nextX = currX + dx[i];
                int nextY = currY + dy[i];

             if(cellColors[nextX][nextY].r==255 && cellColors[nextX][nextY].g==255 && cellColors[nextX][nextY].b==255){
                        text.setString("0");
                        text.setFillColor(sf::Color::Blue);
                        text.setPosition(nextY*40,nextX*40);
                        window.draw(text);
             }

             if(cellColors[nextX][nextY].r==255 && cellColors[nextX][nextY].g==0 && cellColors[nextX][nextY].b==255){
                        text.setString("1");
                        text.setFillColor(sf::Color::Blue);
                        text.setPosition(nextY*40,nextX*40);
                        window.draw(text);
             }
             if(cellColors[nextX][nextY].r==0 && cellColors[nextX][nextY].g==255 && cellColors[nextX][nextY].b==255){
                        text.setString("2");
                        text.setFillColor(sf::Color::Blue);
                        text.setPosition(nextY*40,nextX*40);
                        window.draw(text);
             }
             if(cellColors[nextX][nextY].r==0 && cellColors[nextX][nextY].g==0 && cellColors[nextX][nextY].b==0){
                        text.setString("3");
                        text.setFillColor(sf::Color::Blue);
                        text.setPosition(nextY*40,nextX*40);
                        window.draw(text);
             }

                if (nextX >= 0 && nextX < ROW && nextY >= 0 && nextY < COL && maze[nextX][nextY] == 0 && shortestPath(maze, startX, startY, nextX, nextY) == shortestDist - 1) {
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

     for (int i = 0; i < cellColors.size(); ++i) {
            for (int j = 0; j <cellColors.size(); ++j) {
                 if(cellColors[i][j].r==255 && cellColors[i][j].g==255 && cellColors[i][j].b==0){

                        text.setString("0");
                        text.setFillColor(sf::Color::Blue);
                        text.setPosition(j*40,i*40);
                        window.draw(text);
                 }

           }
    }


for (int i = 0; i < cellColors.size(); i++) {
    for (int j = 0; j < cellColors[i].size(); j++) {

    }

}
sayi--;



    window.display();
}



  auto finish = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();
  std::cout << "Gecen sure: " << duration << " saniye" << std::endl;

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
