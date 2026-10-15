# BigTwo — Diagrams

> **Patterns:** Chain of Responsibility (`CardPatternHandler`) + Template Method / hook (`Round` → `FirstRound`) + Strategy (`Player::action`)

## Class Diagram

```mermaid
classDiagram
    class Bigtwo {
        -vector~Player~ players
        -vector~Round~ rounds
        -Deck deck
        -CardPatternHandler handler
        +GameStart()
        +GameEnd()
        +isEnd() bool
        +doDeal()
        +FristPlayer() Player
        +FirstRound(Player) Round
        +newRound(Player) Round
        +vaildHandle(cards) bool
        +CampareHandle(cards, topplay) bool
        +PatternNameHandle(cards) string
    }
    class Round {
        -Bigtwo game
        -vector~Card~ TopPlay
        -Player TopPlayer
        -int pass
        +takeTurn(vector~Player~) Player
        +condition(cards)$ bool
        +newRound(Player, Bigtwo)$ Round
    }
    class FirstRound {
        +condition(cards)$ bool
        +newRound(Player, Bigtwo)$ FirstRound
    }
    class CardPatternHandler {
        <<abstract>>
        -CardPatternHandler next
        +vaild(cards) bool
        +isSamePatternHandle(p1, p2) bool
        +BiggerHandle(p1, p2) bool
        +PatternNameHandle(cards) string
        #match(cards)* bool
        #isBigger(p1, p2)* bool
        #GetPatternName()* string
    }
    class SingleHandler
    class PairHandler
    class StraightHandler {
        +GetMaxCard(cards) Card
    }
    class FullHouseHandler {
        +GetThreeMaxCard(cards) Card
    }
    class Player {
        <<abstract>>
        -string name
        -HandCard handcard
        +NameSelf()*
        +action()* vector~int~
        +Play() vector~Card~
        +Deal(Deck)
        +RemoveCardFromHand(cards)
        +isHandCardEmpty() bool
    }
    class HumanPlayer {
        +NameSelf()
        +action() vector~int~
    }
    class AIPlayer {
        +NameSelf()
        +action() vector~int~
    }
    class HandCard {
        -vector~Card~ handcard
        +AddCard(Card)
    }
    class Deck {
        -vector~Card~ cards
        +DrawCard() Card
        +Suffle()
    }
    class Card {
        -Rank rank
        -Suit suit
        +isBigger(Card) bool
        +GenCardFromChar(rank, suit)$ Card
    }

    Bigtwo o-- "4" Player
    Bigtwo *-- "*" Round
    Bigtwo --> Deck
    Bigtwo --> CardPatternHandler : chain head
    Round --> Bigtwo
    Round <|-- FirstRound
    CardPatternHandler --> CardPatternHandler : next
    CardPatternHandler <|-- SingleHandler
    CardPatternHandler <|-- PairHandler
    CardPatternHandler <|-- StraightHandler
    CardPatternHandler <|-- FullHouseHandler
    Player <|-- HumanPlayer
    Player <|-- AIPlayer
    Player *-- HandCard
    HandCard o-- "*" Card
    Deck o-- "52" Card
```

## Sequence Diagram — game flow

```mermaid
sequenceDiagram
    autonumber
    participant G as Bigtwo
    participant P as Player
    participant FR as FirstRound
    participant R as Round

    G->>P: NameSelf() (each player)
    G->>G: doDeal()
    G->>G: FristPlayer() (holder of club 3)
    G->>FR: FirstRound(topPlayer)
    FR->>FR: takeTurn(players) — first play must contain club 3
    FR-->>G: topPlayer
    loop until isEnd()
        G->>R: newRound(topPlayer)
        R->>R: takeTurn(players)
        R-->>G: topPlayer (last one not passed)
    end
    G->>G: GameEnd()
```

## Sequence Diagram — validating and comparing a play (CoR)

Chain built in `main()`: `Single → Pair → FullHouse → Straight`

```mermaid
sequenceDiagram
    autonumber
    participant R as Round
    participant P as Player
    participant G as Bigtwo
    participant S as SingleHandler
    participant Pa as PairHandler
    participant FH as FullHouseHandler
    participant St as StraightHandler

    R->>P: Play()
    P->>P: action() (Human: stdin / AI: auto)
    P-->>R: cards
    alt cards empty
        R->>R: pass-- , next player
    else
        R->>G: CampareHandle(cards, TopPlay)
        G->>S: vaild(cards)
        S->>Pa: vaild(cards) if not single
        Pa->>FH: vaild(cards) if not pair
        FH->>St: vaild(cards) if not full house
        G->>S: isSamePatternHandle(cards, TopPlay)
        G->>S: BiggerHandle(cards, TopPlay)
        S-->>G: forwarded along chain until a handler matches
        G-->>R: true / false
        opt legal and bigger
            R->>P: RemoveCardFromHand(cards)
            R->>R: TopPlay = cards, TopPlayer = P, pass = 3
        end
    end
```
