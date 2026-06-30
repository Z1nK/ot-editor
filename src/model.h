#pragma once

#include <memory>
#include <string>
#include <vector>

#include "primitive.h"

class Document {
 public:
  void AddPrimitive(std::unique_ptr<Primitive> primitive);
  void DeletePrimitive(size_t index);
  void SetPath(const std::string& filepath);
  const std::vector<std::unique_ptr<Primitive>>& GetPrimitives() const;
  void clear();

 private:
  std::vector<std::unique_ptr<Primitive>> primitives_;
  std::string filepath_;
};
