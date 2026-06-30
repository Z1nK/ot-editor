#include "controller.h"

#include <iostream>

EditorController::EditorController(Document& model, EditorView& view)
    : model_(model), view_(view) {}

void EditorController::CreateNewDocument() {
  std::cout << "Creating a new document." << std::endl;
  model_.clear();
  model_.SetPath("");
  view_.Render(model_);
}

void EditorController::OpenDocument(const std::string& filepath) {
  std::cout << "Opening document: " << filepath << std::endl;
  model_.SetPath(filepath);
  // Emulating load of a document by adding a primitive for demonstration
  // purposes
  model_.AddPrimitive(std::make_unique<Circle>(Point{0.0, 0.0}, 1.0));
  view_.Render(model_);
}

void EditorController::SaveDocument(const std::string& filepath) {
  std::cout << "Saving document to: " << filepath << std::endl;
  model_.SetPath(filepath);
  view_.Render(model_);
}

void EditorController::AddPrimitive(std::unique_ptr<Primitive> primitive) {
  model_.AddPrimitive(std::move(primitive));
  view_.Render(model_);
}

void EditorController::DeletePrimitive(size_t index) {
  model_.DeletePrimitive(index);
  view_.Render(model_);
}

void EditorController::PanCamera(double dx, double dy) {
  view_.PanByScreenDelta(dx, dy);
  view_.Render(model_);
}

void EditorController::ZoomCameraAt(double factor, double anchorScreenX,
                                    double anchorScreenY) {
  view_.ZoomAtScreenPoint(factor, anchorScreenX, anchorScreenY);
  view_.Render(model_);
}

void EditorController::ResetCamera() {
  view_.SetCamera({0.0, 0.0});
  view_.Render(model_);
}
