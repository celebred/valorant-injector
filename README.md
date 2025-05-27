# 🔗 Usermode Valorant Injector via SetWindowHookEx

An updated fork of [DrNseven's hookloader](https://github.com/DrNseven/hookloader), a popular usermode injector for **VALORANT** using `SetWindowHookEx`. This technique allows DLL injection without using kernel drivers or vulnerable manual mapping — and despite what many are saying, **this method is still fully functional**.

---

## 💡 Why This Matters

Lately, nearly every paid VALORANT cheat (P2C) relies on DrNseven’s hookloader — but most won’t admit it. Instead, they repackage it, make slight changes, and claim it’s their own detection-proof loader.

Even worse, many claim this method is “patched” or “detected.” The truth is:  
**They’re signing their DLLs with blacklisted or reused certificates, which triggers detection — not the injection method itself.**

---

## 🆕 What’s New in This Version

- ✅ Updated window class detection to `VALORANTUnrealWindow` (breaking change from recent updates)  
- 🔧 Automatic export resolver — no need to define the function name manually  
- 🧹 Cleaner, more organized codebase  
- 🛠️ Minor internal improvements for clarity and stability  

---

## 🔗 References

- 📌 Original GitHub Repo: [DrNseven/hookloader](https://github.com/DrNseven/hookloader)  
- 💬 Discussion & Binary: [UC Thread - hookloader fork](https://www.unknowncheats.me/forum/valorant/702198-hookloader-fork.html)

---

## ⚠️ Disclaimer

This repository is provided **for educational and research purposes only**.  
Usage against game terms of service or for malicious intent is not encouraged or supported.

---
