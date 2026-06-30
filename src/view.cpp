#include "view.h"

#include <algorithm>

void EditorView::PanByScreenDelta(double dx, double dy) {
  camera_.offsetX += dx / camera_.zoom;
  camera_.offsetY += dy / camera_.zoom;
}

void EditorView::ZoomAtScreenPoint(double factor, double screenX,
                                   double screenY) {
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

void EditorView::Render(const Document& doc) {
  for (const auto& primitive : doc.GetPrimitives()) {
    primitive->Draw(camera_.offsetX, camera_.offsetY, camera_.zoom);
  }
}

Camera EditorView::GetCamera() const { return camera_; }

void EditorView::SetCamera(const Camera& camera) { camera_ = camera; }
