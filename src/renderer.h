#pragma once

#include "primitive.h"
#include "primitive_visitor.h"

struct Camera;

class ConsoleRenderer : public IPrimitiveVisitor {
 public:
  explicit ConsoleRenderer(const Camera& camera);
  void Visit(const Circle& c) override;
  void Visit(const Square& s) override;
  void Visit(const Rectangle& r) override;
  void Visit(const Line& l) override;

 private:
  const Camera& camera_;
};
