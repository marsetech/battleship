# Installation & Build Guide

This guide provides detailed instructions for building, testing, and installing **Battleship**, a modern C++ implementation of the classic Battleship game, using **CMake presets** and GitHub Actions workflows.

> [!NOTE]
> All source and header files follow a modular and maintainable structure, supporting scalability.

---

## Table of Contents

- [Prerequisites](#prerequisites)
- [Cloning the Repository](#cloning-the-repository)
- [Building the Project](#building-the-project)
  - [Development Build](#development-build)
  - [Release Build](#release-build)
- [Running the Game](#running-the-game)
- [Installing System-wide](#installing-system-wide-optional)
- [Continuous Integration](#continuous-integration)

---

## Prerequisites

Before building **Battleship**, ensure that the following software components are installed and properly configured:

- **Git** — distributed version control system.
- **C++17 compatible compiler** (e.g., G++, Clang, MSVC).
- **CMake ≥ 3.16** — cross-platform build system and project configuration tool.

> [!TIP]
> Verify the installed compiler supports C++17 features by running `g++ --version`,`clang++ --version` or `cl` on Windows.

### Example Installation (Linux)

**Ubuntu/Debian-based systems:**

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake git
```

**Arch Linux/Manjaro:**

```bash
sudo pacman -Sy --needed base-devel git gcc cmake
```
The above commands install essential development tools, the compiler toolchain, and CMake.
On other distributions or operating systems, adjust the package manager commands accordingly.

---

## Cloning the Repository

Obtain a local copy of the project by cloning the repository, then navigate into the project root:

```bash
git clone https://github.com/marsetech/battleship.git
cd battleship
```

> [!TIP]
> Always perform subsequent build and installation commands from the project root directory to ensure CMake presets and relative paths function correctly.

---

## Building the Project

Battleship relies on **CMake Presets**, defined in the repository-root configuration file [`CMakePresets`](../CMakePresets.json), to provide standardized, reproducible, and portable build configurations across development, testing, and release environments.

> [!IMPORTANT]
> - All CMake commands must be executed from the project root directory.
> - Development builds include the full test suite and are intended for developers and CI pipelines.
> - Release builds are optimized, exclude tests, and are intended for end users.

> [!TIP]
> CMake presets simplify switching between build types and environments.

### Development Build

The development configuration enables tests and debugging features and is suitable for local development and continuous integration.

```bash
# Configure project with dev preset
cmake --preset dev

# Build project
cmake --build --preset dev
```

(Optional, **Dev-Build** only) Running Tests:

```bash
ctest --test-dir build --output-on-failure
```

> [!NOTE]
> All tests are implemented with [Catch2](https://catch2-temp.readthedocs.io/en/latest/index.html) testing framework.

### Release Build

The release configuration produces an optimized build of the game without tests, intended for distribution and end-user execution.

```bash
# Configure project with release preset
cmake --preset release

# Build project
cmake --build --preset release
```

---

## Running the Game

After successfully building the project, the executable can be launched directly from the build output directory.

```bash
# Development build
./build/BattNavale

# Release build
./build-release/BattNavale
```

Alternatively, when using the development configuration, the game can be executed via the dedicated CMake custom target:

```bash
cmake --build --preset dev --target run
```

> [!NOTE]
> The **run** target is available only for development builds and is intended to simplify local testing.

---

## Installing System-wide (Optional)

The game executable can be installed system-wide using CMake’s install mechanism.
By default, the installation prefix is set to `/usr/local`.

```bash
cmake --install build-release
```

Once the installation is complete, the game can be launched from any terminal session:

```bash
BattNavale
```

> [!WARNING]
> Installing to system directories may require elevated privileges. Run the installation command with **sudo**.

---

## Continuous Integration

This project includes a [GitHub Actions workflow](../.github/workflows/ci.yml) with two jobs:

- Build & Test (dev preset): Configures and builds the project using the development preset and executes the full test suite on each push and pull request.
- Builds the optimized release executable without tests, suitable for distribution.

The continuous integration pipeline helps ensure build reproducibility, maintain code quality, and prevent regressions on the **main** and **develop** branches.
