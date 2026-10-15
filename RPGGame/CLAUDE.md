# RPGGame — 協作指引（給 Claude）

這個資料夾是 Anthony 練習 **架構設計** 的 RPG 回合制戰鬥專案（C++20 / CMake / GoogleTest）。
需求表：[`need/need.md`](need/need.md)（原文：[`need/need.txt`](need/need.txt)；以原文為準）　目前類別圖與循序圖：[`diagrams.md`](diagrams.md)

---

## 1. 合作規則

**先遵守根目錄的 [`../CLAUDE.md`](../CLAUDE.md)**（合作流程、提示階梯、不可以做的事）。以下是本專案的補充。

### 1.1 本專案的特殊情況
- RPGGame 在建立這套流程**之前就已經有第一版設計與程式**，所以本專案是「回頭 review 既有設計」，從 §4 的待討論問題開始，而不是從 OOA 從頭開始。
- Anthony 之後會上傳**他自己畫的設計圖**，那才是設計的依據。[`diagrams.md`](diagrams.md) 已於 2026-10-12 依 D1–D39 改畫成**決定後的設計**；2026-10-14 起已實作的部分改用程式實際名稱，類別圖拆成 6 張並標出數量與依賴，各部分以 ✅ / ⬜ 標示是否已實作；與 Anthony 自己的圖不一致時以他的圖為準，並先問他。
- 討論後若 Anthony 決定修改設計，才依他的決定更新 `diagrams.md`。

### 1.2 實作
- **目前階段：實作中（2026-10-13 起）**。Anthony 決定本專案的演算法都不自己寫，由 Claude 實作。**原則：Anthony 原本寫好、能用的程式照原本的保留，只改設計決策要求變動的地方，不重寫**。2026-10-14 起全部實作完成（技能、Role、Observer、決策者、State 流程、`Battle`、`RPG`、parser、`main.cpp`，見 §7）。
- 實作階段：一般、簡單的邏輯由 Claude 直接實作；Anthony 會指定**他要自己動手**的區塊，這些區塊 Claude 只講概念與步驟、寫框架（宣告、簽名、空本體 + `// TODO:`），寫完再 review。

### 1.3 紀錄
- Anthony 做出決定後，記到「§5 設計決策紀錄」。
- §4 中討論完的問題把狀態改成 ✅ 並附決策編號，不要刪除。

---

## 2. 需求重點（摘要，細節以 need.txt 原文為準；need.md 文末有〈需求疑問〉）

| 主題 | 重點 |
|---|---|
| 戰鬥流程 | 每回合依 `T1` 再 `T2` 的順序，每位**活著**的角色行動一次；死者跳過 |
| 單次行動 | **S1** 選行動（MP 不足 → 印訊息並重選）→ **S2** 選目標（需要 m 位且候選 n > m 才選，否則自動全選）→ **S3** 扣 MP → 執行 → 更新效果 |
| 結束條件 | 每次 S3 後檢查：英雄死亡 或 任一方被殲滅 |
| 狀態 | 正常 / 石化（跳過 S1–S3）/ 中毒（S1 前 −30 HP，可能因此死亡）/ 受到鼓舞（每個造成傷害的行動對每位目標 +50）；新狀態覆寫舊狀態並重新計算 3 回合（含當前回合），結束後回正常 |
| 行動 | 普通攻擊 + 10 種技能（水球、火球、自我治療、石化、下毒、召喚、自爆、鼓舞、詛咒、一拳攻擊） |
| 召喚 / 詛咒 | 史萊姆死亡且召喚者活著 → 召喚者 +30 HP；受詛咒者死亡且施咒者活著 → 每位不同施咒者 + 受詛咒者剩餘 MP（同一施咒者不疊加） |
| 一拳攻擊 | 由上而下比對條件，套用第一個符合的效果 |
| AI | 每個 AI 有 `seed`（初始 0）；S1 選第 `seed % 行動數`；S2 選 `u[s%n] … u[(s+m-1)%n]`；**每做完一個決策 seed + 1**；必須完全照規則才能對上測資 |
| 英雄 | 決策來自輸入的每一行（S1 和 S2 共用同一串輸入） |
| **設計需求（OCP）** | ① 可從模組外部擴充新的 AI 實作 ② 可新增或刪除技能類別而不改模組程式碼 ③ 狀態的擴充也要遵守 OCP ④ 新狀態要能把新行為加進一拳攻擊（且一拳攻擊不只看狀態，也可能看其他屬性） |
| 輸出 | 角色名稱帶 `[1]` / `[2]` 前綴；技能、狀態以中文顯示；固定格式的訊息（見 need.txt「輸出格式」） |

---

## 3. 目前程式快照（2026-10-14，全部實作完成；10 組測資整場輸出一致）

| 區塊 | 現況 |
|---|---|
| `Skill/` | ✅ 保留原本的 `attack()`、`setName` / `setMp` 寫法；名稱改中文（D27）；移除 `targetEnemy` / `targetFriend` 與巨集，改為 `getCandidates()`（D29、D33）；新增 `announce()`（§7 I1）；傷害改走 `actor->getState()->doDamage()`（D16）；`costHp(actor)`：行動的 HP 代價，預設 0、自爆 = 全部 HP（D47） |
| `OnePunchHandler/` | ✅ 移除 `next` 指標，改由 `OnePunch` 以 `vector` 注入（D21、D23）；`handle / match / doHandle` 帶入 `actor`（D22）；用 `dynamic_cast` 判斷狀態（D25）；`OnePunch` 擁有處理鏈，解構時釋放（D49） |
| `Observer/` | ✅ `UntilDie(Role* dead)`（pull model，D18）；`SummonObserver` +30、`CurserObserver` + 剩餘 MP，施放者已死就不給 |
| `State/` | ✅ `doDamage` / `damage`（D16）、受到鼓舞 +50、計時狀態回合數 3（D11）；移除 `entryState` / `exitState` 裡的除錯輸出；**`State::decision()` 是預設行動流程（S1 → S2 → S3，D10、D12）**，石化覆寫成整段跳過、中毒覆寫成先扣 30 再沿用預設流程；各狀態持有中文名稱 `getDisplayName()`（§7.6）；`damage()` 改為 protected，`decision()` 在施放後支付 `Skill::costHp()`（D47） |
| `Role/` | ✅ `lossHp()`：歸零當下印死亡並通知觀察者（D17）；建立時自動加入普通攻擊（D28）；`getDisplayName()`；`checkMp(Skill*)` 只檢查（D9，取代 `checkActionLossMp`）；`endThisRound()`（D11）；`takeTurn(t1, t2, actorSide)` 交給 `state->decision(...)`（D10）；決策者 `setDecider / getDecider`（D4）；英雄識別 `setIdentity / isHero`（D6）；✅ `Hero` / `AI` 子類別已刪除（D4）；`NonHero` 已刪除、`Slime` 直接繼承 `Role`（D43）並以 `Slime()` 持有需求數值（D44）；`lossHp()` 改為 private、只開放給 `State`（D47）；解構時也釋放觀察者與決策者，`setDecider` 換掉時釋放舊的、禁止複製（D49） |
| `IAction` / `AIAction` / `HeroAction` | ✅ `IAction`：`chooseAction(skills)`、`chooseTargets(candidates, m)`（D4、D5、D7、D8）；`AIAction`：seed 規則（§7.2 I5）；`HeroAction`：從注入的 `istream` 讀英雄決策（D37，§7.5） |
| `Game/` | ✅ `Troop` 新增軍隊編號（輸出前綴）；`Battle::startBattle()` 回合迴圈（D1、D11、D20、D30、D31）、`isHeroAlive()`；`RPG::GameStart()` 啟動戰鬥並印勝負（§7.2 I9）；`RPG::makeAction()`、`Troop::StartBattle()` 已刪除（D42）；`Troop` 擁有角色（含召喚的史萊姆），解構時釋放、禁止複製（D49） |
| Client | ✅ `test/libary/RPG_parser`：解析輸入、技能建造函式（D26、D36，§7.2 I10）；`main.cpp`：讀測資 / `--play` 實際玩 / 標準輸入三種用法（§7.2 I11）；Client 擁有並釋放兩支 `Troop`，英雄的 `HeroAction` 以 `new` 交給 Role；parser 格式錯誤時自行釋放已建立的物件（D49）；`main` 組裝輸出 `CompositeOutput({ConsoleOutput})` 並 `io::setOutput`（D50） |
| `utils/Output.hpp` | ✅ 輸出小工具（D50）：`io::Output` ← `ConsoleOutput`、`StreamOutput`、`CompositeOutput`；模組的 19 處 `std::cout` 全部改成 `io::output().write(...)` |
| 測試 | ✅ `ExampleTests.cpp` 11、`SkillTests.cpp` 46、`RoleTests.cpp` 25、`OutputTests.cpp` 7、`AIActionTests.cpp` 11、`HeroActionTests.cpp` 15、`StateFlowTests.cpp` 16、`BattleTests.cpp` 10、`ParserTests.cpp` 8、`TestcaseReplayTests.cpp` 11（`testcases/` 10 組用正式的 parser + RPG 整場比對，加上測資清單檢查），共 160 個全部通過；主程式 `RPGGAME <測資.in>` 的輸出也與 10 組 `.out` 完全相同。每個測試的流程與通過標準見 [`test/TESTS.md`](test/TESTS.md) |

---

## 4. 設計審查：待討論問題

> 基準：**只以 need.txt 為準**（見根目錄 CLAUDE.md §3）。只寫觀察與問題，刻意不寫答案；一次討論一題。
> 「必要」= 不處理就無法滿足需求；「開放問題」= 需求沒要求，可聊但不必改。

### 目前進度（2026-10-12 17:58）
- ✅ A1–A7 已結案（決策 D1–D20）。
- ✅ A8 已結案（決策 D21–D25）。
- ✅ A9 已結案（決策 D26–D28）。
- ✅ A10 已結案（決策 D29–D34）。
- ✅ A11 已結案（決策 D35–D39）。**必要問題 A1–A11 全部結案，架構設計完成。**
- ✅ 2026-10-13 進入實作：技能周邊 + 單元測試完成（§7）。
- ✅ 2026-10-14：全部實作完成，10 組測資整場輸出與 `.out` 一致（§7.7）。
- ✅ 2026-10-15：開放問題 O2–O5 結案（D42–D48）；O1 結案（D49）；O6 結案（D50）。**開放問題 O1–O6 全部結案。**

### 收尾建議順序
主流程是骨架，其他問題都掛在它上面，所以建議依序：
**A1 → A2 → A3 → A4 → A5 → A6 → A7 → A8 → A9 → A10 → A11**

---

### 4.1 必要（有需求依據）

#### A1. 一次行動（S1 → S2 → S3）由誰負責？
- **需求依據**：遊戲流程 2.2、2.3（S1/S2/S3 的順序、MP 不足重選、S3 後檢查結束條件）。
- **觀察**：沒有任何類別擁有這個流程；`RPG::makeAction()`、`Battle::startBattle()` 是空的。
- **思考**：流程中哪些步驟對所有角色都一樣、哪些會因「誰做決策」或「處於什麼狀態」而不同？這種「骨架固定、部分步驟可換」的結構，你在 repo 哪個專案做過？流程放在 `Role`、`Battle` 或新類別，各會讓誰知道太多？
- 狀態：✅ 結案（D1、D2）；「狀態到期由誰換回正常」移到 A4

#### A2. 英雄與 AI 的決策要怎麼接上 S1 / S2？
- **需求依據**：設計需求 ①（可從外部擴充新的 AI）、AI 決策章節（seed 規則）、輸入格式（英雄決策來自輸入行，S1 與 S2 共用）、召喚（史萊姆由 AI 操控）。
- **觀察**：`AI` 是 `Role` 子類別並持有 `seed`；`IAction::action()` 沒有參數且與 `AI` 無關；召喚的 `Slime` 繼承 `NonHero` 而非 `AI`；英雄的輸入來源沒有對應類別。
- **思考**：一個角色要做幾「種」決策？你的介面能表達嗎？新增一種 AI 時要改哪些檔案、會不會動到 `Role` 的繼承樹？召喚出來的史萊姆要怎麼拿到 AI 決策能力？
- 狀態：✅ 結案（D4–D8）

#### A3. MP 的「檢查」與「扣除」
- **需求依據**：S1（MP 不足 → 印「你缺乏 MP，不能進行此行動。」並重選）、S3（選完目標後才扣 MP）。
- **觀察**：`Role::checkActionLossMp()` 同時檢查、扣除，並印英文訊息。
- **思考**：這一個函式能同時對上 S1 與 S3 兩個時間點嗎？
- 狀態：✅ 結案（D9）

#### A4. 狀態需要在哪些時間點介入？
- **需求依據**：角色狀態章節（石化跳過 S1–S3、中毒在 S1 前扣 30、鼓舞加傷害、3 回合含當前回合、覆寫重算、到期回正常）；設計需求 ③（狀態擴充要遵守 OCP）。
- **觀察**：`State` 只有 `decision()`（全為 stub）；狀態用預設建構子建立，`Role::setState()` 沒有 `setRole()`，狀態物件拿不到角色。
- **思考**：把一回合的時間軸畫出來，標出三種狀態各自介入的點，`State` 需要幾個 hook？「3 回合含當前回合」在什麼時間點倒數？到期換回正常時由誰換、原本的狀態物件此時會不會已被 `delete`？
- 狀態：✅ 結案（D10–D12）；鼓舞的 +50 移到 A5

#### A5. 鼓舞的 +50 傷害與傷害輸出
- **需求依據**：受到鼓舞（每個造成傷害的行動、每位被傷害者 +50）；設計需求 ②③（新增技能 / 狀態不改模組）；輸出格式（每次傷害一行、死亡再一行）。
- **觀察**：每個技能在 `attack()` 內自己呼叫 `target->damage(n)`；`Role::damage(int)` 看不到是誰造成的傷害。
- **思考**：照現在寫法，加上鼓舞效果要改幾個檔案？「行動者對目標造成傷害」有沒有唯一的通道？那個通道需要知道哪些資訊？
- 狀態：✅ 結案（D13–D17）

#### A6. 死亡事件與觀察者（召喚、詛咒）
- **需求依據**：召喚（史萊姆死亡且召喚者活著 → +30 HP）、詛咒（受詛咒者死亡且施咒者活著 → + 剩餘 MP；同一施咒者不疊加）；中毒、自爆也會造成死亡。
- **觀察**：`Role::damage()` 不會觸發 `notifyObservers()`，目前沒有地方呼叫它；`UntilDie()` 沒有參數，但詛咒需要死者的剩餘 MP；`Curse` 判斷「是否已被同一人詛咒」時，走訪的是所有種類的 observer。
- **思考**：通知要帶什麼資料（push / pull）？每一條死亡路徑都會通知到嗎？「不疊加」由誰判斷最自然？
- 狀態：✅ 結案（D14、D17–D19）

#### A7. 回合中有角色加入或死亡時的輪流順序
- **需求依據**：遊戲流程 2.2（死者不輪到）、召喚（史萊姆加入隊尾且**此回合**就能行動）。
- **觀察**：`Summon` 在行動中呼叫 `troop->addRole(slime)`。
- **思考**：`Battle` 走訪軍隊的同時有人加入，結果取決於 `getRoles()` 回傳副本還是參考——兩種情況各會怎樣？哪一種符合「此回合就能行動」？
- 狀態：✅ 結案（D20）

#### A8. 一拳攻擊能否從外部擴充
- **需求依據**：設計需求 ② 的補充（新狀態要能把新行為加進一拳攻擊；一拳也可能依其他屬性判斷）。
- **觀察**：處理鏈寫死在 `OnePunch` 建構子；handler 用 `getState()->getName() == "PoisonedState"` 字串比對。
- **思考**：新增一個狀態 + 對應的一拳效果，現在要改哪些檔案？鏈的組裝該由誰負責？字串比對打錯字時，編譯器能幫你嗎？
- 狀態：✅ 結案（D21–D25）

#### A9. 技能名稱 → 技能物件，以及刪除技能檔案
- **需求依據**：設計需求 ②（刪除技能類別檔案不影響模組、可從外部新增技能）；輸入用中文技能名；輸出要印中文技能名。
- **觀察**：沒有「名稱 → `Skill`」的機制；類別內的名稱是英文（`"Fireball"`）。
- **思考**：如果用一個 `if (name == "火球")` 的函式建立技能，刪掉 `Fireball.cpp` 時會怎樣？這個函式屬於模組內部還是 Client？
- 狀態：✅ 結案（D26–D28）

#### A10. 目標規則的表達
- **需求依據**：行動章節（1 位敵軍、所有敵軍、自己、3 位友軍、戰場上所有角色、無）；S2 規則（n > m 才選）；候選順序 T1→T2。
- **觀察**：`targetEnemy` / `targetFriend` 加巨集；`TARGET_FRIEND_SELF` 是 0，但 `BasicAttack` 等也用 `setTargetFriend(0)` 表示「不選友軍」。
- **思考**：「0」代表「不選」還是「選自己」？兩個整數能表達需求列出的 6 種規則嗎？候選名單（活著、排除自己、排序）由誰計算？
- 狀態：✅ 結案（D29–D34）

#### A11. 整場遊戲的輸出驗證
- **需求依據**：「AI 必須完全遵照此規則實作，才能與測資有相符的行為結果」；輸入 / 輸出格式章節。
- **觀察**：只有技能的單元測試，沒有整場「輸入 → 輸出」比對（`BigTwo/test/testSet` 有類似做法）。輸出訊息目前以英文散落在各類別。
- **思考**：要比對整場輸出，英雄決策從哪裡讀才能在測試中替換？輸出要怎麼收集？
- 狀態：✅ 結案（D35–D39）

---

### 4.2 開放問題（超出需求，可聊可不改）

- **O1. 物件擁有權** ✅ 結案（D49）：擁有權順著「誰裝著誰」：Client 擁有兩支 `Troop` → `Troop` 擁有角色 → `Role` 擁有狀態、技能、觀察者、決策者 → `OnePunch` 擁有處理鏈；以裸指標 + 解構子 `delete` 實作，不用 `std::unique_ptr`。
- **O2. `Troop` 與 `Battle` 的責任** ✅ 結案（D42、D45）：`Troop::StartBattle()` 已刪除（`Troop` 不再認識 `Battle`）；`Battle` 的成員改名為陣營 `heroTroop` / `opponentTroop`。
- **O3. 命名與詞彙表** ✅ 結案（D46）：維持 `Skill` / `attack()` 命名，`attack` 意指「施放行動」，已在 `Skill.hpp` 註明。
- **O4. 防止技能繞過傷害通道** ✅ 結案（D47）：`lossHp` private、`damage` protected，技能只能用 `doDamage`；自爆的自殺改為 `costHp()` 由流程支付；`RoleTests` 以 static_assert 在編譯期檢查。
- **O5. 技能名稱重複定義** ✅ 結案（D48）：維持現狀，名稱在 Client 的建造函式與技能本身各寫一次；兩邊一致由 `ParserTest.CreatesEveryRequirementSkillByChineseName`（PA-05）把關。日後有需求再補名稱 → 建立技能的 factory mapping。
- **O6. 輸出目的地可替換** ✅ 結案（D50）：模組改寫 `io::output()`（`include/utils/Output.hpp`），輸出用 Composite 組裝：Leaf 決定輸出到哪、Composite 決定渲染；Client 以 `io::setOutput` 更換，測試不再需要 `rdbuf`。

## 5. 設計決策紀錄

| # | 日期 | 對應問題（A# / O#） | 決定 | 理由 / 取捨 |
|---|---|---|---|---|
| D1 | 2026-10-12 | A1 | **流程**：Troop 註冊在 `RPG`；`Battle` 是兩個 `Troop` 之間的**關聯類別**，負責依 T1 → T2 輪流活著的角色、知道英雄是誰、判斷是否結束，並把結果回報給 RPG。目前一個 RPG 只跑一場 Battle。 | 對應詞彙表「戰鬥 = 兩軍對戰直到一方殲滅」；不為多場戰鬥預先設計 |
| D2 | 2026-10-12 | A1 | **一次行動的骨架（Template Method）**（原放在 `Role`，D10 後改由 State 主導）：狀態前置效果 → S1 → MP 檢查 → 算候選 → S2 → 扣 MP → 執行。只有 **S1 選行動、S2 選目標** 這兩個決策因英雄 / AI 而不同，交給「決策者」處理（與 `IAction` 有關，細節在 A2 討論）。 | 英雄的 S1、S2 共用輸入，AI 的 S1、S2 共用 seed，兩個決策放在同一處 |
| D3 | 2026-10-12 | A1 | **技能 = Role 攜帶的策略（Strategy）**：技能宣告自己的 MP 與目標需求（可選幾位友軍 / 敵軍）；Role 依此算出候選、由決策者選目標；最後呼叫技能的 `doAction(actor, targets)` 執行。後續邏輯（改變狀態、一拳攻擊的責任鏈等）都在技能內部處理。 | 避免在 Role 裡用 switch 依技能種類分支；「目標需求」的表達方式留到 A10 |
| D4 | 2026-10-12 | A2 | **決策者 = Role 持有的 `IAction`（Strategy）**：移除 `Hero` / `AI` 這兩個 Role 子類別，改由 `IAction` 的實作代表控制者（英雄：讀輸入；`AIAction`：依 seed）。`seed` 放在 `AIAction`。召喚的史萊姆可自由綁定任一種 `IAction`。「做決定」與「執行行動（委派給技能的 `doAction`）」是兩件事。 | 符合需求 ①（新 AI 只要新增 `IAction` 實作）；待確認：決策者是否回傳選擇結果給 Role（見 A2 討論） |
| D5 | 2026-10-12 | A2 | **S1：決策者只回傳選了哪個行動（技能）；Role 檢查 MP**，不足就印「你缺乏 MP，不能進行此行動。」並再問決策者一次，直到合法。 | 檢查 / 印訊息 / 重選只寫在 Role 一處，新增 `IAction` 實作也不會漏掉 MP 檢查 |
| D6 | 2026-10-12 | A2 | **英雄識別**：Role 帶一個識別字元（`'h'`）標示英雄，Battle 據此判斷英雄是否死亡。 | 以本需求而言足夠（只有一位英雄）；另一選項「Battle 記住 T1 第一位」也可行，未採用 |
| D7 | 2026-10-12 | A2 | **S2：Role 依技能的目標需求篩出候選名單，連同要選的人數 m 交給決策者**；決策者從中選出 m 位回傳，Role 再把選中的目標交給技能的 `doAction`。 | 篩選規則集中在 Role，英雄 / AI 只負責「挑」**（D29 後：候選改由技能計算，Role 只負責轉交給決策者）** |
| D8 | 2026-10-12 | A2 | **「n ≤ m 自動全選、略過 S2」由決策者判斷**。 | 取捨：每個 `IAction` 實作都要各自處理這條規則（與 D5 把 MP 檢查集中在 Role 的理由相反）；好處是 AI 可就地決定 seed 是否 +1 |
| D9 | 2026-10-12 | A3 | **MP 拆成兩步**：`checkMp` 只做檢查（S1 用）；扣除 MP 由 Role 的骨架在呼叫 `doAction` 之前執行（S3）。 | 對齊需求 S1 / S3 的時間點；程式碼留到實作階段調整（目前仍是 `checkActionLossMp`） |
| D10 | 2026-10-12 | A4 | **狀態主導整段行動流程（State pattern，方案 b）**：Role 持有 State，輪到角色時由 State 接手整段流程（含問 `IAction`、MP 檢查、選目標、執行）。石化：跳過；中毒：先扣 HP、確認存活再走流程；受到鼓舞：走流程，造成傷害時 +50。 | 理由：需求 ③ 要求狀態擴充遵守 OCP，未來的新狀態可能改變流程順序，若流程固定在 Role 就得改 Role。取捨：固定流程可能在各 State 重複（待確認預設流程放哪）；一拳攻擊依目標狀態判斷，已由 CoR 處理，與本決策無關。**D2 的骨架位置隨本決策調整。** |
| D11 | 2026-10-12 | A4 | **回合數算法**：「含當前回合」= 施加當下的回合算 1 回合（即使目標本回合已行動過）；例：第 1 回合被石化 → 第 1、2、3 回合被跳過，第 4 回合恢復正常。**每回合結束**：Battle 呼叫 `role->endThisRound()`，由 Role 將 state 的回合數 −1，等於 0 時由 **Role** 呼叫 `setState()` 換回正常狀態。 | 對應 need.md Q7 的解讀；由 Role（而非 State 自己）切換狀態，避免 State 在自己的函式內被 delete |
| D12 | 2026-10-12 | A4 | **固定流程寫在 `State` 最上層的抽象類別**（預設實作），各狀態繼承後只覆寫不同的部分（石化：跳過；中毒：先扣 HP 再沿用預設流程）。 | 讓 D10 的方案 b 不必在每個狀態重抄流程；新增狀態預設就有 MP 檢查等步驟 |
| D13（初步） | 2026-10-12 | A5 | **傷害經過行動者的 State 結算**：技能在 `doAction(actor, targets)` 中，透過「行動者目前的 State」提供的傷害函式對目標造成傷害；各狀態可調整傷害（受到鼓舞 +50，正常狀態不加成）。 | 加成由狀態決定，新增會影響傷害的狀態時不必改技能（需求 ③）；待確認：技能是否可能繞過這個函式直接扣血、傷害訊息由誰印 |
| D14 | 2026-10-12 | A5 / A6 | **死亡在 HP 歸零的當下立即處理**（不是整個行動結束後才結算）：印出「<目標> 死亡。」並透過 Observer 通知觀察者（詛咒、召喚）。中毒、自爆造成的死亡同樣會觸發。 | 符合「每位目標受傷後若死亡就緊接著印死亡訊息」；待確認：這個檢查放在哪，才能讓技能傷害、中毒扣血、自爆三條路徑都經過 |
| D15 | 2026-10-12 | A5 | **鼓舞加成的需求解讀**：一拳攻擊的 3 次 80 傷害，每次都 +50；自爆的自殺算一次傷害；輸出的傷害值為加成後的數值。 | 對應 need.md Q8，Anthony 的解讀（之後若測資不符再調整） |
| D16 | 2026-10-12 | A5 | **傷害流程**：技能不回傳傷害值，而是在 `doAction`（或一拳攻擊的 handler）內，**每造成一次傷害就呼叫一次** `actor.state.doDamage(target, n)`（套用行動者狀態的加成，如鼓舞 +50）→ 目標的 `state.damage()`（保留給會影響「受到傷害」的狀態）→ 目標 `lossHp()`。**「X 對 Y 造成 N 點傷害。」由 `actor.state.doDamage()` 印**（唯一同時知道行動者、目標與加成後數值的地方）；目標的 `state.damage()` 只負責轉交 `lossHp()`，不再調整傷害。 | 多目標、一拳 80×3、自爆都能自然表達，每一下各自加成、各印一行；傷害訊息只印一次且為最終數值 |
| D17 | 2026-10-12 | A5 / A6 | **`lossHp()` 是 HP 減少的唯一出口**：扣完立刻檢查 HP ≤ 0 → 印「<角色> 死亡。」→ 通知觀察者。技能傷害、中毒扣血、自爆都必須經過它。 | 確保輸出順序正確（每位目標受傷後緊接死亡訊息），且中毒 / 自爆致死也會觸發詛咒、召喚獎勵 |
| D18 | 2026-10-12 | A6 | **觀察者採 pull model**：死亡時 Role 只把「自己（死者）」交給觀察者，觀察者自行讀取需要的資料（如剩餘 MP），並自行判斷施咒者 / 召喚者是否仍活著。 | 新增其他「死亡時觸發」的效果時不必修改 Role；直接帶資料（push）雖然更簡潔，但會讓 Role 決定要給哪些資料 |
| D19 | 2026-10-12 | A6 | **「同一施咒者不疊加」由 `Curse` 判斷**：Role 只提供自己的 observer 清單，由 `Curse` 從中辨認既有的詛咒並判斷是否為同一施咒者。 | Role 不需要認識「詛咒」；刪除 `Curse` / `CurserObserver` 檔案不影響模組（需求 ②） |
| D20 | 2026-10-12 | A7 | **輪流順序由 `Battle` 負責**：T1 全部輪完再換 T2；用 `while` + 索引 `idx` 走訪，每一圈都重新讀取 Troop 的目前人數（`size`），所以本回合召喚加入隊尾的史萊姆也會輪到；輪到時跳過已死亡的角色。 | range-for 會在開始時存下 `end`，且 `push_back` 可能使 iterator 失效；改用索引可避免。Troop 需提供人數與「第 i 位角色」 |
| D21 | 2026-10-12 | A8 | **一拳攻擊的處理鏈由 Client 組裝後注入 `OnePunch`**：Client（`main.cpp` 等組裝程式碼）依需要的順序把 handler 放好，在 `new OnePunch(...)` 時傳入；`OnePunch` 不在內部寫死鏈。鏈改用 vector / list 依序存放 handler（可取代 `next` 指標），方便插入與刪除。 | 符合「Client 自外部擴充、不改模組程式碼」與 need.md Tip（依賴注入）；新增狀態時只改 Client 的組裝程式碼。取捨：Client 必須自己知道正確順序（由上而下比對）。已排除：在 `OnePunch` / `Skill` / `RPG` / `Battle` 內組鏈（皆屬模組內部）、由新技能自行註冊（技能間互相依賴、時機與順序難控制） |
| D22 | 2026-10-12 | A8 | **handler 介面改為 `handle(Role* actor, Role* target)`**，與技能的 `doAction(actor, targets)` 一致；`OnePunch` 對每位目標各呼叫一次鏈。 | 每次呼叫時傳入 actor，同一個 `OnePunch` 被不同角色共用也沒問題；每一下傷害都能依 D16 走 `actor.state.doDamage(target, n)` |
| D23 | 2026-10-12 | A8 | **`OnePunch` 不提供預設鏈**：需求列出的四條規則也一律由 Client 組好傳入；`OnePunch` 不 include 任何具體狀態或 handler。 | 需求 ②：刪除「下毒」「石化」「鼓舞」等技能與其狀態時，`OnePunch` 仍可編譯、不受影響 |
| D24 | 2026-10-12 | A8 | **具體的 handler 屬於模組外部的擴充**：`HpHandler`、`PoisonPetrochemicalHandler` 等不屬於模組，和它們依賴的狀態一起被加入、一起被刪除；`OnePunch` 只認得抽象的 `OnePunchHandler`。 | 刪除某個狀態時連帶要調整的 handler 是 Client 的責任，不算模組壞掉；若 handler 放在模組內，刪除狀態檔案會讓模組編譯失敗（違反需求 ②） |
| D25 | 2026-10-12 | A8 | **handler 改用型別判斷（如 `dynamic_cast`）辨認目標狀態**，不再用 `getName()` 字串比對。 | 類別名稱打錯會在編譯期失敗；依賴具體 State 不是問題，因為 handler 與其狀態同屬外部擴充（D24） |
| D26 | 2026-10-12 | A9 | **Client 讀檔並建立技能**：由 Client 解析輸入檔的軍隊行，用 Client 端的簡易建造函式把技能名稱（如「火球」）轉成對應的 `Skill` 物件，建好角色與軍隊後再交給 `RPG`。模組不負責「名稱 → 技能」的對應。 | 需求 ②：刪除技能檔案時只需調整 Client 的建造函式，模組不受影響；與 D21 相同的思路（由 Client 組裝） |
| D27 | 2026-10-12 | A9 | **每個技能子類別各自持有自己的中文名稱**（如 `Fireball` 只知道自己叫「火球」），模組輸出時透過 `Skill*` 取得名稱；不在 `Skill` 基底類別建立集中的對照表。英文名稱保留給程式內部（寫 code）使用，不用於輸出。 | 需求 ②：集中的表會列出所有技能，新增 / 刪除技能都得改模組；各自持有則刪檔即消失。輸入名稱與輸出名稱在 Client 與技能各寫一份 → 列為開放問題 O5 |
| D28 | 2026-10-12 | A9 | **普通攻擊是 Role 自帶的行動**：`Role` 建立時自動加入 `BasicAttack`，固定在行動清單第 0 項；Client 只加入輸入檔列出的技能。`BasicAttack` 屬於模組內部。 | 輸入的技能清單不含普通攻擊，但每個角色都有；需求 ② 的「可刪除」指技能，普通攻擊是「行動」而非技能；由 Role 加入可保證它在第 0 項，AI 的 `seed % 行動數` 才對得上測資 |
| D29 | 2026-10-12 | A10 | **候選名單由技能計算（方案 ③）**：Role 問技能「此行動者在此戰場的候選有誰、要選幾位」，技能回傳類似 tuple 的（候選名單, m）；Role 再交給 `IAction` 挑選（n ≤ m 全選，D8），之後扣 MP、呼叫 `doAction`。**調整 D7**：Role 不再依技能描述篩候選。 | 目標規則（數量、敵 / 友 / 自己 / 全場 / 無）隨技能變動，由技能自己決定，新增需要新規則的技能也不必改模組（需求 ②）；同時解決 `(0, 0)` 同時代表「自己」與「無」的問題。算候選是規則、選目標是決策，兩者分開。已排除：① 規則種類 + 人數、② 修正兩個整數的編碼（規則種類寫死在模組） |
| D30 | 2026-10-12 | A10 | **Battle 整理候選的原始資料**：輪到某角色時，Battle 依該角色所屬軍隊整理出「行動者的友軍名單、行動者的敵軍名單」，並在整理時排除死者；名單經 Role → State 固定流程交給技能，技能據此算出（候選, m）（D29）。 | 只有 Battle 同時知道兩軍與行動者屬於哪一軍；每次輪流都要過濾死者，集中在 Battle 一處。同一角色的回合中、S2 之前，只有行動者自己可能死亡（中毒），所以在輪到時過濾即可**（D31 後：改給 T1 / T2 名單，不分友敵）** |
| D31 | 2026-10-12 | A10 | **調整 D30：Battle 改給「T1 名單、T2 名單（皆已排除死者、各自依隊伍順序）＋行動者屬於哪一軍」**，不再整理成友軍 / 敵軍；由技能自行判斷哪一份是友軍、哪一份是敵軍。 | 需求要求候選排序遵守 T1 → T2；照 T1 / T2 給，自爆等「全場」技能的順序天生正確，不會出現 T2 角色施放時變成 T2 → T1 的錯誤。取捨：每個技能都要自己判斷敵友。已排除：a. 友敵 + 旗標、b. 友敵 + 全場名單 |
| D32 | 2026-10-12 | A10 | **共用的敵友判斷放在 `Skill` 抽象父類別**：「從 T1 / T2 找出敵軍」、「找出友軍（不含自己）」等每個技能都會用到的小動作，由 `Skill` 基底類別提供給子類別使用。 | 所需輸入（T1、T2、行動者屬於哪一軍、actor）技能已經全部拿到（D31），不必回頭依賴 Battle；所有技能都繼承 `Skill`，可共用且不重抄。父類別只依賴 `Role`，不依賴具體技能，刪除技能不受影響 |
| D33 | 2026-10-12 | A10 | **「算候選」為 `Skill` 的 virtual 函式，預設實作 = 1 位敵軍**；需要其他規則的技能（火球、自我治療、召喚、自爆、鼓舞）自行覆寫，並呼叫 D32 的共用小函式。 | 「1 位敵軍」使用次數最多（普通攻擊、水球、石化、下毒、詛咒、一拳，共 6 個），這些技能不必覆寫。取捨：新技能忘了覆寫時會默默變成「1 位敵軍」，編譯期不會報錯（未採用純虛擬） |
| D34 | 2026-10-12 | A10 | **自爆的目標不含自己（need.md Q5，解讀甲）**：目標 = 全場其他活著的角色（依 T1 → T2）；輸出「<自己> 對 <其他角色> 使用了 自爆。」、對每位目標各印一行傷害；自己 HP 直接歸零並印「<自己> 死亡。」。**已用 `testcases/self-explosion.out` 驗證**：目標名單不含自己、依 T1 → T2；自己歸零**不印**傷害訊息；「<自己> 死亡。」在所有目標的傷害 / 死亡訊息**之後**才印。 | Anthony 的解讀，測資相符（D15「自殺算一次傷害」對輸出沒有影響） |
| D35 | 2026-10-12 | A11 | **測資放在 `RPGGame/testcases/`（10 組 `.in` / `.out`）並 commit 進 repo**，不照 BigTwo 放 `test/testSet/`。 | 根目錄 `.gitignore` 忽略 `testSet`，放在 `testcases/` 才會被 commit |
| D36 | 2026-10-12 | A11 | **解析 `.in` 沿用 BigTwo 做法**：在 `test/libary/` 放 RPG 專用 parser，把軍隊行建成 `Troop`（技能用 D26 的建造函式、T1 第一位標成英雄 D6），其餘各行為英雄決策。 | D26「Client 讀檔」的落實；測資的英雄名字是「英雄」而非需求寫的「Hero」，D6 用旗標判斷不受影響 |
| D37 | 2026-10-12 | A11 | **英雄的 `IAction` 注入 `std::istream&`**：正式執行傳 `std::cin`，測試傳讀測資檔的 stream。 | 依 D4 只有英雄的 `IAction` 讀輸入，只注入這一處；不照抄 BigTwo 把 `plays` 一路傳遞 / 回傳穿過每一層；S1、S2 共用同一串輸入、MP 不足重選讀下一行都自然成立；`std::istream` 本身即可替換的輸入來源，不另設介面 |
| D38 | 2026-10-12 | A11 | （2026-10-15 已由 D50 取代）**測試時用 `rdbuf` 把 `std::cout` 導向字串收集輸出**，模組內部維持直接寫 `std::cout`。 | 輸出散落在 `doDamage`、`lossHp`、State 流程、技能等多處，注入 `ostream&` 要改整條呼叫鏈的簽名；需求只要求輸出正確，未要求輸出目的地可替換（列為 O6） |
| D39 | 2026-10-12 | A11 | **用 gtest 參數化測試（`TEST_P`）比對**：每組 `.in` / `.out` 一個案例，逐行比對，失敗時報出第一個不同的行號，並把實際輸出寫到 `build/<名稱>.actual.txt` 供 diff。 | 10 組、每組數十到上百行，無法人工比對；一組一案例可直接看出哪個技能出錯 |
| D40 | 2026-10-14 | A2（補充） | **召喚的史萊姆由 AI 操控，但和其他角色一樣「攜帶」決策者**：`Summon` 建出史萊姆後呼叫 `slime->setDecider(new AIAction())`，不把 AI 寫死在 `Slime` 類別裡；每隻史萊姆有自己的 `AIAction`（seed 從 0 開始、互不影響）。 | 需求：英雄以外的角色都由 AI 操控；沿用 D4「Role 持有 `IAction`」的同一套機制。取捨：`Summon`（外部擴充）因此依賴 `AIAction`；依 D41 `AIAction` 屬於模組內部，這是「外部 → 模組」的依賴，方向正確 |
| D41 | 2026-10-14 | 實作後補充（模組邊界） | **`AIAction`、`HeroAction` 與抽象的 `OnePunchHandler` 屬於模組內部**。要擴充時，在模組外部新增實作（新的 AI、新的一拳規則 handler），只依賴它該依賴的介面（`IAction`、`OnePunchHandler`），模組內部不必改動。具體的一拳 handler（`HpHandler` 等）仍是外部擴充（D24）。 | 介面與需求要求的兩種決策者是模組提供的能力；新增實作只往模組方向依賴（需求 ①④），刪除外部的實作不影響模組 |
| D42 | 2026-10-14 | 實作後補充（O2） | **刪除 `RPG::makeAction()` 與 `Troop::StartBattle()`**：一次行動已委派給 `Role::takeTurn` → `State::decision()`（D10），建立與啟動戰鬥已由 `RPG::GameStart()` 負責（D1），這兩個函式不再需要。`Troop` 因此不再認識 `Battle`。 | 該委派的都已委派；留著沒用的入口會讓人誤以為有第二條流程 |
| D43 | 2026-10-14 | 實作後補充（D4 延伸） | **刪除 `NonHero`，`Slime` 改為直接繼承 `Role`**。`Slime` 保留，因為 `Summon` 用它建立召喚的史萊姆。 | 「是不是英雄」由 `Role` 的 identity 判斷（D6），不需要 `NonHero` 這層繼承；`NonHero` 建構子只是重設一次 `NormalState`，`Role` 建構時本來就會設 |
| D44 | 2026-10-14 | 實作後補充（D43 延伸） | **史萊姆的數值由 `Slime` 自己持有**：建構子改為 `Slime()`，內部呼叫 `Role(100, 0, 50, "Slime")`；`Summon` 只寫 `new Slime()`，再裝上觀察者與 `AIAction`。 | 需求對史萊姆的描述（100 HP、0 MP、50 STR、沒有技能）集中在 `Slime`，`Summon` 只負責「召喚」這個動作；與 D27（技能各自持有名稱）同樣的思路。已排除：刪掉 `Slime`、由 `Summon` 直接 `new Role(...)`（史萊姆這個概念只剩一行數字） |
| D45 | 2026-10-14 | O2 | **`Battle` 的兩支軍隊改名為陣營：`heroTroop`（英雄方，T1，先行動）與 `opponentTroop`（對手方，T2）**，取代原本的 `ally` / `enemy`。 | Anthony 認為 `Battle` 應該知道哪一軍是英雄方。不用 `ally` / `enemy`，因為需求詞彙表的「友軍 / 敵軍」是相對於某個角色而言（T2 的角色行動時，T1 是它的敵軍），容易混淆。已排除：維持 `ally` / `enemy`、以輪流順序命名 `t1` / `t2` |
| D46 | 2026-10-14 | O3 | **維持 `Skill` / `attack()` 的命名**：`Skill` 是所有行動（含普通攻擊）的抽象，`attack(actor, targets)` 的意思是「施放這個行動」，不限於造成傷害。只在 `Skill.hpp` 的宣告加上註解說明，不改名。 | Anthony 認為這不是問題：`Skill` 只是用來抽象描述技能，`attack` 當成施放。改名（例如 `cast` / `perform`）要動 11 個技能、測試與文件，換來的只是用詞更貼近詞彙表 |
| D47 | 2026-10-14 | O4 | **技能造成傷害只能走 `doDamage`，由編譯器強制**：`Role::lossHp` 改為 private（`friend class State`）、`State::damage` 改為 protected；中毒改呼叫自己的 `damage(30)`。**自爆的自殺改視為技能的「HP 代價」**：`Skill` 新增 `virtual int costHp(Role* actor) const`（預設 0），`SelfExplosion` 回傳全部 HP；`State::decision()` 在 `attack()` 之後支付（不印傷害訊息，死亡訊息自然排在所有目標之後，D34）。 | Anthony 要求技能的寫法統一、不要多一個 `die()` 入口；自殺與 MP 一樣是施放的代價，由流程支付。代價：`Skill` 多一個 virtual；直接呼叫 `attack()` 的自爆測試改成經過流程 |
| D48 | 2026-10-15 | O5 | **技能名稱維持兩處定義，不改**：輸入名稱留在 Client 的 `RPG_parser::createSkill`（D26），輸出名稱留在各技能的建構子（D27）。 | Anthony 認為不是大問題：兩邊不一致時 PA-05 會失敗；日後若有其他需求（例如技能種類變多、名稱可設定）再補 factory mapping。已排除（目前）：名稱只寫一次的註冊機制 |
| D49 | 2026-10-15 | O1 | **擁有權順著「誰裝著誰」**：Client（`main` / 測試）擁有兩支 `Troop`；`Troop` 擁有加入的角色（含召喚加入的史萊姆），解構時釋放，`removeRole` 交回呼叫端；`Role` 擁有狀態、技能、觀察者與**決策者**，`setDecider` 換掉時釋放舊的；`OnePunch` 擁有注入的處理鏈。英雄的 `HeroAction` 改由 `main` 以 `new` 交給 Role。**以裸指標 + 解構子 `delete` 實作，不用 `std::unique_ptr`**。 | Anthony：結束時由 Troop 自動釋放角色，Role 釋放自己持有的；決策者也歸 Role 擁有（若改由 Client 擁有，召喚途中產生的 `AIAction` 沒人知道要釋放）。`unique_ptr` 主要是讓型別保護記憶體，但需求沒有要求，用 `delete` 改動最小。已排除（目前）：`std::unique_ptr`、決策者由 Client 擁有 |
| D50 | 2026-10-15 | O6 | **輸出改用一個簡單的 Composite 小工具，放在 utils**（`include/utils/Output.hpp`，header-only）：介面 `io::Output::write(一整行)`；**Leaf 決定輸出到哪**（`ConsoleOutput`、`StreamOutput`），**Composite 決定加上什麼渲染**（`CompositeOutput::render()` 預設原樣，先渲染再依序分送；巢狀組合讓不同分支有不同渲染）。**模組透過單一存取點取得**：`io::output()`；Client 用 `io::setOutput()` 組裝 / 更換，未設定時是主控台。取代 D38（測試改用 `setOutput`，不再換 `rdbuf`）。 | Anthony：`std::cout` 寫死目的地、全域格式狀態、只能一個目的地、遊戲輸出與除錯訊息分不開；參考 logframework 的 Exporter / Composite，但只要最簡單的版本。取得方式選單一存取點（B）：改動最小；代價是它仍是全域狀態（只是換成自己定義的介面）。已排除：一路注入 `Output&`（A）、直接引用 logframework（有 Level / 時間戳記，不符合「輸出必須與 .out 一字不差」） |

---

## 6. 建置與測試

```bash
cd RPGGame
cmake -S . -B build
cmake --build build
./build/bin/RPGGAME testcases/poison.in          # 讀測資跑整場（輸出可與 testcases/poison.out 比對）
./build/bin/RPGGAME --play testcases/poison.in   # 實際玩：軍隊來自檔案，英雄決策由鍵盤輸入
./build/bin/RPGGAME < testcases/poison.in        # 全部從標準輸入
./build/bin/SimpleTest                           # 單元測試；Windows (MinGW) build 完會自動執行
cd test && ./run_tests.sh                        # Windows: run_tests.bat
```

---

## 7. 實作紀錄

### 7.1 2026-10-13：技能周邊 + 單元測試
- **範圍**：技能、一拳攻擊（含 handler）、觀察者，以及技能直接用到的 `State` / `Role` / `Troop` 功能。State 流程、`AIAction`、`Battle`、`RPG`、`main.cpp` 維持原本的程式與 TODO。
- **原則**：在 Anthony 原本的程式上做最小修改；原本能用的命名與寫法（`attack()`、`addSkill` / `getSkills`、`setName` / `setMp`、`Slime` 類別、`Curse` 的不疊加判斷、一拳 80 × 3 的迴圈）都保留。
- 只因設計決策而改的：`targetEnemy` / `targetFriend` → `getCandidates()`（D29）、`damage()` → `lossHp()`（D17）、`UntilDie()` → `UntilDie(dead)`（D18）、一拳的 `next` 指標 → 注入的 `vector`（D21–D25）、名稱改中文（D27）、Role 自動加入普通攻擊（D28）。
- 順手修正的錯誤：`Skill` 解構子改為 `virtual`（`Role` 透過 `Skill*` 刪除技能）；`Role` 建構時把 `troop` 初始化為 `nullptr`（原本未初始化）；移除 `State::entryState` / `exitState` 的除錯輸出（會混進遊戲輸出）。
- 單元測試：原本的 `ExampleTests.cpp` 11 個 + 新的 `SkillTests.cpp` 41 個，共 52 個通過；刻意改壞程式（鼓舞不加成、詛咒疊加、死亡重複通知、一拳不停在第一條規則、召喚 / 詛咒不給獎勵）都會被測試抓到。

### 7.2 實作時自行決定、請 Anthony 確認的地方
| # | 內容 | 理由 |
|---|---|---|
| I1 | **S3 的行動訊息由技能的 `announce(actor, targets)` 印**（virtual；預設「X 對 a, b 使用了 Z。」，沒有目標時「X 使用了 Z。」；`BasicAttack` 覆寫成「X 攻擊 Y。」、`SelfHealing` 覆寫成「X 使用了 自我治療。」）。呼叫時機：State 流程在扣 MP 後、`attack` 前（流程尚未實作）。 | 設計討論沒有決定誰印這行；格式隨行動而異，放在技能裡新增技能不必改模組（需求 ②） |
| I2 | **輸出名稱前綴**：`Troop` 記住自己的編號（`Troop(int id)`，預設 1），`Role::getDisplayName()` 回傳「[編號]名稱」。 | 召喚的史萊姆加入哪一軍就自動帶對的前綴 |
| I3 | **`actorSide` 用 `int`（1 = T1、2 = T2）**，與輸出前綴一致。 | 最簡單的表示法 |
| I4 | ~~一拳 80 × 3 沿用原本的迴圈：目標死亡後剩下幾下仍會印傷害~~ → **2026-10-14 修正：目標死亡後就停止**（`PoisonPetrochemicalHandler` 迴圈條件加上 `!target->isDead()`）。 | 原本寫「測資沒有這種情況」是錯的：`testcases/one-punch.out` 第 88–90 行，目標在第 2 下死亡，沒有第 3 行傷害 |
| I5 | **`AIAction` 在 S2 自動全選（m = 0 或 n ≤ m）時 seed 不 + 1**；S2 真的選目標時，選完 m 位才 + 1 一次。 | 需求「每做完一項決策 seed + 1」，自動全選不是 AI 的決策；`waterball-and-fireball-1v2` 中 Slime1 的行動順序（普通攻擊 → 火球 → 普通攻擊 → MP 不足 → 普通攻擊）只有這樣才對得上 |
| I6 | **「輪到 X (HP: …, MP: …, STR: …, State: …)。」由 `Role::takeTurn` 在交給狀態之前印**。 | 石化也要印（需求）；`testcases/poison.out` 印的是中毒扣 30 **之前**的 HP，所以要在狀態效果之前印。放在 Role 而不是各狀態，石化 / 中毒不必各自重印 |
| I7 | **「選擇 m 位目標: (0) … (1) …」由 `HeroAction::chooseTargets` 在真的要選（n > m）時印**；「選擇行動：(0) …」由 `State::decision()` 印、每個角色都印。 | 需求寫明 S2 提示只在「英雄的回合」；10 組測資中只有英雄印過這行。放在 `HeroAction`，State 流程不必判斷 `isHero()` |
| I8 | **每個狀態在建構子設定自己的中文名稱 `displayName`**，`State::getDisplayName()` 回傳；原本的 `getName()`（類別名稱）保留。 | 與 D27（技能各自持有中文名稱）同樣理由：新增 / 刪除狀態不必改 `State`（需求 ③）；`ExampleTests` 仍用 `getName()` 比對類別名稱 |
| I9 | **勝負由 `RPG` 印**：`Battle::startBattle()` 跑到結束，`RPG::GameStart()` 再依 `Battle::isHeroAlive()` 印「你獲勝了！」或「你失敗了！」。`Battle` 在 `startBattle()` 開始時從兩軍找出 identity 為 `'h'` 的英雄，找不到就丟例外。 | D1「Battle 判斷是否結束並把結果回報給 RPG」；保留原本 `void startBattle()` 的簽名，用查詢函式回報結果 |
| I10 | **Parser 介面 `RPG_parser::parse(std::istream&)`**：讀到 `#軍隊-2-結束` 就停，串流剩下的就是英雄決策；T1 第一位 `setIdentity('h')`，其他角色 `setDecider(new AIAction())`；**英雄的決策者由呼叫端設定**。技能建造函式 `RPG_parser::createSkill(name)` 也在這裡。放在 `test/libary`（D36），以 `__RPG_CLIENT_SRCS` 編進 `RPGGAME_LIB`，主程式與測試共用。 | 用串流而不是檔名（BigTwo 的做法），讀測資時同一個檔案串流可直接交給 `HeroAction`（D37）；`--play` 時改交 `std::cin`。不放進 `__TEST_UTILS__SRCS`，因為 `SimpleTest_LIB` 看不到模組的標頭檔 |
| I11 | **`main.cpp` 三種用法**：`RPGGAME <測資.in>`（軍隊與決策都來自檔案）、`RPGGAME --play <測資.in>`（軍隊來自檔案、決策由鍵盤輸入）、`RPGGAME`（都從標準輸入，可 `< 測資.in`）；錯誤（檔案打不開、格式錯誤、未知技能、決策用完）印到 stderr 並回傳 1。原本結尾的 `std::system("pause")` 拿掉。 | 讀測資模式的輸出必須和 `.out` 完全相同，不能多印；`pause` 會讓 exe 一直執行，造成之前 build 時 `RPGGAME.exe: Permission denied` |
| I12 | **`Role`、`Troop` 禁止複製**（複製建構與複製指定都 `= delete`）。 | D49 之後兩者都用裸指標擁有物件，若被複製，兩份解構子會重複 `delete`；目前沒有任何地方需要複製。RL-23 以 `static_assert` 檢查 |
| I13 | **輸出小工具的細節**：命名空間用 `io`（`utils.h` 的 `utils` 是 class，不能再當命名空間）；`write` 一次寫一整行，模組先組好字串再寫；`ConsoleOutput` 用 `std::endl`（每行 flush，`--play` 的提示會在讀鍵盤前出現，與原本行為相同）；`setOutput` 不擁有傳入物件、回傳先前的值方便還原、`nullptr` = 預設主控台；`CompositeOutput` 擁有子節點、禁止複製（比照 D49）。 | 與既有程式風格與 D49 一致；測試的 `OutputCapture` 可以巢狀使用 |

### 7.3 2026-10-14：Role 與 Observer
- **Observer**：7.1 已完成（`UntilDie(Role* dead)`、召喚 +30、詛咒 + 剩餘 MP、施放者已死不給）；本次只補測試（通知順序、只通知一次、移除後不通知、獎勵在死亡訊息之後）。
- **Role**（在原本的程式上補齊設計決策）：
  - `checkActionLossMp(int)` → `checkMp(const Skill*)`：只檢查、不扣除、不印訊息（D9）；扣 MP 用原本的 `lossMp()`。
  - `endThisRound()`：狀態回合數 −1，歸零由 Role 換回 `NormalState`（D11）。
  - `takeTurn(t1, t2, actorSide)`：交給目前狀態的 `decision(t1, t2, actorSide)`（D10）；`State::decision()` 的簽名因此帶入戰場資訊，四個狀態的內容仍是原本的 stub。
  - `setDecider / getDecider`（D4）、`setIdentity / getIdentity / isHero`（D6）。
- 未做（不在本次範圍）：移除 `Hero` / `AI` 子類別（D4，需要刪檔並調整 `ExampleTests.cpp` 與 `main.cpp`）、`IAction` 介面與 `AIAction` 內容、State 流程。
- 測試：新增 `test/RoleTests.cpp` 20 個，全部 72 個通過；刻意改壞（MP 邊界、回合倒數、`takeTurn` 未委派、`isHero`、`removeObserver`）都會被抓到。
- 修正（2026-10-14）：`Role::setTroop()` 原本會 `RequireNonNull`，但 `Troop::removeRole()` 會呼叫 `setTroop(nullptr)`，導致 `removeRole` 一定丟例外；改為接受 `nullptr`（代表離開軍隊），並補上測試。

### 7.4 2026-10-14：移除 Hero / AI 子類別、IAction / AIAction
- **刪除** `Hero.hpp/.cpp`、`AI.hpp/.cpp`（D4）；`ExampleTests.cpp`、`main.cpp` 的 `new Hero(...)` 改為 `new Role(...)`（參數順序相同）。英雄改由 `setIdentity('h')` 標示（D6），決策交給 `IAction`。
- **保留** `NonHero`、`Slime`（之後由 D43 刪除 `NonHero`）：D4 只決定移除 `Hero` / `AI`；史萊姆是否保留子類別在討論中沒有決定（`Summon` 目前 `new Slime(...)`）。
- **`IAction`**：原本的 `action()` 換成 `chooseAction(skills)` → `Skill*`、`chooseTargets(candidates, m)` → `vector<Role*>`，並加上 virtual 解構子。MP 檢查不在介面內（D5）。
- **`AIAction`**：`seed`（預設 0，可由建構子指定）、`getSeed()`；規則見 §7.2 I5 與 `diagrams.md` ⑦。
- **未做**：英雄的 `HeroAction`（D37，讀 `istream`）；「選擇行動：(0) …」「選擇 1 位目標: …」這兩行提示等實作 State 流程時處理（**更正**：只有「選擇行動」每個角色都印；「選擇 m 位目標」只有英雄印，見 §7.2 I7）。
- 測試：新增 `test/AIActionTests.cpp` 11 個（含重現測資 Slime1 的行動順序），`RoleTests` 的 `DummyAction` 改為新介面；全部 83 個通過。刻意改壞（自動全選也 + 1、公式少一位、每選一位就 + 1、S1 不 + 1、`n ≤ m` 寫成 `n < m`）都會被抓到。
- CMake：`src/*/*.cmake` 的 `file(GLOB)` 加上 `CONFIGURE_DEPENDS`；`test/CMakeLists.txt` 的測試檔清單改為 `file(GLOB … CONFIGURE_DEPENDS *.cpp)`。新增 / 刪除 `.cpp` 後直接 build，CMake 會自動重新搜尋，不必手動重跑 `cmake -S . -B build`，也不必再改測試清單（已實測新增 / 刪除測試檔與原始檔）。
- **召喚的史萊姆攜帶 `AIAction`（D40）**：`Summon::attack` 加上 `slime->setDecider(new AIAction())`；`SkillTests` 新增 `SummonedSlimeCarriesItsOwnAIAction`（共 84 個通過；拿掉 `setDecider` 會被抓到）。

### 7.5 2026-10-14：HeroAction 與測試文件
- **`HeroAction`**（`include/Role/HeroAction.hpp`、`src/Role/HeroAction.cpp`）：建構時注入 `std::istream&`（D37），正式執行傳 `std::cin`、測試傳 `istringstream`。
  - S1：讀一行，選第 i 個行動；MP 不足由呼叫端再呼叫 → 讀下一行（需求「再次決策即 `<英雄決策-i+1>`」）。
  - S2：n > m 時讀一行、以「, 」切開，依**輸入順序**回傳目標；m = 0 或 n ≤ m 時**不讀輸入**（D8；用 `waterball-and-fireball-1v2.in` 的 7 行決策驗證：自動全選若也讀行，行數會對不上）。
  - 容錯：略過空白行、接受 `\r\n`；輸入用完丟 `std::runtime_error`、索引超出範圍丟 `std::out_of_range`、目標數字個數 ≠ m 丟 `std::invalid_argument`（測資保證格式正確，這些是除錯用）。
- 測試：新增 `test/HeroActionTests.cpp` 14 個（含重現 `waterball-and-fireball-1v2`、`cheerup` 兩組測資的英雄決策），全部 98 個通過。
- **測試文件** [`test/TESTS.md`](test/TESTS.md)：每個測試的目的、依據、準備資料、步驟與預期、通過標準；另含執行方式、共用工具、Mutation 檢查表（2026-10-14 全部重跑確認）與尚未涵蓋的範圍。**之後新增測試時要同步更新此文件**。

### 7.6 2026-10-14：State 行動流程
- **`State::decision()` 改為預設流程**（原本是純虛擬函式，四個狀態都是除錯用 stub；D10、D12）：
  1. S1：印「選擇行動：(0) 普通攻擊 (1) …」→ `decider->chooseAction()` → `actor->checkMp()`；不足就印「你缺乏 MP，不能進行此行動。」並回到 S1 重印選單。
  2. S2：`skill->getCandidates()` → `decider->chooseTargets()`（自動全選與英雄的提示都在決策者裡，D8、I7）。
  3. S3：`actor->lossMp()` → `skill->announce()` → `skill->attack()`。
- **只覆寫不同的部分**：`PetrochemicaledState::decision()` 是空的（不問決策者：AI 的 seed 不變、英雄不讀輸入）；`PoisonedState::decision()` 先 `lossHp(30)`（不印傷害、歸零時印死亡並通知觀察者），活著才呼叫 `State::decision()`。`NormalState`、`CheerupedState` 刪除原本的 stub，直接沿用預設流程。
- `Role::takeTurn()` 先印「輪到 …」（I6）；各狀態加上中文 `displayName`（I8）；`HeroAction` 在 S2 真的要選時印提示（I7）。
- **修正 I4**：一拳攻擊的 80 × 3 在目標死亡後停止（整場重播 `one-punch` 時發現）。
- **測試**：
  - 新增 `test/StateFlowTests.cpp`：`StateFlowTest` 16 個（每種狀態、MP 不足重選、英雄 / AI 的 S2 提示差異、召喚的史萊姆用自己的 AI 行動、自爆經過流程）。
  - `TestcaseReplayTest` 10 個：在測試內用簡易 parser + Battle 迴圈（T1 → T2、每圈重讀人數、跳過死者、每次行動後檢查結束、回合結束 `endThisRound`）重播 `testcases/` 全部 10 組，**輸出與 `.out` 逐行完全一致**。這是測試用的鷹架，正式的 `Battle` / `RPG` / parser 完成後改用正式流程。
  - `SkillTests` 新增 `OnePunchStopsHittingOnceTargetDies`；`RoleTests` 的 `takeTurn` 測試改為檢查「輪到 …」；`HeroActionTests` 新增 S2 提示測試，fixture 把輸出靜音。
  - 共 126 個全部通過；刻意改壞 15 種流程細節（見 `TESTS.md` §9）都會被抓到。

### 7.7 2026-10-14：Battle、RPG、parser 與 main.cpp
- **`Battle`**（在原本的 `Battle(Troop* ally, Troop* enemy)` 上補齊；`ally` = T1、`enemy` = T2，之後由 D45 改名為 `heroTroop` / `opponentTroop`）：
  - `startBattle()`：找出英雄（I9）→ 每回合 T1 再 T2；用索引走訪且每圈重讀 `getRoles().size()`（召喚的史萊姆本回合就行動，D20）；跳過死者；把兩軍**活著的**名單與 actorSide 交給 `takeTurn`（D30、D31）；**每次行動後**檢查「英雄死亡或任一方殲滅」，成立就立即結束；回合結束對所有角色 `endThisRound()`（D11）。
  - `isHeroAlive()`：給 `RPG` 判斷勝負。
- **`RPG::GameStart()`**：原本就會 `new Battle` 並 `startBattle()`，補上最後印勝負（I9）。`RPG::makeAction()`（原本的空 TODO）與 `Troop::StartBattle()` 在目前設計中沒有用到，Anthony 決定刪除（D42）。
- **Client**：`test/libary/RPG_parser.hpp/.cpp`（I10）、`test/libary/test.cmake` 新增 `__RPG_CLIENT_SRCS`、根目錄 `CMakeLists.txt` 把它加進 `COMM_SRCS`；`main.cpp` 改寫成三種用法（I11），原本測試詛咒用的範例程式碼移除。
- **測試**：
  - `BattleTests.cpp` 10 個：需要英雄、結束條件（敵軍殲滅、英雄死亡但 T1 還有人）、輪流順序與跳過死者、召喚的史萊姆同回合行動、回合結束倒數、`RPG` 印勝負。
  - `ParserTests.cpp` 8 個：兩軍屬性與技能、英雄與 AI、讀完停在決策行、CRLF 與空白行、10 種技能名稱、一拳的處理鏈、未知技能、各種格式錯誤。
  - `TestcaseReplayTests.cpp` 11 個：原本 `StateFlowTests` 裡的測試用鷹架（簡易 parser + 迴圈）**移除**，改用正式的 `RPG_parser` + `HeroAction` + `RPG`；不一致時寫出 `<名稱>.actual.txt`（D39）；另加一個測試確認 `testcases/` 的每個 `.in` 都有被跑到。
  - 共 145 個全部通過；`RPGGAME` 主程式三種用法對 10 組測資的輸出都與 `.out` 相同（含 LF / CRLF 檔案）；刻意改壞 Battle / RPG / parser 的 14 個地方都會被抓到（見 `TESTS.md`）。

### 7.8 2026-10-14：開放問題 O2–O5
- **O2（D42、D45）**：刪除 `Troop::StartBattle()`；`Battle` 的成員改名為 `heroTroop` / `opponentTroop`。
- **O3（D46）**：維持 `Skill` / `attack()` 命名，在 `Skill.hpp` 註明 `attack` 是「施放」。
- **O4（D47）**：
  - `Role::lossHp` private + `friend class State`；`State::damage` protected；`PoisonedState` 改呼叫 `damage(30)`。
  - `Skill::costHp(actor)`（預設 0）、`SelfExplosion::costHp` = 全部 HP；`SelfExplosion::attack` 不再自殺；`State::decision()` 在 `attack()` 之後詢問並支付 HP 代價（施放途中得到的 HP 也算在內）。
  - 測試：直接呼叫 `lossHp` 的 13 處改走 `doDamage`（`RoleTests` 用 fixture 的 `hurt()`）或完整流程（`SkillTests` 新增 `castThroughFlow()`）；`ExampleTests` 的 `SelfExplosionTest` 改為檢查 `attack()` 不扣施放者 HP、`costHp()` = 500；新增 `SelfExplosionCostsAllHpButAttackItselfDoesNotKill`、`OnlySelfExplosionCostsHp`、`DoDamageIsTheOnlyPublicWayToReduceHp`（用 C++20 concept + static_assert 在編譯期確認 `lossHp` / `damage` 不公開）。共 149 個通過，10 組測資整場輸出不變。
  - 刻意改壞：不支付 HP 代價、在施放前支付、預設代價改成全部 HP → 測試失敗；把 `lossHp` 或 `damage` 改回 public → **編譯失敗**（static_assert 訊息直接指出原因）。
- **O5（D48）**：不改程式；維持兩處名稱定義，由 PA-05 檢查一致。

### 7.9 2026-10-15：開放問題 O1（D49）
- **程式**：
  - `Troop::~Troop()` 釋放所有角色；`Role::~Role()` 另外釋放觀察者與決策者；`Role::setDecider()` 換掉不同的決策者時釋放舊的（設成同一個不釋放）；`OnePunch::~OnePunch()` 釋放處理鏈。
  - `Role`、`Troop` 加上 `= delete` 的複製建構 / 複製指定（§7.2 I12）。
  - `main.cpp`：英雄改為 `setDecider(new HeroAction(heroInput))`；戰鬥結束（或丟例外）後 `delete` 兩支 `Troop`。
  - `RPG_parser`：角色建立後**先**加入 `Troop` 再加技能；格式錯誤時 `delete` 已建立的兩支 `Troop` 再丟例外（呼叫端拿不到 setup，只能由 parser 釋放）。
- **測試**：原本把 stack 上的決策者交給 `setDecider(&x)` 的地方都改成 `new`（`StateFlowTests` 全部、`AIActionTests` AI-10、`HeroActionTests` HA-12、`RoleTests` RL-05、`BattleTests` / `SkillTests` 的 fixture、`TestcaseReplayTests`）；`ParserTests` 與 `TestcaseReplayTests` 用完 `delete` 兩支 `Troop`；RL-03、RL-12 自己 `delete` 被移除的角色 / 觀察者。新增 RL-23–25、SK-46，共 153 個通過，10 組測資整場輸出不變。
- **記憶體檢查**：AddressSanitizer 建置下，`RPGGAME` 三種用法 × 10 組、未知技能、決策行不足都沒有洩漏或重複釋放（修改前 summon 一組就洩漏 63 個配置）；單元測試只剩 Anthony 原本的 `ExampleTests.cpp` 自己 `new` 而沒有釋放的物件（保留原樣）。
- **刻意改壞**：Troop 不刪角色 → RL-23；Role 不刪決策者 / 觀察者 → RL-24；設成同一個決策者也刪 → RL-25（ASan 下 heap-use-after-free）；OnePunch 不刪處理鏈 → SK-46。

### 7.10 2026-10-15：開放問題 O6（D50）
- **新增** `include/utils/Output.hpp`（header-only，命名空間 `io`）：`Output`、`ConsoleOutput`、`StreamOutput`、`CompositeOutput`（`render` 預設原樣）、`output()`、`setOutput()`（§7.2 I13）。
- **模組**：`RPG`、`Role`、`HeroAction`、`State`、`Skill`、`BasicAttack`、`SelfHealing` 的 19 處 `std::cout` 改成先組好一行字串、再 `io::output().write(...)`；模組內已沒有 `std::cout`。
- **Client**：`main.cpp` 組裝 `CompositeOutput({new ConsoleOutput()})`，開局 `setOutput`、結束（或丟例外）時還原。
- **測試**：各檔的 `CoutCapture` 改名 `OutputCapture`，改用 `setOutput(StreamOutput(字串))`；`ParserTests` 的手動 `rdbuf` 也改掉。新增 `OutputTests.cpp`（OU-01–07）。共 160 個通過，10 組測資整場輸出不變（三種用法都相同），AddressSanitizer 下 `RPGGAME` 無洩漏。
- **刻意改壞**：Composite 不套用 render → OU-04；不釋放子節點 → OU-05；`setOutput` 不回傳先前的 → OU-06；死亡訊息改回直接寫 `std::cout` → 27 個測試失敗（`OutputCapture` 收不到）。
