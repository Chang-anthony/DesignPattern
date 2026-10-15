# OOA_Training / 5 — Employee generalization

> **Concept:** Generalization — `Teacher` and `Executive` share the `Employee` base; `School` depends only on `Employee`.

## Class Diagram

```mermaid
classDiagram
    class School {
        -set~Employee~ employees
        +Employ(Employee)
    }
    class Employee {
        -bool is_teacher
        -bool is_excutive
    }
    class Teacher
    class Executive
    Employee <|-- Teacher
    Employee <|-- Executive
    School "1" o-- "*" Employee
```

## Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant Sc as School
    participant T as Teacher
    participant E as Executive
    Main->>T: new Teacher() (is_teacher = true)
    Main->>E: new Executive() (is_excutive = true)
    Main->>Sc: Employ(teacher)
    Main->>Sc: Employ(executive)
```
