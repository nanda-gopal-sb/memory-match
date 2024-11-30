#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#define CELL_SIZE 80
#define COLUMNS 8
#define ROWS 8
#define FONT_HEIGHT = 16

struct Cell
{
  int number = 1;
  int x;         // obvious
  int y;         // obvious
  bool open;     // this is when the player peeks
  bool openPerm; // openPerm is when the player gets a pair correctly
  Cell(int x1, int y1)
  {
    x = x1;
    y = y1;
    open = false;
    openPerm = false;
  }
};

// global variables
std::vector<Cell> cells; // arrays for storing the 64 cells
sf::Font font;           // the font, this needs to be gobal for some reason
int clicks_num = 0;      // I need to use in a lot of functions
sf::Time elapsed1;       // this variable for storing the time elapsed

// to check for win
bool isWin()
{
  bool win = true;
  // runs a loop and checks for openPerm
  for (Cell cell : cells)
  {
    if (!cell.openPerm)
    {
      return false;
    }
  }
  return true;
}

// to check if the index is already accounted for
bool isInArray(int num, std::vector<int> &arr)
{
  for (auto nums : arr)
  {
    if (nums == num)
      return true;
  }
  return false;
}

void fillNums()
{
  std::random_device rd;
  std::mt19937 gen(rd());                         // seeding the number generator
  std::uniform_int_distribution<> distrib(0, 63); // between 0 and 63(64) indices
  int rand = 0;
  std::vector<int> arr; // to keep track of the indices in the array
  for (int i = 1; i <= ((ROWS * COLUMNS) / 2); i++)
  {
    for (int j = 0; j < 2; j++)
    {
      while (isInArray(rand, arr)) // if the indices is already in the array run again
      {
        rand = distrib(gen);
      }
      arr.push_back(rand);
      cells[rand].number = i; // puts the number 1 into a random position in the array
    }
  }
}

sf::Text DrawText(int lmao)
{
  sf::Text text;
  if (!font.loadFromFile("assests/daFont.ttf"))
  {
    std::cout << "unable";
  }
  else
  {
    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(sf::Color(255, 255, 255));
  }
  return text;
}

sf::Text DrawText()
{
  sf::Text text;
  if (!font.loadFromFile("assests/daFont.ttf"))
  {
    std::cout << "unable";
  }
  else
  {
    text.setFont(font);
    text.setCharacterSize(64);
    text.setFillColor(sf::Color(26, 127, 0));
  }
  return text;
}

void fillCell()
{
  for (int a = 0; a < ROWS; a++)
  {
    for (int b = 0; b < COLUMNS; b++)
    {
      // cells.push_back(Cell(b, a, 4));
      cells.push_back(Cell(b, a));
    }
  }
  fillNums();
}
void black()
{
  sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);
      cell_shape.setFillColor(sf::Color(0, 0, 0));
    }
  }
}
void drawRec(sf::RenderWindow &window, bool win, bool close)
{
  auto text = DrawText();
  sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));
  if (win)
  {
    text = DrawText(9);
    text.setPosition(0, 0);
    std::string str1("The number of clicks you made -");
    text.setString(str1.append(std::to_string(clicks_num)));
    window.draw(text);
    auto text2 = DrawText(8);
    text2.setPosition(0, 100);
    str1 = "The time you took - ";
    text2.setString(str1.append(std::to_string(elapsed1.asSeconds())));
    window.draw(text2);
    return;
  }
  if (close)
  {
    black();
    return;
  }
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      text.setPosition(CELL_SIZE * i, CELL_SIZE * j);
      text.setString(std::to_string(cells[i + COLUMNS * j].number));
      cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);

      if (!cells[i + COLUMNS * j].open)
      {
        cell_shape.setFillColor(sf::Color(73, 98, 185));
        window.draw(cell_shape);
      }

      if (cells[i + COLUMNS * j].open)
      {
        cell_shape.setFillColor(sf::Color(255, 136, 0));
        window.draw(cell_shape);
        window.draw(text);
      }
      if (cells[i + COLUMNS * j].openPerm)
      {
        cell_shape.setFillColor(sf::Color(0, 0, 0));
        window.draw(cell_shape);
      }
    }
  }
}
void text(sf::RenderWindow &window)
{
  auto text = DrawText();
  text.setString("Victory is yours");
  text.setPosition(0, 0);
  window.draw(text);
}
bool checkIfCorrectAndClear()
{
  int count = 0;
  int arr[2] = {0};
  for (int i = 0; i < cells.size(); i++)
  {
    if (count == 2)
      break;
    if (cells[i].open)
    {
      arr[count] = i;
      count++;
    }
  }
  if (cells[arr[0]].number == cells[arr[1]].number)
  {
    cells[arr[0]].openPerm = true;
    cells[arr[1]].openPerm = true;
    cells[arr[0]].open = false;
    cells[arr[1]].open = false;
    return true;
  }
  else
  {
    cells[arr[0]].open = false;
    cells[arr[1]].open = false;
    return false;
  }
}
void change(sf::RenderWindow &window)
{
  int mouse_x = sf::Mouse::getPosition(window).x / CELL_SIZE;
  int mouse_y = sf::Mouse::getPosition(window).y / CELL_SIZE;
  cells[mouse_x + mouse_y * COLUMNS].open = true;
}
int main()
{
  int mouse_x = 0;
  int mouse_y = 0;
  int opened = 0;
  bool win = false;
  bool close = false;
  fillCell();
  sf::RenderWindow window = sf::RenderWindow({640u, 640u}, "memory-match");
  window.setFramerateLimit(60);
  sf::Clock clock;
  while (window.isOpen())
  {
    for (auto event = sf::Event(); window.pollEvent(event);)
    {
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left)
      {
        clicks_num++;
        if (opened == 2)
        {
          opened = 0;
          checkIfCorrectAndClear();
          if (isWin())
          {
            win = true;
            std::cout << "WIn\n";
            elapsed1 = clock.getElapsedTime();
          }
          change(window);
          opened++;
        }
        else
        {
          change(window);
          opened++;
        }
      }
      if (event.type == sf::Event::Closed)
      {
        window.close();
        close = true;
      }
    }
    window.clear();
    drawRec(window, win, close);
    window.display();
  }
}