# prescriber_system — Diagrams

> **Patterns:** Facade (`PrescriberFacade`) + Strategy (`SaveDiagnositic`)

## Class Diagram

```mermaid
classDiagram
    class PrescriberFacade {
        <<facade>>
        -Database database
        -Prescriber prescriber
        +PrescriberFacade(Database, Prescriber, rulepath, json)
        +diagnosis(id, symptoms, int saveOpt, outputpath)
    }
    class SaveOpts {
        <<enumeration>>
        SAVE_AS_JSON = 0b0010
        SAVE_AS_CSV = 0b0100
    }
    class Database {
        -map~string, Patient~ data
        +parser(string json)
        +AddPatient(Patient)
        +AddCaseById(id, Case)
        +GetPatientByid(id) Patient
    }
    class Prescriber {
        -vector~DiagnosticRules~ rules
        -Database database
        -SaveDiagnositic strategy
        +parser(string file)
        +AddRule(DiagnosticRules)
        +diagnosis(id, symptom)
        +dodiagnosis(symptom, Patient) Prescription
        +save(path, Patient)
        +SetStrategy(SaveDiagnositic)
    }
    class DiagnosticRules {
        -string disease
        -Prescription prescription
        +GenRule(name)$ DiagnosticRules
        +defaultrules()$ vector~DiagnosticRules~
    }
    class Patient {
        -string id
        -string name
        -string gender
        -int age
        -float height
        -float weight
        -vector~Case~ cases
        +AddCase(Case)
    }
    class Case {
        -string symtoms
        -Prescription prescription
        -float time
    }
    class Prescription {
        -string name
        -string potential
        -string medicines
        -string usage
    }
    class SaveDiagnositic {
        <<interface>>
        +save(path, Patient)*
    }
    class SaveJson {
        +save(path, Patient)
    }
    class SaveCsv {
        +save(path, Patient)
    }

    PrescriberFacade --> Database
    PrescriberFacade --> Prescriber
    PrescriberFacade ..> SaveOpts
    PrescriberFacade ..> SaveJson : creates
    PrescriberFacade ..> SaveCsv : creates
    Prescriber --> Database
    Prescriber o-- "*" DiagnosticRules
    Prescriber --> SaveDiagnositic : strategy
    SaveDiagnositic <|.. SaveJson
    SaveDiagnositic <|.. SaveCsv
    DiagnosticRules --> Prescription
    Database "1" o-- "*" Patient
    Patient "1" *-- "*" Case
    Case --> Prescription
```

## Sequence Diagram — one diagnosis through the facade

```mermaid
sequenceDiagram
    autonumber
    participant C as Client
    participant F as PrescriberFacade
    participant DB as Database
    participant P as Prescriber
    participant Pt as Patient
    participant S as SaveJson / SaveCsv

    C->>F: new PrescriberFacade(db, prescriber, rulepath, json)
    F->>DB: parser(json)
    F->>P: parser(rulepath)

    C->>F: diagnosis(id, symptoms, saveOpt, outputpath)
    F->>P: diagnosis(id, symptoms)
    P->>DB: GetPatientByid(id)
    DB-->>P: patient
    P->>P: dodiagnosis(symptoms, patient) — match rules
    P->>Pt: AddCase(new Case(symptoms, prescription, time))
    opt saveOpt has SAVE_AS_CSV
        F->>P: SetStrategy(new SaveCsv())
        F->>P: save(outputpath, patient)
        P->>S: save(path, patient)
    end
    opt saveOpt has SAVE_AS_JSON
        F->>P: SetStrategy(new SaveJson())
        F->>P: save(outputpath, patient)
        P->>S: save(path, patient)
    end
```

> The client only talks to `PrescriberFacade`. Loading data, matching rules, recording the case and choosing an output format are hidden behind one call.

> ⚠️ **Code note:** `PrescriberFacade::diagnosis()` currently checks `saveOpt && SAVE_AS_CSV` (logical AND), which is true for any non-zero `saveOpt`, so both CSV and JSON are always saved. Bitwise `saveOpt & SAVE_AS_CSV` matches the diagram's intent.
