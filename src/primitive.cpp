#include "primitive.h"

Circle::Circle(const Point& center, double radius)
    : center_(center), radius_(radius) {}

void Circle::Accept(IPrimitiveVisitor& visitor) const { visitor.Visit(*this); }
Point Circle::GetCenter() const { return center_; }
double Circle::GetRadius() const { return radius_; }

Square::Square(const Point& topLeft, double sideLength)
    : topLeft_(topLeft), sideLength_(sideLength) {}

void Square::Accept(IPrimitiveVisitor& visitor) const { visitor.Visit(*this); }
Point Square::GetTopLeft() const { return topLeft_; }
double Square::GetSideLength() const { return sideLength_; }

Rectangle::Rectangle(const Point& topLeft, double width, double height)
    : topLeft_(topLeft), width_(width), height_(height) {}

void Rectangle::Accept(IPrimitiveVisitor& visitor) const {
  visitor.Visit(*this);
}
Point Rectangle::GetTopLeft() const { return topLeft_; }
double Rectangle::GetWidth() const { return width_; }
double Rectangle::GetHeight() const { return height_; }

Line::Line(const Point& start, const Point& end) : start_(start), end_(end) {}

void Line::Accept(IPrimitiveVisitor& visitor) const { visitor.Visit(*this); }
Point Line::GetStart() const { return start_; }
Point Line::GetEnd() const { return end_; }
