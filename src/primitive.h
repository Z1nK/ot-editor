#pragma once

#include "primitive_visitor.h"

struct Point {
  double x;
  double y;
};

class Primitive {
 public:
  virtual void Accept(IPrimitiveVisitor& visitor) const = 0;
  virtual ~Primitive() = default;
};

class Circle : public Primitive {
 public:
  Circle(const Point& center, double radius);
  void Accept(IPrimitiveVisitor& visitor) const override;
  Point GetCenter() const;
  double GetRadius() const;

 private:
  Point center_;
  double radius_;
};

class Square : public Primitive {
 public:
  Square(const Point& topLeft, double sideLength);
  void Accept(IPrimitiveVisitor& visitor) const override;
  Point GetTopLeft() const;
  double GetSideLength() const;

 private:
  Point topLeft_;
  double sideLength_;
};

class Rectangle : public Primitive {
 public:
  Rectangle(const Point& topLeft, double width, double height);
  void Accept(IPrimitiveVisitor& visitor) const override;
  Point GetTopLeft() const;
  double GetWidth() const;
  double GetHeight() const;

 private:
  Point topLeft_;
  double width_;
  double height_;
};

class Line : public Primitive {
 public:
  Line(const Point& start, const Point& end);
  void Accept(IPrimitiveVisitor& visitor) const override;
  Point GetStart() const;
  Point GetEnd() const;

 private:
  Point start_;
  Point end_;
};
