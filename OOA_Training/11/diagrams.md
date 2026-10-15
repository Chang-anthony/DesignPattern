# OOA_Training / 11 — File system

> **Concept:** Recursive structure (Composite shape) — a `Directory` holds `Item`s, which can be `File`s or other `Directory`s.

## Class Diagram

```mermaid
classDiagram
    class Item {
        <<abstract>>
    }
    class File
    class Directory {
        -set~Item~ items
        +AddItem(Item)
        +Delete()
    }
    Item <|-- File
    Item <|-- Directory
    Directory "1" o-- "*" Item
```

## Sequence Diagram

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant Root as Directory root
    participant F1 as File f1
    participant D1 as Directory one
    Main->>Root: AddItem(f1)
    Main->>Root: AddItem(f2)
    Main->>Root: AddItem(one)
    Main->>Root: Delete()
    Root->>Root: items = empty set
```
