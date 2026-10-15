# treasuremap — Diagrams

> **Patterns:** State (`State`) + Strategy (`AttackType`) + Chain of Responsibility (`TouchedHandler`)

## Class Diagram

```mermaid
classDiagram
    class Adventure {
        -vector~vector~Mapobject~~ objs
        -Charator charactor
        -TouchedHandler handler
        +GameStart()$
        +newGame()$ Adventure
        +startRound() Round
        +touched(Mapobject, Mapobject)
        +refersh(Mapobject, Coord)
        +remove(Mapobject)
        +isEnd() bool
        +GameEnd()
    }
    class Round {
        -Adventure game
        +run()
        +gen()
        +render()
        +operation()
    }
    class TouchedHandler {
        <<abstract>>
        -TouchedHandler next
        #Adventure game
        +handle(Mapobject, Mapobject)
        #match(Mapobject, Mapobject)* bool
        #dohandle(Mapobject, Mapobject)*
    }
    class RoleObstacleTouched {
        +Do(Role, Obstacle)
    }
    class RoleTreasureTouched {
        +Do(Role, Treasure)
    }

    class Mapobject {
        <<abstract>>
        #string symbol
        #Coord pos
        #Adventure game
        +move(int x, int y)*
        +IsNearBy(Mapobject) bool
    }
    class Obstacle
    class Treasure {
        -Content content
        +open(Role)
    }
    class Coord {
        -int x
        -int y
        +distance(Coord) double
    }
    class Content {
        <<enumeration>>
        SuperStar
        Posion
        Accelerating
        Heal
        Devil
        KingRock
        DokoDemoDoor
    }

    class Role {
        <<abstract>>
        #int Hp
        #State state
        #AttackType attackType
        +action()
        +attack()
        +injured(int)
        +EnterState(State)
        +move(int x, int y)
        +Do()*
        +gainHp(int)*
        +fullHp()* bool
    }
    class Charator {
        +Do()
    }
    class Monster {
        +Do()
    }

    class State {
        <<abstract>>
        #int round
        #Role role
        +enterState()*
        +exitState(State)*
        +action()*
        +attacked(int)*
        +StateName()* string
    }
    class NormalState
    class Invincible
    class Poisoned
    class Accelerated
    class Healing
    class Orderless
    class Stockpile
    class Erupting
    class Teleport

    class AttackType {
        <<abstract>>
        #int damage
        #Role charator
        +attack()*
    }
    class NormalAttack
    class FullAttack
    class MonsterAttack

    Adventure "1" *-- "*" Mapobject
    Adventure --> Charator
    Adventure ..> Round : creates
    Adventure --> TouchedHandler : chain head
    TouchedHandler --> TouchedHandler : next
    TouchedHandler <|-- RoleObstacleTouched
    TouchedHandler <|-- RoleTreasureTouched

    Mapobject <|-- Obstacle
    Mapobject <|-- Treasure
    Mapobject <|-- Role
    Mapobject *-- Coord
    Treasure --> Content
    Role <|-- Charator
    Role <|-- Monster

    Role "1" --> "1" State : current state
    State --> Role
    State <|-- NormalState
    State <|-- Invincible
    State <|-- Poisoned
    State <|-- Accelerated
    State <|-- Healing
    State <|-- Orderless
    State <|-- Stockpile
    State <|-- Erupting
    State <|-- Teleport

    Role "1" --> "1" AttackType : strategy
    AttackType <|-- NormalAttack
    AttackType <|-- FullAttack
    AttackType <|-- MonsterAttack
```

## State Diagram — role states

```mermaid
stateDiagram-v2
    direction LR
    [*] --> NormalState
    NormalState --> Invincible : hit
    NormalState --> Treasure : open treasure

    state Treasure {
        direction LR
        Poisoned
        Accelerated
        Healing
        Orderless
        Teleport
        Stockpile --> Erupting : 2 rounds
        Erupting --> Teleport : 3 rounds
    }

    Treasure --> NormalState : time up
    Treasure --> Invincible : hit
    Invincible --> NormalState : 2 rounds
```

Opening a treasure calls `Role::EnterState()` from **any** state. Details per state:

| State | From treasure | Each round | Ends after | When attacked |
|---|---|---|---|---|
| NormalState | — | `Do()` once | — | lose HP → Invincible |
| Invincible | SuperStar | `Do()` once | 2 rounds → Normal | takes no damage |
| Poisoned | Posion | −15 HP, `Do()` | 3 rounds → Normal | lose HP → Invincible |
| Accelerated | Accelerating | `Do()` twice | 3 rounds → Normal | lose HP → Normal |
| Healing | Heal | +30 HP, `Do()` | 5 rounds or full HP → Normal | lose HP → Invincible |
| Orderless | Devil | random move | 3 rounds → Normal | lose HP → Invincible |
| Stockpile | KingRock | `Do()` | 2 rounds → Erupting | lose HP → Normal |
| Erupting | (from Stockpile) | `Do()` with `FullAttack` | 3 rounds → Teleport | lose HP → Invincible |
| Teleport | DokoDemoDoor | `Do()`, then jump to random cell | 1 round → Normal | lose HP → Invincible |

## Sequence Diagram — one round

```mermaid
sequenceDiagram
    autonumber
    participant A as Adventure
    participant R as Round
    participant C as Charator
    participant S as State (current)
    participant H as TouchedHandler chain
    participant T as Treasure

    A->>A: GameStart() → newGame()
    loop until isEnd()
        A->>R: startRound()
        R->>R: gen(), render()
        R->>C: action()
        C->>S: action()
        S->>C: Do() (read input: move or attack)
        alt move into empty cell
            C->>A: refersh(this, newPos)
        else move into an object
            C->>A: touched(this, obj)
            A->>H: handle(role, obj)
            alt RoleTreasureTouched matches
                H->>T: open(role)
                T->>T: content2State(role, content)
                T->>C: EnterState(newState)
                H->>A: remove(treasure)
            else RoleObstacleTouched matches
                H-->>C: blocked
            end
        end
        S->>S: round++, maybe exitState(next)
        R->>R: each Monster.action() (same flow)
    end
    A->>A: GameEnd()
```

## Sequence Diagram — attack uses the strategy, damage goes through the state

```mermaid
sequenceDiagram
    participant C as Charator
    participant AT as AttackType (Normal / Full)
    participant M as Monster
    participant MS as Monster.State

    C->>AT: attack()
    AT->>M: injured(damage)
    M->>MS: attacked(damage)
    alt Invincible
        MS->>M: lossHp(0)
    else other states
        MS->>M: lossHp(damage)
        MS->>M: EnterState(Invincible / NormalState)
    end
```
