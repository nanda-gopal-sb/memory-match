#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#define CELL_SIZE 64
#define COLUMNS 8
#define ROWS 8

void drawRec(sf::RenderWindow *window) {
  sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);
      cell_shape.setFillColor(sf::Color(73, 98, 185));

      window->draw(cell_shape);
    }
  }
}
int main() {
  sf::Vector2i position = sf::Mouse::getPosition();
  auto window = sf::RenderWindow({510u, 510u}, "memory-match");
  window.setFramerateLimit(144);
  sf::RectangleShape rectangle(sf::Vector2f(50, 50));
  while (window.isOpen()) {
    for (auto event = sf::Event(); window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();
    drawRec(&window);  // PASS BY REFERENCE
    window.display();
  }
}
