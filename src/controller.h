#pragma once

#include <memory>
#include <string>

#include "model.h"
#include "primitive.h"
#include "view.h"

class EditorController {
 public:
  EditorController(Document& model, EditorView& view);

  void CreateNewDocument();
  void OpenDocument(const std::string& filepath);
  void SaveDocument(const std::string& filepath);
  void AddPrimitive(std::unique_ptr<Primitive> primitive);
  void DeletePrimitive(size_t index);
  void PanCamera(double dx, double dy);
  void ZoomCameraAt(double factor, double anchorScreenX,
                    double anchorScreenY);
  void ResetCamera();

 private:
  Document& model_;
  EditorView& view_;
};
