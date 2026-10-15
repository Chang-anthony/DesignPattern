# OOA_Training / 6 — Person, Love, Marry

> **Concept:** Association classes with lifecycle — `Love` links two persons; `Marry` is created from a `Love` and can break it.

## Class Diagram

```mermaid
classDiagram
    class Preson {
        -Love inlove
        +InLove(Preson) Love
    }
    class Love {
        <<association class>>
        -Preson p1
        -Preson p2
        -Marry marry
        +Domarry() Marry
        +breakup()
    }
    class Marry {
        -int day
        -Love inlove
        +Divorce(int day)
    }
    Preson "2" -- "0..1" Love
    Love "1" -- "0..1" Marry
```

## Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant P1 as Preson p1
    participant L as Love
    participant M as Marry
    participant P2 as Preson p2
    Main->>P1: InLove(p2)
    alt p1 already in love
        P1-->>Main: throw invalid_argument
    else
        P1->>L: new Love(p1, p2)
        P1-->>Main: love
    end
    Main->>L: Domarry()
    L->>M: new Marry(this, 10)
    L-->>Main: marry
    Main->>M: Divorce(9)
    alt day != 10
        M->>L: SetMarry(nullptr)
        M->>L: breakup()
        L->>P1: SetInLove(nullptr)
        L->>P2: SetInLove(nullptr)
    else
        M-->>Main: "this marry is happy"
    end
```
