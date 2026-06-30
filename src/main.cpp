#include <iostream>
#include <memory>

#include "controller.h"
#include "model.h"
#include "primitive.h"
#include "ui_handlers.h"
#include "view.h"

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
