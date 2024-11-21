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
  Cell(int x1, int y1, int num) {
    x = x1;
    y = y1;
    open = false;
    openPerm = false;
    number = num;
  }
};

std::vector<Cell> cells;

sf::Font font;
bool checkInArray(int num) {
  int count = 0;
  for (auto cell : cells) {
    if (cell.number == num) {
      count++;
    }
  }
  if (count >= 32) {
    return true;
  }
  return false;
}
int getRand() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 32);
  int rand = distrib(gen);
  while (checkInArray(rand)) {
    rand = distrib(gen);
  }
  return rand;
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
    text.setFillColor(sf::Color::Green);
  }
  return text;
}

void fillCell() {
  for (int a = 0; a < ROWS; a++) {
    for (int b = 0; b < COLUMNS; b++) {
      // cells.push_back(Cell(b, a, 4));
      cells.push_back(Cell(b, a, getRand()));
    }
  }
}
void drawRec(sf::RenderWindow& window) {
  auto text = DrawText();
  sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      text.setPosition(CELL_SIZE * i, CELL_SIZE * j);
      text.setString(std::to_string(cells[i + COLUMNS * j].number));
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
          break;
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