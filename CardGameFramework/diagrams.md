# CardGameFramework — Diagrams

> **Pattern:** Template Method (`CardGame::GameStart`)

## Class Diagram

```mermaid
classDiagram
    class CardGame {
        <<abstract>>
        -vector~Player~ players
        -Deck deck
        +GameStart()
        +GameEnd(Player)
        #Round()*
        #DrawCardEnd()* bool
        #IsGameEnd()* bool
        #GetWinner()* Player
    }
    class Deck {
        -vector~Card~ cards
        +DrawCard() Card
        +Suffle()
        +ReFresh(vector~Card~) Deck
    }
    class Card {
        <<abstract>>
        +render()*
    }
    class Hand {
        -vector~Card~ hand
        +AddCard(Card)
    }
    class Player {
        <<abstract>>
        -string name
        -Hand hand
        +AddCard(Card)
        +NameSelf()
        +takeTurn(vector~Card~)* Card
    }

    class Showdown {
        -int drawcardend
        -int round
        +Round()
        +DrawCardEnd() bool
        +IsGameEnd() bool
        +GetWinner() Player
        +Bigger(vector~Card~) Player
    }
    class ShowDownCard {
        -Rank rank
        -Suit suit
        +GenCards()$ vector~Card~
        +render()
        +IsBigger(ShowDownCard) bool
    }
    class ShowDownPlayer {
        <<abstract>>
        -int point
        +gainPoint()
    }
    class ShowDownHumanPlayer
    class ShowDownAIPlayer

    class Uno {
        -Card newCard
        -vector~Card~ passCards
        -bool gameEnd
        +Round()
        +DrawCardEnd() bool
        +IsGameEnd() bool
        +GetWinner() Player
        +IsVaild(Card) bool
    }
    class UnoCard {
        -Color color
        -Number number
        +GenCards()$ vector~Card~
        +render()
        +IsSame(UnoCard) bool
    }
    class UnoPlayer {
        <<abstract>>
    }
    class UnoHumanPlayer
    class UnoAIPlayer

    CardGame o-- "*" Player
    CardGame --> Deck
    Deck o-- "*" Card
    Player *-- Hand
    Hand o-- "*" Card

    CardGame <|-- Showdown
    CardGame <|-- Uno
    Card <|-- ShowDownCard
    Card <|-- UnoCard
    Player <|-- ShowDownPlayer
    Player <|-- UnoPlayer
    ShowDownPlayer <|-- ShowDownHumanPlayer
    ShowDownPlayer <|-- ShowDownAIPlayer
    UnoPlayer <|-- UnoHumanPlayer
    UnoPlayer <|-- UnoAIPlayer
```

## Sequence Diagram — the template method

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant G as CardGame (template)
    participant Sub as Showdown / Uno (hooks)
    participant P as Player
    participant D as Deck

    Main->>G: GameStart()
    loop each player
        G->>P: NameSelf()
    end
    G->>D: Suffle()
    loop while Sub.DrawCardEnd()
        G->>Sub: DrawCardEnd()
        loop each player
            G->>D: DrawCard()
            G->>P: AddCard(card)
        end
    end
    loop while Sub.IsGameEnd()
        G->>Sub: Round()
        Sub->>P: takeTurn(cards)
        P-->>Sub: Card
    end
    G->>Sub: GetWinner()
    Sub-->>G: winner
    G->>G: GameEnd(winner)
```

> The order of steps is fixed in `CardGame`. `Showdown` and `Uno` only fill in the hook methods (`Round`, `DrawCardEnd`, `IsGameEnd`, `GetWinner`).
