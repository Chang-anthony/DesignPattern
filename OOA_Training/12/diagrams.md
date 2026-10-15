# OOA_Training / 12 — Journey structure

> **Concept:** Multi-level aggregation — Journey → Chapter → Mission → Scene / Challenge. (Model only; `main()` is empty.)

## Class Diagram

```mermaid
classDiagram
    class Journey {
        -set~Chapter~ chapters
        +AddChapter(Chapter)
    }
    class Chapter {
        -set~Mission~ missions
        +AddMission(Mission)
    }
    class Mission {
        -set~Scene~ scenes
        -set~Challenge~ challenge
        +AddScene(Scene)
        +AddChallenge(Challenge)
    }
    class Scene
    class Challenge
    Journey "1" *-- "*" Chapter
    Chapter "1" *-- "*" Mission
    Mission "1" *-- "*" Scene
    Mission "1" *-- "*" Challenge
```

## Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant C as Client
    participant J as Journey
    participant Ch as Chapter
    participant M as Mission
    C->>M: AddScene(scene)
    C->>M: AddChallenge(challenge)
    C->>Ch: AddMission(mission)
    C->>J: AddChapter(chapter)
```
