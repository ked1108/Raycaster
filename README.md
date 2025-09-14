# Raycaster Engine



A simple **C++ OpenGL raycaster engine** inspired by *Wolfenstein 3D*.
Features include:

* **Random maze generation** (recursive backtracking).
* **First-person navigation** with collision detection.
* **Raycasting renderer** with walls, floor, ceiling, and shading.
* **Mini-map overlay** for debugging.
* **ImGui integration** to tweak settings (FOV, speed, etc.) at runtime.

![Demo](./demo.gif)

---

## 🚀 Features

* **Raycasting (DDA algorithm)** to render walls column by column.
* **Dynamic maze generation** each run.
* **Player movement** (WASD + arrow keys).
* **Runtime controls** with ImGui (adjust FOV, move speed, etc.).
* **Cross-platform** build with CMake (Linux, macOS, Windows).

---

## 📦 Dependencies

This project uses the following libraries:

* [GLFW](https://www.glfw.org/) – windowing and input
* [GLAD](https://glad.dav1d.de/) – OpenGL function loader
* [Dear ImGui](https://github.com/ocornut/imgui) – runtime UI

CMake will fetch these automatically if you use the provided configuration.

---

## 🔧 Build Instructions

### 1. Clone the repository

```bash
git clone https://github.com/ked1108/Raycaster.git
cd Raycaster
```

### 2. Configure with CMake

```bash
cmake -B build
```

### 3. Build

```bash
cmake --build build
```

### 4. Run

```bash
./build/raycaster
```

---

## 🎮 Controls

* **W / S** → Move forward / backward
* **A / D** → Strafe left / right
* **← / →** → Rotate camera
* **M** → Toggle minimap (optional)

---

## ⚙️ Runtime Settings (ImGui)

Open the **Settings** window in the top-left to adjust:

* Field of View (FOV)
* Move speed
* Turn speed
---

## 📜 License

MIT License — feel free to use and modify.
