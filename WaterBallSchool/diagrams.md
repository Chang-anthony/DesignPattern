# WaterBallSchool — Diagrams

> **Focus:** OOA domain model (aggregation hierarchy, association class, abstract scene)

## Class Diagram

```mermaid
classDiagram
    class Journey {
        -string name
        -string description
        -int price
        -vector~Chapter~ chapters
        -vector~Adventurer~ adventurers
        -vector~TourGroup~ tourgroups
        +Join(Student) Adventurer
        +FirstMission() Mission
        +MatchTourGroup(Adventurer) TourGroup
    }
    class Chapter {
        -int id
        -string name
        -vector~Mission~ missions
        +GetFirstMission() Mission
    }
    class Mission {
        -int id
        -string name
        -Challenge challenge
        -vector~Scene~ scenes
        +ExpAward() int
    }
    class Challenge {
        -int id
        -string name
    }
    class Scene {
        <<abstract>>
        -int id
        -int exp
        -string name
        +ExpAward()* int
    }
    class VideoScene {
        +ExpAward() int
    }
    class ContentScene {
        +ExpAward() int
    }
    class Student {
        -string account
        -string password
        -int level
        -int exp
        -LevelSheet levelsheet
        -vector~CheckMissionState~ missioncarryon
        -vector~Adventurer~ adventurers
        +CarryMission(Mission) CheckMissionState
        +GainExp(int)
        +LevelUp()
    }
    class Adventurer {
        -int id
        -Student student
        -Journey journey
        -TourGroup group
        +CarryOnMission(Mission)
    }
    class TourGroup {
        -int id
        -vector~Adventurer~ adventurers
        +Add(Adventurer)
    }
    class CheckMissionState {
        <<association class>>
        -state currentstate (inprogress / done)
        -Student student
        -Mission mission
        +CompleteMission()
    }
    class LevelSheet {
        +queryform(int exp) int
        +form(int exp)$ int
    }

    Journey "1" *-- "1..*" Chapter
    Chapter "1" *-- "1..*" Mission
    Mission "1" --> "0..1" Challenge
    Mission "1" *-- "1..*" Scene
    Scene <|-- VideoScene
    Scene <|-- ContentScene

    Journey "1" o-- "*" Adventurer
    Journey "1" o-- "*" TourGroup
    TourGroup "1" o-- "*" Adventurer
    Adventurer "*" --> "1" Student
    Student --> LevelSheet
    Student "1" -- "*" CheckMissionState
    CheckMissionState "*" -- "1" Mission
```

## Sequence Diagram — a student joins a journey and completes a mission

```mermaid
sequenceDiagram
    autonumber
    actor S as Student
    participant J as Journey
    participant Ad as Adventurer
    participant Ch as Chapter
    participant CMS as CheckMissionState
    participant TG as TourGroup
    participant M as Mission
    participant L as LevelSheet

    S->>J: Join(student)
    J->>Ad: new Adventurer(id, student, journey)
    J->>Ch: chapters[0].GetFirstMission()
    Ch-->>J: first mission
    J->>Ad: CarryOnMission(first)
    Ad->>S: CarryMission(first)
    S->>CMS: new CheckMissionState(student, mission)
    J->>J: MatchTourGroup(adventurer)
    J->>TG: Add(adventurer)
    J-->>S: adventurer

    S->>CMS: CompleteMission()
    CMS->>CMS: currentstate = done
    CMS->>M: ExpAward()
    M->>M: sum of scene.ExpAward()
    M-->>CMS: exp
    CMS->>S: GainExp(exp)
    S->>L: queryform(exp)
    L-->>S: new level
    loop level difference
        S->>S: LevelUp()
    end
```
