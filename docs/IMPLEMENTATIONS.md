# Project Roadmap

This document provides a structured overview of the **Battleship** project, detailing implemented features, ongoing work, and planned enhancements.
It serves as a **technical reference** and a **development roadmap** for contributors, maintainers, and stakeholders.

---

## Status Legend

| Symbol | Meaning |
|--------|---------|
| ✅ done | Feature fully implemented and tested |
| ⚙ ongoing | Work in progress or under review |
| ⬜ planned | Feature planned for future implementation |

---

## Implemented Features

- [x] Core game rules
- [x] Difficulty selection
- [x] Advanced position customization
- [x] AI multiplayer mode (single-player)

---

## Planned Features

- [ ] Resizable game board
- [ ] Difficulty selection for AI multiplayer
- [ ] Player vs Player (PvP) mode
- [ ] Graphical user interface (GUI)

---

## Development Roadmap

The diagram below visualizes the **current status** of core gameplay, AI, user interface, and maintenance tasks.

<div align="center">

```mermaid
---
config:
  theme: dark
---
flowchart LR
  %% Core Gameplay
  subgraph CG["**Core Gameplay**"]
    cg1["Game rules implemented"] --> cg1s["✅ done"]
    cg2["Board initialization logic"] --> cg2s["✅ done"]
    cg3["Difficulty selection system"] --> cg3s["✅ done"]
    cg4["Advanced position customization"] --> cg4s["✅ done"]
  end

  %% Artificial Intelligence
  subgraph AI["**Artificial Intelligence**"]
    ai1["AI Multiplayer (single-player)"] --> ai1s["✅ done"]
    ai2["AI difficulty scaling"] --> ai2s["⬜ planned"]
    ai3["PvP local multiplayer"] --> ai3s["⬜ planned"]
    ai4["Extended game modes"] --> ai4s["⬜ planned"]
  end

  %% User Interface
  subgraph UI["**User Interface**"]
    ui1["Resizable board support"] --> ui1s["⬜ planned"]
    ui2["Graphical user interface (GUI)"] --> ui2s["⬜ planned"]
  end

  %% Maintenance & Refactoring
  subgraph MT["**Maintenance & Refactoring**"]
    mt1["Code refactoring"] --> mt1s["⚙ ongoing"]
    mt2["Architecture stabilization"] --> mt2s["⚙ ongoing"]
    mt3["Documentation expansion"] --> mt3s["⚙ ongoing"]
    mt4["State validation & error handling"] --> mt4s["⚙ ongoing"]
  end
```
</div>

> [!NOTE]
> - The roadmap is reviewed periodically to ensure alignment with project milestones and release objectives.
> - Feature availability and priorities may evolve as refactoring and new development cycles proceed.
> - Contributions, suggestions, and improvement proposals are encouraged via [GitHub issues](https://github.com/marsetech/battleship/issues) or discussions.
