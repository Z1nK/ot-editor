#include "ui_handlers.h"

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
