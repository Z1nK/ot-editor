#pragma once

#include <memory>
#include <string>

#include "controller.h"
#include "primitive.h"

void OnClick_NewDocument(EditorController& controller);
void OnClick_OpenDocument(EditorController& controller,
                          const std::string& filepath);
void OnClick_SaveDocument(EditorController& controller,
                          const std::string& filepath);
void OnClick_AddPrimitive(EditorController& controller,
                          std::unique_ptr<Primitive> primitive);
void OnClick_DeletePrimitive(EditorController& controller, size_t index);
