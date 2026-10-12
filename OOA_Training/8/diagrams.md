# OOA_Training / 8 — Registration with score

> **Concept:** Association class carrying data — the `score` belongs to the relationship between `School` and `Student`, not to either side.

## Class Diagram

```mermaid
classDiagram
    class School {
        -set~Registration~ registers
        +Register(Student, int score) Registration
    }
    class Student {
        -Registration registeration
    }
    class Registration {
        <<association class>>
        -School school
        -Student student
        -int score
    }
    School "1" -- "*" Registration
    Registration "*" -- "1" Student
```

## Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant Sc as School
    participant R as Registration
    participant St as Student
    Main->>Sc: Register(me, 90)
    Sc->>R: new Registration(this, student, 90)
    Sc->>Sc: registers.insert(reg)
    Sc->>St: SetRegisration(reg)
    Sc-->>Main: reg
```
