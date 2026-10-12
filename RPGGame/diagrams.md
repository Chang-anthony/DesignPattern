# RPGGame — Diagrams

> **Patterns:** Template Method + State（`State` 主導一次行動的流程）、Strategy（`IAction` 決策者、`Skill` 行動）、Observer（`SkillObserver` 死亡事件）、Chain of Responsibility（`OnePunchHandler`，由 Client 注入）
>
> **依據：** [`CLAUDE.md`](CLAUDE.md) §5 設計決策 D1–D39（2026-10-12 架構設計完成）。本圖畫的是**決定後的設計**，不是目前程式碼的現況；程式碼要到實作階段才會調整。
>
> **方法名稱為暫定**：討論決定的是「責任放在誰身上」，多數方法名稱是為了畫圖暫取的（例如 `takeTurn`、`getCandidates`、`chooseAction`），實作時可以改；沿用自現有程式碼或討論中出現過的名稱（`doAction`、`doDamage`、`lossHp`、`endThisRound`、`checkMp`、`handle`…）保留原名。

| Role | Class |
|---|---|
| 關聯類別（兩軍對戰） | `Battle`（D1） |
| Context（持有狀態與決策者） | `Role` |
| State（Template Method 骨架在抽象類別） | `State` ← `NormalState`、`PoisonedState`、`PetrochemicaledState`、`CheerupedState` |
| Strategy：決策者 | `IAction` ← `AIAction`、英雄的 `IAction`（暫稱 `HeroAction`） |
| Strategy：行動 | `Skill` ← `BasicAttack` + 10 種技能 |
| Observer | `SkillObserver` ← `SummonObserver`、`CurserObserver` |
| Chain of Responsibility | `OnePunchHandler` ← `HpHandler`、`PoisonPetrochemicalHandler`、`CheerupHandler`、`NormalHandler` |

### 與舊版（從程式碼反推的圖）相比的主要改變

| 改變 | 決策 |
|---|---|
| 移除 `Hero` / `AI` 這兩個 `Role` 子類別，改由 `Role` 持有 `IAction`；`seed` 移到 `AIAction` | D4 |
| 一次行動的流程由 `State` 主導，固定流程寫在 `State` 抽象類別 | D10、D12 |
| 傷害一律經過 `actor.state.doDamage()` → `target.state.damage()` → `target.lossHp()` | D16、D17 |
| 觀察者改為 pull model：`UntilDie(dead)` 帶入死者 | D18 |
| 候選名單改由技能計算（`getCandidates`），移除 `targetEnemy` / `targetFriend` | D29、D33 |
| Battle 交給行動流程的是 T1 / T2 活著的角色名單 + 行動者屬於哪一軍 | D30、D31 |
| 一拳攻擊的處理鏈改為 `vector` 並由 Client 注入；handler 介面加入 `actor`；移除 `next` 指標 | D21–D23 |
| handler 用型別判斷狀態，不再比對字串 | D25 |

---

## OOD — 類別圖

```mermaid
classDiagram
    class RPG {
        -Troop t1
        -Troop t2
        -Battle battle
        +GameStart(Troop t1, Troop t2)
        +GameEnd()
    }
    class Battle {
        -Troop t1
        -Troop t2
        +startBattle()
        -isEnd() bool
    }
    class Troop {
        -vector~Role~ roles
        +addRole(Role)
        +size() int
        +getRole(int i) Role
        +Annihilated() bool
    }

    class Role {
        -int hp
        -int mp
        -int str
        -string name
        -char identity
        -State state
        -IAction decider
        -vector~Skill~ actions
        -vector~SkillObserver~ observers
        +addAction(Skill)
        +takeTurn(t1, t2, actorSide)
        +checkMp(Skill) bool
        +lossMp(int)
        +lossHp(int)
        +gainHp(int)
        +isDead() bool
        +isHero() bool
        +setState(State)
        +endThisRound()
        +addObserver(SkillObserver)
        +getObservers() vector~SkillObserver~
        -notifyObservers()
    }

    class IAction {
        <<interface>>
        +chooseAction(vector~Skill~ actions) Skill*
        +chooseTargets(vector~Role~ candidates, int m) vector~Role~*
    }
    class AIAction {
        -int seed
    }
    class HeroAction {
        -istream input
    }

    class Skill {
        <<abstract>>
        -string name
        -int mp
        +getName() string
        +getMp() int
        +getCandidates(actor, t1, t2, actorSide) Candidates
        +doAction(Role actor, vector~Role~ targets)*
        #enemiesOf(actor, t1, t2, actorSide) vector~Role~
        #alliesOf(actor, t1, t2, actorSide) vector~Role~
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
        -vector~OnePunchHandler~ handlers
        +OnePunch(vector~OnePunchHandler~ handlers)
    }

    class State {
        <<abstract>>
        -int round
        -Role role
        +takeTurn(t1, t2, actorSide)
        +doDamage(Role target, int n)
        +damage(int n)
        +getRound() int
        +setRound(int)
    }
    class NormalState
    class PoisonedState {
        +takeTurn(t1, t2, actorSide)
    }
    class PetrochemicaledState {
        +takeTurn(t1, t2, actorSide)
    }
    class CheerupedState {
        +doDamage(Role target, int n)
    }

    class SkillObserver {
        <<abstract>>
        -Role actor
        +UntilDie(Role dead)*
        +getRole() Role
    }
    class SummonObserver
    class CurserObserver

    class OnePunchHandler {
        <<abstract>>
        +match(Role actor, Role target)* bool
        +doHandle(Role actor, Role target)*
    }
    class HpHandler
    class PoisonPetrochemicalHandler
    class CheerupHandler
    class NormalHandler

    RPG --> "2" Troop
    RPG --> Battle
    Battle --> "2" Troop : T1, T2
    Troop "1" o-- "*" Role

    Role "1" --> "1" State
    State --> Role
    State <|-- NormalState
    State <|-- PoisonedState
    State <|-- PetrochemicaledState
    State <|-- CheerupedState

    Role "1" --> "1" IAction : decider
    IAction <|.. AIAction
    IAction <|.. HeroAction

    Role "1" o-- "*" Skill : actions
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

    Role "1" o-- "*" SkillObserver
    SkillObserver --> Role : actor
    SkillObserver <|-- SummonObserver
    SkillObserver <|-- CurserObserver

    OnePunch "1" o-- "*" OnePunchHandler : 依序比對
    OnePunchHandler <|-- HpHandler
    OnePunchHandler <|-- PoisonPetrochemicalHandler
    OnePunchHandler <|-- CheerupHandler
    OnePunchHandler <|-- NormalHandler
```

**圖中的符號說明**

- `Candidates`：類似 tuple 的（候選名單 `vector<Role*>`, 要選的人數 `m`）（D29）。
- `t1, t2`：Battle 整理好的 T1、T2 名單，**都已排除死者**、各自依隊伍順序；`actorSide`：行動者屬於 T1 還是 T2（D30、D31）。
- `identity`：識別字元，`'h'` 代表英雄（D6）。
- `Skill::getCandidates()` 是 virtual，**預設 = 1 位敵軍**；火球、自我治療、召喚、自爆、鼓舞覆寫它，並呼叫 `enemiesOf` / `alliesOf`（D32、D33）。
- `Role` 建立時自動把 `BasicAttack` 放在 `actions` 第 0 項；Client 只加入輸入檔列出的技能（D28）。
- 每個技能子類別各自持有自己的**中文名稱**，輸出時用 `getName()`（D27）。

### 每個類別負責什麼

| 類別 | 責任 | 決策 |
|---|---|---|
| `RPG` | 註冊兩支軍隊、建立並啟動 `Battle`、接收結果 | D1 |
| `Battle` | 依 T1 → T2、用索引 + 每圈重讀人數輪流（召喚的史萊姆本回合就能行動）、跳過死者；整理 T1 / T2 活著的名單；每次行動後判斷是否結束（英雄死亡 / 一方殲滅）；每回合結束呼叫 `endThisRound()` | D1、D11、D20、D30、D31 |
| `Role` | 持有 State、決策者、行動、觀察者；`checkMp` 只檢查；`lossHp` 是 HP 減少的唯一出口（印死亡、通知觀察者）；回合數歸零時由 Role 換回 `NormalState` | D5、D9、D11、D17 |
| `State` | 固定流程（S1 → MP 檢查 → 算候選 → S2 → 扣 MP → 執行）；`doDamage` 套用行動者的加成並印傷害訊息；`damage` 轉交 `lossHp` | D10、D12、D16 |
| `IAction` | 只做兩個決策：選行動、選目標；n ≤ m 時自動全選也由它判斷（AI 可就地決定 seed 要不要 +1） | D4、D5、D7、D8 |
| `Skill` | 宣告 MP、名稱；計算候選；`doAction` 內每造成一次傷害就呼叫一次 `actor.state.doDamage()` | D3、D16、D29 |
| `SkillObserver` | 收到死者後自行讀資料、自行判斷施咒者 / 召喚者是否還活著 | D18 |
| `Curse` | 從目標的 observer 清單判斷「同一施咒者不疊加」 | D19 |
| `OnePunch` | 對每位目標依序比對 Client 注入的 handler，套用第一個成立的；**沒有預設鏈** | D21–D23 |

### 模組內部 vs 外部擴充（只列已決定的）

| 範圍 | 包含 | 決策 |
|---|---|---|
| **模組內部** | `RPG`、`Battle`、`Troop`、`Role`、`State`、`NormalState`、`IAction`、`Skill`、`BasicAttack`、`SkillObserver` | D1、D11、D28、D32 |
| **外部擴充**（可直接刪檔，不影響模組） | 10 種技能（含 `OnePunch`）、具體的 `OnePunchHandler`；`Curse` / `CurserObserver` 等技能專屬的觀察者；技能帶出的狀態（中毒、石化、鼓舞） | D19、D23、D24、需求 ② |
| **Client** | 讀測資 / 輸入、名稱 → 技能的建造函式、組裝一拳攻擊的處理鏈、建立角色與軍隊、決定每個角色的 `IAction` | D21、D26、D36、D37 |

> 討論中沒有明確決定、圖中暫時這樣畫的：`OnePunchHandler` 抽象類別歸在哪一邊、`AIAction` / `HeroAction` 屬於模組還是 Client、召喚的史萊姆是否保留 `Slime` 子類別（圖中直接用 `Role` 表示）。

---

## OOD — 循序圖：Client 組裝與啟動

```mermaid
sequenceDiagram
    autonumber
    participant C as Client（main / 測試）
    participant F as 技能建造函式
    participant OP as OnePunch
    participant R as Role
    participant G as RPG

    C->>C: 解析 .in：軍隊行 + 英雄決策行
    loop 每位角色
        C->>R: new Role(name, hp, mp, str)
        Note right of R: 建構時自動加入 BasicAttack（第 0 項）
        loop 該角色的每個技能名稱
            C->>F: create("火球" / "一拳攻擊" / …)
            alt 一拳攻擊
                F->>OP: new OnePunch([HpHandler, PoisonPetrochemicalHandler, CheerupHandler, NormalHandler])
                Note right of OP: 順序由 Client 決定
            end
            F-->>C: Skill*
            C->>R: addAction(skill)
        end
        alt T1 的第一位
            C->>R: 標成英雄 'h'，decider = HeroAction(istream)
        else 其他角色
            C->>R: decider = AIAction（seed = 0）
        end
    end
    C->>G: GameStart(t1, t2)
```

> 正式執行時 `HeroAction` 讀 `std::cin`；測試時讀測資檔剩下的英雄決策行（D37）。S1 和 S2 共用同一串輸入。

## OOD — 循序圖：一回合與一次行動

```mermaid
sequenceDiagram
    autonumber
    participant B as Battle
    participant R as Role（行動者）
    participant S as State（行動者的）
    participant D as IAction
    participant K as Skill

    loop 每一回合
        loop T1 再 T2，idx = 0；idx < troop.size()（每圈重讀）
            alt 角色已死亡
                B->>B: 跳過
            else 活著
                B->>B: 整理 t1、t2（排除死者）與 actorSide
                B->>R: takeTurn(t1, t2, actorSide)
                R->>S: takeTurn(t1, t2, actorSide)
                Note over S: 石化：跳過 S1–S3<br/>中毒：先 lossHp(30)，死了就結束<br/>其他：走預設流程
                loop S1：直到 MP 足夠
                    S->>D: chooseAction(actions)
                    D-->>S: skill
                    S->>R: checkMp(skill)
                    opt MP 不足
                        S->>S: 印「你缺乏 MP，不能進行此行動。」
                    end
                end
                S->>K: getCandidates(actor, t1, t2, actorSide)
                K-->>S: (candidates, m)
                S->>D: chooseTargets(candidates, m)
                Note right of D: m = 0 或 n ≤ m：自動全選、略過 S2
                D-->>S: targets
                S->>R: lossMp(skill.getMp())
                S->>K: doAction(actor, targets)
                B->>B: 判斷是否結束（英雄死亡 / 一方殲滅）
            end
        end
        loop 每位角色
            B->>R: endThisRound()
            Note right of R: 狀態回合數 −1，歸零時 setState(NormalState)
        end
    end
```

## OOD — 循序圖：傷害、死亡與觀察者

```mermaid
sequenceDiagram
    autonumber
    participant K as Skill / OnePunchHandler
    participant AS as actor.state
    participant TS as target.state
    participant T as target
    participant O as SkillObserver

    loop 每造成一次傷害（一拳的 80 × 3 就是 3 次）
        K->>AS: doDamage(target, n)
        Note right of AS: 套用加成（鼓舞 +50）<br/>印「X 對 Y 造成 N 點傷害。」（N 為加成後數值）
        AS->>TS: damage(n')
        TS->>T: lossHp(n')
        opt HP ≤ 0
            T->>T: 印「Y 死亡。」
            T->>O: UntilDie(target)
            Note right of O: pull：自行讀死者剩餘 MP，<br/>自行判斷施咒者 / 召喚者是否活著
        end
    end
```

> 中毒扣的 30 HP、自爆的自殺也都經過 `lossHp()`，所以同樣會印死亡、觸發觀察者（D14、D17）。
> 自爆：目標不含自己、依 T1 → T2；對所有目標處理完後，才讓自己 HP 歸零並印「<自己> 死亡。」，自己歸零**不印**傷害訊息（D34，已用 `testcases/self-explosion.out` 驗證）。

## OOD — 循序圖：一拳攻擊（Chain of Responsibility）

```mermaid
sequenceDiagram
    autonumber
    participant OP as OnePunch
    participant H as handlers（Client 注入的 vector）
    participant AS as actor.state

    loop 每位目標
        loop 依 vector 順序
            OP->>H: match(actor, target)
            alt 成立（第一個）
                OP->>H: doHandle(actor, target)
                H->>AS: doDamage(target, n)（可能多次）
                Note right of H: 例：CheerupHandler 造成 100 傷害後<br/>把目標狀態換回正常
                OP->>OP: 停止比對
            end
        end
    end
```

> handler 用型別判斷（如 `dynamic_cast`）辨認目標的狀態，不比對字串（D25）；具體 handler 和它們依賴的狀態一起屬於外部擴充（D24）。

## State Diagram — role states（狀態機）

角色身上的狀態效果（State pattern 的 4 個具體狀態）之間**所有的轉移**。

- 菱形是「被施加狀態」的分岔：**任何狀態**（包括已經是同一種狀態）被施加新狀態時，都會覆寫成新狀態並重設 round = 3。
- 石化 / 中毒 / 受到鼓舞在每回合結束時由 `endThisRound()` 把 round − 1，round > 0 時維持原狀態；歸零時由 **Role** 換回正常。
- 任何狀態下 HP ≤ 0 都會死亡（見轉移表最後一列），圖中省略以免線太多。

```mermaid
stateDiagram-v2
    direction TB
    state "正常 NormalState" as Normal
    state apply <<choice>>
    state "石化 PetrochemicaledState<br/>輪到時跳過 S1–S3" as Petri
    state "中毒 PoisonedState<br/>輪到時先 lossHp(30)" as Poisoned
    state "受到鼓舞 CheerupedState<br/>doDamage() 每次 +50" as Cheer

    [*] --> Normal : 角色建立

    Normal --> apply : 被施加狀態
    Petri --> apply : 被施加狀態（含相同狀態）
    Poisoned --> apply : 被施加狀態（含相同狀態）
    Cheer --> apply : 被施加狀態（含相同狀態）

    apply --> Petri : [石化] round = 3
    apply --> Poisoned : [下毒] round = 3
    apply --> Cheer : [鼓舞] round = 3

    Petri --> Normal : endThisRound() 後 round = 0
    Poisoned --> Normal : endThisRound() 後 round = 0
    Cheer --> Normal : endThisRound() 後 round = 0 / 被一拳攻擊
```

### 轉移表

| 目前狀態 | 事件 | 條件 | 轉移後 | 動作 / 由誰執行 | 依據 |
|---|---|---|---|---|---|
| 任一狀態（含相同狀態） | 被「石化」命中 | — | 石化 | `target.setState(new PetrochemicaledState)`，round = 3；舊狀態由 Role 釋放 | 需求「覆寫並重新倒數」、D11 |
| 任一狀態（含相同狀態） | 被「下毒」命中 | — | 中毒 | 同上，round = 3 | 同上 |
| 任一狀態（含相同狀態） | 被「鼓舞」選為目標 | — | 受到鼓舞 | 同上，round = 3 | 同上 |
| 石化 / 中毒 / 受到鼓舞 | 回合結束 `endThisRound()`（Battle 呼叫） | round > 1 | 不變 | Role 將 round − 1 | D11 |
| 石化 / 中毒 / 受到鼓舞 | 回合結束 `endThisRound()` | round = 1（−1 後歸零） | 正常 | **Role** 呼叫 `setState(NormalState)`（不由 State 自己換） | D11 |
| 受到鼓舞 | 被一拳攻擊命中 | 不符合「HP ≥ 500」「中毒或石化」 | 正常 | `CheerupHandler` 先造成 100 傷害，再 `setState(NormalState)` | 需求一拳第 3 條、D24 |
| 任一狀態 | `lossHp()` 後 HP ≤ 0 | — | （角色死亡） | 印「X 死亡。」、通知觀察者；之後 Battle 跳過此角色 | D17、D20 |

**round 的計算**（D11）：施加當下的回合算第 1 回合。例：第 1 回合被石化 → round = 3；第 1、2、3 回合結束時各 −1，第 3 回合結束歸零 → 第 4 回合恢復正常，所以第 1、2、3 回合都被跳過。正常狀態沒有 round，不倒數。

## 測試：整場輸入 → 輸出比對（D35–D39）

```mermaid
sequenceDiagram
    autonumber
    participant T as TEST_P（每組 .in / .out 一個案例）
    participant P as RPG parser（test/libary）
    participant G as RPG
    participant O as ostringstream

    T->>P: parse("testcases/<名稱>.in")
    P-->>T: t1, t2（英雄的 HeroAction 讀剩下的決策行）
    T->>O: std::cout.rdbuf(O)
    T->>G: GameStart(t1, t2)
    T->>T: 還原 std::cout
    T->>T: 和 <名稱>.out 逐行比對
    opt 不一致
        T->>T: 報出第一個不同的行號，寫出 build/<名稱>.actual.txt
    end
```
