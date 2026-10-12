# RPGGame — Diagrams

> **Patterns:** State (`State`) + Observer (`SkillObserver`) + Chain of Responsibility (`OnePunchHandler`) + Strategy (`Skill`, `IAction`)
>
> *Work in progress* — `Battle::startBattle()`, `RPG::makeAction()`, the state `decision()` methods and the observers' `UntilDie()` reactions are still stubs. Diagrams show the implemented parts plus the intended structure.

## Class Diagram

```mermaid
classDiagram
    class RPG {
        -Battle battle
        +GameStart(Troop, Troop)
        +GameEnd()
        +makeAction(Role)
    }
    class Battle {
        -Troop ally
        -Troop enemy
        +startBattle()
    }
    class Troop {
        -vector~Role~ roles
        +addRole(Role)
        +removeRole(Role)
        +Annihilated() bool
        +StartBattle(Troop) Battle
    }

    class Role {
        -int hp
        -int mp
        -int str
        -string name
        -State state
        -vector~Skill~ skills
        -vector~SkillObserver~ observers
        -Troop troop
        +isDead() bool
        +damage(int)
        +setState(State)
        +addSkill(Skill)
        +addObserver(SkillObserver)
        +removeObserver(SkillObserver)
        +notifyObservers()
    }
    class Hero
    class AI {
        -int seed
    }
    class NonHero
    class Slime
    class IAction {
        <<interface>>
        +action()*
    }
    class AIAction {
        +action()
    }

    class Skill {
        <<abstract>>
        -string name
        -int mp
        -int targetEnemy
        -int targetFriend
        +attack(Role actor, vector~Role~ targets)*
    }
    class BasicAttack
    class Waterball
    class Fireball
    class SelfHealing
    class Petrochemical
    class Poison
    class Summon
    class SelfExplosion
    class Cheerup
    class Curse
    class OnePunch {
        -OnePunchHandler handler
    }

    class State {
        <<abstract>>
        -int round
        -Role role
        -string name
        +entryState(State)
        +exitState()
        +decision()*
    }
    class NormalState
    class PoisonedState
    class PetrochemicaledState
    class CheerupedState

    class SkillObserver {
        <<abstract>>
        -Role actor
        +UntilDie()*
    }
    class SummonObserver
    class CurserObserver

    class OnePunchHandler {
        <<abstract>>
        -OnePunchHandler next
        +handle(Role target)
        #match(Role)* bool
        #doHandle(Role)*
    }
    class HpHandler
    class PoisonPetrochemicalHandler
    class CheerupHandler
    class NormalHandler

    RPG --> Battle
    Battle --> "2" Troop
    Troop "1" o-- "*" Role
    Role --> Troop

    Role <|-- Hero
    Role <|-- AI
    Role <|-- NonHero
    NonHero <|-- Slime
    IAction <|.. AIAction
    AI ..> IAction

    Role "1" o-- "*" Skill
    Skill <|-- BasicAttack
    Skill <|-- Waterball
    Skill <|-- Fireball
    Skill <|-- SelfHealing
    Skill <|-- Petrochemical
    Skill <|-- Poison
    Skill <|-- Summon
    Skill <|-- SelfExplosion
    Skill <|-- Cheerup
    Skill <|-- Curse
    Skill <|-- OnePunch

    Role "1" --> "1" State
    State --> Role
    State <|-- NormalState
    State <|-- PoisonedState
    State <|-- PetrochemicaledState
    State <|-- CheerupedState

    Role "1" o-- "*" SkillObserver
    SkillObserver --> Role : actor
    SkillObserver <|-- SummonObserver
    SkillObserver <|-- CurserObserver

    OnePunch --> OnePunchHandler : chain head
    OnePunchHandler --> OnePunchHandler : next
    OnePunchHandler <|-- HpHandler
    OnePunchHandler <|-- PoisonPetrochemicalHandler
    OnePunchHandler <|-- CheerupHandler
    OnePunchHandler <|-- NormalHandler
```

## Sequence Diagram — OnePunch (Chain of Responsibility)

Chain built in `OnePunch()`: `HpHandler → PoisonPetrochemicalHandler → CheerupHandler → NormalHandler`

```mermaid
sequenceDiagram
    autonumber
    participant A as Actor
    participant OP as OnePunch
    participant H1 as HpHandler
    participant H2 as PoisonPetrochemicalHandler
    participant H3 as CheerupHandler
    participant H4 as NormalHandler
    participant T as Target

    A->>OP: attack(actor, targets)
    OP->>H1: handle(target)
    alt target HP >= 500
        H1->>T: damage(300)
    else
        H1->>H2: handle(target)
        alt Poisoned or Petrochemicaled
            H2->>T: damage(80) x3
        else
            H2->>H3: handle(target)
            alt Cheeruped
                H3->>T: damage(100)
                H3->>T: setState(new NormalState)
            else
                H3->>H4: handle(target)
                opt NormalState
                    H4->>T: damage(100)
                end
            end
        end
    end
```

## Sequence Diagram — Curse and Summon (Observer)

```mermaid
sequenceDiagram
    autonumber
    participant A as Actor
    participant Cu as Curse
    participant T as Target
    participant Su as Summon
    participant Tr as Actor's Troop
    participant S as Slime

    A->>Cu: attack(actor, targets)
    Cu->>T: getObservers()
    alt actor has not cursed this target yet
        Cu->>T: addObserver(new CurserObserver(actor))
    end

    A->>Su: attack(actor, targets)
    Su->>S: new Slime(100, 0, 50)
    Su->>S: addObserver(new SummonObserver(actor))
    Su->>Tr: addRole(slime)

    Note over T,S: when the observed role dies (planned)
    T->>T: notifyObservers()
    T-->>A: observer.UntilDie() — reward the actor
```

## Sequence Diagram — applying a state

```mermaid
sequenceDiagram
    participant A as Actor
    participant P as Poison
    participant T as Target
    participant Old as old State
    participant New as PoisonedState

    A->>P: attack(actor, targets)
    P->>T: setState(new PoisonedState)
    T->>Old: exitState()
    T->>T: delete old state
    T->>New: entryState(newState)
```
