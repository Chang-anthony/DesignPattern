# KeyBoardShortCut — Diagrams

> **Pattern:** Command (with undo / redo and macro commands)

| Role | Class |
|---|---|
| Client | `Client` |
| Invoker | `MainController` |
| Command | `Command` + concrete commands |
| Receiver | `Tank`, `Telecom`, `MainController` (for `ResetCommand`) |

## Class Diagram

```mermaid
classDiagram
    class Client {
        -MainController contorl
        -Tank tank
        -Telecom telecom
        +control()
        +control(char key)
        +genCommand(int) Command
        +renderChooseList()
    }
    class MainController {
        <<invoker>>
        -vector~Command~ command [26 keys]
        -stack~Command~ done
        -stack~Command~ s2
        +setCommand(char key, Command)
        +opeator(char key)
        +undo()
        +redo()
        +resetCommand()
        +undoresetCommand()
    }
    class Command {
        <<interface>>
        +execute()*
        +undo()*
    }
    class TankMoveForwardCommand {
        -Tank tank
        +execute()
        +undo()
    }
    class TankMoveBackwardCommand {
        -Tank tank
        +execute()
        +undo()
    }
    class TelecomConnectCommand {
        -Telecom telecom
        +execute()
        +undo()
    }
    class TelecomdisConnectCommand {
        -Telecom telecom
        +execute()
        +undo()
    }
    class ResetCommand {
        -MainController controller
        +execute()
        +undo()
    }
    class MarcoCommand {
        <<composite>>
        -vector~Command~ marco
        +execute()
        +undo()
    }
    class Tank {
        <<receiver>>
        +moveForward()
        +moveBackward()
    }
    class Telecom {
        <<receiver>>
        +connect()
        +disconnect()
    }

    Client --> MainController
    Client ..> Command : creates
    MainController o-- "0..26" Command
    Command <|.. TankMoveForwardCommand
    Command <|.. TankMoveBackwardCommand
    Command <|.. TelecomConnectCommand
    Command <|.. TelecomdisConnectCommand
    Command <|.. ResetCommand
    Command <|.. MarcoCommand
    MarcoCommand o-- "*" Command
    TankMoveForwardCommand --> Tank
    TankMoveBackwardCommand --> Tank
    TelecomConnectCommand --> Telecom
    TelecomdisConnectCommand --> Telecom
    ResetCommand --> MainController
```

## Sequence Diagram — press a key, undo, redo

```mermaid
sequenceDiagram
    autonumber
    actor U as User
    participant C as Client
    participant MC as MainController
    participant Cmd as TankMoveForwardCommand
    participant T as Tank

    U->>C: bind key 'a' to "move forward"
    C->>C: genCommand(n)
    C->>MC: setCommand('a', cmd)

    U->>C: press 'a'
    C->>MC: opeator('a')
    MC->>Cmd: execute()
    Cmd->>T: moveForward()
    MC->>MC: done.push(cmd), clear redo stack s2

    U->>C: undo (2)
    C->>MC: undo()
    MC->>MC: cmd = done.pop()
    MC->>Cmd: undo()
    Cmd->>T: moveBackward()
    MC->>MC: s2.push(cmd)

    U->>C: redo (3)
    C->>MC: redo()
    MC->>MC: cmd = s2.pop()
    MC->>Cmd: execute()
    Cmd->>T: moveForward()
    MC->>MC: done.push(cmd)
```

## Sequence Diagram — macro command

```mermaid
sequenceDiagram
    autonumber
    participant MC as MainController
    participant M as MarcoCommand
    participant C1 as TankMoveForwardCommand
    participant C2 as TelecomConnectCommand

    MC->>M: execute()
    M->>C1: execute()
    M->>C2: execute()
    Note over MC,M: undo() runs every sub-command's undo()
```
