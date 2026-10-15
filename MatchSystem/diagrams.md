# MatchSystem — Diagrams

> **Patterns:** Strategy (`MatchType`) + Decorator (`Reverse`)

## Class Diagram

```mermaid
classDiagram
    direction LR
    class MatchSystem {
        -set~Individual~ individuals
        -MatchType matchtype
        +AddIndividuals(Individual)
        +Match(Individual) Individual
        +SetMatchType(MatchType)
    }
    class MatchType {
        <<abstract>>
        +Match(Individual, set~Individual~)* vector~Individual~
        +result(Individual, set~Individual~)* Individual
    }
    class DistanceBase {
        +Match(Individual, set~Individual~) vector~Individual~
        +result(Individual, set~Individual~) Individual
    }
    class HabitBase {
        +Match(Individual, set~Individual~) vector~Individual~
        +result(Individual, set~Individual~) Individual
    }
    class Reverse {
        <<decorator>>
        -MatchType reverse
        +Match(Individual, set~Individual~) vector~Individual~
        +result(Individual, set~Individual~) Individual
    }
    class Individual {
        -int id
        -int age
        -string gender
        -string intro
        -Coord coord
        -vector~Habit~ habits
        +AddHabit(Habit)
    }
    class Coord {
        -int x
        -int y
    }
    class Habit {
        -string habit
    }

    MatchSystem "1" o-- "*" Individual
    MatchSystem --> MatchType : strategy
    MatchType <|-- DistanceBase
    MatchType <|-- HabitBase
    MatchType <|-- Reverse
    Reverse o-- MatchType : wraps
    Individual *-- Coord
    Individual o-- "*" Habit
```

## Sequence Diagram — matching with a decorated strategy

```mermaid
sequenceDiagram
    autonumber
    participant C as Client
    participant MS as MatchSystem
    participant R as Reverse
    participant S as HabitBase / DistanceBase

    C->>MS: new MatchSystem(new Reverse(new HabitBase()))
    C->>MS: AddIndividuals(one / two / three)
    C->>MS: Match(one)
    MS->>R: result(one, individuals)
    R->>R: Match(one, individuals)
    R->>S: Match(one, individuals)
    S-->>R: sorted list (best match first)
    R->>R: reverse the list
    R-->>MS: result[0]
    MS-->>C: matched Individual
```

> Without the decorator, `MatchSystem` calls `HabitBase::result()` directly and gets the best match. Wrapping it in `Reverse` changes the outcome without touching `HabitBase`.
