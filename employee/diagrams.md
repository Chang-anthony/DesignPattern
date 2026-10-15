# employee — Diagrams

> **Pattern:** Proxy (virtual proxy + protection proxy)

| Role | Class |
|---|---|
| Subject | `Database` |
| Real subject | `RealDatabase` |
| Virtual proxy | `LazyInitDatabaseProxy` |
| Protection proxy | `PasswordProtectProxy` |

## Class Diagram

```mermaid
classDiagram
    class Database {
        <<abstract subject>>
        #string fileName
        +getEmployeeById(int id)* Employee
        +getSubordinatesById(int id)* vector~Employee~
    }
    class RealDatabase {
        <<real subject>>
        -vector~string~ lines
        +RealDatabase(fileName) reads whole file
        +getEmployeeById(int id) Employee
        +getSubordinatesById(int id) vector~Employee~
        -readDataByid(int id) Employee
    }
    class LazyInitDatabaseProxy {
        <<virtual proxy>>
        -RealDatabase realDatabase
        +getEmployeeById(int id) Employee
        +getSubordinatesById(int id) vector~Employee~
    }
    class PasswordProtectProxy {
        <<protection proxy>>
        +getEmployeeById(int id) Employee
        +getSubordinatesById(int id) vector~Employee~
        -authenticate() bool
    }
    class Employee {
        -int id
        -string name
        -int age
        -vector~Employee~ subordinates
    }
    class RealEmployee

    Database <|-- RealDatabase
    Database <|-- LazyInitDatabaseProxy
    LazyInitDatabaseProxy <|-- PasswordProtectProxy
    LazyInitDatabaseProxy --> RealDatabase : created on first use
    Database ..> Employee : returns
    Employee <|-- RealEmployee
    Employee o-- "*" Employee : subordinates
```

## Sequence Diagram — protected, lazily-loaded lookup

```mermaid
sequenceDiagram
    autonumber
    participant C as main
    participant PP as PasswordProtectProxy
    participant LP as LazyInitDatabaseProxy (base part)
    participant RD as RealDatabase
    participant F as data.data

    C->>PP: getEmployeeById(id)
    PP->>PP: authenticate() — env PASSWORD == expected?
    alt wrong / missing password
        PP-->>C: nullptr
    else authenticated
        PP->>LP: LazyInitDatabaseProxy::getEmployeeById(id)
        opt realDatabase == nullptr (first call)
            LP->>RD: new RealDatabase(fileName)
            RD->>F: read all lines
        end
        LP->>RD: getEmployeeById(id)
        RD->>RD: parse lines[id] + subordinates
        RD-->>LP: Employee
        LP-->>PP: Employee
        PP-->>C: Employee
    end
```

> `main.cpp` demo: query id 4 without `PASSWORD` (→ nullptr), set `PASSWORD=1qaz2wsx` and query id 4 again (prints the subordinate tree), then `getSubordinatesById(5)`.

> Both proxies keep the `Database` interface, so the client cannot tell whether it talks to the real database or a proxy.
