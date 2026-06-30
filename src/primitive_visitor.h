#pragma once

class Circle;
class Square;
class Rectangle;
class Line;

class IPrimitiveVisitor {
 public:
  virtual void Visit(const Circle& c) = 0;
  virtual void Visit(const Square& s) = 0;
  virtual void Visit(const Rectangle& r) = 0;
  virtual void Visit(const Line& l) = 0;
  virtual ~IPrimitiveVisitor() = default;
};
