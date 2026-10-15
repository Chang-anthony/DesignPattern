# Mat3D — Diagrams

> **Patterns:** Chain of Responsibility (`Handle`) + Template Method (`PrintPlaneTemplate`)

## Class Diagram

```mermaid
classDiagram
    class Mat3D {
        -int m
        -int n
        -int r
        -char*** coord
        -Handle handler
        +printValueAndAddress(x, y, z)
        +writeNewValue(x, y, z, char)
        +PrintALL()
        +HandlePrintPlane(string flat, int plane, Mat3D)
    }
    class Handle {
        <<abstract>>
        -Handle next
        +HandlePrintPlane(string flat, int plane, Mat3D)
        +printHandle(int plane, Mat3D)*
        +match(string flat)* bool
    }
    class PrintPlaneTemplate {
        <<abstract>>
        +printHandle(int plane, Mat3D)
        #GetValue(i, j, plane, Mat3D)* char
        #GetNum1(Mat3D)* int
        #GetNum2(Mat3D)* int
        #IsBounder(plane, Mat3D)* bool
    }
    class MNHandle {
        +match(flat) bool
        +GetValue() char
        +GetNum1() int
        +GetNum2() int
        +IsBounder() bool
    }
    class MRHandle {
        +match(flat) bool
        +GetValue() char
        +GetNum1() int
        +GetNum2() int
        +IsBounder() bool
    }
    class NRHandle {
        +match(flat) bool
        +GetValue() char
        +GetNum1() int
        +GetNum2() int
        +IsBounder() bool
    }

    Mat3D --> Handle : handler
    Handle --> Handle : next
    Handle <|-- PrintPlaneTemplate
    PrintPlaneTemplate <|-- MNHandle
    PrintPlaneTemplate <|-- MRHandle
    PrintPlaneTemplate <|-- NRHandle
```

## Sequence Diagram — print the "MN" plane

Chain built in `main()`: `MRHandle → MNHandle → NRHandle`

```mermaid
sequenceDiagram
    autonumber
    participant Main as main()
    participant M as Mat3D
    participant MR as MRHandle
    participant MN as MNHandle
    participant T as PrintPlaneTemplate (inherited by MN)

    Main->>M: HandlePrintPlane("mn", z, mat)
    M->>MR: HandlePrintPlane("mn", z, mat)
    MR->>MR: match("mn") = false
    MR->>MN: HandlePrintPlane("mn", z, mat)
    MN->>MN: match("mn") = true
    MN->>T: printHandle(z, mat)
    T->>MN: IsBounder(z, mat)
    alt plane index in range
        T->>MN: GetNum1(mat), GetNum2(mat)
        loop i < num1, j < num2
            T->>MN: GetValue(i, j, z, mat)
        end
    else out of range
        T-->>Main: print error
    end
```

> **CoR** decides *which* plane handler runs. **Template Method** fixes *how* a plane is printed; subclasses only supply indexing (`GetNum1/GetNum2/GetValue`) and bounds checking.
