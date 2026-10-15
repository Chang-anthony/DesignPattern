# OOA_Training / 14 — Heroes attack each other

> **Concept:** Self-association used for interaction — each `Hero` knows the other heroes and attacks a random one.

## Class Diagram

```mermaid
classDiagram
    class Hero {
        -int hp
        -int strength
        -int Defense
        -vector~Hero~ heros
        +TakeTurn()
        +Attack(Hero)
    }
    Hero "1" --> "*" Hero : knows
```

## Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant A as Hero A
    participant H as each hero
    participant T as random target
    Main->>A: SetHeros({A, B, C, D})
    Main->>A: TakeTurn()
    loop each hero in heros
        A->>A: target = heros[rand() % 4]
        opt hero != target
            A->>H: Attack(target)
            H->>T: hp = hp - strength + Defense
        end
    end
```
