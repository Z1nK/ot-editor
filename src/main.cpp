#include <iostream>
#include <algorithm>
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
  virtual void Draw(double offsetX = 0.0, double offsetY = 0.0,
                    double zoom = 1.0) const = 0;
  virtual ~Primitive() = default;
};

class Circle : public Primitive {
 public:
  Circle(const Point& center, double radius)
      : center_(center), radius_(radius) {}
  void Draw(double offsetX = 0.0, double offsetY = 0.0,
            double zoom = 1.0) const override {
    const double screenX = (center_.x + offsetX) * zoom;
    const double screenY = (center_.y + offsetY) * zoom;
    const double screenRadius = radius_ * zoom;
    std::cout << "Drawing a circle at (" << screenX << ", "
              << screenY << ") with radius " << screenRadius
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
  void Draw(double offsetX = 0.0, double offsetY = 0.0,
            double zoom = 1.0) const override {
    const double screenX = (topLeft_.x + offsetX) * zoom;
    const double screenY = (topLeft_.y + offsetY) * zoom;
    const double screenSide = sideLength_ * zoom;
    std::cout << "Drawing a square at (" << screenX << ", "
              << screenY << ") with side length " << screenSide
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

  void Draw(double offsetX = 0.0, double offsetY = 0.0,
            double zoom = 1.0) const override {
    const double screenX = (topLeft_.x + offsetX) * zoom;
    const double screenY = (topLeft_.y + offsetY) * zoom;
    const double screenWidth = width_ * zoom;
    const double screenHeight = height_ * zoom;
    std::cout << "Drawing a rectangle at (" << screenX << ", "
              << screenY << ") with width " << screenWidth
              << " and height " << screenHeight << std::endl;
  }

 private:
  Point topLeft_;
  double width_;
  double height_;
};

class Line : public Primitive {
 public:
  Line(const Point& start, const Point& end) : start_(start), end_(end) {}
  void Draw(double offsetX = 0.0, double offsetY = 0.0,
            double zoom = 1.0) const override {
    const double startX = (start_.x + offsetX) * zoom;
    const double startY = (start_.y + offsetY) * zoom;
    const double endX = (end_.x + offsetX) * zoom;
    const double endY = (end_.y + offsetY) * zoom;
    std::cout << "Drawing a line from (" << startX << ", "
              << startY << ") to (" << endX << ", "
              << endY << ")" << std::endl;
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
  double zoom = 1.0;
};

class EditorView {
 public:
  void PanByScreenDelta(double dx, double dy) {
    camera_.offsetX += dx / camera_.zoom;
    camera_.offsetY += dy / camera_.zoom;
  }

  void ZoomAtScreenPoint(double factor, double screenX, double screenY) {
    constexpr double kMinZoom = 0.1;
    constexpr double kMaxZoom = 10.0;

    const double oldZoom = camera_.zoom;
    const double newZoom = std::clamp(oldZoom * factor, kMinZoom, kMaxZoom);
    if (newZoom == oldZoom) {
      return;
    }

    camera_.offsetX += screenX / newZoom - screenX / oldZoom;
    camera_.offsetY += screenY / newZoom - screenY / oldZoom;
    camera_.zoom = newZoom;
  }

  void Render(const Document& doc) {
    for (const auto& primitive : doc.GetPrimitives()) {
      primitive->Draw(camera_.offsetX, camera_.offsetY, camera_.zoom);
    }
  }

  Camera GetCamera() const { return camera_; }

  void SetCamera(const Camera& camera) { camera_ = camera; }

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
    model_.AddPrimitive(std::move(primitive));
    view_.Render(model_);
  }

  void DeletePrimitive(size_t index) {
    model_.DeletePrimitive(index);
    view_.Render(model_);
  }

  void PanCamera(double dx, double dy) {
    view_.PanByScreenDelta(dx, dy);
    view_.Render(model_);
  }

  void ZoomCameraAt(double factor, double anchorScreenX,
                    double anchorScreenY) {
    view_.ZoomAtScreenPoint(factor, anchorScreenX, anchorScreenY);
    view_.Render(model_);
  }

  void ResetCamera() {
    view_.SetCamera({0.0, 0.0});
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

  std::cout << "-------------Current camera state: "
            << "offsetX = " << view.GetCamera().offsetX
            << ", offsetY = " << view.GetCamera().offsetY
            << ", zoom = " << view.GetCamera().zoom << std::endl;
  controller.PanCamera(100.0, 50.0);
    std::cout << "-------------Current camera state: "
            << "offsetX = " << view.GetCamera().offsetX
            << ", offsetY = " << view.GetCamera().offsetY
            << ", zoom = " << view.GetCamera().zoom << std::endl;
  controller.ZoomCameraAt(2.0, 0.0, 0.0);
    std::cout << "-------------Current camera state: "
            << "offsetX = " << view.GetCamera().offsetX
            << ", offsetY = " << view.GetCamera().offsetY
            << ", zoom = " << view.GetCamera().zoom << std::endl;

  OnClick_SaveDocument(controller, "output.txt");

  return 0;
}