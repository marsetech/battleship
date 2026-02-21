<h1 align="center">
  <br>
    <a href="https://github.com/marsetech/battleship">
      <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Flogodix.com%2Flogo%2F1784749.png&f=1&nofb=1&ipt=49b4ad1423dddee550c5ff27a22eb2255d1a3377d8aaed36e5cce4a37d4538af" alt="Battleship" width="150">
    </a>
  <br>
    Battleship
  <br>
</h1>

<h4 align="center">
  A modern C++ implementation of the classic Battleship game
</h4>

<p align="center">
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/license-MIT-blue?style=flat" alt="License">
  </a>
  <a href="https://github.com/marsetech/battleship/actions/workflows/ci.yml">
    <img src="https://github.com/marsetech/battleship/actions/workflows/ci.yml/badge.svg" alt="CI Status">
  </a>
<!--
  <a href="https://github.com/marsetech/battleship/issues">
    <img src="https://img.shields.io/github/issues/marsetech/battleship?style=flat" alt="Issues">
  </a>
-->
  <a href="https://www.paypal.me/sonopoverosissimo">
    <img src="https://img.shields.io/badge/$-Support-ff69b4.svg?maxAge=2592000&amp;style=flat" alt="Support">
  </a>
</p>

<p align="center">
  <a href="#overview">Overview</a> •
  <a href="#features">Features</a> •
  <a href="#prerequisites">Prerequisites</a> •
  <a href="#installation">Installation</a> •
  <a href="#license">License</a>
</p>

---

## Overview

**Battleship** is a modern C++ implementation of the classic strategy game.
It features:

- Advanced AI with customizable difficulty levels
- Flexible board configuration and game modes
- Single-player and multiplayer options

This project combines **classic gameplay** with **modern software design practices**, emphasizing modularity, maintainability, and scalability.

> [!NOTE]
> For technical details, please refer to the [`ARCHITECTURE`](docs/ARCHITECTURE.md) documentation.

> [!IMPORTANT]
> This project originated as a **university assignment**. See [`HISTORY`](docs/HISTORY.md) for a detailed evolution of the project.

---

## Features

- **Classic Battleship Rules**: Play solo following traditional rules.
- **AI Opponent**: Compete against an intelligent AI with multiple difficulty levels.
- **Game Customization**: Adjust board size, ship types, and game modes.
- **Multiplayer**: Local or network-based multiplayer support.

A comprehensive list of **implemented and planned features** is available in [`IMPLEMENTATIONS`](docs/IMPLEMENTATIONS.md), along with the **project roadmap**.

> [!CAUTION]
> This project is intended for **educational and experimental purposes**.

---

## Prerequisites

This project uses CMake with CMake Presets to ensure a clean, reproducible, and platform-independent build process. Ensure the following software is installed:

- [Git](https://git-scm.com/)
- [G++](https://gcc.gnu.org/)
- [CMake](https://cmake.org/) (optional, recommended for advanced builds)

---

## Installation

See the detailed [Installation & Build Guide](docs/INSTALLATION.md) for instructions on:

- Installing prerequisites
- Cloning the repository
- Building the project (development or release presets)
- Running tests
- Installing the game system-wide

> [!WARNING]
> Manual compilation of each source file is possible but not recommended, see [`INSTALLATION`](docs/INSTALLATION.md).

---

## License

This project is licensed under the MIT License. For full details, see the [LICENSE](LICENSE) file.
