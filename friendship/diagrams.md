# friendship — Diagrams

> **Pattern:** Adapter (object adapter)

| Role | Class |
|---|---|
| Client | `RelationshipAnalyer` |
| Target | `RelationshipGraph` |
| Adapter | `ConnectivityAnalyerAdapter` |
| Adaptee | `Graph` (third-party style library) |

## Class Diagram

```mermaid
classDiagram
    direction LR
    class RelationshipAnalyer {
        <<client>>
        -vector~Relation~ graph
        -RelationshipGraph analyzer
        +parser(scripts) vector~Relation~
        +hasConnection(graph, name1, name2) bool
        +isMutualFriend(graph, name1, name2) vector~string~
        +AddRelation(Relation)
    }
    class RelationshipGraph {
        <<target>>
        +parser(scripts)* vector~Relation~
        +hasConnection(graph, name1, name2)* bool
        +isMutualFriend(graph, name1, name2)* vector~string~
    }
    class ConnectivityAnalyerAdapter {
        <<adapter>>
        -Graph libary
        +parser(scripts) vector~Relation~
        +hasConnection(graph, name1, name2) bool
        +isMutualFriend(graph, name1, name2) vector~string~
        -parseLine(line) pair
        -ToConnections(graph) vector~vector~string~~
        -Trim(string) string
    }
    class Graph {
        <<adaptee>>
        -vector~vector~string~~ connections
        +hasConnection(name1, name2) bool
        +isMutualFriend(name1, name2) vector~string~
        -dfs(name1, name2, visited) bool
    }
    class Relation {
        -map~string, Friends~ relations
    }
    class Friends {
        -vector~string~ friends
        +AddFriend(name)
    }

    RelationshipAnalyer --> RelationshipGraph
    RelationshipAnalyer o-- "*" Relation
    RelationshipGraph <|-- ConnectivityAnalyerAdapter
    ConnectivityAnalyerAdapter --> Graph : adapts
    Relation o-- Friends
```

## Sequence Diagram — "are A and B connected?"

```mermaid
sequenceDiagram
    autonumber
    participant C as Client
    participant RA as RelationshipAnalyer
    participant AD as ConnectivityAnalyerAdapter
    participant G as Graph (library)

    C->>RA: parser(scriptLines)
    RA->>AD: parser(scriptLines)
    AD->>AD: parseLine() + Trim() per line
    AD-->>RA: vector of Relation
    C->>RA: hasConnection(graph, "A", "B")
    RA->>AD: hasConnection(graph, "A", "B")
    AD->>AD: ToConnections(graph) — Relation → edge list
    AD->>G: SetConnections(edges)
    AD->>G: hasConnection("A", "B")
    G->>G: dfs()
    G-->>AD: bool
    AD-->>RA: bool
    RA-->>C: bool
```

> The client never sees `Graph`'s data format. Swapping in another graph library means writing a new adapter only.
