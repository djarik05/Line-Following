# 5-Sensor Pattern-Based Line Follower Robot (Arduino)


::contentReference[oaicite:0]{index=0}


This project implements a **pattern-based line follower robot** using **5 analog IR sensors** and **two DC motors** controlled by an Arduino.  
The logic detects **straight paths, slight curves, 45° turns, 75° turns, sharp turns**, and also includes an **intelligent line-lost recovery system**.

---

## 🔧 Hardware Requirements

- Arduino Uno / Nano
- 5× Analog IR Line Sensors  
- Dual DC Motor Driver (L298N / TB6612FNG / equivalent)
- 2× DC Motors with wheels
- Robot chassis
- Power supply (7–12V depending on motors)

---

## 📌 Pin Configuration

### Sensor Pins
| Sensor | Arduino Pin |
|------|------------|
| S1 (Left) | A5 |
| S2 | A4 |
| S3 (Center) | A3 |
| S4 | A2 |
| S5 (Right) | A1 |

### Motor Pins
| Motor | PWM Pin | Direction Pin |
|-----|--------|---------------|
| Right Motor | D9 | D7 |
| Left Motor | D10 | D8 |

---

## ⚙️ Key Parameters

```cpp
int threshold = 690;
