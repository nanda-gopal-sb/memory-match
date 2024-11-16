#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#define CELL_SIZE 64
#define COLUMNS 8
#define ROWS 8

void drawRec(sf::RenderWindow &window) {
  sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3));
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);
      cell_shape.setFillColor(sf::Color(73, 98, 185));
      window.draw(cell_shape);
    }
  }
}

int main() {
  auto window = sf::RenderWindow({510u, 510u}, "memory-match");
  window.setFramerateLimit(144);
  sf::RectangleShape rectangle(sf::Vector2f(50, 50));
  while (window.isOpen()) {
    for (auto event = sf::Event(); window.pollEvent(event);) {
      switch (event.type) {
        // If the user clicked the close window button
        case sf::Event::Closed: {
          // We close the window
          window.close();
          break;
        }
        case sf::Event::MouseButtonReleased: {
          switch (event.mouseButton.button) {
            // If the LMB is released
            case sf::Mouse::Left: {
              int mouse_x = sf::Mouse::getPosition(window).x / CELL_SIZE;
              int mouse_y = sf::Mouse::getPosition(window).y / CELL_SIZE;
              std::cout << "clicked" << "\n";
            }
              window.clear();
              drawRec(window);  // PASS BY REFERENCE
              window.display();
          }
        }
      }
    }
  }
}