# Design Pattern Learning Code

C++ practice projects for object-oriented analysis (OOA) and the classic GoF design patterns. Each top-level folder is a self-contained CMake project that models one small problem (a card game, a logging framework, an RPG…) and applies one or more patterns to it.

## Contents

- [Pattern index](#pattern-index)
- [Common project layout](#common-project-layout)
- [Build and test](#build-and-test)
- [Projects](#projects)
  - [OOA_Training](#ooa_training--object-oriented-analysis-basics)
  - [WaterBallSchool](#waterballschool--ooa-domain-model)
  - [ShowDown](#showdown--ooa)
  - [MatchSystem](#matchsystem--strategy--decorator)
  - [CardGameFramework](#cardgameframework--template-method)
  - [Collision](#collision--chain-of-responsibility)
  - [Mat3D](#mat3d--chain-of-responsibility--template-method)
  - [BigTwo](#bigtwo--chain-of-responsibility--template-method--strategy)
  - [YtChannel](#ytchannel--observer)
  - [KeyBoardShortCut](#keyboardshortcut--command)
  - [treasuremap](#treasuremap--state--strategy--chain-of-responsibility)
  - [prescriber_system](#prescriber_system--facade--strategy)
  - [friendship](#friendship--adapter)
  - [employee](#employee--proxy)
  - [logframework](#logframework--composite--strategy)
  - [RPGGame](#rpggame--state--observer--chain-of-responsibility--strategy)
- [Diagrams](#diagrams)
- [Pattern concepts](#pattern-concepts)

---

## Pattern index

| Pattern | Category | Where it is used |
|---|---|---|
| OOA (association, aggregation, inheritance) | — | OOA_Training, WaterBallSchool, ShowDown |
| Strategy | Behavioral | MatchSystem, BigTwo, treasuremap, prescriber_system, logframework, RPGGame |
| Template Method | Behavioral | CardGameFramework, Mat3D, BigTwo |
| Chain of Responsibility | Behavioral | Collision, Mat3D, BigTwo, treasuremap, RPGGame |
| Observer | Behavioral | YtChannel, RPGGame |
| Command | Behavioral | KeyBoardShortCut |
| State | Behavioral | treasuremap, RPGGame |
| Facade | Structural | prescriber_system |
| Adapter | Structural | friendship |
| Proxy | Structural | employee |
| Composite | Structural | logframework, KeyBoardShortCut (macro), OOA_Training/11 |
| Decorator | Structural | MatchSystem (`Reverse`) |

---

## Common project layout

Most projects follow the same shape:

```
<Project>/
├── CMakeLists.txt      # project definition, fetches GoogleTest, builds <PROJECT>_LIB + executable
├── main.cpp            # demo / entry point
├── include/            # headers (*.hpp / *.h), sometimes split into sub-folders by role
│   └── utils/utils.h   # small shared helpers
├── src/                # implementations, mirroring include/
│   └── *.cmake / CMakeLists.txt   # source lists
└── test/
    ├── CMakeLists.txt
    ├── ExampleTests.cpp          # GoogleTest cases
    ├── libary/                   # test helpers (FileIterator, parsers)
    ├── testSet/                  # *.in / *.out golden files (BigTwo)
    └── run_tests.sh / run_tests.bat
```

`KeyBoardShortCut` and `YtChannel` use `lib/` instead of `include/` + `src/` (header and source side by side).

## Build and test

Requirements: CMake ≥ 3.12, a C++20 compiler. GoogleTest is downloaded automatically through `FetchContent`.

```bash
cd <Project>
cmake -S . -B build
cmake --build build
./build/<executable>          # run the demo
cd test && ./run_tests.sh     # or run_tests.bat on Windows; runs build/Test
```

---

## Projects

### OOA_Training — object-oriented analysis basics

📐 **Diagrams:** [`OOA_Training/diagrams.md`](OOA_Training/diagrams.md) — class + sequence diagrams

Fifteen small exercises that translate a domain description into classes and relationships before any pattern is used. Each numbered folder is its own CMake project.

```
OOA_Training/
├── 1/   Teacher, Handout                 # simple association
├── 2/   Teacher, Student                 # many-to-many (std::set on both sides)
├── 3/   School, Teacher                  # bidirectional one-to-many
├── 4/   School, Classroom                # aggregation
├── 5/   Employee ← Teacher / Executive   # inheritance (generalization)
├── 6/   Person, Love, Marry              # association classes with state (relationship over time)
├── 7/   Classmate                        # self-association (friends of the same class)
├── 8/   Student, School, Registration    # association class carrying data (score)
├── 9/   City, Road                       # graph-like association
├── 10/  Employee ← Manager               # reflexive manager/subordinate
├── 11/  Item ← File / Directory          # recursive structure (Composite shape)
├── 12/  Journey, Chapter, Mission, Scene, Challenge   # multi-level aggregation
├── 13/  World, Adventurer
├── 14/  Hero                             # attributes + collection
└── 15/  WebServer, Browser, Response, Resource ← File ← Html / Image ← JPG / PNG   # deeper hierarchy
```

**Concept:** OOA is about finding the nouns (classes), the verbs (methods), and the *multiplicity* of relationships. Key ideas practised here:
- **Association** – one object holds a reference to another (`Teacher*`).
- **Aggregation / composition** – a whole owns a collection of parts (`std::set<Classroom*>`).
- **Association class** – when the relationship itself has data (`Registration` has a `score`; `Marry` has a `day`).
- **Generalization** – shared attributes move up into a base class (`Employee`).

### WaterBallSchool — OOA domain model

📐 **Diagrams:** [`WaterBallSchool/diagrams.md`](WaterBallSchool/diagrams.md) — class + sequence diagrams

```
WaterBallSchool/include/
├── Journey.h           # a course: chapters, adventurers, tour groups
├── Chapter.h → Mission.h → Scene.h (abstract) ← VideoScene.h / ContentScene.h
├── Challenge.h
├── Student.h, Adventurer.h, TourGroup.h
├── CheckMissionState.h # association class: which student is doing which mission + progress
└── LevelSheet.h        # exp → level lookup
```

**Concept:** a full domain model of an online course platform. `Scene` is an abstract class whose subclasses decide `ExpAward()`; `CheckMissionState` is an association class that links a `Student` to a `Mission` and stores its completion state.

### ShowDown — OOA

📐 **Diagrams:** [`ShowDown/diagrams.md`](ShowDown/diagrams.md) — class + sequence diagrams

```
ShowDown/include/
├── Showdown.hpp          # game flow
├── Card, Deck, Rank, Suit
├── Player ← HumanPlayer / AIPlayer
└── ExchangeCard.hpp      # association class: a temporary hand exchange between two players
```

**Concept:** model a card game from a requirement spec. Human vs AI players differ only in how they choose, so they share a `Player` base.

### MatchSystem — Strategy (+ Decorator)

📐 **Diagrams:** [`MatchSystem/diagrams.md`](MatchSystem/diagrams.md) — class + sequence diagrams

```
MatchSystem/include/
├── MatchSystem.hpp, Individual.hpp, Coord.hpp, Habit.hpp
├── MatchType.hpp          # strategy interface: Match(), result()
├── DistanceBase.hpp       # match by nearest coordinate
├── HabitBase.hpp          # match by most common habits
└── Reverse.hpp            # wraps another MatchType and reverses its result
```

**Concept:** the matching algorithm is swappable at runtime. `MatchSystem` depends only on `MatchType`; new algorithms are new classes. `Reverse` holds a `MatchType*` and is itself a `MatchType`, which is the Decorator idea — it adds behaviour (reversing order) without changing the wrapped strategy.

### CardGameFramework — Template Method

📐 **Diagrams:** [`CardGameFramework/diagrams.md`](CardGameFramework/diagrams.md) — class + sequence diagrams

```
CardGameFramework/include/
├── CardFramework/   CardGame (abstract), Card, Deck, Hand, Player   # reusable skeleton
├── ShowDown/        Showdown : CardGame, ShowDownCard, ShowDownPlayer ← Human / AI
└── Uno/             Uno : CardGame, UnoCard, UnoPlayer ← Human / AI
```

**Concept:** `CardGame::GameStart()` fixes the order of the game (deal → rounds → end → winner). The varying steps — `Round()`, `DrawCardEnd()`, `IsGameEnd()`, `GetWinner()` — are pure virtual hooks implemented by `Showdown` and `Uno`. Two different games reuse one algorithm skeleton.

### Collision — Chain of Responsibility

📐 **Diagrams:** [`Collision/diagrams.md`](Collision/diagrams.md) — class + sequence diagrams

```
Collision/include/
├── World.hpp                 # moves sprites, triggers collisions
├── Sprite.hpp ← Hero / Water / Fire
├── CollisionHandle.hpp       # base handler with `next`
├── HeroFireHandler, HeroWaterHandler, WaterFireHandler, SameTypeHandler
```

**Concept:** `World` sends every collision to the first handler. Each handler checks whether it matches the pair of sprite types; if not, it forwards to `next`. Adding a new collision rule means adding a new handler to the chain, not editing a big `if/else` in `World`.

### Mat3D — Chain of Responsibility + Template Method

📐 **Diagrams:** [`Mat3D/diagrams.md`](Mat3D/diagrams.md) — class + sequence diagrams

```
Mat3D/include/
├── Mat3D.hpp                 # 3D char matrix (m × n × r)
├── Handle.hpp                # CoR base: match(flat) + next
├── PrintPlaneTemplate.hpp    # Template Method: printHandle() loop, abstract GetValue/GetNum1/GetNum2/IsBounder
└── MNHandle / MRHandle / NRHandle   # print the MN, MR or NR plane
```

**Concept:** the chain selects which plane to print (`"MN"`, `"MR"`, `"NR"`); the template class owns the shared printing loop and each concrete handler only supplies plane-specific indexing. Shows how two patterns compose: CoR picks *who*, Template Method defines *how*.

### BigTwo — Chain of Responsibility + Template Method + Strategy

📐 **Diagrams:** [`BigTwo/diagrams.md`](BigTwo/diagrams.md) — class + sequence diagrams

```
BigTwo/include/
├── bigtwo/
│   ├── Bigtwo.hpp
│   ├── Round.hpp ← FirstRound.hpp          # Template Method: a round; the first round adds the ♣3 rule
│   ├── CardPatternHandler.hpp              # CoR base: match(), isBigger(), GetPatternName()
│   └── SingleHandler, PairHandler, StraightHandler, FullHouseHandler
├── Card/    Card, Deck, Rank, Suit
└── Player/  Player ← HumanPlayer / AIPlayer, HandCard   # Strategy: how a player chooses a play
test/testSet/   *.in / *.out golden files (straight, fullhouse, illegal-actions, …)
```

**Concept:** card-pattern validation and comparison is a chain (single → pair → straight → full house); a new pattern is one new handler. `FirstRound` overrides the round’s validity condition. Human and AI players are interchangeable decision strategies. Behaviour is verified with input/output golden files.

### YtChannel — Observer

📐 **Diagrams:** [`YtChannel/diagrams.md`](YtChannel/diagrams.md) — class + sequence diagrams

```
YtChannel/lib/
├── Channel/     Channel.hpp (subject), Video.hpp
└── Subscriber/  ChannelSubscriber.hpp (observer) ← Waterball / Fireball
```

**Concept:** `Channel` keeps a list of `ChannelSubscriber*`. When a video is uploaded it calls `notifiy()`, and each subscriber reacts in its own way (`Waterball` likes the video, `Fireball` unsubscribes). The channel never knows concrete subscriber types. A monitor thread with a mutex watches for uploads.

### KeyBoardShortCut — Command

📐 **Diagrams:** [`KeyBoardShortCut/diagrams.md`](KeyBoardShortCut/diagrams.md) — class + sequence diagrams

```
KeyBoardShortCut/lib/
├── Command/  Command.hpp (execute/undo)
│             TankMoveForward/Backward, TelecomConnect/Disconnect, ResetCommand, MarcoCommand
└── Device/   MainController.hpp (invoker), Tank.hpp, Telecom.hpp (receivers), Client.hpp
```

**Concept:** each key is bound to a `Command` object instead of a hard-coded function. `MainController` keeps two stacks to support **undo/redo**. `MarcoCommand` (macro) holds a list of commands and runs them as one — a Composite of commands. `ResetCommand` clears key bindings and can itself be undone.

### treasuremap — State + Strategy + Chain of Responsibility

📐 **Diagrams:** [`treasuremap/diagrams.md`](treasuremap/diagrams.md) — class + sequence diagrams

```
treasuremap/include/
├── Game/       Adventure, Round, TouchedHandler (CoR) ← RoleObstacleTouched / RoleTreasureTouched
├── Mapobject/  Mapobject ← Obstacle / Treasure / Role, Coord, Content
└── Role/
    ├── Role ← Charator / Monster
    ├── State.hpp ← NormalState, Invincible, Poisoned, Accelerated, Healing,
    │               Orderless, Stockpile, Erupting, Teleport
    └── AttackType.hpp ← NormalAttack, FullAttack, MonsterAttack   # Strategy
```

**Concept:** a role’s behaviour (how many actions, how it takes damage, what happens each turn) depends on its current `State`. States implement `enterState`/`exitState`/`action`/`attacked` and switch the role to the next state themselves (e.g. `Stockpile` → `Erupting` → `Teleport`). Attack style is a separate strategy. Touch events between map objects go through a handler chain.

### prescriber_system — Facade (+ Strategy)

📐 **Diagrams:** [`prescriber_system/diagrams.md`](prescriber_system/diagrams.md) — class + sequence diagrams

```
prescriber_system/include/
├── PrescriberFacade.hpp      # single entry: diagnosis(id, symptoms, saveOpt, outputPath)
├── Database, Patient, Case
├── Prescriber, DiagnosticRules, Prescription
└── SaveDiagnositic.hpp ← SaveJson / SaveCsv   # Strategy for output format
data.json                     # patient data
```

**Concept:** loading the database, loading rules, running the prescriber and saving the result involve many classes. `PrescriberFacade` hides that subsystem behind one method, so the client only calls `diagnosis(...)`. Output format is selected with bit flags (`SAVE_AS_JSON`, `SAVE_AS_CSV`) and implemented as interchangeable savers.

### friendship — Adapter

📐 **Diagrams:** [`friendship/diagrams.md`](friendship/diagrams.md) — class + sequence diagrams

```
friendship/include/
├── RelationshipAnalyer.hpp          # client
├── RelationshipGraph.hpp            # target interface: parser, hasConnection, isMutualFriend
├── ConnectivityAnalyerAdapter.hpp   # adapter: implements RelationshipGraph using Graph
├── Graph.hpp                        # adaptee: third-party style graph library
└── Relation.hpp, Friends.hpp
script.txt                           # input relationships
```

**Concept:** the client expects `RelationshipGraph`, but the existing `Graph` library has a different interface. The adapter converts relationship data into what `Graph` understands (`ToConnections`, `parseLine`) and translates the results back, so neither side has to change.

### employee — Proxy

📐 **Diagrams:** [`employee/diagrams.md`](employee/diagrams.md) — class + sequence diagrams

```
employee/include/
├── Database.hpp                  # subject interface: getEmployeeById, getSubordinatesById
├── RealDatabase.hpp              # real subject: reads data.data
├── LazyInitDatabaseProxy.hpp     # virtual proxy: create RealDatabase only on first use
├── PasswordProtectProxy.hpp      # protection proxy: check password before delegating
└── Employee.hpp ← RealEmployee.hpp
data.data                         # employee records
```

**Concept:** a proxy has the same interface as the real object and controls access to it. Here, two proxies are stacked: lazy initialisation (avoid loading the file until needed) and password protection (deny access without the right credential).

### logframework — Composite + Strategy

📐 **Diagrams:** [`logframework/diagrams.md`](logframework/diagrams.md) — class + sequence diagrams

```
logframework/include/
├── Logger.hpp ← Log.hpp          # loggers form a parent/child tree (GetLog(name), child list)
├── Level.hpp                     # TRACE(0) < INFO(1) < DEBUG(2) < WARN(3) < ERROR(4), threshold check
├── Layout.hpp ← StandardLayout   # Strategy: how a message is formatted
└── Exporter.hpp ← ConsoleExporter / FileExporter / CompositeExporter   # Composite
```

**Concept:** an `Exporter` decides where a message goes. `CompositeExporter` contains a list of exporters and is also an `Exporter`, so the logger can send to console + file without knowing it is sending to many. Formatting is a pluggable `Layout`. Loggers are linked into a parent/child tree (`root` → `app.game` → `app.game.ai`), each with its own level, layout and exporter.

### RPGGame — State + Observer + Chain of Responsibility + Strategy

📐 **Diagrams:** [`RPGGame/diagrams.md`](RPGGame/diagrams.md) — class + sequence diagrams

Turn-based battle between two troops. All 10 official testcases in `RPGGame/testcases/` reproduce their expected output exactly. Design decisions and implementation notes: [`RPGGame/CLAUDE.md`](RPGGame/CLAUDE.md); every unit test with its pass criteria: [`RPGGame/test/TESTS.md`](RPGGame/test/TESTS.md).

```
RPGGame/include/
├── Game/            RPG, Battle, Troop
├── Role/            Role ← Slime, IAction ← AIAction / HeroAction   # Strategy for decisions
├── Skill/           Skill ← BasicAttack, Waterball, Fireball, SelfHealing, Petrochemical, Poison,
│                            Summon, SelfExplosion, Cheerup, Curse, OnePunch
├── State/           State ← NormalState, PoisonedState, PetrochemicaledState, CheerupedState
├── Observer/        SkillObserver ← SummonObserver, CurserObserver
└── OnePunchHandler/ OnePunchHandler ← HpHandler, PoisonPetrochemicalHandler, CheerupHandler, NormalHandler

RPGGame/test/libary/RPG_parser   client side: parses the input format and maps skill names to Skill objects
RPGGame/main.cpp                 client: wires parser, HeroAction and RPG together
```

**Concept:** combines several patterns in one game:
- **State** – a role’s status (poisoned, petrified, cheered up) changes what it can do each turn and lasts a set number of rounds. The base `State::decision()` holds the default turn flow (Template Method); petrified skips it, poisoned loses 30 HP first.
- **Observer** – `Summon` and `Curse` register observers on a role; when that role dies, the observers reward the summoner (+30 HP) or each curser (+ remaining MP).
- **Chain of Responsibility** – `OnePunch` has different effects depending on the target (high HP, poisoned/petrified, cheered up, normal); each case is a handler.
- **Strategy** – who decides (`IAction`: `HeroAction` reads input, `AIAction` follows the seed rule), and each skill is its own class with a common `Skill` interface.

**Run** (from `RPGGame/` after building):

```bash
./build/bin/RPGGAME testcases/poison.in          # replay a testcase (output matches testcases/poison.out)
./build/bin/RPGGAME --play testcases/poison.in   # play: troops from the file, hero decisions from the keyboard
./build/bin/RPGGAME < testcases/poison.in        # read everything from standard input
```

---

## Diagrams

Every project folder has a `diagrams.md` with Mermaid diagrams (GitHub and VS Code with a Mermaid extension render them directly):

- **Class diagram** – classes, key fields/methods and relationships (inheritance, composition, association).
- **Sequence diagram** – the main runtime flow, showing how the pattern’s participants call each other.
- **State diagram** – where the State pattern is used (`treasuremap`).

`OOA_Training/diagrams.md` is an index of the 15 exercises plus a UML relationship cheat sheet.

### Adding a new project folder

1. Create the folder with the usual layout (`CMakeLists.txt`, `main.cpp`, `include/`, `src/`, `test/`).
2. Copy [`DIAGRAM_TEMPLATE.md`](DIAGRAM_TEMPLATE.md) to `<NewProject>/diagrams.md` and replace the example diagrams.
3. Add the project to the [Pattern index](#pattern-index) and add a section under [Projects](#projects) with the folder tree, the concept, and the diagrams link.

> Do not name the folder `UML/` — it is listed in `.gitignore`.

---

## Pattern concepts

**Strategy** — Define a family of algorithms behind one interface and make them interchangeable. The context holds a pointer to the interface and does not care which algorithm it gets. *Use when* the same task can be done in several ways and you want to switch without `if/else`.

**Template Method** — A base class defines the fixed steps of an algorithm and leaves some steps as abstract hooks. Subclasses fill in the hooks but cannot change the order. *Use when* several classes share the same flow but differ in a few steps.

**Chain of Responsibility** — Requests pass along a linked list of handlers; each handler either handles the request or forwards it to `next`. *Use when* you have many conditional cases and want to add new cases by adding classes, not editing a central `switch`.

**Observer** — A subject keeps a list of observers and notifies them when its state changes. *Use when* one change should trigger reactions in an open-ended set of other objects without tight coupling.

**Command** — Turn a request into an object with `execute()` and `undo()`. The invoker stores commands, so you get key binding, queuing, macros and undo/redo for free.

**State** — An object delegates its behaviour to a state object, and replaces that state object when it transitions. *Use when* behaviour depends heavily on a mode and the mode changes at runtime; it removes large `switch (state)` blocks.

**Facade** — Provide one simple interface over a complex subsystem. Clients call the facade; the subsystem classes still exist and can be used directly when needed.

**Adapter** — Wrap an existing class (adaptee) so it fits the interface the client expects (target). *Use when* you want to reuse a library whose interface does not match yours.

**Proxy** — A stand-in object with the same interface as the real one, used to control access: lazy loading (virtual proxy), permission checks (protection proxy), remote access, caching.

**Composite** — Treat a group of objects the same way as a single object by making the container implement the same interface as its items (e.g. `CompositeExporter`, `Directory`, macro commands).

**Decorator** — Wrap an object with another object of the same interface to add behaviour without modifying it (e.g. `Reverse` around a matching strategy).

### Design principles behind the patterns

- **Open/Closed** – extend behaviour by adding classes (new handler, new strategy, new state) instead of modifying existing code.
- **Program to an interface** – clients depend on abstract bases (`MatchType`, `Exporter`, `Command`), not concrete classes.
- **Composition over inheritance** – most patterns here hold a pointer to a collaborator rather than subclassing for every variation.
- **Single Responsibility** – each handler / state / command does one thing.

---

## Reference

- E. Gamma, R. Helm, R. Johnson, J. Vlissides — *Design Patterns: Elements of Reusable Object-Oriented Software*
- [Refactoring.Guru — Design Patterns](https://refactoring.guru/design-patterns)
- Exercises are based on the Waterball Software Design course (水球軟體學院).
