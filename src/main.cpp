#include <iostream>
#include <memory>
#include <string>
#include <vector>

// -------------------------
// MODEL
// -------------------------
struct Point {
  double x;
  double y;
};

class Primitive {
 public:
  virtual void Draw(double offsetX = 0.0, double offsetY = 0.0) const = 0;
  virtual ~Primitive() = default;
};

class Circle : public Primitive {
 public:
  Circle(const Point& center, double radius)
      : center_(center), radius_(radius) {}
  void Draw(double offsetX = 0.0, double offsetY = 0.0) const override {
    std::cout << "Drawing a circle at (" << center_.x + offsetX << ", "
              << center_.y + offsetY << ") with radius " << radius_
              << std::endl;
  }

 private:
  Point center_;
  double radius_;
};

class Square : public Primitive {
 public:
  Square(const Point& topLeft, double sideLength)
      : topLeft_(topLeft), sideLength_(sideLength) {}
  void Draw(double offsetX = 0.0, double offsetY = 0.0) const override {
    std::cout << "Drawing a square at (" << topLeft_.x + offsetX << ", "
              << topLeft_.y + offsetY << ") with side length " << sideLength_
              << std::endl;
  }

 private:
  Point topLeft_;
  double sideLength_;
};

class Rectangle : public Primitive {
 public:
  Rectangle(const Point& topLeft, double width, double height)
      : topLeft_(topLeft), width_(width), height_(height) {}

  void Draw(double offsetX = 0.0, double offsetY = 0.0) const override {
    std::cout << "Drawing a rectangle at (" << topLeft_.x + offsetX << ", "
              << topLeft_.y + offsetY << ") with width " << width_
              << " and height " << height_ << std::endl;
  }

 private:
  Point topLeft_;
  double width_;
  double height_;
};

class Line : public Primitive {
 public:
  Line(const Point& start, const Point& end) : start_(start), end_(end) {}
  void Draw(double offsetX = 0.0, double offsetY = 0.0) const override {
    std::cout << "Drawing a line from (" << start_.x + offsetX << ", "
              << start_.y + offsetY << ") to (" << end_.x + offsetX << ", "
              << end_.y + offsetY << ")" << std::endl;
  }

 private:
  Point start_;
  Point end_;
};

class Document {
 public:
  void AddPrimitive(std::unique_ptr<Primitive> primitive) {
    std::cout << "Adding a primitive to the document." << std::endl;
    primitives_.push_back(std::move(primitive));
  }

  void DeletePrimitive(size_t index) {
    if (index < primitives_.size()) {
      std::cout << "Deleting a primitive from the document." << std::endl;
      primitives_.erase(primitives_.begin() + index);
    }
  }

  void SetPath(const std::string& filepath) {
    std::cout << "Setting document path to: " << filepath << std::endl;
    filepath_ = filepath;
  }

  const std::vector<std::unique_ptr<Primitive>>& GetPrimitives() const {
    return primitives_;
  }

  void clear() {
    std::cout << "Clearing the document." << std::endl;
    primitives_.clear();
  }

 private:
  std::vector<std::unique_ptr<Primitive>> primitives_;
  std::string filepath_;
};

// -------------------------
// VIEW
// -------------------------

struct Camera {
  double offsetX = 0.0;
  double offsetY = 0.0;
};

class EditorView {
 public:
  void SetCameraOffset(double dx, double dy) {
    camera_.offsetX += dx;
    camera_.offsetY += dy;
  }

  void Render(const Document& doc) {
    for (const auto& primitive : doc.GetPrimitives()) {
      primitive->Draw(camera_.offsetX, camera_.offsetY);
    }
  }

 private:
  Camera camera_;
};

// -------------------------
// CONTROLLER
// -------------------------

class EditorController {
 public:
  EditorController(Document& model, EditorView& view)
      : model_(model), view_(view) {}

  void CreateNewDocument() {
    std::cout << "Creating a new document." << std::endl;
    model_.clear();
    model_.SetPath("");
    view_.Render(model_);
  }

  void OpenDocument(const std::string& filepath) {
    std::cout << "Opening document: " << filepath << std::endl;
    model_.SetPath(filepath);
    // Emulating load of a document by adding a primitive for demonstration
    // purposes
    model_.AddPrimitive(std::make_unique<Circle>(Point{0.0, 0.0}, 1.0));
    view_.Render(model_);
  }

  void SaveDocument(const std::string& filepath) {
    std::cout << "Saving document to: " << filepath << std::endl;
    model_.SetPath(filepath);
    view_.Render(model_);
  }

  void AddPrimitive(std::unique_ptr<Primitive> primitive) {
    std::cout << "Adding a primitive to the document." << std::endl;
    model_.AddPrimitive(std::move(primitive));
    view_.Render(model_);
  }

  void DeletePrimitive(size_t index) {
    std::cout << "Deleting a primitive from the document." << std::endl;
    model_.DeletePrimitive(index);
    view_.Render(model_);
  }

  void PanCamera(double dx, double dy) {
    view_.SetCameraOffset(dx, dy);
    view_.Render(model_);
  }

 private:
  Document& model_;
  EditorView& view_;
};

// -------------------------
// button click handlers
// -------------------------

void OnClick_NewDocument(EditorController& controller) {
  controller.CreateNewDocument();
}

void OnClick_OpenDocument(EditorController& controller,
                          const std::string& filepath) {
  controller.OpenDocument(filepath);
}

void OnClick_SaveDocument(EditorController& controller,
                          const std::string& filepath) {
  controller.SaveDocument(filepath);
}

void OnClick_AddPrimitive(EditorController& controller,
                          std::unique_ptr<Primitive> primitive) {
  controller.AddPrimitive(std::move(primitive));
}

void OnClick_DeletePrimitive(EditorController& controller, size_t index) {
  controller.DeletePrimitive(index);
}

int main() {
  Document doc;
  EditorView view;
  EditorController controller(doc, view);
  OnClick_NewDocument(controller);
  OnClick_AddPrimitive(controller,
                       std::make_unique<Circle>(Point{0.0, 0.0}, 1.0));
  OnClick_AddPrimitive(controller,
                       std::make_unique<Square>(Point{0.0, 0.0}, 1.0));
  OnClick_AddPrimitive(controller,
                       std::make_unique<Rectangle>(Point{0.0, 0.0}, 1.0, 2.0));
  OnClick_AddPrimitive(
      controller, std::make_unique<Line>(Point{0.0, 0.0}, Point{1.0, 1.0}));
  OnClick_DeletePrimitive(controller, 1);
  OnClick_SaveDocument(controller, "output.txt");

  view.Render(doc);

  return 0;
}