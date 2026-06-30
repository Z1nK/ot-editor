#include "renderer.h"

#include <iostream>

#include "view.h"

ConsoleRenderer::ConsoleRenderer(const Camera& camera) : camera_(camera) {}

void ConsoleRenderer::Visit(const Circle& c) {
  const Point center = c.GetCenter();
  const double screenX = (center.x + camera_.offsetX) * camera_.zoom;
  const double screenY = (center.y + camera_.offsetY) * camera_.zoom;
  const double screenRadius = c.GetRadius() * camera_.zoom;
  std::cout << "Drawing a circle at (" << screenX << ", "
            << screenY << ") with radius " << screenRadius
            << std::endl;
}

void ConsoleRenderer::Visit(const Square& s) {
  const Point topLeft = s.GetTopLeft();
  const double screenX = (topLeft.x + camera_.offsetX) * camera_.zoom;
  const double screenY = (topLeft.y + camera_.offsetY) * camera_.zoom;
  const double screenSide = s.GetSideLength() * camera_.zoom;
  std::cout << "Drawing a square at (" << screenX << ", "
            << screenY << ") with side length " << screenSide
            << std::endl;
}

void ConsoleRenderer::Visit(const Rectangle& r) {
  const Point topLeft = r.GetTopLeft();
  const double screenX = (topLeft.x + camera_.offsetX) * camera_.zoom;
  const double screenY = (topLeft.y + camera_.offsetY) * camera_.zoom;
  const double screenWidth = r.GetWidth() * camera_.zoom;
  const double screenHeight = r.GetHeight() * camera_.zoom;
  std::cout << "Drawing a rectangle at (" << screenX << ", "
            << screenY << ") with width " << screenWidth
            << " and height " << screenHeight << std::endl;
}

void ConsoleRenderer::Visit(const Line& l) {
  const Point start = l.GetStart();
  const Point end = l.GetEnd();
  const double startX = (start.x + camera_.offsetX) * camera_.zoom;
  const double startY = (start.y + camera_.offsetY) * camera_.zoom;
  const double endX = (end.x + camera_.offsetX) * camera_.zoom;
  const double endY = (end.y + camera_.offsetY) * camera_.zoom;
  std::cout << "Drawing a line from (" << startX << ", "
            << startY << ") to (" << endX << ", "
            << endY << ")" << std::endl;
}
