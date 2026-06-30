#pragma once

struct Point {
  double x;
  double y;
};

class Primitive {
 public:
  virtual void Draw(double offsetX = 0.0, double offsetY = 0.0,
                    double zoom = 1.0) const = 0;
  virtual ~Primitive() = default;
};

class Circle : public Primitive {
 public:
  Circle(const Point& center, double radius);
  void Draw(double offsetX = 0.0, double offsetY = 0.0,
            double zoom = 1.0) const override;

 private:
  Point center_;
  double radius_;
};

class Square : public Primitive {
 public:
  Square(const Point& topLeft, double sideLength);
  void Draw(double offsetX = 0.0, double offsetY = 0.0,
            double zoom = 1.0) const override;

 private:
  Point topLeft_;
  double sideLength_;
};

class Rectangle : public Primitive {
 public:
  Rectangle(const Point& topLeft, double width, double height);
  void Draw(double offsetX = 0.0, double offsetY = 0.0,
            double zoom = 1.0) const override;

 private:
  Point topLeft_;
  double width_;
  double height_;
};

class Line : public Primitive {
 public:
  Line(const Point& start, const Point& end);
  void Draw(double offsetX = 0.0, double offsetY = 0.0,
            double zoom = 1.0) const override;

 private:
  Point start_;
  Point end_;
};
