# Collision — Diagrams

> **Pattern:** Chain of Responsibility (`CollisionHandle`)

## Class Diagram

```mermaid
classDiagram
    direction LR
    class World {
        -Sprite sprites[30]
        -CollisionHandle CoR
        +AddSprite(Sprite)
        +Move(int x1, int x2)
        +Collision(Sprite, Sprite, Sprite[])
    }
    class Sprite {
        -int coord
        -char type
        +Remove()
        +RandGenSprite()$ Sprite
    }
    class Hero {
        -int hp
        +GainHp(int)
        +IsDead() bool
    }
    class Water
    class Fire

    class CollisionHandle {
        <<abstract>>
        -CollisionHandle next
        +handle(Sprite, Sprite, Sprite[])
        #match(Sprite, Sprite)* bool
        #dohandle(Sprite, Sprite, Sprite[])*
    }
    class HeroFireHandler {
        +match() bool
        +dohandle()
    }
    class HeroWaterHandler {
        +match() bool
        +dohandle()
    }
    class WaterFireHandler {
        +match() bool
        +dohandle()
    }
    class SameTypeHandler {
        +match() bool
        +dohandle()
    }

    World "1" o-- "0..30" Sprite
    World --> CollisionHandle : head of chain
    Sprite <|-- Hero
    Sprite <|-- Water
    Sprite <|-- Fire
    CollisionHandle <|-- HeroFireHandler
    CollisionHandle <|-- HeroWaterHandler
    CollisionHandle <|-- WaterFireHandler
    CollisionHandle <|-- SameTypeHandler
    CollisionHandle --> CollisionHandle : next
```

## Sequence Diagram — Hero moves onto Fire

Chain built in `main()`: `HeroFireHandler → HeroWaterHandler → WaterFireHandler → SameTypeHandler`

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant W as World
    participant HF as HeroFireHandler
    participant HW as HeroWaterHandler
    participant WF as WaterFireHandler
    participant ST as SameTypeHandler
    participant H as Hero

    Main->>W: Move(2, 3)
    W->>W: c1 = sprites[2], c2 = sprites[3]
    W->>HF: handle(c1, c2, sprites)
    alt HF.match(Hero, Fire)
        HF->>H: GainHp(-10)
        alt hero hp <= 0
            HF->>W: remove both sprites
        else
            HF->>W: move hero to c2's coord
        end
    else not matched
        HF->>HW: handle(c1, c2, sprites)
        HW->>WF: handle(...) if not matched
        WF->>ST: handle(...) if not matched
    end
```

> Adding a new collision rule = adding one new handler class and linking it into the chain. `World` never changes.
