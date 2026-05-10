# RayTracerCPU

CPU ray tracer built from scratch in modern C++17.

The project is focused on clarity and incremental learning: each rendering concept is implemented step by step, from geometry intersection to scene rendering and shading.

Current implementation includes an SFML-based viewer that automatically opens generated PPM images after each render preset.

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
| Preset scene rendering menu | Complete |
| Phong shading (ambient + diffuse + specular) | Complete |
| Hard shadows via shadow rays | Complete |
| Interactive custom scene workflow (lights + objects) | Complete |
| Reflections (recursive with max_depth) | Complete |

## Build And Run

Requirements:
- g++ with C++17 support
- make
- SFML development libraries

Linux (Ubuntu/Debian):

```bash
sudo apt update
sudo apt install libsfml-dev
```

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

--- Basic Presets (Non-Reflective) ---
1. Render Centered Sphere
2. Render Ground Plane
3. Render Three Spheres
4. Render Sphere and Plane
5. Render Custom Scene

--- Reflection Showcase ---
6. Reflective Sphere (30%)
7. Reflective Sphere (80%)
8. Two Spheres Reflecting

0. Exit
```

Generated files:
- Option `1` -> `output/sphere_centered.ppm`
- Option `2` -> `output/ground_plane.ppm`
- Option `3` -> `output/three_spheres.ppm`
- Option `4` -> `output/sphere_and_plane.ppm`
- Option `5` -> `output/multiple_objects.ppm`
- Option `6` -> `output/reflective_sphere_lo.ppm`
- Option `7` -> `output/reflective_sphere_med.ppm`
- Option `8` -> `output/two_reflective_spheres.ppm`

## Custom Scene Workflow

Option `5` (Custom Scene) now follows this flow:

1. Choose light preset:
    - `1` Default
    - `2` Top
    - `3` Left
    - `4` Right
    - `5` Back
2. Choose camera focal length.
3. Add objects from one unified menu (repeat as needed, then render with `0`):
    - `1` Left Sphere
    - `2` Close Sphere
    - `3` Right Sphere
    - `4` Distant Sphere
    - `5` Ground Plane
    - `6` Inclined Plane
    - `7` Background Plane
    - `8` Left Vertical Plane
    - `9` Add Sphere Manually
    - `10` Add Plane Manually
    - `0` Render Scene

Each object addition prints a positive confirmation and current scene object count in the terminal.

## Project Layout

```text
RayTracerCPU/
├── Makefile
├── PPMViewerCLI.cpp
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
│   ├── RenderTests.h
│   ├── Light.h
│   └── Material.h
├── src/
│   ├── main.cpp
│   ├── InputUtils.cpp
│   ├── Menu.cpp
│   ├── ShowPPM.cpp
│   └── RenderTests.cpp
└── output/
    └── *.ppm
```

### Module Responsibilities

- `main.cpp`: program loop and option dispatch.
- `InputUtils`: shared terminal input/output helpers.
- `Menu`: interactive menu rendering.
- `RenderTests`: render presets and custom scene setup.
- `ShowPPM`: robust PPM (`P3`/`P6`) loader and SFML viewer.
- `HittableList`: scene container abstraction for multiple hittable objects.
- `PPMViewerCLI.cpp`: standalone CLI that reuses the same viewer implementation.

## Current Presets

**Basic (Non-Reflective):**
- Centered sphere: `Sphere((0, 0, -1), 0.5)`
- Ground plane: `Plane((0, -0.6, 0), normal=(0, 1, 0))`
- Three spheres: three different radii/depths for quick composition testing
- Sphere + plane: simple "object on floor" baseline scene
- Custom scene: interactive light selection, focal length input, and unified object-add menu

**Reflection Showcase:**
- Reflective Sphere (30%): Single sphere with 30% reflectivity to show subtle reflections
- Reflective Sphere (80%): Single sphere with 80% reflectivity to show high-mirror behavior
- Two Spheres Reflecting: Two spheres with 50% reflectivity each, reflecting one another

## Core Math Notes

- Ray equation: `P(t) = O + tD`, with `t >= 0`.
- Sphere equation: `||P - C||^2 = r^2`.
- Substituting a ray into the sphere equation yields a quadratic in `t`.
- The discriminant determines hit/no-hit and entry/exit intersections.

## Tech Stack

- Language: C++17
- Build: GNU Make + g++
- Image format: PPM (`P3` and `P6` support in viewer)
- Graphics/viewer: SFML (`graphics`, `window`, `system`)

## Rendering Features Implemented

- Sky gradient background.
- Diffuse + specular Phong lighting with ambient term.
- Shadow rays with epsilon bias to avoid self-shadowing acne.
- Shadow behavior: when a point is occluded from the light, only ambient is kept.
- **Recursive reflections** with configurable reflectivity per material.
- Reflection blending: `(1 - reflectivity) * local_color + reflectivity * reflected_color`.
- Max depth limit (4 levels) to prevent excessive recursion and performance cost.

## Author

Manuel Semedo

## PPM Viewer

The main application automatically opens the generated image in a non-resizable SFML window after each render.

You can also open any `.ppm` manually with the standalone viewer.

### Build the standalone viewer

```sh
make viewer
```

Equivalent manual compile:

```sh
g++ -std=c++17 -Iinclude PPMViewerCLI.cpp src/ShowPPM.cpp -o ppm_viewer -lsfml-graphics -lsfml-window -lsfml-system
```

### Run the standalone viewer

```sh
./ppm_viewer path/to/image.ppm
```

Example:
```sh
./ppm_viewer output/sphere_centered.ppm
```

Press ESC or close the window to exit.
