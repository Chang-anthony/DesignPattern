# Service — 協作指引（給 Claude）

Anthony 練習 **架構設計** 的專案：支援「服務探索 / 負載平衡 / 黑名單」等機制自由組合的 Http Client 套件（C++20 / CMake / GoogleTest）。
需求表：[`need/need.md`](need/need.md)（原文：[`need/need.txt`](need/need.txt)；以原文為準）　圖：[`diagrams.md`](diagrams.md)

---

## 1. 合作規則

**先遵守根目錄的 [`../CLAUDE.md`](../CLAUDE.md)**：OOA → OOD → 流程討論 → 畫圖 → 實作；一次一個議題；用提問引導，不替 Anthony 決定設計。

- 本專案從頭照流程走，**目前在階段 1：OOA**。
- Anthony 做出決定後記到 §5；討論完的問題標 ✅ 並附決策編號，不要刪除。
- 實作階段：Anthony 指定要自己做的部分只寫框架；沒有特別提的由 Claude 實作，自行決定的細節記到 §7。

---

## 2. 需求重點（摘要，細節以 need.txt 原文為準）

| 編號 | 需求 | 重點 |
|---|---|---|
| A1 | Http Client 套件 | 透過 Http/Https 取得某一 URL 的內容，**只需支援 GET** |
| A2 | 服務探索 | 依配置檔（`host: ip, ip, …`）把 Host 換成「第一項仍有效的 IP」；請求失敗 → 該 IP 失效 10 分鐘 |
| A3 | 負載平衡 | 依序**輪流**（Round Robin）選擇 IP；失效的 IP 不會被選 |
| A4 | 黑名單 | 網址包含黑名單 Host → 中止請求並拋出例外 |
| B1 | 不重複 | 不能有超過 3 行的重複程式行為 |
| B2 | 自由組合 | 三種機制可任意挑選、任意排列（也可以都不開），每種排列都要依同一套邏輯運作 |
| B3 | 可擴充 | 不改既有套件程式碼，就能擴充新機制、新增 `FakeHttpClient` 以外的 `HttpClient` 實作 |
| C1 | `FakeHttpClient` | 不實作 Http；`sendRequest(request: HttpRequest)` 只輸出到 Console：成功印 `[SUCCESS] <url>`，失敗噴例外 |

---

## 3. 需求疑問（等 Anthony 確認，詳見 need.md 文末）

| # | 疑問 | 狀態 |
|---|---|---|
| Q1 | 背景知識的負載平衡例子輪完一圈寫「回到 `.15`」，A3 的例子是回到第一項——原文筆誤？ | 待確認 |
| Q2 | 服務探索遇到請求失敗：這次請求直接失敗，還是同一次請求內改試下一個 IP？ | 待確認 |
| Q3 | 負載平衡跳過的「失效 IP」，是否就是服務探索標記的那一份？ | 待確認 |
| Q4 | 黑名單是 Host 完全相同才擋，還是網址字串包含就擋？黑名單表也由配置檔提供嗎？ | 待確認 |
| Q5 | 原文沒有測資，也沒說要不要有主程式；驗證以單元測試為主即可？ | 待確認 |

---

## 4. 目前進度

- ✅ 2026-10-15：需求表整理完成（[`need/need.md`](need/need.md)）。
- ✅ 2026-10-15：專案骨架（CMake、`utils/`、測試框架）可 build；`src/`、`include/` 目前沒有任何模組程式碼。
- ⏸ **目前**：階段 1 OOA。

---

## 5. 設計決策紀錄

| # | 日期 | 階段 | 決定 | 理由 / 取捨 |
|---|---|---|---|---|
| | | | （尚無） | |

---

## 6. 建置與測試

```bash
cd Service
cmake -S . -B build
cmake --build build
./build/bin/SERVICE        # 主程式（尚未實作）
./build/bin/SimpleTest     # 單元測試；Windows (MinGW) build 完會自動執行
```

---

## 7. 實作紀錄

### 7.1 2026-10-15：專案骨架
- 從 RPGGame 複製 CMake 與測試框架；`project(SERVICE)`。
- `src/source.cmake`：自動收集 `src/` 底下所有 `.cpp`（含子資料夾，`GLOB_RECURSE … CONFIGURE_DEPENDS`）；`include/include.cmake`：`include/` 的每個子資料夾自動加入 include 路徑。之後新增資料夾 / 檔案都不必改 CMake。
- `include/utils/Output.hpp`：沿用 RPGGame 的輸出小工具（RPGGame D50）；`test/OutputTests.cpp` 保留 OU-01–06（OU-07 依賴 RPGGame 的模組，已移除）。是否在本專案使用，等設計時再決定。
