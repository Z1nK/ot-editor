#pragma once

#include "model.h"

struct Camera {
  double offsetX = 0.0;
  double offsetY = 0.0;
  double zoom = 1.0;
};

class EditorView {
 public:
  void PanByScreenDelta(double dx, double dy);
  void ZoomAtScreenPoint(double factor, double screenX, double screenY);
  void Render(const Document& doc);
  Camera GetCamera() const;
  void SetCamera(const Camera& camera);

 private:
  Camera camera_;
};
