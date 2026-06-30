#include "primitive.h"

#include <iostream>

Circle::Circle(const Point& center, double radius)
    : center_(center), radius_(radius) {}

void Circle::Draw(double offsetX, double offsetY, double zoom) const {
  const double screenX = (center_.x + offsetX) * zoom;
  const double screenY = (center_.y + offsetY) * zoom;
  const double screenRadius = radius_ * zoom;
  std::cout << "Drawing a circle at (" << screenX << ", "
            << screenY << ") with radius " << screenRadius
            << std::endl;
}

Square::Square(const Point& topLeft, double sideLength)
    : topLeft_(topLeft), sideLength_(sideLength) {}

void Square::Draw(double offsetX, double offsetY, double zoom) const {
  const double screenX = (topLeft_.x + offsetX) * zoom;
  const double screenY = (topLeft_.y + offsetY) * zoom;
  const double screenSide = sideLength_ * zoom;
  std::cout << "Drawing a square at (" << screenX << ", "
            << screenY << ") with side length " << screenSide
            << std::endl;
}

Rectangle::Rectangle(const Point& topLeft, double width, double height)
    : topLeft_(topLeft), width_(width), height_(height) {}

void Rectangle::Draw(double offsetX, double offsetY, double zoom) const {
  const double screenX = (topLeft_.x + offsetX) * zoom;
  const double screenY = (topLeft_.y + offsetY) * zoom;
  const double screenWidth = width_ * zoom;
  const double screenHeight = height_ * zoom;
  std::cout << "Drawing a rectangle at (" << screenX << ", "
            << screenY << ") with width " << screenWidth
            << " and height " << screenHeight << std::endl;
}

Line::Line(const Point& start, const Point& end) : start_(start), end_(end) {}

void Line::Draw(double offsetX, double offsetY, double zoom) const {
  const double startX = (start_.x + offsetX) * zoom;
  const double startY = (start_.y + offsetY) * zoom;
  const double endX = (end_.x + offsetX) * zoom;
  const double endY = (end_.y + offsetY) * zoom;
  std::cout << "Drawing a line from (" << startX << ", "
            << startY << ") to (" << endX << ", "
            << endY << ")" << std::endl;
}
