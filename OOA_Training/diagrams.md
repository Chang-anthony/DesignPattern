# OOA_Training — Diagram Index

Each exercise folder has its own `diagrams.md` with a class diagram and a sequence diagram.

| # | Topic | Concept |
|---|---|---|
| [1](1/diagrams.md) | Teacher uses Handout | Dependency — `Teacher` only uses a `Handout` as a parameter; it does not keep a reference. |
| [2](2/diagrams.md) | Teacher ↔ Student | Bidirectional many-to-many association — both sides keep a `std::set` of the other. |
| [3](3/diagrams.md) | School employs Teacher | Bidirectional one-to-many — the school keeps all teachers, each teacher knows its school. |
| [4](4/diagrams.md) | School has Classroom | Composition-style aggregation — a `Classroom` cannot exist without its `School` (passed in the constructor) and registers itself. |
| [5](5/diagrams.md) | Employee generalization | Generalization — `Teacher` and `Executive` share the `Employee` base; `School` depends only on `Employee`. |
| [6](6/diagrams.md) | Person, Love, Marry | Association classes with lifecycle — `Love` links two persons; `Marry` is created from a `Love` and can break it. |
| [7](7/diagrams.md) | Classmate friends | Reflexive (self) association — a `Classmate` is friends with other `Classmate`s, kept on both sides. |
| [8](8/diagrams.md) | Registration with score | Association class carrying data — the `score` belongs to the relationship between `School` and `Student`, not to either side. |
| [9](9/diagrams.md) | City and Road | Graph-like association — a `Road` connects exactly two `City` objects; each city keeps its roads. |
| [10](10/diagrams.md) | Manager and Employee | Inheritance + reflexive one-to-many — a `Manager` is an `Employee` and manages other employees. |
| [11](11/diagrams.md) | File system | Recursive structure (Composite shape) — a `Directory` holds `Item`s, which can be `File`s or other `Directory`s. |
| [12](12/diagrams.md) | Journey structure | Multi-level aggregation — Journey → Chapter → Mission → Scene / Challenge. (Model only; `main()` is empty.) |
| [13](13/diagrams.md) | World and Adventurer | Bidirectional association with behaviour delegation — the adventurer rolls a die and asks the world to move it. |
| [14](14/diagrams.md) | Heroes attack each other | Self-association used for interaction — each `Hero` knows the other heroes and attacks a random one. |
| [15](15/diagrams.md) | Browser and WebServer | Deeper inheritance hierarchy + request/response collaboration. (Model only; `main()` is empty.) |

## UML relationship cheat sheet (Mermaid syntax)

| Relationship | Mermaid | Meaning | Example here |
|---|---|---|---|
| Dependency | `A ..> B` | A uses B temporarily (parameter / local) | 1 |
| Association | `A -- B` / `A --> B` | A keeps a reference to B | 2, 3, 9 |
| Aggregation | `A o-- B` | whole has parts; parts can live alone | 5, 11 |
| Composition | `A *-- B` | parts cannot live without the whole | 4, 12 |
| Inheritance | `A <\|-- B` | B is a kind of A | 5, 10, 11, 15 |
| Realization | `A <\|.. B` | B implements interface A | — |
| Association class | separate class linked to both sides | the relationship has its own data | 6, 8 |
