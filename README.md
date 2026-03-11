# 🔦 RayTracerCPU

A CPU-based ray tracer built from scratch in modern C++, with zero external dependencies.  
This is a personal learning project focused on understanding the mathematics and physics behind computer graphics rendering.

---

## About

Ray tracing is one of the most elegant algorithms in computer graphics — it simulates how light travels by casting rays from a virtual camera into a 3D scene and computing the color of each pixel based on what those rays hit.

This project implements a ray tracer **step by step**, starting from first principles:

- 🧮 **Linear algebra** — 3D vectors, dot/cross products, normalization
- 📐 **Geometric intersections** — ray–sphere, ray–plane equations
- 💡 **Phong lighting model** — ambient, diffuse, and specular components
- 🌑 **Shadows** — shadow ray casting with epsilon bias
- 🪞 **Reflections** — recursive ray tracing with depth limiting
- 🖼️ **PPM image output** — zero-dependency image format, readable by any viewer

The goal is to deeply understand the rendering pipeline by writing every piece of it by hand, in C++, without relying on graphics libraries.

---

## Features

| Feature | Status |
|---|---|
| `Vec3` class — operators, dot, cross, length, normalize | ✅ Done |
| `Ray` class — `P(t) = origin + t·direction` | ✅ Done |
| `Image` — PPM output (`P3` format) | ✅ Done |
| Gradient sky render | ✅ Done |
| Interactive Vec3 test menu | ✅ Done |
| `Camera` — viewport and ray generation per pixel | 🚧 In progress |
| `Sphere` — ray–sphere intersection | 🚧 In progress |
| `Hittable` / `HittableList` — polymorphic scene objects | 🚧 In progress |
| Phong shading (`Light`, `Material`) | 📋 Planned |
| Shadow rays | 📋 Planned |
| Recursive reflections | 📋 Planned |
| Multi-object scene composition | 📋 Planned |

---

## Build & Run

**Requirements:** `g++` with C++17 support (no other dependencies needed).

```bash
# Clone the repository
git clone https://github.com/semedooo/RayTracerCPU.git
cd RayTracerCPU

# Build
make

# Run
make run
# or
./raytracer
```

**Clean build artifacts:**
```bash
make clean
```

---

## Usage

The program starts an interactive menu for testing vector operations and rendering:

```
=== Ray Tracer CPU - Tests ===
1. Sum (+)
2. Subtraction (-)
3. Multiplication (*)
4. Division (/)
5. Dot Product (dot)
6. Cross Product (cross)
7. Length (length)
8. Normalize (normalized)
9. Generate test PPM image
0. Exit
```

Selecting **option 9** generates a gradient test image at `output/test.ppm`.

---

## Project Structure

```
RayTracerCPU/
├── Makefile              # Build rules (g++, C++17)
├── README.md
├── PLANO.md              # Development roadmap (Portuguese)
├── include/
│   ├── Vec3.h            # ✅ 3D vector math
│   ├── Point.h           # ✅ 3D point (P3)
│   ├── Ray.h             # ✅ Ray: origin + t·direction
│   ├── Image.h           # ✅ PPM image output
│   ├── Camera.h          # 🚧 Viewport & ray generation
│   ├── Hittable.h        # 🚧 Abstract hittable interface
│   ├── Sphere.h          # 🚧 Sphere geometry
│   ├── Light.h           # 📋 Point light source
│   └── Material.h        # 📋 Phong material properties
├── src/
│   └── main.cpp          # Entry point & interactive test menu
└── output/
    └── *.ppm             # Rendered images (generated at runtime)
```

---

## Core Concepts

### Vec3 — 3D Vector Math
All geometry lives in `Vec3`, a zero-overhead class implementing the full set of operations needed for ray tracing:
- Component-wise `+`, `-`, `*`, `/`
- **Dot product:** `a·b = ax·bx + ay·by + az·bz` (used in lighting and intersection tests)
- **Cross product:** `a×b` (used for constructing coordinate frames)
- **Normalization:** `v̂ = v / ‖v‖` (directions must always be unit vectors)

### Ray — Parametric Line
A ray is defined as `P(t) = origin + t × direction`, where `t ≥ 0`.  
For every pixel on screen, a ray is cast from the camera's origin through that pixel's viewport position.

### Ray–Sphere Intersection
Substituting the ray equation into the sphere equation yields a quadratic in `t`.  
The discriminant `Δ = b² − 4ac` tells us:
- `Δ < 0` → no intersection
- `Δ = 0` → tangent (one point)
- `Δ > 0` → two intersections (entry and exit)

### Phong Lighting Model
Each visible surface point is shaded using three components:
- **Ambient** — constant base light (`Ia`)
- **Diffuse** — `Id = kd · I · max(0, n̂ · l̂)` — brighter surfaces face the light (`kd` = diffuse reflectance, `I` = light intensity)
- **Specular** — `(r̂ · v̂)^α` — mirror-like highlight based on shininess

---

## Technologies

- **Language:** C++17
- **Build:** GNU Make + g++
- **Image format:** PPM (P3 text format — zero dependencies)
- **Dependencies:** none (standard library only)

---

## Roadmap

See [`PLANO.md`](PLANO.md) for the full step-by-step development plan, including theory notes for each stage.

---

## Author

**Manuel Semedo** — Computer Science student  
Built as a hands-on study of computer graphics, from scratch.