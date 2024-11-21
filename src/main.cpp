#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#define CELL_SIZE 64
#define COLUMNS 8
#define ROWS 8
#define FONT_HEIGHT = 16
struct Cell {
  int x;
  int y;
  bool open;
  bool openToPeek;
  Cell(int x1, int y1) {
    x = x1;
    y = y1;
    open = false;
  }
};

std::vector<Cell> cells;

void fillCell() {
  for (int a = 0; a < ROWS; a++) {
    for (int b = 0; b < COLUMNS; b++) {
      cells.push_back(Cell(b, a));
    }
  }
}
void drawRec(sf::RenderWindow& window) {
  sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);
      if (!cells[i + COLUMNS * j].open)
        cell_shape.setFillColor(sf::Color(73, 98, 185));
      else
        cell_shape.setFillColor(sf::Color(100, 100, 100));
      window.draw(cell_shape);
    }
  }
}
int main() {
  fillCell();
  sf::RenderWindow window = sf::RenderWindow({510u, 510u}, "memory-match");
  window.setFramerateLimit(144);
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
              int mouse_x = sf::Mouse::getPosition(window).x / CELL_SIZE;
              int mouse_y = sf::Mouse::getPosition(window).y / CELL_SIZE;
              cells[mouse_x + mouse_y * COLUMNS].open = true;
            }
          }
        }
      }
    }
    window.clear();
    drawRec(window);  // PASS BY REFERENCE
    window.display();
  }
}