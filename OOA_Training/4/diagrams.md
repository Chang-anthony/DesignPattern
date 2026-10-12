# OOA_Training / 4 — School has Classroom

> **Concept:** Composition-style aggregation — a `Classroom` cannot exist without its `School` (passed in the constructor) and registers itself.

## Class Diagram

```mermaid
classDiagram
    class School {
        -set~Classroom~ classrooms
        +AddClassroom(Classroom)
    }
    class Classroom {
        -School school
        +Classroom(School)
    }
    School "1" *-- "*" Classroom
```

## Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant Sc as School
    participant C as Classroom
    Main->>C: new Classroom(nkust)
    C->>Sc: AddClassroom(this)
    Main->>C: new Classroom(nkust)
    C->>Sc: AddClassroom(this)
```
