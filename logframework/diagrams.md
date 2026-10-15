# logframework — Diagrams

> **Patterns:** Composite (`CompositeExporter`) + Strategy (`Layout`, `Exporter`) + logger hierarchy (parent / child tree)

## Class Diagram

```mermaid
classDiagram
    class Logger {
        #string name
        #Level level
        #Layout layout
        #Exporter exporter
        #Log parent
        +trace(msg)
        +debug(msg)
        +info(msg)
        +warn(msg)
        +error(msg)
        +CheckThreshold(Level) bool
    }
    class Log {
        -vector~Logger~ child
        +Log(name, level, layout, exporter)
        +Log(parent, name, level, layout, exporter)
        +GetLog(name) Logger
    }
    class Level {
        <<enumeration>>
        TRACE = 0
        INFO = 1
        DEBUG = 2
        WARN = 3
        ERROR = 4
    }
    class Layout {
        <<abstract>>
        #Logger logger
        +format(msg)* string
    }
    class StandardLayout {
        +format(msg) string
        -GetCurrentTime() string
    }
    class Exporter {
        <<abstract component>>
        #Logger logger
        +output(msg)*
        +SetLogger(Logger)
    }
    class ConsoleExporter {
        <<leaf>>
        +output(msg)
    }
    class FileExporter {
        <<leaf>>
        -string filename
        -ofstream file
        +output(msg)
    }
    class CompositeExporter {
        <<composite>>
        -vector~Exporter~ exporters
        +output(msg)
        +SetLogger(Logger)
    }

    Logger <|-- Log
    Log "0..1" <-- "*" Log : parent / child
    Logger --> Level
    Logger --> Layout : format strategy
    Logger --> Exporter : output target
    Layout <|-- StandardLayout
    Exporter <|-- ConsoleExporter
    Exporter <|-- FileExporter
    Exporter <|-- CompositeExporter
    CompositeExporter o-- "*" Exporter : children
```

## Sequence Diagram — `gamelog->info("...")`

Setup in `main()`:
`root (DEBUG, Console)` → `app.game (INFO, Composite[Console, File game.log])` → `app.game.ai (TRACE, Composite[Console, File ai.log])`

```mermaid
sequenceDiagram
    autonumber
    participant C as Client
    participant L as Log "app.game"
    participant Ly as StandardLayout
    participant CE as CompositeExporter
    participant Con as ConsoleExporter
    participant Fi as FileExporter (game.log)

    C->>L: info("game info message")
    L->>L: CheckThreshold(INFO) — INFO >= logger level?
    alt below threshold
        L-->>C: dropped
    else passes
        L->>Ly: format(msg)
        Ly->>L: GetLevel(), GetName()
        Ly-->>L: "time |-INFO app.game - msg"
        L->>CE: output(formatted)
        CE->>Con: output(formatted)
        CE->>Fi: output(formatted)
    end
```

> `Logger` does not know it is writing to two places: `CompositeExporter` looks like any single `Exporter`.
