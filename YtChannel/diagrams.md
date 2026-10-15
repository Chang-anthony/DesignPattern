# YtChannel — Diagrams

> **Pattern:** Observer (`Channel` = subject, `ChannelSubscriber` = observer)

## Class Diagram

```mermaid
classDiagram
    direction LR
    class Channel {
        <<subject>>
        -string name
        -vector~Video~ videos
        -vector~ChannelSubscriber~ subscribers
        -thread moniterThread
        -mutex mutex
        +upload(Video)
        +notifiy()
        +AddSubscriber(ChannelSubscriber)
        +RemoveSubscriber(ChannelSubscriber)
        +startmoniter()
    }
    class Video {
        -string title
        -string description
        -int length
    }
    class ChannelSubscriber {
        <<abstract observer>>
        -string name
        -vector~Channel~ channels
        +subscribe(Channel)
        +unsubsribe(Channel)
        +received(Channel)*
    }
    class Waterball {
        +received(Channel)
    }
    class Fireball {
        +received(Channel)
    }

    Channel "1" *-- "*" Video
    Channel "*" o-- "*" ChannelSubscriber : subscribers
    ChannelSubscriber <|-- Waterball
    ChannelSubscriber <|-- Fireball
```

## Sequence Diagram — subscribe, upload, notify

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant WB as Waterball
    participant FB as Fireball
    participant Ch as Channel (水球軟體學院)

    Main->>WB: subscribe(channel)
    WB->>Ch: AddSubscriber(this)
    Main->>FB: subscribe(channel)
    FB->>Ch: AddSubscriber(this)

    Main->>Ch: upload(Video "C1M1S3", 60s)
    Ch->>Ch: videos.push_back(video)
    Ch->>Ch: notifiy()
    Ch->>WB: received(channel)
    WB->>Ch: getVideos().back()
    opt length >= 180
        WB-->>WB: like the video
    end
    Ch->>FB: received(channel)
    FB->>Ch: getVideos().back()
    opt length <= 60
        FB->>FB: unsubsribe(channel)
        FB->>Ch: RemoveSubscriber(this)
    end
```

> The channel only knows the abstract `ChannelSubscriber::received()`. Each subscriber decides its own reaction.
