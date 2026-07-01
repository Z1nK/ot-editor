# ot-editor

A simple 2D primitive editor, built in C++20 around an MVC architecture with a
visitor-based rendering pipeline.

## Building

```bash
cmake -S . -B build
cmake --build build
```

This produces the `ot-editor` executable. A Debian package can also be
generated via CPack (`cpack --config build/CPackConfig.cmake`).

## Architecture

The editor follows the **Model-View-Controller** pattern:

- **Model** — `Document` owns the collection of primitives that make up a
  drawing.
- **View** — `EditorView` holds the `Camera` (pan/zoom state) and renders the
  document by dispatching to a `ConsoleRenderer`.
- **Controller** — `EditorController` mediates between the model and view,
  exposing operations like opening/saving documents, adding/removing
  primitives, and panning/zooming the camera.

Shapes (`Circle`, `Square`, `Rectangle`, `Line`) all derive from the abstract
`Primitive` base class and are rendered using the **Visitor** pattern:
`ConsoleRenderer` implements `IPrimitiveVisitor`, and each primitive's
`Accept()` method dispatches to the matching `Visit()` overload.

## Class diagram

```mermaid
classDiagram
    class Point {
        +double x
        +double y
    }

    class Primitive {
        <<abstract>>
        +Accept(IPrimitiveVisitor& visitor) void*
    }

    class Circle {
        -Point center_
        -double radius_
        +Circle(center, radius)
        +Accept(IPrimitiveVisitor& visitor) void
        +GetCenter() Point
        +GetRadius() double
    }

    class Square {
        -Point topLeft_
        -double sideLength_
        +Square(topLeft, sideLength)
        +Accept(IPrimitiveVisitor& visitor) void
        +GetTopLeft() Point
        +GetSideLength() double
    }

    class Rectangle {
        -Point topLeft_
        -double width_
        -double height_
        +Rectangle(topLeft, width, height)
        +Accept(IPrimitiveVisitor& visitor) void
        +GetTopLeft() Point
        +GetWidth() double
        +GetHeight() double
    }

    class Line {
        -Point start_
        -Point end_
        +Line(start, end)
        +Accept(IPrimitiveVisitor& visitor) void
        +GetStart() Point
        +GetEnd() Point
    }

    class IPrimitiveVisitor {
        <<interface>>
        +Visit(const Circle&)* void
        +Visit(const Square&)* void
        +Visit(const Rectangle&)* void
        +Visit(const Line&)* void
    }

    class ConsoleRenderer {
        -Camera& camera_
        +ConsoleRenderer(camera)
        +Visit(const Circle&) void
        +Visit(const Square&) void
        +Visit(const Rectangle&) void
        +Visit(const Line&) void
    }

    class Camera {
        +double offsetX
        +double offsetY
        +double zoom
    }

    class Document {
        -vector~unique_ptr~Primitive~~ primitives_
        -string filepath_
        +AddPrimitive(unique_ptr~Primitive~) void
        +DeletePrimitive(size_t index) void
        +SetPath(string filepath) void
        +GetPrimitives() vector~unique_ptr~Primitive~~
        +clear() void
    }

    class EditorView {
        -Camera camera_
        +PanByScreenDelta(dx, dy) void
        +ZoomAtScreenPoint(factor, x, y) void
        +Render(const Document& doc) void
        +GetCamera() Camera
        +SetCamera(const Camera&) void
    }

    class EditorController {
        -Document& model_
        -EditorView& view_
        +EditorController(model, view)
        +CreateNewDocument() void
        +OpenDocument(filepath) void
        +SaveDocument(filepath) void
        +AddPrimitive(unique_ptr~Primitive~) void
        +DeletePrimitive(size_t index) void
        +PanCamera(dx, dy) void
        +ZoomCameraAt(factor, x, y) void
        +ResetCamera() void
    }

    Primitive <|-- Circle
    Primitive <|-- Square
    Primitive <|-- Rectangle
    Primitive <|-- Line
    IPrimitiveVisitor <|.. ConsoleRenderer
    Primitive ..> IPrimitiveVisitor : Accept(visitor)
    Document o-- "0..*" Primitive : primitives_
    EditorView *-- Camera : camera_
    EditorView ..> Document : Render(doc)
    EditorView ..> ConsoleRenderer : creates
    ConsoleRenderer o-- Camera : camera_
    EditorController --> Document : model_
    EditorController --> EditorView : view_
    EditorController ..> Primitive : passes through

    Circle ..> Point
    Square ..> Point
    Rectangle ..> Point
    Line ..> Point
```
