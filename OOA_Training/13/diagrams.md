# OOA_Training / 13 — World and Adventurer

> **Concept:** Bidirectional association with behaviour delegation — the adventurer rolls a die and asks the world to move it.

## Class Diagram

```mermaid
classDiagram
    class World {
        -set~Adventurer~ adventurers
        +AddAdventurer(Adventurer)
        +MoveForward(Adventurer, int steps)
    }
    class Adventurer {
        -World world
        -int step
        +RolltheDice()
        +AddStep(int)
    }
    World "1" -- "*" Adventurer
```

## Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant Ad as Adventurer
    participant W as World
    loop 50 times
        Main->>Ad: RolltheDice()
        Ad->>Ad: random forward (1-3 / 4-6 / 0)
        Ad->>W: MoveForward(this, forward)
        W->>Ad: AddStep(forward)
    end
```
