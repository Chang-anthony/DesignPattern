# RPGGame — 單元測試文件

本文件說明 `RPGGame/test/` 底下**每一個**單元測試：測什麼、依據哪條需求或設計決策、怎麼準備資料、執行步驟、以及**通過標準**。

- 需求：[`../need/need.md`](../need/need.md)　設計決策 D1–D40 與實作紀錄：[`../CLAUDE.md`](../CLAUDE.md)　圖：[`../diagrams.md`](../diagrams.md)
- 測試框架：GoogleTest（`TEST` / `TEST_F`），C++20
- 最後更新：2026-10-15（O1 物件擁有權 D49、O6 輸出 Composite D50），共 **160** 個測試，全部通過；主程式的手動驗證見 §11

---

## 1. 如何執行

### 1.1 建置與執行

```bash
cd RPGGame
cmake -S . -B build
cmake --build build                 # Windows (MinGW)：build 完會自動執行 SimpleTest（RunTests 目標）
./build/bin/SimpleTest              # 執行全部測試
```

只跑某一組或某一個測試（`--gtest_filter` 支援 `*` 萬用字元）：

```bash
./build/bin/SimpleTest --gtest_filter='HeroActionTest.*'
./build/bin/SimpleTest --gtest_filter='SkillBehaviorTest.OnePunch*'
./build/bin/SimpleTest --gtest_filter='RoleTest.CheckMpBoundaryIsInclusive'
./build/bin/SimpleTest --gtest_filter='AllTestcases/TestcaseReplayTest.*'   # 只跑 10 組測資整場重播
./build/bin/SimpleTest --gtest_list_tests          # 列出所有測試名稱
```

### 1.2 整體通過標準

| 項目 | 標準 |
|---|---|
| 結果 | 最後一行為 `[  PASSED  ] 160 tests.`，沒有任何 `[  FAILED  ]` |
| 程式結束 | 測試程式正常結束（沒有 crash / segmentation fault）；crash 視同失敗 |
| 新增測試檔 | `test/CMakeLists.txt` 以 `file(GLOB … CONFIGURE_DEPENDS *.cpp)` 收集，新增 / 刪除 `test/*.cpp` 後直接 build 即可，不必修改 CMake |
| 單一測試 | 該測試內**所有** `EXPECT_*` / `ASSERT_*` 都成立；`ASSERT_*` 失敗會立即中止該測試（後續檢查不執行） |

### 1.3 測試檔一覽

| 編號 | 檔案 | Test suite | 數量 | 測試對象 |
|---|---|---|---|---|
| EX | `ExampleTests.cpp` | `SkillTest` | 11 | Anthony 原本的技能測試（只檢查 HP / MP / 狀態，不檢查輸出） |
| SK | `SkillTests.cpp` | `SkillBehaviorTest` | 46 | 技能：名稱、MP、候選、輸出訊息、傷害、狀態、召喚、詛咒、一拳攻擊 |
| RL | `RoleTests.cpp` | `RoleTest` | 25 | `Role`：屬性、軍隊、MP、HP 與死亡、觀察者、狀態與回合倒數、擁有權（D49） |
| AI | `AIActionTests.cpp` | `AIActionTest` | 11 | `AIAction`：seed 規則（S1、S2、自動全選） |
| HA | `HeroActionTests.cpp` | `HeroActionTest` | 15 | `HeroAction`：從輸入讀英雄決策（S1、S2、提示、格式容錯、錯誤處理） |
| ST | `StateFlowTests.cpp` | `StateFlowTest` | 16 | `State::decision()` 行動流程、「輪到 …」、石化 / 中毒 / 鼓舞 |
| RP | `TestcaseReplayTests.cpp` | `AllTestcases/TestcaseReplayTest`、`TestcaseListTest` | 11 | `testcases/` 10 組用正式 parser + RPG 整場比對、測資清單檢查 |
| PA | `ParserTests.cpp` | `ParserTest` | 8 | Client 端 `RPG_parser`：解析輸入、技能建造函式、錯誤處理 |
| BT | `BattleTests.cpp` | `BattleTest` | 10 | `Battle` 回合迴圈、結束條件、`RPG` 宣布勝負 |
| OU | `OutputTests.cpp` | `OutputTest` | 7 | `io::Output`：Leaf、Composite 渲染與分送、擁有子節點、單一存取點（D50，見 §14） |
| | | **合計** | **160** | |

### 1.4 測試共用的工具與慣例

| 名稱 | 所在檔案 | 用途 |
|---|---|---|
| `OutputCapture` | SK、RL、HA、ST、BT、RP | 建構時 `io::setOutput()` 換成寫到字串的 `StreamOutput`，解構時還原成先前的輸出（D50；原本叫 `CoutCapture`、用 `std::cout.rdbuf()`，D38）。模組若有地方繞過 `io::output()` 直接寫 `std::cout`，就收不到而讓測試失敗；`lines()` 依換行切成 `vector<string>`，用來**逐行比對**輸出 |
| `SkillBehaviorTest` / `RoleTest` fixture | SK、RL | 內含 `Troop t1{1}`、`Troop t2{2}`；`add(troop, name, hp, mp, str)` 建立角色並加入軍隊，所以輸出名稱會帶 `[1]` / `[2]` 前綴 |
| `run(skill, actor, targets)` | SK | 直接呼叫 `skill.attack(actor, targets)` 並回傳輸出行；**不經過 State 流程，所以不扣 MP、不印行動訊息、不付 HP 代價** |
| `castThroughFlow(actor, index)` | SK | 每次 `new` 一個讀 fixture 輸入（`index`）的 `HeroAction` 交給 actor（Role 擁有，換掉的舊決策者由 Role 釋放，D49），讓 actor 經過完整的 `takeTurn` 施放第 index 個行動：扣 MP、施放、支付 HP 代價（D47）；回傳完整輸出 |
| `RoleTest::hurt(target, n)` | RL | 由 fixture 的 `attacker`（不在軍隊，名稱 `Attacker`）呼叫 `getState()->doDamage(target, n)`；`lossHp` 不公開後（D47），測試也走正規傷害通道，會多印一行「Attacker 對 … 造成 n 點傷害。」 |
| `alive1()` / `alive2()` | SK | 模擬 Battle 交給技能的 T1、T2 名單（D30、D31） |
| `requirementChain()` | SK | 依需求順序組好的一拳處理鏈：`HpHandler → PoisonPetrochemicalHandler → CheerupHandler → NormalHandler`（D21） |
| `RecordingState` | RL | 只記錄 `decision()` 被呼叫的次數與參數，用來確認 `Role::takeTurn` 有交給狀態（D10） |
| `RecordingObserver` | RL | 被通知時把「標籤:死者名稱」記到 log，用來確認通知順序與次數（D18） |
| `DummyAction` | RL | 最簡單的 `IAction`：永遠選第一個行動、回傳全部候選 |
| `TrackedAction` / `TrackedObserver` / `TrackedRole` | RL | 解構時把旗標設為 `true`，用來確認誰釋放了誰（D49） |
| `TrackedHandler` | SK | 解構時計數 +1，用來確認 `OnePunch` 釋放處理鏈（D49） |
| `std::istringstream` | HA | 模擬英雄的輸入（D37：`HeroAction` 注入 `std::istream&`） |
| `namesOf(roles)` | AI、HA | 把 `vector<Role*>` 轉成名字清單，方便比對 |
| `HeroActionTest::mute` | HA | fixture 成員 `OutputCapture`：把 `chooseTargets` 印的提示靜音；要檢查提示的測試在裡面再開一個 `OutputCapture`（巢狀導向，結束時還原到外層） |
| `StateFlowTest::turn(role)` | ST | 依角色所屬軍隊決定 actorSide，呼叫 `takeTurn(t1.getRoles(), t2.getRoles(), side)` 並回傳**完整輸出** |
| `readExpected` / `playTestcase` | RP | 讀 `.out`（去 `\r`、去檔尾空行）／用正式的 `RPG_parser` + `HeroAction` + `RPG` 跑一組測資（見 §8） |
| `addHero` / `addAI` / `runBattle` / `turnHeaders` | BT | 建立英雄與 AI 角色、執行 `startBattle()` 收集輸出、只取「輪到 …」行（見 §10） |

輸出格式依 `testcases/*.out`：傷害「`<行動者> 對 <目標> 造成 <N> 點傷害。`」、死亡「`<角色> 死亡。`」，名稱一律帶軍隊前綴。

### 1.5 每個測試的寫法

每個測試都列出以下欄位：

- **目的**：這個測試要證明的行為。
- **依據**：需求段落或 `CLAUDE.md` 的決策編號。
- **準備**：建立的角色（`名稱 HP / MP / STR`）、軍隊、狀態等前置資料。
- **步驟與預期**：依序執行的動作，每一步後面的「→」是該步驟要成立的檢查。
- **通過標準**：整個測試算通過的條件（摘要）。

**編號規則**：編號一旦給出就固定，之後新增的測試接在該檔案的最後一號（例如 SK-43、HA-15），文件中放在相關主題的位置；這樣 §9 的對照表與其他文件引用的編號不會跑掉。

---

## 2. EX — `ExampleTests.cpp`（`SkillTest`，11 個）

Anthony 原本寫的技能測試。每個測試都直接呼叫 `skill->attack(actor, targets)`，只檢查 MP 花費、HP 與狀態的結果（不檢查輸出文字）。角色一律以 `new Role(hp, mp, str, "h")` 建立、**不加入軍隊**。

> 共同準備：除特別註明外，`actor` 與 `target` 都是 `Role 500 / 500 / 50`。

#### EX-01 `SkillTest.BasicAttackTest`
- **目的**：普通攻擊的 MP 花費為 0，傷害等於行動者的 STR。
- **依據**：需求「行動」表（普通攻擊：MP 0、STR 點傷害）。
- **準備**：`skill = new BasicAttack()`；actor STR = 50。
- **步驟與預期**：
  1. `skill->getMp()` → `0`
  2. `skill->attack(actor, {target})` → `target->getHp() == 450`（500 − 50）
- **通過標準**：MP 為 0，目標 HP 剛好少 STR。

#### EX-02 `SkillTest.FireballTest`
- **目的**：火球花 50 MP，對每位目標各造成 50 點傷害。
- **依據**：需求「行動」表（火球：MP 50、所有敵軍各 50）。
- **準備**：`target = 500 / 500 / 50`、`target2 = 300 / 500 / 50`。
- **步驟與預期**：
  1. `skill->getMp()` → `50`
  2. `skill->attack(actor, {target, target2})` → `target` HP `450`、`target2` HP `250`
- **通過標準**：兩位目標都只少 50。

#### EX-03 `SkillTest.WaterballTest`
- **目的**：水球花 50 MP，對單一目標造成 120 點傷害。
- **依據**：需求「行動」表（水球：MP 50、120 傷害）。
- **步驟與預期**：
  1. `skill->getMp()` → `50`
  2. `skill->attack(actor, {target})` → `target` HP `380`
- **通過標準**：目標 HP 少 120。

#### EX-04 `SkillTest.OnePunchTest`
- **目的**：一拳攻擊依目標條件套用**第一個**成立的效果（4 條規則各測一次）。
- **依據**：需求「一拳攻擊」；D21–D25（處理鏈由 Client 注入、用型別判斷狀態）。
- **準備**：`skill = new OnePunch({HpHandler, PoisonPetrochemicalHandler, CheerupHandler, NormalHandler})`。
- **步驟與預期**：
  1. `skill->getMp()` → `180`
  2. 目標 `500 / 500 / 50`（HP ≥ 500）：攻擊 → HP `200`（−300，規則 1）
  3. `target2 = 400 HP`，設為 `CheerupedState`：→ `getState()->getName() == "CheerupedState"`；攻擊 → HP `300`（−100，規則 3），狀態變回 `"NormalState"`
  4. `target3 = 400 HP`，設為 `PetrochemicaledState`：攻擊 → HP `160`（−80 × 3，規則 2），狀態仍為 `"PetrochemicaledState"`
  5. `target4 = 400 HP`，設為 `PoisonedState`：攻擊 → HP `160`（−80 × 3，規則 2），狀態仍為 `"PoisonedState"`
  6. `target5 = 200 HP`，正常狀態：攻擊 → HP `100`（−100，規則 4）
- **通過標準**：4 條規則的傷害與狀態變化都正確；只有「受到鼓舞」會被換回正常。

#### EX-05 `SkillTest.SelfExplosionTest`
- **目的**：自爆花 200 MP，對目標造成 150 點傷害；自殺是它的 HP 代價。
- **依據**：需求「行動」表（自爆）；D34、D47。
- **步驟與預期**：
  1. `skill->getMp()` → `200`
  2. `skill->attack(actor, {target})` → `target` HP `350`；`actor` HP 仍為 `500`（`attack()` 只對目標施放）
  3. `skill->costHp(actor)` → `500`（全部 HP，由 State 流程在施放後支付）
- **通過標準**：目標 −150、`attack()` 不扣施放者 HP、代價為全部 HP。
- **備註**：2026-10-14 因 D47 修改；原本檢查 `attack()` 之後施放者 HP 為 0。

#### EX-06 `SkillTest.SelfHealingTest`
- **目的**：自我治療花 50 MP，只替行動者加 150 HP。
- **依據**：需求「行動」表（自我治療）。
- **步驟與預期**：
  1. `skill->getMp()` → `50`
  2. `skill->attack(actor, {target})` → `actor` HP `650`、`target` HP 維持 `500`
- **通過標準**：只有行動者被治療，即使傳入其他目標也不受影響。

#### EX-07 `SkillTest.PoisonTest`
- **目的**：下毒花 80 MP，把目標換成中毒狀態，當下不扣血。
- **依據**：需求「行動」表（下毒）、「角色狀態」（中毒在輪到時才扣 30）。
- **步驟與預期**：
  1. `skill->getMp()` → `80`
  2. `skill->attack(actor, {target})` → `target` HP 維持 `500`、`getState()->getName() == "PoisonedState"`
- **通過標準**：狀態改變、HP 不變。

#### EX-08 `SkillTest.CheerupTest`
- **目的**：鼓舞花 100 MP，把目標換成受到鼓舞狀態。
- **步驟與預期**：
  1. `skill->getMp()` → `100`
  2. `skill->attack(actor, {target})` → `target` HP 維持 `500`、狀態 `"CheerupedState"`
- **通過標準**：狀態改變、HP 不變。

#### EX-09 `SkillTest.PetrochemicalTest`
- **目的**：石化花 100 MP，把目標換成石化狀態。
- **步驟與預期**：
  1. `skill->getMp()` → `100`
  2. `skill->attack(actor, {target})` → `target` HP 維持 `500`、狀態 `"PetrochemicaledState"`
- **通過標準**：狀態改變、HP 不變。

#### EX-10 `SkillTest.CurseTest`
- **目的**：詛咒在目標身上掛 `CurserObserver`；**同一施咒者不疊加**、不同施咒者各掛一個。
- **依據**：需求「詛咒」；D19（由 `Curse` 判斷是否已被同一人詛咒）。
- **準備**：`actor`、`actor2`、`target` 都是 `500 / 500 / 50`。
- **步驟與預期**：
  1. `skill->getMp()` → `100`
  2. `actor` 詛咒 `target` → HP 不變；`observers[0]->getRole() == actor`
  3. `actor2` 詛咒 `target` → `observers[0]` 是 `actor`、`observers[1]` 是 `actor2`
  4. `actor` 再詛咒一次 → `observers.size() == 2`，順序仍為 `actor`、`actor2`
- **通過標準**：觀察者數量為 2（不是 3），且順序為加入順序。

#### EX-11 `SkillTest.SummonTest`
- **目的**：召喚花 150 MP，在**施放者所屬軍隊**的隊尾加入一隻史萊姆，並在史萊姆身上掛 `SummonObserver`。
- **依據**：需求「召喚」；D20（加入隊尾）。
- **準備**：`troop = new Troop()` 加入 `actor`；`troop2 = new Troop()` 加入 `target`。
- **步驟與預期**：
  1. `skill->getMp()` → `150`
  2. `skill->attack(actor, {target})` → `target` HP 維持 `500`
  3. `troop->getRoles()` → 大小 `2`，`roles[1]->getName() == "Slime"`
  4. `target->getObservers().size()` → `0`（傳入的目標不受影響）
  5. 史萊姆的觀察者 → 數量 `1`，`getRole() == actor`
- **通過標準**：史萊姆加入施放者的軍隊、觀察者指向施放者。

---

## 3. SK — `SkillTests.cpp`（`SkillBehaviorTest`，46 個）

技能的行為與**輸出文字**。角色用 fixture 的 `add(t1/t2, …)` 建立，所以名稱帶 `[1]` / `[2]` 前綴。`run(skill, actor, targets)` 直接呼叫 `attack()` 並收集輸出（不經過 State 流程：不扣 MP、不印行動訊息）。

### 3.1 名稱、MP、普通攻擊、前綴

#### SK-01 `EachActionHasItsChineseNameAndMpCost`
- **目的**：11 個行動各自持有正確的中文名稱與 MP 花費。
- **依據**：D27（技能各自持有中文名稱）；需求「行動」表。
- **步驟與預期**：逐一 `new` 每個行動，檢查 `getName()` 與 `getMp()`（失敗時 `SCOPED_TRACE` 會標出是哪個技能）：

  | 行動 | 名稱 | MP |
  |---|---|---|
  | `BasicAttack` | 普通攻擊 | 0 |
  | `Waterball` | 水球 | 50 |
  | `Fireball` | 火球 | 50 |
  | `SelfHealing` | 自我治療 | 50 |
  | `Petrochemical` | 石化 | 100 |
  | `Poison` | 下毒 | 80 |
  | `Summon` | 召喚 | 150 |
  | `SelfExplosion` | 自爆 | 200 |
  | `Cheerup` | 鼓舞 | 100 |
  | `Curse` | 詛咒 | 100 |
  | `OnePunch` | 一拳攻擊 | 180 |
- **通過標準**：11 筆名稱與 MP 全部相符。

#### SK-02 `RoleAlwaysHasBasicAttackAsFirstAction`
- **目的**：角色建立時自動擁有普通攻擊，且固定在第 0 項；之後加入的技能依序排在後面。
- **依據**：D28（AI 的 `seed % 行動數` 依賴這個順序）。
- **步驟與預期**：
  1. `Role role(100, 100, 10, "A")` → 行動數 `1`，第 0 項是 `BasicAttack`
  2. `addSkill(火球)`、`addSkill(水球)` → 行動依序為 普通攻擊、火球、水球
  3. `Role withSkills(…, {詛咒, 召喚})`（建構子帶技能）→ 依序為 普通攻擊、詛咒、召喚
- **通過標準**：兩種建構方式下，普通攻擊都在第 0 項。

#### SK-03 `DisplayNameHasTroopPrefix`
- **目的**：輸出用名稱帶軍隊編號前綴；沒有軍隊時不帶。
- **依據**：需求「輸出格式」；§7.2 I2。
- **準備**：`英雄` 加入 T1、`Slime1` 加入 T2、`Alone` 不加入軍隊。
- **步驟與預期**：`getDisplayName()` → `"[1]英雄"`、`"[2]Slime1"`、`"Alone"`
- **通過標準**：三者都相符。

### 3.2 候選名單（D29–D34）

#### SK-04 `DefaultCandidatesAreOneEnemy`
- **目的**：沒有覆寫 `getCandidates` 的 6 個行動，候選 = 敵軍、m = 1，且不論行動者在哪一軍都正確。
- **依據**：D33（預設 1 位敵軍）、D31（T1 / T2 + actorSide）。
- **準備**：T1 = 英雄、Ally；T2 = S1、S2。
- **步驟與預期**：對 普通攻擊、水球、石化、下毒、詛咒、一拳攻擊 各執行：
  1. 英雄（actorSide = 1）→ 候選 `{S1, S2}`、`m == 1`
  2. S1（actorSide = 2）→ 候選 `{英雄, Ally}`、`m == 1`
- **通過標準**：6 個行動 × 2 個方向全部相符。

#### SK-05 `FireballCandidatesAreAllEnemies`
- **目的**：火球的候選 = 全部敵軍，m = 敵軍人數（所以 n ≤ m，自動全選）。
- **準備**：T1 = 英雄；T2 = S1、S2、S3。
- **步驟與預期**：`getCandidates(英雄, …, 1)` → 候選 `{S1, S2, S3}`、`m == 3`
- **通過標準**：候選與 m 都相符。

#### SK-06 `SelfHealingCandidateIsSelf`
- **目的**：自我治療的目標只有自己。
- **準備**：T1 = 英雄、Ally；T2 = S1。
- **步驟與預期**：`getCandidates(英雄, …)` → 候選 `{英雄}`、`m == 1`
- **通過標準**：候選不含友軍與敵軍。

#### SK-07 `SummonHasNoCandidates`
- **目的**：召喚不需要目標（m = 0，略過 S2）。
- **步驟與預期**：`getCandidates(英雄, …)` → 候選為空、`m == 0`
- **通過標準**：兩者都成立。

#### SK-08 `CheerupCandidatesAreAlliesExcludingSelfAndPickThree`
- **目的**：鼓舞的候選 = 友軍（不含自己）、m = 3；友軍不足 3 位時 n ≤ m。
- **準備**：T1 = A、B、C、D；T2 = E、F。
- **步驟與預期**：
  1. B 施放（actorSide = 1）→ 候選 `{A, C, D}`（不含 B）、`m == 3`
  2. E 施放（actorSide = 2）→ 候選 `{F}`、`m == 3`（之後由 `IAction` 自動全選，D8）
- **通過標準**：兩個方向都相符。

#### SK-09 `SelfExplosionCandidatesAreEveryoneElseInT1ThenT2Order`
- **目的**：自爆的候選 = 全場其他角色，**順序永遠是 T1 → T2**（即使由 T2 的角色施放）。
- **依據**：D31、D34。
- **準備**：T1 = A、B；T2 = C、D。
- **步驟與預期**：
  1. C 施放（actorSide = 2）→ 候選 `{A, B, D}`、`m == 3`
  2. A 施放（actorSide = 1）→ 候選 `{B, C, D}`
- **通過標準**：不含自己，且順序為 T1 → T2。

### 3.3 行動訊息（S3）

#### SK-10 `AnnounceFormats`
- **目的**：`announce()` 印出的 S3 行動訊息格式正確。
- **依據**：需求「輸出格式」；§7.2 I1。
- **準備**：T1 = 英雄；T2 = Slime1、Slime2。
- **步驟與預期**：在同一個 `OutputCapture` 內依序呼叫，輸出必須**逐行**等於：
  1. `BasicAttack().announce(英雄, {Slime1})` → `[1]英雄 攻擊 [2]Slime1。`
  2. `Fireball().announce(英雄, {Slime1, Slime2})` → `[1]英雄 對 [2]Slime1, [2]Slime2 使用了 火球。`
  3. `Waterball().announce(英雄, {Slime2})` → `[1]英雄 對 [2]Slime2 使用了 水球。`
  4. `SelfHealing().announce(Slime1, {Slime1})` → `[2]Slime1 使用了 自我治療。`
  5. `Summon().announce(英雄, {})` → `[1]英雄 使用了 召喚。`
- **通過標準**：5 行完全相同（含全形句號、逗號後的空白）。

### 3.4 傷害（D16、D17）

#### SK-11 `BasicAttackDealsStrDamage`
- **準備**：英雄 `500 / 500 / 40`（T1）、Slime1 `100 / 100 / 30`（T2）。
- **步驟與預期**：
  1. `run(普通攻擊, 英雄, {Slime1})` → 輸出 `["[1]英雄 對 [2]Slime1 造成 40 點傷害。"]`
  2. → Slime1 HP `60`
  3. → 英雄 MP 仍為 `500`（技能本身不扣 MP，D9）
- **通過標準**：傷害 = STR、輸出一行、MP 不變。

#### SK-12 `BasicAttackWithZeroStrStillPrintsZeroDamage`
- **目的**：STR 為 0 時仍印出「造成 0 點傷害」（測資 `cheerup.out` 有這種行）。
- **準備**：Servant4 `1000 / 0 / 0`（T1）、Slime1 `500 / 0 / 0`（T2）。
- **步驟與預期**：輸出 `["[1]Servant4 對 [2]Slime1 造成 0 點傷害。"]`；Slime1 HP 維持 `500`
- **通過標準**：輸出與 HP 都相符。

#### SK-13 `WaterballDeals120Damage`
- **準備**：英雄 `300 / 500 / 100`、Slime2 `150 / 200 / 50`。
- **步驟與預期**：輸出 `["[1]英雄 對 [2]Slime2 造成 120 點傷害。"]`；Slime2 HP `30`
- **通過標準**：輸出與 HP 都相符。

#### SK-14 `FireballDeals50ToEachTargetInOrder`
- **目的**：火球對每位目標各印一行傷害，順序同目標順序。
- **準備**：英雄 `300 / 500 / 100`；Slime1 `200 / 60 / 49`、Slime2 `200 / 200 / 50`。
- **步驟與預期**：輸出依序為 `[1]英雄 對 [2]Slime1 造成 50 點傷害。`、`[1]英雄 對 [2]Slime2 造成 50 點傷害。`；兩者 HP 都是 `150`
- **通過標準**：2 行順序正確、HP 正確。

#### SK-15 `DeathMessageFollowsEachTargetsDamageImmediately`
- **目的**：多目標時，每位目標受傷後**緊接著**印自己的死亡訊息（不是全部打完才一起印）。
- **依據**：D14、D17。
- **準備**：Slime1 `50 HP`、Slime2 `30 HP`，英雄用火球。
- **步驟與預期**：輸出必須是 4 行、順序為：
  1. `[1]英雄 對 [2]Slime1 造成 50 點傷害。`
  2. `[2]Slime1 死亡。`
  3. `[1]英雄 對 [2]Slime2 造成 50 點傷害。`
  4. `[2]Slime2 死亡。`

  → 兩者 `isDead()` 為真
- **通過標準**：4 行完全相同且順序正確。

#### SK-16 `DeathIsAnnouncedOnlyOnce`
- **目的**：已死亡的角色再受傷時，只印傷害，不再印死亡。
- **準備**：Slime1 `100 HP`，英雄用水球（120）。
- **步驟與預期**：
  1. 第一次水球 → `[傷害 120, "[2]Slime1 死亡。"]`
  2. 第二次水球 → 只有 `["[1]英雄 對 [2]Slime1 造成 120 點傷害。"]`
- **通過標準**：死亡訊息總共只出現一次。

### 3.5 自我治療

#### SK-17 `SelfHealingAdds150HpToActorOnly`
- **準備**：Slime1 `20 / 100 / 30`（T2）、英雄 `470 / 500 / 40`（T1）。
- **步驟與預期**：
  1. `run(自我治療, Slime1, {Slime1})` → 沒有任何輸出
  2. → Slime1 HP `170`、MP 仍為 `100`
  3. → 英雄 HP 仍為 `470`
- **通過標準**：只有施放者 +150、不印訊息、不扣 MP。

### 3.6 狀態類技能（D10、D11）

#### SK-18 `PetrochemicalPetrifiesTargetForThreeRounds`
- **準備**：英雄 `400 / 99999 / 30`、BOSS `270 / 9999 / 399`。
- **步驟與預期**：
  1. `run(石化, 英雄, {BOSS})` → 沒有輸出
  2. → BOSS 狀態是 `PetrochemicaledState`（`dynamic_cast` 與 `getName()` 都確認）
  3. → `getRound() == 3`、HP 仍為 `270`
- **通過標準**：狀態、回合數、HP 都相符。

#### SK-19 `PoisonPoisonsTargetForThreeRounds`
- **準備**：英雄 `1000 / 500 / 0`、Slime1 `120 / 90 / 50`。
- **步驟與預期**：無輸出；Slime1 狀態 `PoisonedState`、`round == 3`、HP 仍為 `120`（輪到時才扣）
- **通過標準**：同上。

#### SK-20 `CheerupCheersEveryTargetForThreeRounds`
- **準備**：T1 = 英雄、Servant1–3。
- **步驟與預期**：
  1. `run(鼓舞, 英雄, {Servant1, Servant2, Servant3})` → 無輸出
  2. → 3 位 Servant 都是 `CheerupedState`、`round == 3`
  3. → 英雄自己仍是 `NormalState`
- **通過標準**：3 位目標都被鼓舞、施放者不受影響。

#### SK-21 `NewStateOverwritesOldStateAndResetsRounds`
- **目的**：新狀態覆寫舊狀態並重設為 3 回合；施加相同狀態也會重設。
- **依據**：需求「新狀態覆寫並重新計算 3 回合」；D11。
- **步驟與預期**：
  1. 對 Slime1 下毒，手動 `setRound(2)` 模擬過了一回合
  2. 再石化 → 狀態是 `PetrochemicaledState`、`round == 3`
  3. 手動 `setRound(1)`，再石化一次 → `round == 3`
- **通過標準**：兩次覆寫都重設為 3。

#### SK-22 `CheeredActorDealsExtra50PerDamage`
- **目的**：受到鼓舞的行動者，每次造成傷害 +50。
- **依據**：需求「受到鼓舞」；D16。
- **準備**：英雄鼓舞 Servant1（`1000 / 0 / 0`）；Slime1 `500 HP`。
- **步驟與預期**：
  1. Servant1 普通攻擊 → `["[1]Servant1 對 [2]Slime1 造成 50 點傷害。"]`（0 + 50）
  2. Servant1 水球 → `["[1]Servant1 對 [2]Slime1 造成 170 點傷害。"]`（120 + 50）
  3. → Slime1 HP `280`（500 − 50 − 170）
- **通過標準**：輸出的是加成後數值，HP 也扣加成後數值。

### 3.7 召喚（Observer：`SummonObserver`）

#### SK-23 `SummonAddsSlimeToTheEndOfActorsTroop`
- **準備**：英雄 `500 / 10000 / 30`（T1）、Slime1（T2）。
- **步驟與預期**：
  1. `run(召喚, 英雄, {})` → 無輸出
  2. → T1 人數 `2`、T2 人數仍為 `1`
  3. → 新史萊姆：`getDisplayName() == "[1]Slime"`、HP `100`、MP `0`、STR `50`、`NormalState`
  4. → 行動只有 1 個「普通攻擊」
  5. → 觀察者 1 個，型別是 `SummonObserver`，`getRole() == 英雄`
- **通過標準**：史萊姆的屬性、所屬軍隊、觀察者全部正確。

#### SK-24 `EverySummonCreatesItsOwnSlime`
- **步驟與預期**：召喚兩次 → T1 人數 `3`；兩隻史萊姆是不同物件；第二隻也有 1 個觀察者
- **通過標準**：每次召喚都是新的史萊姆。

#### SK-25 `SummonedSlimeCarriesItsOwnAIAction`
- **目的**：召喚的史萊姆由 AI 操控，透過 `setDecider` 攜帶**自己的** `AIAction`。
- **依據**：D4、D40。
- **步驟與預期**：
  1. 召喚兩次，取得 slime1、slime2
  2. 兩者的 `getDecider()` 都能 `dynamic_cast` 成 `AIAction`，且是不同物件
  3. slime1 的 seed → `0`
  4. `slime1->getDecider()->chooseAction(...)` → `"普通攻擊"`；slime1 seed → `1`、slime2 seed 仍為 `0`
- **通過標準**：各自擁有獨立的 AI 與 seed。

#### SK-26 `SummonerGains30HpWhenSlimeDies`
- **準備**：英雄 `401 HP`（T1）召喚史萊姆；敵人 Slime1 STR `99`（T2）。
- **步驟與預期**：
  1. 敵人攻擊史萊姆 → `["[2]Slime1 對 [1]Slime 造成 99 點傷害。"]`；英雄 HP 仍為 `401`
  2. 再攻擊一次 → `[傷害 99, "[1]Slime 死亡。"]`；英雄 HP `431`
- **通過標準**：史萊姆死亡時（且只在死亡時）召喚者 +30。

#### SK-27 `DeadSummonerGainsNothing`
- **準備**：英雄 `10 HP` 召喚史萊姆；敵人 STR `200`。
- **步驟與預期**：敵人先打死英雄（`isDead()`）→ 再打死史萊姆（`isDead()`）→ 英雄 HP 仍為 `0`
- **通過標準**：召喚者已死亡時不給 +30。

### 3.8 自爆（D34）

#### SK-28 `SelfExplosionHitsOthersThenActorDiesLast`
- **目的**：自爆依 T1 → T2 對其他所有人造成 150；自己的死亡訊息**最後**才印，且自己歸零**不印**傷害訊息。
- **依據**：D34（已用 `testcases/self-explosion.out` 驗證）。
- **依據補充**：D47（自殺是 HP 代價，由 `State::decision()` 在施放後支付）。
- **準備**：T1 = 英雄 `999999 HP`（加上自爆，行動 (1)）、A `100 HP`；T2 = A `200 HP`。用 `castThroughFlow(英雄, 1)` 經過完整流程施放。
- **步驟與預期**：輸出的**最後 4 行**必須是：
  1. `[1]英雄 對 [1]A 造成 150 點傷害。`
  2. `[1]A 死亡。`
  3. `[1]英雄 對 [2]A 造成 150 點傷害。`
  4. `[1]英雄 死亡。`

  → 英雄、[1]A 死亡；[2]A HP `50`
- **通過標準**：4 行順序正確，沒有「英雄 對 英雄」的傷害行。

#### SK-29 `SelfExplosionDeathTriggersObservers`
- **目的**：支付自爆的 HP 代價也經過 `lossHp`，所以會觸發觀察者（詛咒獎勵）。
- **準備**：Curser `1000 / 0 / 0`（T2）詛咒英雄 `1000 / 500 / 0`（T1，加上自爆）。
- **步驟與預期**：
  1. `castThroughFlow(英雄, 1)` → 最後一行 `[1]英雄 死亡。`
  2. → Curser HP `1150`（1000 − 150 + 英雄剩餘 MP 300；流程先扣了 200 MP）
- **通過標準**：輸出與 HP 都相符。

#### SK-30 `CurserKilledByExplosionGainsNothing`
- **準備**：Curser `100 HP` 詛咒英雄（加上自爆）；`castThroughFlow(英雄, 1)` 自爆打 Curser（150 傷害）。
- **步驟與預期**：英雄死亡；Curser HP 仍為 `0`
- **通過標準**：施咒者先被炸死，英雄死亡時不給獎勵。

#### SK-44 `SelfExplosionCostsAllHpButAttackItselfDoesNotKill`（2026-10-14 新增）
- **目的**：`SelfExplosion::attack()` 只對目標施放；自殺是 `costHp()` 宣告的代價。
- **依據**：D47。
- **準備**：英雄 `1234 HP`、Slime `1000 HP`。
- **步驟與預期**：
  1. `run(自爆, 英雄, {Slime})` → `["[1]英雄 對 [2]Slime 造成 150 點傷害。"]`
  2. → 英雄 HP 仍為 `1234`
  3. `costHp(英雄)` → `1234`
- **通過標準**：三點都成立。

#### SK-45 `OnlySelfExplosionCostsHp`（2026-10-14 新增）
- **目的**：除了自爆，所有行動的 HP 代價都是 0（預設值）。
- **依據**：D47。
- **步驟與預期**：普通攻擊、水球、火球、自我治療、石化、下毒、召喚、鼓舞、詛咒、一拳攻擊的 `costHp(英雄)` 都是 `0`；`SelfExplosion().costHp(英雄)` 是英雄目前的 HP `777`
- **通過標準**：11 個都相符。

### 3.9 詛咒（Observer：`CurserObserver`，D18、D19）

#### SK-31 `CurseFromSameCurserDoesNotStack`
- **準備**：A、B（T1）、T（T2），全部 `500 / 500 / 50`。
- **步驟與預期**：
  1. A 詛咒 T → 無輸出
  2. B 詛咒 T、A 再詛咒 T
  3. → T 的觀察者 `2` 個：`[0]` 屬於 A、`[1]` 屬於 B；T HP 仍為 `500`
- **通過標準**：同一施咒者只算一次。

#### SK-32 `EachDifferentCurserGainsRemainingMpOnDeath`
- **目的**：需求範例：依序被 A、B、A 詛咒，死亡時剩 60 MP → A、B 各 +60。
- **準備**：A `100 HP`、B `200 HP`（T1）；T `10 / 60 / 0`（T2）。
- **步驟與預期**：A、B、A 依序詛咒 T → A 用水球打死 T → A HP `160`、B HP `260`
- **通過標準**：兩位施咒者各 +60，A 沒有拿到兩次。

#### SK-33 `DeadCurserGainsNothing`
- **準備**：Curser `10 HP` 詛咒 T（`10 / 999 / 100`）；T 用普通攻擊打死 Curser。
- **步驟與預期**：英雄用水球打死 T → Curser HP 仍為 `0`
- **通過標準**：施咒者已死不給獎勵。

#### SK-34 `CursedRoleDyingFromOtherHpLossStillRewardsCurser`
- **目的**：非技能的扣血（中毒）致死，也會觸發詛咒獎勵。
- **依據**：D17（所有 HP 減少都走 `lossHp`）、D47（中毒走 `State::damage`）。
- **準備**：英雄 `300 HP` 詛咒 Slime（`30 / 999 / 0`），Slime 中毒。
- **步驟與預期**：
  1. `slime->takeTurn(…)` → 輸出 `["輪到 [2]Slime (HP: 30, MP: 999, STR: 0, State: 中毒)。", "[2]Slime 死亡。"]`
  2. → 英雄 HP `1299`（300 + 999）
- **通過標準**：輸出與 HP 都相符。

### 3.10 一拳攻擊（Chain of Responsibility，D21–D25）

> 共同準備：除特別註明外，`OnePunch punch(requirementChain())`，英雄 STR 0（傷害完全由規則決定）。

#### SK-35 `OnePunchDeals300WhenTargetHpAtLeast500`
- **步驟與預期**：
  1. Slime1 `601 HP` → `["[1]英雄 對 [2]Slime1 造成 300 點傷害。"]`；HP `301`
  2. Slime2 剛好 `500 HP` → 也是 300 傷害（邊界：≥ 500 成立）
- **通過標準**：兩次都套用規則 1。

#### SK-36 `OnePunchHitsPoisonedOrPetrifiedTargetThreeTimes`
- **準備**：Slime2 `300 HP` 中毒、Slime3 `300 HP` 石化。
- **步驟與預期**：
  1. 打 Slime2 → 3 行 `[1]英雄 對 [2]Slime2 造成 80 點傷害。`；HP `60`
  2. 打 Slime3 → HP `60`
- **通過標準**：每一下各印一行，兩種狀態都套用規則 2。

#### SK-43 `OnePunchStopsHittingOnceTargetDies`（2026-10-14 新增）
- **目的**：中毒 / 石化目標在 80 × 3 的途中死亡時，剩下的幾下不再出手、不再印傷害。
- **依據**：`testcases/one-punch.out` 第 88–90 行（目標在第 2 下死亡，沒有第 3 行）；§7.2 I4。
- **準備**：Slime1 `160 HP`、中毒。
- **步驟與預期**：輸出必須是 3 行：`[1]英雄 對 [2]Slime1 造成 80 點傷害。` × 2、`[2]Slime1 死亡。`；HP `0`
- **通過標準**：沒有第 3 行傷害。

#### SK-37 `OnePunchOnCheeredTargetDeals100AndResetsToNormal`
- **準備**：Slime1 `201 HP`、受到鼓舞。
- **步驟與預期**：輸出 `["[1]英雄 對 [2]Slime1 造成 100 點傷害。"]`；HP `101`；狀態變成 `NormalState`
- **通過標準**：傷害與狀態都相符（規則 3）。

#### SK-38 `OnePunchOnNormalTargetDeals100`
- **準備**：Slime1 `301 HP`、正常狀態。
- **步驟與預期**：輸出 100 傷害一行；HP `201`
- **通過標準**：規則 4。

#### SK-39 `OnePunchUsesOnlyTheFirstMatchingRule`
- **目的**：同時符合多條規則時，只套用第一條。
- **準備**：Slime1 `800 HP` 且中毒（同時符合規則 1、2）。
- **步驟與預期**：只有一行 300 傷害；HP `500`；仍為 `PoisonedState`
- **通過標準**：沒有出現 80 × 3。

#### SK-40 `OnePunchFromCheeredActorAdds50ToEveryHit`
- **目的**：受到鼓舞的行動者用一拳，**每一下**都 +50。
- **依據**：D15。
- **準備**：英雄受到鼓舞；Slime1 `400 HP` 中毒。
- **步驟與預期**：3 行 `[1]英雄 對 [2]Slime1 造成 130 點傷害。`；HP `10`
- **通過標準**：每行都是 130（80 + 50）。

#### SK-41 `OnePunchWithoutHandlersDoesNothing`
- **目的**：`OnePunch` 沒有預設鏈；沒有注入 handler 時不做任何事。
- **依據**：D23。
- **步驟與預期**：`OnePunch punch({})` 打 `601 HP` 的目標 → 沒有輸出、HP 仍為 `601`
- **通過標準**：不崩潰、無輸出、無傷害。

#### SK-42 `OnePunchAcceptsHandlersInjectedByClient`
- **目的**：Client 可以從外部加入新規則（不改 `OnePunch`），且規則可依**狀態以外的屬性**判斷。
- **依據**：需求設計需求 ④；D21、D24。
- **準備**：測試內自訂 `HighMpHandler`（目標 MP ≥ 999 → 造成 1 點傷害），插在鏈的最前面。Mage `900 / 999`、Slime `900 / 0`。
- **步驟與預期**：
  1. 打 Mage → `["[1]英雄 對 [2]Mage 造成 1 點傷害。"]`（新規則先成立）
  2. 打 Slime → `["[1]英雄 對 [2]Slime 造成 300 點傷害。"]`（新規則不成立，往下到規則 1）
- **通過標準**：兩行都相符。

#### SK-46 `OnePunchReleasesItsHandlers`（2026-10-15 新增）
- **目的**：`OnePunch` 擁有 Client 注入的處理鏈，解構時一併釋放。
- **依據**：D49（O1）。
- **準備**：兩個 `TrackedHandler`（解構時計數 +1）。
- **步驟與預期**：
  1. 在區塊內建立 `OnePunch punch({h1, h2})` → 計數 `0`
  2. 離開區塊（`punch` 解構）→ 計數 `2`
- **通過標準**：兩個 handler 都被釋放，且只釋放一次。

---

## 4. RL — `RoleTests.cpp`（`RoleTest`，25 個）

`Role` 本身的責任：屬性、所屬軍隊、MP 檢查、HP 與死亡、觀察者、狀態與回合倒數。

### 4.1 基本屬性與軍隊

#### RL-01 `StartsInNormalStateWithBasicAttackFirst`
- **目的**：新角色的初始狀態、屬性與行動清單。
- **依據**：需求「戰鬥開始時狀態為正常」；D28。
- **準備**：`Role role(100, 50, 10, "A", {火球, 詛咒})`。
- **步驟與預期**：
  1. 狀態是 `NormalState`，且 `getState()->getRole() == &role`（狀態綁定角色）
  2. 行動 `3` 個：`[0]` 是 `BasicAttack`、`[1]` 火球、`[2]` 詛咒
  3. HP `100`、MP `50`、STR `10`、`isDead()` 為假
- **通過標準**：全部相符。

#### RL-02 `DisplayNameUsesTroopId`
- **步驟與預期**：英雄加入 T1、BOSS 加入 T2 → `"[1]英雄"`、`"[2]BOSS"`；`英雄->getTroop() == &t1`
- **通過標準**：前綴依軍隊編號、`getTroop` 指向所屬軍隊。

#### RL-03 `RemoveRoleDetachesRoleFromTroop`
- **目的**：`Troop::removeRole` 會呼叫 `setTroop(nullptr)`，不可丟例外（2026-10-14 修正）。
- **準備**：T1 = 英雄、Ally。
- **步驟與預期**：
  1. `t1.removeRole(Ally)` → **不丟例外**（`EXPECT_NO_THROW`）
  2. → `t1.getRoles() == {英雄}`
  3. → `Ally->getTroop() == nullptr`、`Ally->getDisplayName() == "Ally"`（沒有前綴）
  4. → `英雄->getTroop()` 仍為 `&t1`
  5. 測試最後 `delete Ally`：移出軍隊後擁有權交回呼叫端（D49）
- **通過標準**：移除成功且只影響被移除的角色。

### 4.2 英雄識別（D6）與決策者（D4）

#### RL-04 `OnlyRoleMarkedWithHIsHero`
- **步驟與預期**：
  1. 新建的英雄 → `isHero()` 為假（預設識別字元是 `' '`）
  2. `setIdentity('h')` → `isHero()` 為真、`getIdentity() == 'h'`
  3. 另一個角色 Slime1 → `isHero()` 為假
- **通過標準**：只有標記 `'h'` 的角色是英雄。

#### RL-05 `HoldsItsDecider`
- **步驟與預期**：
  1. 新角色 → `getDecider() == nullptr`
  2. `setDecider(new DummyAction)` → `getDecider()` 回傳同一個物件（之後由 Role 釋放，D49）
  3. `setDecider(nullptr)` → 丟出 `std::invalid_argument`
- **通過標準**：三點都成立。

### 4.3 MP（D9）

#### RL-06 `CheckMpOnlyChecksAndPrintsNothing`
- **目的**：`checkMp` 只回傳是否足夠，不扣 MP、不印訊息（「你缺乏 MP…」由 State 流程印）。
- **準備**：`Role 100 / 60 / 0`；火球 50、水球 50、詛咒 100。
- **步驟與預期**（在 `OutputCapture` 內）：
  1. `checkMp(火球)` → 真；`checkMp(水球)` → 真；`checkMp(詛咒)` → 假；`checkMp(普通攻擊)` → 真
  2. → MP 仍為 `60`
  3. → 沒有任何輸出
- **通過標準**：判斷正確、MP 不變、無輸出。

#### RL-07 `CheckMpBoundaryIsInclusive`
- **目的**：MP 剛好等於花費時可以施放。
- **步驟與預期**：
  1. MP `50`、火球 50 → `checkMp` 為真
  2. `lossMp(1)` 後 MP `49` → `checkMp` 為假
- **通過標準**：邊界為 `>=`。

#### RL-08 `LossAndGainMp`
- **步驟與預期**：MP `500` → `lossMp(50)` → `450` → `gainMp(10)` → `460`
- **通過標準**：數值相符。

### 4.4 HP 與死亡（D14、D17）

#### RL-09 `LossHpAnnouncesDeathOnlyWhenHpReachesZero`
- **目的**：只有 HP 從大於 0 變成 0 的那一刻才印死亡；已死亡再扣不再印。
- **準備**：Slime1 `100 HP`（T2）；用 `hurt()` 經由 `doDamage` 扣血（`lossHp` 不公開，D47）。
- **步驟與預期**：
  1. `hurt(Slime1, 99)` → 只有 `Attacker 對 [2]Slime1 造成 99 點傷害。`；HP `1`
  2. `hurt(Slime1, 1)` → `Attacker 對 [2]Slime1 造成 1 點傷害。`、`[2]Slime1 死亡。`；`isDead()` 為真
  3. `hurt(Slime1, 10)` → 只有傷害行，**沒有**死亡行
- **通過標準**：死亡訊息只在第 2 步出現一次。

#### RL-10 `GainHpHasNoCap`
- **步驟與預期**：HP `500` → `gainHp(150)` → `650`
- **通過標準**：HP 沒有上限（需求未規定上限）。

### 4.5 觀察者（D18）

#### RL-11 `ObserversAreNotifiedOnceInTheOrderTheyWereAdded`
- **準備**：T（`10 HP`）依序加入觀察者 a、b（`RecordingObserver`）。
- **步驟與預期**：`hurt(T, 10)` 兩次 → log 為 `["a:T", "b:T"]`
- **通過標準**：依加入順序、各只通知一次、收到的是死者本身（pull model）。

#### RL-12 `RemovedObserverIsNotNotified`
- **步驟與預期**：加入觀察者後 `removeObserver` → `getObservers()` 為空；T 死亡 → log 為空；移除後擁有權交回呼叫端，測試自己 `delete`（D49）
- **通過標準**：移除後不會被通知。

#### RL-13 `ObserverRewardsAreAppliedAfterDeathMessage`
- **準備**：Curser `100 HP`、Summoner `100 HP`（T1）；T `10 / 70 / 0`（T2）掛上 `CurserObserver(Curser)`、`SummonObserver(Summoner)`。
- **步驟與預期**：
  1. `hurt(T, 10)` → 輸出 `["Attacker 對 [2]T 造成 10 點傷害。", "[2]T 死亡。"]`（獎勵本身不印訊息）
  2. → Curser HP `170`（+ 剩餘 MP 70）、Summoner HP `130`（+30）
- **通過標準**：兩種獎勵都正確。

#### RL-14 `DeadObserverOwnersGetNoReward`
- **準備**：同 RL-13，但 Curser、Summoner 只有 `10 HP`。
- **步驟與預期**：先讓 Curser、Summoner 死亡，再讓 T 死亡 → 兩者 HP 仍為 `0`
- **通過標準**：已死亡的施放者不會被「救活」。

### 4.6 狀態與回合（D10、D11）

#### RL-15 `SetStateReplacesStateAndBindsRole`
- **步驟與預期**：`setState(new PoisonedState())` → 狀態是 `PoisonedState`、`getRole() == &role`、`getRound() == 3`
- **通過標準**：三點都成立。

#### RL-16 `TakeTurnHandsTheBattlefieldToCurrentState`
- **目的**：`Role::takeTurn` 先印「輪到 …」，再把戰場資訊原封不動交給目前狀態的 `decision()`。
- **依據**：D10；§7.2 I6。
- **準備**：英雄 `100 / 0 / 0`（T1）的狀態換成 `RecordingState`（中文名稱設為「測試」）；Slime1 在 T2。
- **步驟與預期**：`英雄->takeTurn(t1.getRoles(), t2.getRoles(), 1)`：
  1. 輸出 → `["輪到 [1]英雄 (HP: 100, MP: 0, STR: 0, State: 測試)。"]`
  2. `calls == 1`、`lastT1 == {英雄}`、`lastT2 == {Slime1}`、`lastSide == 1`
- **通過標準**：印一行「輪到 …」、呼叫一次且參數相同。

#### RL-17 `NormalStateHasNoCountdown`
- **步驟與預期**：正常狀態下 `endThisRound()` 兩次 → 狀態物件不變（同一個指標），仍為 `NormalState`
- **通過標準**：正常狀態不倒數、不被替換。

#### RL-18 `TimedStatesReturnToNormalAfterThreeRoundEnds`
- **目的**：石化、中毒、鼓舞都在 3 次回合結束後換回正常。
- **步驟與預期**：對三種狀態各執行：
  1. `endThisRound()` → round `2`
  2. `endThisRound()` → round `1`，狀態物件仍是原本那個
  3. `endThisRound()` → 換成 `NormalState`，且新狀態 `getRole() == &role`
- **通過標準**：三種狀態都依序倒數並換回正常。

#### RL-19 `OverwrittenStateRestartsCountdown`
- **步驟與預期**：
  1. 中毒後 `endThisRound()` 兩次（剩 1 回合）
  2. 改成石化 → 再 `endThisRound()` 兩次，仍是 `PetrochemicaledState`
  3. 第三次 `endThisRound()` → `NormalState`
- **通過標準**：覆寫後重新從 3 開始算。

#### RL-20 `CheerupBonusEndsWhenStateExpires`
- **準備**：Servant1 `1000 / 0 / 0`（T1）受到鼓舞；Slime1（T2）。
- **步驟與預期**：
  1. 普通攻擊 → `["[1]Servant1 對 [2]Slime1 造成 50 點傷害。"]`
  2. `endThisRound()` 三次
  3. 普通攻擊 → `["[1]Servant1 對 [2]Slime1 造成 0 點傷害。"]`
- **通過標準**：狀態到期後加成消失。

#### RL-21 `SlimeHasTheStatsGivenByRequirement`（2026-10-14 新增）
- **目的**：史萊姆的數值由 `Slime` 自己持有，符合需求的描述。
- **依據**：需求「召喚」（史萊姆擁有 100 HP、0 MP、50 STR，沒有任何技能，初始為正常狀態）；D43、D44。
- **步驟與預期**：`Slime slime;` →
  1. 名稱 `"Slime"`、HP `100`、MP `0`、STR `50`
  2. 行動只有 1 個，且是 `BasicAttack`
  3. 狀態是 `NormalState`；`isHero()` 為假
  4. `getDecider()` 為 `nullptr`（決策者由 `Summon` 裝上，D40）
- **通過標準**：全部成立。

#### RL-22 `DoDamageIsTheOnlyPublicWayToReduceHp`（2026-10-14 新增）
- **目的**：確認技能（或任何外部程式）只能用 `doDamage` 造成傷害，`lossHp` / `damage` 不公開。
- **依據**：D47（O4）。
- **步驟與預期**：用 C++20 concept 檢查「從外部呼叫得到嗎」，再以 `static_assert` 判斷：
  1. `Role::lossHp` → 呼叫不到
  2. `State::damage` → 呼叫不到
  3. `State::doDamage` → 呼叫得到
- **通過標準**：**能編譯**就代表通過（執行時只有 `SUCCEED()`）。若有人把 `lossHp` 或 `damage` 改回 public，整個測試程式會編譯失敗，錯誤訊息是 `Role::lossHp must not be public` / `State::damage must not be public`。

### 4.7 擁有權（D49）

規則：Client（`main` / 測試）擁有兩支 `Troop` → `Troop` 擁有角色 → `Role` 擁有狀態、技能、觀察者、決策者 → `OnePunch` 擁有處理鏈（SK-46）。

#### RL-23 `TroopReleasesItsRolesButNotRemovedOnes`（2026-10-15 新增）
- **目的**：`Troop` 解構時釋放仍在軍隊裡的角色；被 `removeRole` 的角色不釋放。`Role`、`Troop` 不能複製。
- **依據**：D49。
- **準備**：`TrackedRole` Kept、Removed（解構時把各自的旗標設為 `true`）。
- **步驟與預期**：
  1. `static_assert`：`Troop`、`Role` 都不可複製建構、不可複製指定（不成立就**編譯失敗**）
  2. 在區塊內建立 `Troop troop(1)`，加入 Kept、Removed，再 `removeRole(Removed)`
  3. 離開區塊 → Kept 已釋放、Removed **沒有**被釋放
  4. 測試自己 `delete Removed` → Removed 已釋放
- **通過標準**：四點都成立。

#### RL-24 `RoleReleasesItsObserversAndDecider`（2026-10-15 新增）
- **目的**：`Role` 解構時釋放自己的觀察者與決策者（狀態、技能原本就會釋放）。
- **依據**：D49。
- **準備**：在區塊內建立 `Role role`，`addObserver(new TrackedObserver)`、`setDecider(new TrackedAction)`。
- **步驟與預期**：離開區塊 → 觀察者、決策者的旗標都是 `true`
- **通過標準**：兩個都被釋放。

#### RL-25 `ReplacingDeciderReleasesOnlyTheOldOne`（2026-10-15 新增）
- **目的**：換決策者時釋放舊的；設成同一個不能釋放自己。
- **依據**：D49。
- **步驟與預期**：
  1. `setDecider(first)` 兩次 → first **沒有**被釋放、`getDecider() == first`
  2. `setDecider(second)` → first 已釋放、second 沒有
- **通過標準**：兩步都成立（若「設成同一個」也釋放，first 的旗標會變成 `true`，在 ASan 建置下還會出現 heap-use-after-free）。

---

## 5. AI — `AIActionTests.cpp`（`AIActionTest`，11 個）

`AIAction` 的 seed 規則（需求「AI 決策」章節）：

| 呼叫 | 回傳 | seed |
|---|---|---|
| `chooseAction(skills)` | `skills[seed % 行動數]` | + 1 |
| `chooseTargets(candidates, m)`，n > m | `u[s % n] … u[(s + m − 1) % n]` | 全部選完才 + 1 |
| `chooseTargets(candidates, m)`，m = 0 或 n ≤ m | 全部候選 | **不變**（§7.2 I5） |

> 共同準備：fixture 內有 A、B、C 三個角色，`abc = {A, B, C}`。

#### AI-01 `SeedStartsAtZero`
- **步驟與預期**：`AIAction ai;` → `getSeed() == 0`
- **通過標準**：初始值為 0（需求）。

#### AI-02 `ChooseActionPicksSeedModuloActionCountAndIncrementsSeed`
- **準備**：角色有 4 個行動：普通攻擊、火球、水球、詛咒。
- **步驟與預期**：連續 `chooseAction` 6 次 → 依序 `普通攻擊、火球、水球、詛咒、普通攻擊、火球`；seed `6`
- **通過標準**：每次選第 `seed % 4` 個並 +1，超過後繞回。

#### AI-03 `ChooseActionStartsFromGivenSeed`
- **準備**：3 個行動（普通攻擊、火球、水球），`AIAction ai(5)`。
- **步驟與預期**：`chooseAction` → `水球`（5 % 3 = 2）；seed `6`
- **通過標準**：建構子指定的 seed 生效。

#### AI-04 `ChooseActionWithNoActionThrows`
- **步驟與預期**：`chooseAction({})` → 丟 `std::invalid_argument`；seed 仍為 `0`
- **通過標準**：不會除以 0、不會改 seed。

#### AI-05 `ChooseTargetsMatchesRequirementExample`
- **依據**：需求範例：seed = 2、候選 (A, B, C)、選 2 位 → (C, A)，之後 seed = 3。
- **步驟與預期**：`AIAction ai(2)`；`chooseTargets(abc, 2)` → `{C, A}`；seed `3`
- **通過標準**：與需求範例一致（也驗證了 need.md Q1：最後一位是 `(s + m − 1) % n`）。

#### AI-06 `ChooseSingleTargetRotatesWithSeed`
- **步驟與預期**：`chooseTargets(abc, 1)` 連續 4 次 → `A`、`B`、`C`、`A`；seed `4`
- **通過標準**：單選時每次 +1 並繞回。

#### AI-07 `SelectingManyTargetsIncrementsSeedOnlyOnce`
- **準備**：`abcd = {A, B, C, D}`，`AIAction ai(1)`。
- **步驟與預期**：
  1. `chooseTargets(abcd, 3)` → `{B, C, D}`；seed `2`（不是 4）
  2. 再一次 → `{C, D, A}`（繞回開頭）；seed `3`
- **通過標準**：選多位只 +1 一次。

#### AI-08 `CandidatesNotMoreThanMAreAllSelectedWithoutUsingSeed`
- **準備**：`AIAction ai(7)`。
- **步驟與預期**：
  1. `chooseTargets(abc, 3)`（n = m）→ `{A, B, C}`
  2. `chooseTargets({B}, 1)`（n = m = 1）→ `{B}`
  3. `chooseTargets({A, B}, 3)`（n < m，例如鼓舞只剩 2 位友軍）→ `{A, B}`
  4. → seed 仍為 `7`
- **通過標準**：自動全選、依原順序、seed 不變。

#### AI-09 `NoTargetSkillSkipsSelectionWithoutUsingSeed`
- **步驟與預期**：`AIAction ai(4)`；`chooseTargets({}, 0)` → 空；seed 仍為 `4`
- **通過標準**：m = 0（召喚、自我治療）不消耗 seed。

#### AI-10 `RoleUsesAIActionThroughIActionInterface`
- **準備**：角色有普通攻擊、下毒；`setDecider(new AIAction())`（Role 擁有，D49）。
- **步驟與預期**：透過 `role.getDecider()`（型別 `IAction*`）呼叫 `chooseAction` 兩次 → 第一次是 `BasicAttack`、第二次是「下毒」
- **通過標準**：Role 只認得 `IAction` 介面也能使用 AI。

#### AI-11 `ReplaysSlime1FromWaterballAndFireballTestcase`
- **目的**：重現 `testcases/waterball-and-fireball-1v2` 中 `[2]Slime1` 的 4 次行動，證明「自動全選不 +1」才對得上測資。
- **準備**：英雄（唯一的敵人）；Slime1 `200 / 60 / 49`，行動：普通攻擊、火球。測試內用 lambda 模擬一次行動：`chooseAction` → MP 不足就記錄並重選 → `getCandidates` → `chooseTargets`（應自動選英雄）→ `lossMp`。
- **步驟與預期**：模擬 4 次輪到 → 紀錄依序為：
  1. `普通攻擊`（seed 0）
  2. `火球`（seed 1，扣 50 → MP 10）
  3. `普通攻擊`（seed 2）
  4. `MP 不足：火球`（seed 3）→ `普通攻擊`（seed 4）

  → Slime1 MP `10`、seed `5`
- **通過標準**：紀錄 5 筆完全相同；若自動全選也 +1，第 2 筆會變成普通攻擊而失敗。

---

## 6. HA — `HeroActionTests.cpp`（`HeroActionTest`，15 個）

`HeroAction` 從注入的 `std::istream` 讀英雄決策（D37）：

- 每個決策一行，數字以「`, `」隔開（例如 `1`、`0, 1, 2`）；**S1 與 S2 共用同一串輸入**。
- S1：讀一行 → 選第 i 個行動；MP 不足時呼叫端再呼叫一次 → 讀**下一行**。
- S2：n > m 時先印「選擇 m 位目標: (0) … (1) …」（§7.2 I7），再讀一行 m 個數字，依**輸入順序**回傳；m = 0 或 n ≤ m 時**不印、不讀輸入**、直接回傳全部候選。

> 共同準備：fixture 內有 A、B、C（`abc`）與英雄 `300 / 500 / 100`，行動為 (0) 普通攻擊 (1) 火球 (2) 水球。輸入都用 `std::istringstream` 建立。fixture 的 `mute` 把輸出靜音（`chooseTargets` 會印提示）。

### 6.1 S1：選行動

#### HA-01 `ChooseActionReadsIndexFromNextLine`
- **步驟與預期**：輸入 `"2\n"` → `chooseAction` 回傳「水球」
- **通過標準**：數字對應行動索引。

#### HA-02 `EachChooseActionConsumesOneLine`
- **步驟與預期**：輸入 `"1\n0\n2\n"`，連續呼叫 3 次 → `火球、普通攻擊、水球`
- **通過標準**：每次呼叫讀一行、依序前進。

#### HA-03 `InsufficientMpRetryReadsNextLine`
- **依據**：需求：英雄 MP 不足時被要求再次決策（讀 `<英雄決策-i+1>`）。
- **準備**：英雄 `100 / 30 / 10`，行動：普通攻擊、火球（50 MP）；輸入 `"1\n0\n"`。
- **步驟與預期**：模擬 S1 迴圈（`chooseAction` → `checkMp` 不足就再呼叫）→ 紀錄 `["MP 不足：火球", "普通攻擊"]`
- **通過標準**：重選時讀的是第二行。

### 6.2 S2：選目標

#### HA-04 `ChooseTargetsReturnsCandidatesInInputOrder`
- **步驟與預期**：輸入 `"2, 0\n"`；`chooseTargets(abc, 2)` → `{C, A}`
- **通過標準**：依輸入順序，不排序。

#### HA-05 `ChooseSingleTarget`
- **步驟與預期**：輸入 `"1\n"`；`chooseTargets(abc, 1)` → `{B}`
- **通過標準**：相符。

#### HA-06 `AutoSelectionDoesNotConsumeInput`
- **目的**：略過 S2 時不能吃掉下一個決策行（否則之後全部錯位）。
- **依據**：D8；需求「n ≤ m 時略過 S2」。
- **步驟與預期**：輸入只有 `"2\n"`：
  1. `chooseTargets(abc, 3)`（n = m）→ `{A, B, C}`
  2. `chooseTargets({A}, 1)` → `{A}`
  3. `chooseTargets({A, B}, 3)`（n < m）→ `{A, B}`
  4. `chooseTargets({}, 0)` → 空
  5. `chooseAction` → 「水球」（`2` 這行仍在）
- **通過標準**：前 4 步都沒有讀輸入，第 5 步讀到的是第一行。

#### HA-15 `PromptsForTargetsOnlyWhenActuallyChoosing`（2026-10-14 新增）
- **目的**：英雄在 S2 真的要選時印提示；略過 S2 時不印。
- **依據**：需求「輸出格式」：「如果此為英雄的回合」印 `選擇 <m> 位目標: (0) <候選-1> …`；§7.2 I7。
- **準備**：輸入 `"2, 0\n"`；在 `OutputCapture` 內執行。
- **步驟與預期**：
  1. `chooseTargets(abc, 2)` → 印 `選擇 2 位目標: (0) A (1) B (2) C`
  2. `chooseTargets({A, B}, 2)`（n = m）→ 不印
  3. `chooseTargets({}, 0)`（m = 0）→ 不印

  → 全部輸出只有第 1 步那一行
- **通過標準**：輸出剛好 1 行且格式相同（`位目標:` 後是半形冒號加空白）。

### 6.3 輸入格式的容錯

#### HA-07 `AcceptsWindowsLineEndings`
- **目的**：在 Windows 上編輯的測資檔是 `\r\n` 結尾，也要能正確解析。
- **步驟與預期**：輸入 `"1\r\n2, 0\r\n"` → `chooseAction` 為「火球」、`chooseTargets(abc, 2)` 為 `{C, A}`
- **通過標準**：`\r` 不影響解析。

#### HA-08 `SkipsBlankLines`
- **步驟與預期**：輸入 `"\n   \n1\n\n2, 0\n"` → `chooseAction` 為「火球」、`chooseTargets(abc, 2)` 為 `{C, A}`
- **通過標準**：空白行被略過，不會被當成決策。

### 6.4 錯誤處理

#### HA-09 `ThrowsWhenInputRunsOut`
- **步驟與預期**：輸入 `"1\n"`；第一次 `chooseAction` 正常；第二次 → 丟 `std::runtime_error`
- **通過標準**：輸入用完時明確丟例外（不會讀到垃圾值或卡住）。

#### HA-10 `ThrowsOnOutOfRangeIndex`
- **步驟與預期**：輸入 `"3\n0, 5\n"`：
  1. `chooseAction`（只有 0–2）→ 丟 `std::out_of_range`
  2. `chooseTargets(abc, 2)`（索引 5）→ 丟 `std::out_of_range`
- **通過標準**：兩者都丟例外。

#### HA-11 `ThrowsWhenTargetCountDiffersFromM`
- **步驟與預期**：輸入 `"0\n"`；`chooseTargets(abc, 2)` → 丟 `std::invalid_argument`
- **通過標準**：數字個數不等於 m 時丟例外。

### 6.5 與 Role 搭配與測資重現

#### HA-12 `RoleCarriesHeroActionThroughIActionInterface`
- **步驟與預期**：英雄 `setIdentity('h')`、`setDecider(new HeroAction(input))`（Role 擁有，D49），輸入 `"2\n"` → `isHero()` 為真；`getDecider()->chooseAction(...)` 為「水球」
- **通過標準**：英雄透過 `IAction` 介面使用 `HeroAction`（D4、D6）。

#### HA-13 `ReplaysHeroFromWaterballAndFireballTestcase`
- **目的**：重現 `testcases/waterball-and-fireball-1v2.in` 的 7 行英雄決策（`1 / 2 / 1 / 2 / 1 / 2 / 1`）。
- **準備**：Slime1 `200 / 60 / 49`、Slime2 `200 / 200 / 50`；lambda 模擬一次行動：`chooseAction` → `getCandidates(英雄, {英雄}, 敵軍, 1)` → `chooseTargets`。
- **步驟與預期**：

  | 回合 | 敵軍 | 讀到的行 | 結果 |
  |---|---|---|---|
  | 1 | Slime1、Slime2 | `1` | 火球 → Slime1 Slime2（n = m，不讀行） |
  | 2 | Slime1、Slime2 | `2`、`1` | 水球 → Slime2 |
  | 3 | Slime1、Slime2 | `2`、`1` | 水球 → Slime2 |
  | 4 | Slime1 | `2` | 水球 → Slime1（n = m = 1，不讀行） |
  | 5 | Slime1 | `1` | 火球 → Slime1 |

  → 之後再 `chooseAction` 丟 `std::runtime_error`（7 行剛好用完）
- **通過標準**：5 筆紀錄完全相同，且輸入剛好用完。

#### HA-14 `ReplaysHeroFromCheerupTestcase`
- **目的**：重現 `testcases/cheerup.in` 的英雄決策（`1 / 0, 1, 2 / 1 / 2, 3, 4 / 0`），驗證多目標輸入。
- **準備**：英雄 `500 / 10000 / 30`（行動：普通攻擊、鼓舞）；T1 另有 Servant1–5；T2 = Slime1。
- **步驟與預期**：
  1. 第 1 次 → `["鼓舞", "Servant1", "Servant2", "Servant3"]`
  2. 第 2 次 → `["鼓舞", "Servant3", "Servant4", "Servant5"]`
  3. 第 3 次 → `["普通攻擊", "Slime1"]`（只有 1 位敵軍，不讀行）
- **通過標準**：3 次結果與 `cheerup.out` 中英雄的行動一致。

---

## 7. ST — `StateFlowTests.cpp`（`StateFlowTest`，16 個）

`State::decision()` 的行動流程（D10、D12）與 `Role::takeTurn` 印的「輪到 …」（§7.2 I6）。每個測試用 fixture 的 `turn(role)` 讓角色行動一次並收集**完整輸出**，逐行比對。

> 共同準備：fixture 有 `Troop t1{1}`、`t2{2}`；`add(troop, name, hp, mp, str, skills)` 建角色並加入軍隊；`turn(role)` 依角色所屬軍隊決定 actorSide，呼叫 `role->takeTurn(t1.getRoles(), t2.getRoles(), side)`。AI 用 `AIAction`、英雄用 `HeroAction` + `istringstream`。

流程摘要（預設流程，`NormalState` / `CheerupedState` 沿用）：

```
輪到 X (HP: h, MP: m, STR: s, State: 正常)。        ← Role::takeTurn（I6）
選擇行動：(0) 普通攻擊 (1) …                        ← S1，每個角色都印
[你缺乏 MP，不能進行此行動。 → 回到 S1 重印選單]
[選擇 m 位目標: (0) … (1) …]                        ← S2，只有英雄、且 n > m 時（I7）
X 對 a, b 使用了 Z。 / X 攻擊 Y。 / X 使用了 Z。      ← S3：先扣 MP，再 announce
X 對 a 造成 N 點傷害。 [a 死亡。] …                  ← attack
```

### 7.1 「輪到 …」與狀態名稱

#### ST-01 `StatesHaveChineseDisplayNames`
- **目的**：每個狀態有自己的中文名稱（「輪到 …」那一行用），類別名稱 `getName()` 不變。
- **依據**：需求「輸出格式」（狀態只可能是 正常 / 石化 / 中毒 / 受到鼓舞）；§7.2 I8。
- **步驟與預期**：`getDisplayName()` → `正常`、`石化`、`中毒`、`受到鼓舞`；`PoisonedState().getName()` → `"PoisonedState"`
- **通過標準**：5 個比對都成立。

#### ST-02 `TurnStartsWithHeaderShowingStatsAndState`
- **準備**：英雄 `300 / 500 / 100`（T1，AI 決策）、Slime1（T2）。
- **步驟與預期**：`turn(英雄)` 的第一行 → `輪到 [1]英雄 (HP: 300, MP: 500, STR: 100, State: 正常)。`
- **通過標準**：格式完全相同（半形括號與逗號、全形句號）。

### 7.2 預設流程（S1 → S2 → S3）

#### ST-03 `NormalFlowPrintsMenuThenActionAndDamage`
- **準備**：英雄 `300 / 500 / 100`（T1）；Slime1 `200 / 60 / 49`（T2，行動：普通攻擊、火球；`AIAction` seed 0）。
- **步驟與預期**：`turn(Slime1)` 輸出必須是：
  1. `輪到 [2]Slime1 (HP: 200, MP: 60, STR: 49, State: 正常)。`
  2. `選擇行動：(0) 普通攻擊 (1) 火球`
  3. `[2]Slime1 攻擊 [1]英雄。`
  4. `[2]Slime1 對 [1]英雄 造成 49 點傷害。`

  → 英雄 HP `251`、Slime1 MP 仍為 `60`
- **通過標準**：4 行完全相同；目標只有 1 位，AI 自動選，不印目標提示。

#### ST-04 `ChosenActionCostsMpBeforeExecuting`
- **準備**：英雄 `300 / 500 / 100`（行動：普通攻擊、火球、水球；輸入 `"1\n"`）；T2 = Slime1、Slime2。
- **步驟與預期**：輸出依序為「輪到」、`選擇行動：(0) 普通攻擊 (1) 火球 (2) 水球`、`[1]英雄 對 [2]Slime1, [2]Slime2 使用了 火球。`、兩行 50 傷害；英雄 MP `450`
- **通過標準**：S3 扣了 50 MP；火球自動全選，不印目標提示。

#### ST-05 `InsufficientMpPrintsMessageAndAsksAgain`
- **依據**：需求 S1（MP 不足 → 印訊息並重新選擇）；D5、D9。
- **準備**：Slime1 `150 / 10 / 49`（行動：普通攻擊、火球；`AIAction(1)`）。
- **步驟與預期**：輸出必須是 6 行：
  1. `輪到 [2]Slime1 (HP: 150, MP: 10, STR: 49, State: 正常)。`
  2. `選擇行動：(0) 普通攻擊 (1) 火球`（seed 1 → 火球）
  3. `你缺乏 MP，不能進行此行動。`
  4. `選擇行動：(0) 普通攻擊 (1) 火球`（**重印**選單；seed 2 → 普通攻擊）
  5. `[2]Slime1 攻擊 [1]英雄。`
  6. `[2]Slime1 對 [1]英雄 造成 49 點傷害。`

  → MP 仍為 `10`（不合法的行動不扣）、seed `3`、英雄 HP `251`
- **通過標準**：6 行完全相同且 MP、seed 正確。

#### ST-06 `HeroIsPromptedForTargetsOnlyWhenChoosing`
- **依據**：需求「輸出格式」S2；§7.2 I7。
- **準備**：英雄（行動：普通攻擊、水球；輸入 `"1\n1\n1\n"`）；T2 = Slime1、Slime2。
- **步驟與預期**：
  1. 第一次 `turn(英雄)` → 「輪到」、選單、`選擇 1 位目標: (0) [2]Slime1 (1) [2]Slime2`、`[1]英雄 對 [2]Slime2 使用了 水球。`、120 傷害；Slime2 HP `80`
  2. 讓 Slime2 死亡，只給 T2 = `{Slime1}` 再行動一次 → 「輪到」（MP `450`）、選單、`使用了 水球`、120 傷害，**沒有**目標提示行
- **通過標準**：提示只在第 1 次（2 位候選選 1 位）出現。

#### ST-07 `AIChoosesTargetsWithoutPrompt`
- **準備**：T1 = A、B（`500 HP`）；Slime1 `200 / 100 / 0`（行動：普通攻擊、水球；`AIAction(1)`）。
- **步驟與預期**：輸出為「輪到」、選單、`[2]Slime1 對 [1]A 使用了 水球。`、`[2]Slime1 對 [1]A 造成 120 點傷害。`；B HP 仍為 `500`；seed `3`
- **通過標準**：AI 依 seed 選了 A（`u[2 % 2]`），且沒有印目標提示。

#### ST-08 `RoleWithoutDeciderCannotAct`
- **步驟與預期**：沒有設定決策者的英雄（正常狀態）`takeTurn` → 丟 `std::invalid_argument`
- **通過標準**：不會用空指標繼續執行。

### 7.3 各狀態只覆寫不同的部分

#### ST-09 `PetrifiedRoleOnlyPrintsHeader`
- **依據**：需求「石化：略過 S1、S2、S3，仍要印出『輪到 …』」。
- **準備**：BOSS `270 / 9999 / 399`（T2，AI）被石化；英雄 `400 HP`。
- **步驟與預期**：輸出只有 `輪到 [2]BOSS (HP: 270, MP: 9999, STR: 399, State: 石化)。`；seed 仍為 `0`；英雄 HP 仍為 `400`
- **通過標準**：一行、沒有問決策者、沒有行動。

#### ST-10 `PetrifiedHeroDoesNotConsumeInput`
- **準備**：英雄（行動：普通攻擊、水球；輸入 `"1\n"`）被石化。
- **步驟與預期**：`turn(英雄)` 只有 1 行；之後直接呼叫 `chooseAction` → 「水球」（`1` 這行還在）
- **通過標準**：石化的英雄不讀輸入（否則後面的決策會全部錯位）。

#### ST-11 `PoisonedRoleLoses30BeforeActing`
- **依據**：需求「中毒：進入 S1 前 HP − 30」；`testcases/poison.out` 印的是扣血前的 HP。
- **準備**：英雄 `1000 / 500 / 0`；Slime1 `120 / 90 / 50`（AI）中毒。
- **步驟與預期**：輸出為：
  1. `輪到 [2]Slime1 (HP: 120, MP: 90, STR: 50, State: 中毒)。`（扣血**前**的 120）
  2. `選擇行動：(0) 普通攻擊`
  3. `[2]Slime1 攻擊 [1]英雄。`
  4. `[2]Slime1 對 [1]英雄 造成 50 點傷害。`

  → Slime1 HP `90`、英雄 HP `950`
- **通過標準**：4 行相同；扣 30 不印傷害訊息。

#### ST-12 `PoisonedRoleDyingCannotAct`
- **準備**：Slime1 `30 / 90 / 50` 中毒。
- **步驟與預期**：輸出只有 `輪到 [2]Slime1 (HP: 30, …, State: 中毒)。`、`[2]Slime1 死亡。`；`isDead()` 為真、seed 仍為 `0`、英雄 HP 仍為 `1000`
- **通過標準**：死亡後不印選單、不行動。

#### ST-13 `PoisonDeathTriggersObservers`
- **準備**：英雄 `300 HP` 詛咒 Slime1（`30 / 70 / 0`），Slime1 中毒。
- **步驟與預期**：`turn(Slime1)` → Slime1 中毒死亡 → 英雄 HP `370`（+ 剩餘 MP 70）
- **通過標準**：中毒致死也會觸發詛咒獎勵（D17）。

#### ST-14 `CheeredRoleUsesDefaultFlowWithBonus`
- **準備**：Servant1 `1000 / 0 / 0`（AI）受到鼓舞；Slime1 `500 HP`。
- **步驟與預期**：輸出為 `輪到 [1]Servant1 (…, State: 受到鼓舞)。`、`選擇行動：(0) 普通攻擊`、`[1]Servant1 攻擊 [2]Slime1。`、`[1]Servant1 對 [2]Slime1 造成 50 點傷害。`；Slime1 HP `450`
- **通過標準**：走預設流程、傷害 +50。

### 7.4 經過流程的特殊技能

#### ST-15 `SummonedSlimeActsWithItsOwnAI`
- **依據**：需求「召喚的史萊姆本回合就能行動」；D40。
- **準備**：英雄 `500 / 10000 / 30`（行動：普通攻擊、召喚；輸入 `"1\n"`）；敵人 Slime1 `1000 / 0 / 99`。
- **步驟與預期**：
  1. `turn(英雄)` → 「輪到」、`選擇行動：(0) 普通攻擊 (1) 召喚`、`[1]英雄 使用了 召喚。`；英雄 MP `9850`；T1 人數 `2`
  2. `turn(新的史萊姆)` → `輪到 [1]Slime (HP: 100, MP: 0, STR: 50, State: 正常)。`、`選擇行動：(0) 普通攻擊`、`[1]Slime 攻擊 [2]Slime1。`、50 傷害；敵人 HP `950`
- **通過標準**：史萊姆用 `Summon` 給的 AI 正常行動。

#### ST-16 `SelfExplosionThroughFlow`
- **準備**：英雄 `500 / 200 / 0`（行動：普通攻擊、自爆；輸入 `"1\n"`）；T2 = A `100 HP`、B `300 HP`。
- **步驟與預期**：輸出 7 行：「輪到」、`選擇行動：(0) 普通攻擊 (1) 自爆`、`[1]英雄 對 [2]A, [2]B 使用了 自爆。`、`[1]英雄 對 [2]A 造成 150 點傷害。`、`[2]A 死亡。`、`[1]英雄 對 [2]B 造成 150 點傷害。`、`[1]英雄 死亡。`；英雄 MP `0`、A 死亡、B HP `150`
- **通過標準**：先扣 MP、行動訊息列出所有目標、自己的死亡最後印。

---

## 8. RP — `TestcaseReplayTests.cpp`（`AllTestcases/TestcaseReplayTest` 10 個 + `TestcaseListTest` 1 個）

用 `testcases/` 的 10 組 `.in` 跑**整場遊戲**，輸出與 `.out` **逐行**比對（D35–D39）。走的是正式流程，與主程式 `RPGGAME <測資.in>` 相同：

```
ifstream in("testcases/<名稱>.in")
RPGSetup setup = RPG_parser::parse(in)        // 讀兩軍，串流停在第一行英雄決策
setup.hero->setDecider(new HeroAction(in))   // 同一個串流：剩下的行就是英雄決策；由 Role 釋放（D49）
RPG rpg; rpg.GameStart(t1, t2); rpg.GameEnd() // 在 OutputCapture 內，收集所有輸出（含「你獲勝了！」）
delete setup.t1; delete setup.t2               // Client 擁有兩軍，角色由 Troop 一併釋放（D49）
```

### 8.1 每一組的流程與通過標準

**流程**（10 組都一樣）：

1. 確認 `testcases/<名稱>.in`、`<名稱>.out` 都存在；不存在 → `ASSERT` 失敗並印出路徑（測資目錄由 `__FILE__` 推得：`test/` 的上一層 `testcases/`）。
2. 讀 `.out`：去掉行尾 `\r`（測資檔是 Windows 換行）與檔尾空行。
3. 依上面的流程跑整場並收集輸出。
4. 若輸出與 `.out` 不同：把實際輸出寫到「測試執行時的目前目錄」下的 `<名稱>.actual.txt`（Windows 自動執行時是 `build/bin/`），可直接用 diff 對照。
5. 從第 1 行開始逐行比對；第一個不同的行**立即停止**，報告「`<名稱>.out 第 N 行不同`」與兩邊的內容。
6. 最後比對行數。

**通過標準**：每一行都相同（包含最後一行「你獲勝了！」/「你失敗了！」），且行數相同。

| # | 測試名稱（`…/OutputMatchesExpectedFile/<參數>`） | `.out` 行數 | 這組主要驗證 |
|---|---|---|---|
| RP-01 | `cheerup` | 70 | 鼓舞選 3 位友軍（英雄輸入 `0, 1, 2`）、+50、STR 0 印「造成 0 點傷害」 |
| RP-02 | `curse` | 75 | 兩位施咒者在受詛咒者死亡時各自獲得剩餘 MP、MP 不足重選 |
| RP-03 | `one-punch` | 106 | 一拳 4 條規則、**目標死亡後停止連擊**（I4） |
| RP-04 | `only-basic-attack` | 82 | 基本流程、英雄選目標的提示 |
| RP-05 | `petrochemical` | 64 | 石化只印「輪到」、3 回合後恢復 |
| RP-06 | `poison` | 83 | 中毒先扣 30（「輪到」印扣血前的 HP）、中毒致死不行動 |
| RP-07 | `self-explosion` | 41 | 自爆目標順序 T1 → T2、自己最後死亡 |
| RP-08 | `self-healing` | 84 | 自我治療、MP 不足重選 |
| RP-09 | `summon` | 128 | 史萊姆加入隊尾且本回合行動、死亡時召喚者 +30 |
| RP-10 | `waterball-and-fireball-1v2` | 52 | 需求範例；AI 的 seed、MP 不足重選 |

#### RP-11 `TestcaseListTest.EveryInputFileIsReplayed`
- **目的**：確認上表列的就是 `testcases/` 裡**全部**的 `.in`；之後新增測資卻忘了加進 `INSTANTIATE_TEST_SUITE_P` 時會失敗。
- **步驟與預期**：列出 `testcases/*.in` 的檔名（不含副檔名）並排序 → 等於上表 10 個名稱。
- **通過標準**：兩個清單完全相同。

---

## 9. PA — `ParserTests.cpp`（`ParserTest`，8 個）

Client 端的 `RPG_parser`（D26、D36，§7.2 I10）。多數測試共用下面這段輸入（`kInput`）：

```
#軍隊-1-開始
英雄 300 500 100 火球 水球
Ally 100 0 10
#軍隊-1-結束
#軍隊-2-開始
攻擊力超強的BOSS 270 9999 399 石化 自爆
#軍隊-2-結束
1
0, 1
```

#### PA-01 `ParsesBothTroops`
- **步驟與預期**：`parse(kInput)` →
  1. `t1->getId() == 1`、`t2->getId() == 2`；T1 有 2 位、T2 有 1 位
  2. 英雄：`[1]英雄`、`300 / 500 / 100`、行動 `普通攻擊、火球、水球`
  3. Ally：`[1]Ally`、行動只有 `普通攻擊`
  4. BOSS：`[2]攻擊力超強的BOSS`、`270 / 9999 / 399`、行動 `普通攻擊、石化、自爆`
- **通過標準**：全部相符（普通攻擊由 Role 自動加入，D28）。

#### PA-02 `FirstRoleOfTroop1IsTheHeroAndOthersAreAI`
- **步驟與預期**：`setup.hero` 是 T1 第一位且 `isHero()`；英雄的 `getDecider()` 為 `nullptr`（由呼叫端決定，D37）；Ally、BOSS 不是英雄，決策者都是 `AIAction`，而且是不同的物件
- **通過標準**：全部成立。

#### PA-03 `StopsRightAfterTroop2SoHeroDecisionsRemain`
- **步驟與預期**：`parse` 之後在同一個串流 `getline` 兩次 → `"1"`、`"0, 1"`
- **通過標準**：parser 沒有多讀，英雄決策完整留給 `HeroAction`。

#### PA-04 `AcceptsWindowsLineEndingsAndBlankLines`
- **步驟與預期**：每行以 `\r\n` 結尾、開頭與中間有空行 → 英雄行動 `普通攻擊、火球`；`Slime1` 的名稱沒有殘留 `\r`、STR `49`
- **通過標準**：全部成立。

#### PA-05 `CreatesEveryRequirementSkillByChineseName`
- **步驟與預期**：對 `水球、火球、自我治療、石化、下毒、召喚、自爆、鼓舞、詛咒、一拳攻擊` 各呼叫 `createSkill` → 不是 `nullptr`，且 `getName()` 等於傳入的名稱
- **通過標準**：10 個都成立。

#### PA-06 `OnePunchGetsTheRequirementChain`
- **步驟與預期**：`createSkill("一拳攻擊")` 是 `OnePunch`；打 `600 HP` 的目標 → 輸出 `[1]英雄 對 [2]Slime 造成 300 點傷害。`
- **通過標準**：規則 1 生效，代表處理鏈已依需求順序注入（D21）。

#### PA-07 `UnknownSkillIsRejected`
- **步驟與預期**：`createSkill("隕石")` 與含「隕石」的輸入 `parse` → 都丟 `std::invalid_argument`
- **通過標準**：兩者都丟例外。

#### PA-08 `MalformedInputIsRejected`
- **步驟與預期**：以下 8 種輸入 `parse` 都丟 `std::invalid_argument`：空的、缺少開始標記、軍隊 1 沒有結束、缺少軍隊 2、軍隊 2 沒有結束、HP 不是數字、欄位不足、軍隊 1 沒有角色
- **通過標準**：8 種都丟例外（`SCOPED_TRACE` 會標出是哪一種）。

---

## 10. BT — `BattleTests.cpp`（`BattleTest`，10 個）

`Battle` 的回合迴圈與 `RPG` 的勝負宣告（D1、D6、D11、D20、D30、D31，§7.2 I9）。每個情境都設計成會自然結束；英雄用 `HeroAction` + 固定的輸入，其他角色用 `AIAction`。

> 共同準備：fixture 的 `addHero(hp, mp, str, 決策行, 技能)` 建立英雄（`setIdentity('h')`）加入 T1；`addAI(troop, 名稱, hp, mp, str)` 建立 AI 角色；`runBattle(battle)` 在 `OutputCapture` 內呼叫 `startBattle()`；`turnHeaders(lines)` 只留下「輪到 …」的行，用來檢查順序。

#### BT-01 `RequiresAHero`
- **步驟與預期**：兩軍都只有 AI 角色 → `startBattle()` 丟 `std::invalid_argument`
- **通過標準**：丟例外，而不是用空指標判斷英雄。

#### BT-02 `RejectsMissingTroops`
- **步驟與預期**：`Battle(nullptr, &t2)`、`Battle(&t1, nullptr)` → 都丟 `std::invalid_argument`
- **通過標準**：兩者都丟例外。

#### BT-03 `EndsAsSoonAsEnemyTroopIsAnnihilated`
- **準備**：英雄 `500 / 0 / 100`（決策 `0`）；Slime1 `100 HP`、STR `999`。
- **步驟與預期**：輸出剛好 5 行：「輪到 [1]英雄 …」、`選擇行動：(0) 普通攻擊`、`[1]英雄 攻擊 [2]Slime1。`、100 傷害、`[2]Slime1 死亡。`；`isHeroAlive()` 為真
- **通過標準**：T2 被殲滅後立即結束，Slime1 沒有輪到。

#### BT-04 `EndsAsSoonAsHeroDiesEvenMidRound`
- **目的**：英雄死亡就結束，即使英雄所在的軍隊還有人活著（不能只檢查殲滅）。
- **準備**：T1 = 英雄 `10 HP`（決策 `0`、`0`）、Ally `1000 HP`；T2 = S1（STR 50，`AIAction(1)` 讓它打英雄）、S2。
- **步驟與預期**：「輪到」依序只有 英雄、Ally、S1；最後一行 `[1]英雄 死亡。`；英雄死亡、Ally 活著、`isHeroAlive()` 為假
- **通過標準**：S2 沒有輪到。

#### BT-05 `TroopOneActsBeforeTroopTwoAndDeadRolesAreSkipped`
- **準備**：英雄 `1000 / 0 / 100`（6 行決策 `0`）；T2 = S1 `100 HP`、S2 `350 HP`（STR 0）。
- **步驟與預期**：
  1. 「輪到」依序為：英雄、S2（350）、英雄、S2（250）、英雄、S2（150）、英雄、S2（50）、英雄 — 第 1 回合英雄打死 S1，之後 S1 不再輪到
  2. `選擇 1 位目標:` 只出現 **1** 次（第 1 回合有 2 位候選；之後 Battle 只給活著的角色，只剩 S2 → 自動選）
- **通過標準**：順序、跳過死者、候選只含活著的角色都成立。

#### BT-06 `SummonedSlimeActsInTheSameRound`
- **準備**：英雄 `1000 / 150 / 0`（行動：普通攻擊、召喚；決策 `1`）；T2 = S1 `50 HP`。
- **步驟與預期**：「輪到」依序為 英雄、`[1]Slime (HP: 100, MP: 0, STR: 50, State: 正常)`；最後一行 `[2]S1 死亡。`
- **通過標準**：史萊姆加入 T1 隊尾，在 T2 之前、同一回合就行動（D20）。

#### BT-07 `TimedStatesCountDownAtEndOfEachRound`
- **準備**：英雄 `1000 / 80 / 1`（行動：普通攻擊、下毒；決策 `1 / 1 / 0 / 0 / 0 / 0`）；Slime1 `94 HP`、STR 0。
- **步驟與預期**：Slime1 的「輪到」依序為：
  1. `HP: 94 … State: 中毒`（第 1 回合被下毒，−30 → 64）
  2. `HP: 63 … State: 中毒`（第 2 回合；英雄下毒 MP 不足改普通攻擊）
  3. `HP: 32 … State: 中毒`（第 3 回合，−30 → 2；回合結束換回正常）
  4. `HP: 1 … State: 正常`（第 4 回合不再扣血）

  → 第 5 回合 Slime1 被英雄打死
- **通過標準**：中毒剛好持續 3 回合（含施加當下的回合，D11），由 Battle 在回合結束倒數。

#### BT-08 `RPGAnnouncesVictoryWhenHeroSurvives`
- **步驟與預期**：同 BT-03 的情境，改用 `RPG::GameStart` + `GameEnd` → 最後一行 `你獲勝了！`，倒數第二行 `[2]Slime1 死亡。`
- **通過標準**：兩行都相符。

#### BT-09 `RPGAnnouncesDefeatWhenHeroDies`
- **準備**：英雄 `10 HP`、STR 0；Slime1 STR 50。
- **步驟與預期**：最後一行 `你失敗了！`，倒數第二行 `[1]英雄 死亡。`
- **通過標準**：兩行都相符。

#### BT-10 `RPGRejectsMissingTroops`
- **步驟與預期**：`GameStart(nullptr, &t2)`、`GameStart(&t1, nullptr)` → 都丟 `std::invalid_argument`
- **通過標準**：兩者都丟例外。

---

## 11. 主程式 `RPGGAME` 的手動驗證

`main.cpp` 沒有單元測試（它只是把 parser、`HeroAction`、`RPG` 接起來，這條路已由 RP 測試覆蓋）；以下是對執行檔本身的檢查，每次改到 `main.cpp` 或 Client 後建議跑一次。

### 11.1 三種用法

| 指令 | 軍隊來源 | 英雄決策來源 | 用途 |
|---|---|---|---|
| `RPGGAME testcases/<名稱>.in` | 檔案 | 同一個檔案 | 重播測資，輸出應與 `<名稱>.out` 相同 |
| `RPGGAME --play testcases/<名稱>.in` | 檔案 | 鍵盤（`std::cin`） | 實際玩：依畫面上的「選擇行動」「選擇 m 位目標」輸入數字（多個以「, 」隔開） |
| `RPGGAME` | 標準輸入 | 標準輸入 | 可用 `RPGGAME < testcases/<名稱>.in` |
| `RPGGAME --help` | — | — | 顯示用法 |

錯誤時（檔案打不開、輸入格式錯誤、未知技能、英雄決策用完）在 stderr 印「錯誤：…」並回傳 **1**；正常結束回傳 **0**。

### 11.2 驗證步驟與通過標準

Linux / macOS / Git Bash（在 `RPGGame/` 底下）：

```bash
for f in testcases/*.in; do
  n=${f%.in}
  ./build/bin/RPGGAME "$f" | diff -q <(sed 's/\r$//' "$n.out") - > /dev/null && echo "PASS $n" || echo "FAIL $n"
done
```

Windows PowerShell（在 `RPGGame/` 底下）：

```powershell
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8   # 讓 PowerShell 用 UTF-8 讀取程式輸出
Get-ChildItem testcases\*.in | ForEach-Object {
  $actual = & .\build\bin\RPGGAME.exe $_.FullName
  $expected = Get-Content ($_.FullName -replace '\.in$', '.out') -Encoding UTF8
  if (Compare-Object $actual $expected) { "FAIL $($_.Name)" } else { "PASS $($_.Name)" }
}
```

| 檢查 | 通過標準 | 2026-10-14 結果 |
|---|---|---|
| 讀測資模式 × 10 組 | 全部 PASS | ✅ |
| 標準輸入模式（`< 測資.in`）× 10 組 | 全部 PASS | ✅ |
| `--play` 模式，把測資的決策行從標準輸入餵入 × 10 組 | 全部 PASS | ✅ |
| 測資轉成 LF 換行 × 10 組 | 全部 PASS | ✅ |
| `--play` 但決策行不足 | 印到停住的地方，stderr「錯誤：HeroAction: no more hero decisions in input」、回傳 1 | ✅ |
| 檔案不存在 | stderr「錯誤：無法開啟檔案 …」、回傳 1 | ✅ |
| 未知技能 | stderr「錯誤：RPG_parser: unknown skill …」、回傳 1 | ✅ |
| 參數錯誤 / `--help` | 印用法；參數錯誤回傳 1、`--help` 回傳 0 | ✅ |
| 記憶體（D49）：AddressSanitizer 建置，上面三種模式 × 10 組，加上未知技能、決策行不足 | 沒有任何 `AddressSanitizer` / `LeakSanitizer` 訊息（無洩漏、無重複釋放） | ✅（2026-10-15） |

AddressSanitizer 建置（Linux / WSL，gcc 或 clang）：

```bash
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS="-fsanitize=address -fno-omit-frame-pointer" -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
cmake --build build-asan
./build-asan/bin/RPGGAME testcases/summon.in > /dev/null   # stderr 沒有輸出 = 通過
```

---

## 12. 測試有效性（Mutation 檢查）

確認測試真的能抓到錯誤：刻意把程式改壞，測試必須失敗（或 crash）；檢查完再還原。

| 被改壞的地方 | 抓到的測試 |
|---|---|
| 鼓舞不加 +50 | SK-22、SK-40、RL-20 |
| 詛咒同一人會疊加 | EX-10、SK-31、SK-32 |
| `lossHp` 已死亡仍重複印死亡、重複通知 | SK-16、RL-09、RL-11 |
| 一拳不停在第一條成立的規則 | EX-04、SK-35、SK-37、SK-39、SK-42 |
| 召喚者不給 +30 | SK-26、RL-13 |
| 施咒者不給剩餘 MP | SK-29、SK-32、SK-34、RL-13 |
| `checkMp` 邊界寫成 `>` | RL-07 |
| `takeTurn` 沒有委派給狀態 | RL-16 |
| `isHero` 判斷錯誤 | RL-04 |
| `removeObserver` 沒有作用 | RL-12 |
| 回合倒數每次減 2 | RL-18、RL-19、RL-20 |
| `Summon` 沒有 `setDecider` | SK-25 |
| AI：自動全選也 +1 | AI-08、AI-09、AI-11 |
| AI：公式寫成 `(s + i + 1) % n` / 每選一位就 +1 | AI-05、AI-06、AI-07 |
| AI：S1 不 +1 | AI-02、AI-03、AI-10、AI-11 |
| AI：`n ≤ m` 寫成 `n < m` | AI-08、AI-11 |
| Hero：`n ≤ m` 寫成 `n < m` | HA-06、HA-13、HA-14 |
| Hero：自動全選也讀一行 | HA-06、HA-13、HA-14 |
| Hero：目標排序（不依輸入順序） | HA-04、HA-07、HA-08 |
| Hero：不檢查數字個數 | HA-11 |
| Hero：不檢查索引範圍（用 `[]` 取代 `at()`） | HA-10 |
| Hero：空白行不略過 | HA-08（測試程式 crash，視同失敗） |
| 一拳：目標死亡後仍繼續打（I4 改回原樣） | SK-43、RP-03 |
| 流程：MP 不足時不重新選擇 / 不印「你缺乏 MP」/ 選單只印一次 | ST-05、RP-02、RP-08、RP-10 |
| 流程：沒有扣 MP | ST-04、ST-06、ST-15、ST-16、RP（8 組） |
| 流程：沒有印行動訊息 / 行動訊息在傷害之後才印 | ST-03–ST-07、ST-11、ST-14–ST-16、RP（10 組） |
| 流程：選單用「, 」分隔 | ST-03–ST-07、ST-15、ST-16、RP（9 組） |
| 石化仍然行動 | ST-09、ST-10、RP-03、RP-05 |
| 中毒不扣 30 | ST-11–ST-13、RP-03、RP-06 |
| 中毒致死仍然行動 / 先行動再扣 30 | ST-12、RP-06 |
| 「輪到 …」在狀態效果之後才印 | RL-16、ST-02–ST-07、ST-11、ST-12、ST-14–ST-16、RP（10 組） |
| 狀態中文名稱錯誤（中毒寫成石化） | ST-01、ST-11、ST-12、RP-03、RP-06 |
| 英雄從不印目標提示 | HA-15、ST-06、RP（6 組） |
| Battle：T2 先於 T1 | BT-03–BT-09、RP（10 組） |
| Battle：每回合開始時就固定人數（召喚的史萊姆不在本回合行動） | BT-06、RP-09 |
| Battle：不跳過死者 | BT-05、RP（6 組） |
| Battle：候選名單包含死者 | BT-05、RP（6 組） |
| Battle：只在回合結束才檢查是否結束 | BT-04、RP-01、RP-02、RP-09 |
| Battle：不檢查英雄死亡（只看殲滅） | BT-04 |
| Battle：回合結束不倒數 | BT-07、RP-05、RP-06 |
| RPG：勝負訊息相反 | BT-08、BT-09、RP（10 組） |
| Parser：英雄沒有標記 `'h'` | PA-02、RP（10 組） |
| Parser：英雄也裝上 AI | PA-02 |
| Parser：讀過 `#軍隊-2-結束` 還繼續讀 | PA-01–PA-04、RP（10 組） |
| Parser：不去掉行尾 `\r` | PA-04、RP（10 組） |
| Parser：一拳處理鏈順序錯誤 | PA-06、RP-03 |
| Parser：不檢查軍隊 1 是否有角色 | PA-08（測試程式 crash，視同失敗） |
| `Slime()` 的 STR 寫錯（50 → 49） | RL-21、SK-23、ST-15、BT-06、RP-09 |
| 流程沒有支付 HP 代價 | SK-28、SK-29、SK-30、ST-16、RP-07 |
| 流程在施放**之前**支付 HP 代價 | SK-28、SK-29、SK-30、ST-16、RP-07 |
| `Skill::costHp` 預設改成全部 HP | SK-45、BT（6 個）、ST（8 個）、RP（9 組） |
| `Role::lossHp` 改回 public | RL-22（**編譯失敗**：`Role::lossHp must not be public`） |
| `State::damage` 改回 public | RL-22（**編譯失敗**：`State::damage must not be public`） |
| `Troop` 解構時不釋放角色 | RL-23 |
| `Role` 解構時不釋放決策者 | RL-24 |
| `Role` 解構時不釋放觀察者 | RL-24 |
| `setDecider` 設成同一個決策者也釋放 | RL-25（ASan 建置下為 heap-use-after-free） |
| `OnePunch` 解構時不釋放處理鏈 | SK-46 |

| `CompositeOutput` 不套用 `render` | OU-04 |
| `CompositeOutput` 解構時不釋放子節點 | OU-05 |
| `io::setOutput` 不回傳先前的輸出 | OU-06 |
| 模組某處改回直接寫 `std::cout`（例：死亡訊息） | 27 個（RP 10 組、ST、SK、RL、BT…）：`OutputCapture` 收不到 |

> 最後一次全部重跑：2026-10-15，上表每一列都至少有一個測試失敗；還原後 160 個全部通過。

---

## 13. 尚未涵蓋

| 範圍 | 原因 / 現況 |
|---|---|
| `main.cpp` 的單元測試 | 只負責把 parser、`HeroAction`、`RPG` 接起來，這條路已由 RP 覆蓋；執行檔本身用 §11 手動驗證 |
| Windows 主控台以鍵盤輸入中文（不帶參數、軍隊從鍵盤輸入） | 已設定 `SetConsoleCP(CP_UTF8)`，但各版本 Windows 主控台的行為不同，沒有自動測試；建議用 `--play <測資.in>`（軍隊從檔案讀，只需要輸入數字） |
| 物件釋放（記憶體） | 擁有權已定義（D49），RL-23–25、SK-46 檢查「誰釋放誰」；有沒有洩漏不在單元測試裡判斷，改用 AddressSanitizer 手動檢查（§11.2）。Anthony 原本的 `ExampleTests.cpp` 直接 `new` 技能與軍隊而沒有釋放，在 ASan 下會回報測試本身的洩漏（保留原樣，不影響主程式） |

---

## 14. OU — `OutputTests.cpp`（`OutputTest`，7 個，2026-10-15 新增）

`include/utils/Output.hpp` 的輸出小工具（D50）：模組只寫 `io::output().write(一整行)`；Leaf 決定輸出到哪，`CompositeOutput` 決定渲染；Client 用 `io::setOutput` 組裝。fixture 的 `TearDown` 一律 `setOutput(nullptr)` 還原成預設，避免影響其他測試。

| 工具 | 用途 |
|---|---|
| `PrefixOutput` | 測試用的 `CompositeOutput` 子類別：`render` 在每行前加上 tag（示範「Composite 決定渲染」） |
| `TrackedOutput` | 解構時計數 +1，確認 Composite 釋放子節點 |

#### OU-01 `ConsoleOutputWritesLineToCout`
- **目的**：`ConsoleOutput` 把一行寫到 `std::cout` 並換行。
- **步驟與預期**：暫時把 `std::cout` 導向字串（只有測 `ConsoleOutput` 本身才碰 `std::cout`）→ `write("輪到 [1]英雄")` → 收到 `"輪到 [1]英雄\n"`
- **通過標準**：內容與換行都相符。

#### OU-02 `StreamOutputWritesLineToGivenStream`
- **步驟與預期**：`StreamOutput(ostringstream)` 寫 `"a"`、`"b"` → 串流內容 `"a\nb\n"`
- **通過標準**：依序寫入、每行換行。

#### OU-03 `CompositeForwardsSameLineToAllChildrenInOrder`
- **準備**：`CompositeOutput({StreamOutput(first), StreamOutput(second)})`。
- **步驟與預期**：`write("[2]Slime1 死亡。")` → 兩個串流都收到同一行
- **通過標準**：每個子節點都收到，內容不變（預設 `render` 原樣輸出）。

#### OU-04 `NestedCompositesRenderEachBranchIndependently`
- **目的**：渲染只影響該 Composite 底下的子節點（巢狀組合 = 不同分支不同渲染）。
- **準備**：根 `CompositeOutput`（原樣）底下掛 `StreamOutput(plain)` 與 `PrefixOutput("[log] ", {StreamOutput(logged)})`。
- **步驟與預期**：`write("你獲勝了！")` → plain 收到 `"你獲勝了！\n"`、logged 收到 `"[log] 你獲勝了！\n"`
- **通過標準**：兩個分支各自正確。

#### OU-05 `CompositeReleasesItsChildren`
- **步驟與預期**：區塊內建立掛兩個 `TrackedOutput` 的 `CompositeOutput` → 計數 `0`；離開區塊 → 計數 `2`
- **通過標準**：子節點由 Composite 釋放，且只釋放一次（比照 D49）。

#### OU-06 `DefaultIsConsoleAndSetOutputReturnsPreviousForRestore`
- **步驟與預期**：
  1. 未設定 → `io::output()` 是 `ConsoleOutput`
  2. `setOutput(&A)` 回傳 `nullptr`；`setOutput(&B)` 回傳 `&A`；寫 `"x"` → 進 B
  3. `setOutput(&A)` 回傳 `&B`（還原）；寫 `"y"` → 進 A
  4. `setOutput(nullptr)` → 回到 `ConsoleOutput`
- **通過標準**：A 只有 `"y"`、B 只有 `"x"`，四步都成立。

#### OU-07 `ModuleWritesOnlyThroughCurrentOutput`
- **目的**：模組的輸出全部經由 `io::output()`，完全不碰 `std::cout`。
- **準備**：A（T1）、B（T2，`10 HP`）；`setOutput(StreamOutput(captured))`，同時把 `std::cout` 導向另一個字串。
- **步驟與預期**：A 的狀態 `doDamage(B, 10)` → captured = `"[1]A 對 [2]B 造成 10 點傷害。\n[2]B 死亡。\n"`；`std::cout` 收到空字串
- **通過標準**：兩點都成立。
