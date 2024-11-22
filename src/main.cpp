#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#define CELL_SIZE 80
#define COLUMNS 8
#define ROWS 8
#define FONT_HEIGHT = 16
struct Cell {
  int number = 0;
  int count;
  int x;
  int y;
  bool open;
  bool openPerm;
  Cell(int x1, int y1) {
    x = x1;
    y = y1;
    open = true;
    openPerm = false;
  }
};

std::vector<Cell> cells;

bool isWin() {
  bool win = true;
  for (auto cell : cells) {
    if (!cell.openPerm) {
      return false;
    }
  }
  return true;
}

sf::Font font;
bool isInArray(int num, std::vector<int>& arr) {
  for (auto nums : arr) {
    if (nums == num)
      return true;
  }
  return false;
}

int getCount(int toCheck) {
  int count = 0;
  for (auto cell : cells) {
    if (cell.number == toCheck) {
      count++;
    }
  }
  return count;
}
void fillNums() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 63);
  int rand = -1;
  std::vector<int> arr;
  for (int i = 1; i <= 32; i++) {
    for (int j = 0; j < 2; j++) {
      while (isInArray(rand, arr)) {
        rand = distrib(gen);
      }
      arr.push_back(rand);
      cells[rand].number = i;
    }
  }
  for (auto cell : cells) {
    if (cell.number == 1) {
      std::cout << "hit" << "\n";
      std::cout << cell.x << "\n";
      std::cout << cell.y << "\n";
    }
    if (cell.number == 0) {
      std::cout << "hit" << "\n";
      std::cout << cell.x << "\n";
      std::cout << cell.y << "\n";
      cell.number = 1;
    }
  }
}

sf::Text DrawText() {
  sf::Text text;
  if (!font.loadFromFile("assests/daFont.ttf")) {
    std::cout << "unable";
  } else {
    // select the font
    text.setFont(font);  // font is a sf::Font
    // set the string to display
    text.setCharacterSize(64);  // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color(0, 0, 0));
  }
  return text;
}

void fillCell() {
  for (int a = 0; a < ROWS; a++) {
    for (int b = 0; b < COLUMNS; b++) {
      // cells.push_back(Cell(b, a, 4));
      cells.push_back(Cell(b, a));
    }
  }
  fillNums();
  // std::cout << cells.size() << "\n";
}
void drawRec(sf::RenderWindow& window) {
  auto text = DrawText();
  sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      text.setPosition(CELL_SIZE * i, CELL_SIZE * j);
      text.setString(std::to_string(cells[i + COLUMNS * j].number));
      // if (cells[i + COLUMNS * j].number == 0) {
      //   text.setString("1");
      // } else
      //   text.setString(std::to_string(cells[i + COLUMNS * j].number));
      cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);
      if (!cells[i + COLUMNS * j].open) {
        cell_shape.setFillColor(sf::Color(73, 98, 185));
        window.draw(cell_shape);
      }

      if (cells[i + COLUMNS * j].openPerm || cells[i + COLUMNS * j].open) {
        cell_shape.setFillColor(sf::Color(100, 100, 100));
        window.draw(cell_shape);
        window.draw(text);
      }
    }
  }
}
bool isCorrect() {
  int count = 0;
  int* arr = new int[2];
  for (int i = 0; i < cells.size(); i++) {
    if (count == 2)
      break;
    if (cells[i].open) {
      arr[count] = i;
      count++;
    }
  }
  if (cells[arr[0]].number == cells[arr[1]].number) {
    cells[arr[0]].openPerm = true;
    cells[arr[1]].openPerm = true;
    cells[arr[0]].open = false;
    cells[arr[1]].open = false;
    free(arr);
    return true;
  } else {
    cells[arr[0]].open = false;
    cells[arr[1]].open = false;
    free(arr);
    return false;
  }
}

int main() {
  int click = 0;
  fillCell();
  std::cout << cells.size();
  sf::RenderWindow window = sf::RenderWindow({640u, 640u}, "memory-match");
  window.setFramerateLimit(60);
  while (window.isOpen()) {
    for (auto event = sf::Event(); window.pollEvent(event);) {
      switch (event.type) {
        case sf::Event::Closed: {
          window.close();
          continue;
        }
        case sf::Event::MouseButtonReleased: {
          switch (event.mouseButton.button) {
            // If the LMB is released
            case sf::Mouse::Left: {
              if (click < 2) {
                int mouse_x = sf::Mouse::getPosition(window).x / CELL_SIZE;
                int mouse_y = sf::Mouse::getPosition(window).y / CELL_SIZE;
                cells[mouse_x + mouse_y * COLUMNS].open = true;
                click++;
              } else {
                if (isCorrect()) {
                }
                click = 0;
              }
            }
          }
        }
      }
    }
    window.clear();
    drawRec(window);
    window.display();
  }
}