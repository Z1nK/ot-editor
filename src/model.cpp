#include "model.h"

#include <iostream>

void Document::AddPrimitive(std::unique_ptr<Primitive> primitive) {
  std::cout << "Adding a primitive to the document." << std::endl;
  primitives_.push_back(std::move(primitive));
}

void Document::DeletePrimitive(size_t index) {
  if (index < primitives_.size()) {
    std::cout << "Deleting a primitive from the document." << std::endl;
    primitives_.erase(primitives_.begin() + index);
  }
}

void Document::SetPath(const std::string& filepath) {
  std::cout << "Setting document path to: " << filepath << std::endl;
  filepath_ = filepath;
}

const std::vector<std::unique_ptr<Primitive>>& Document::GetPrimitives()
    const {
  return primitives_;
}

void Document::clear() {
  std::cout << "Clearing the document." << std::endl;
  primitives_.clear();
}
