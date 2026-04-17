# RayTracerCPU

CPU ray tracer built from scratch in modern C++17, with no external runtime dependencies.

The project is focused on clarity and incremental learning: each rendering concept is implemented step by step, from vector math to geometric intersection and shading.

## Current Scope

| Component | Status |
|---|---|
| `Vec3` math (`+`, `-`, `*`, `/`, `dot`, `cross`, `length`, `normalized`) | Complete |
| `Ray` (`P(t) = origin + t * direction`) | Complete |
| PPM image writer (`P3`) | Complete |
| Camera viewport + per-pixel ray generation | Complete |
| Sky gradient rendering | Complete |
| Ray-sphere intersection | Complete |
| Normal-based sphere shading | Complete |
| `Hittable` abstraction | Complete |
| `HittableList` scene container | Complete |
| Plane intersection and shading | Complete |
| Multiple-object scene render test | Complete |
| Phong lighting, shadows, reflections | Planned |

## Build And Run

Requirements: `g++` with C++17 support and `make`.

```bash
git clone https://github.com/semedooo/RayTracerCPU.git
cd RayTracerCPU
make
make run
```

Clean artifacts:

```bash
make clean
```

## Interactive Menu

The executable starts an interactive test menu:

```text
=== RayTracerCPU - Interactive Tests ===
-- Vec3 Operations --
1. Vector Add (+)
2. Vector Subtract (-)
3. Vector Multiply (component-wise)
4. Vector Divide (component-wise)
5. Dot Product
6. Cross Product
7. Vector Length
8. Normalize Vector
-- Rendering --
9. Render Gradient Test (PPM)
10. Render Sky Color From Camera Rays
11. Render Sphere Intersection Test
12. Render Multiple Objects Test
0. Exit
```

Generated files:
- Option `9` -> `output/test.ppm`
- Option `10` -> `output/raytracer.ppm`
- Option `11` -> `output/sphere.ppm`
- Option `12` -> `output/multiple_objects.ppm`

## Project Layout

```text
RayTracerCPU/
├── Makefile
├── README.md
├── include/
│   ├── Vec3.h
│   ├── Ray.h
│   ├── Image.h
│   ├── Camera.h
│   ├── Hittable.h
│   ├── HittableList.h
│   ├── Sphere.h
│   ├── Plane.h
│   ├── InputUtils.h
│   ├── Menu.h
│   ├── VectorTests.h
│   ├── RenderTests.h
│   ├── Light.h
│   └── Material.h
├── src/
│   ├── main.cpp
│   ├── InputUtils.cpp
│   ├── Menu.cpp
│   ├── VectorTests.cpp
│   └── RenderTests.cpp
└── output/
    └── *.ppm
```

### Module Responsibilities

- `main.cpp`: program loop and option dispatch.
- `InputUtils`: shared terminal input/output helpers.
- `Menu`: interactive menu rendering.
- `VectorTests`: Vec3 operation handlers (options 1-8).
- `RenderTests`: rendering handlers (options 9-12), including sphere, plane, and multi-object scene tests.
- `HittableList`: scene container abstraction for multiple hittable objects.

## Core Math Notes

- Ray equation: `P(t) = O + tD`, with `t >= 0`.
- Sphere equation: `||P - C||^2 = r^2`.
- Substituting a ray into the sphere equation yields a quadratic in `t`.
- The discriminant determines hit/no-hit and entry/exit intersections.

## Tech Stack

- Language: C++17
- Build: GNU Make + g++
- Image format: plain-text PPM (`P3`)
- Dependencies: C++ standard library only

## Author

Manuel Semedo
