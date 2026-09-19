<div align="center">

```
██╗    ██╗███████╗ █████╗ ████████╗██╗  ██╗███████╗██████╗ 
██║    ██║██╔════╝██╔══██╗╚══██╔══╝██║  ██║██╔════╝██╔══██╗
██║ █╗ ██║█████╗  ███████║   ██║   ███████║█████╗  ██████╔╝
██║███╗██║██╔══╝  ██╔══██║   ██║   ██╔══██║██╔══╝  ██╔══██╗
╚███╔███╔╝███████╗██║  ██║   ██║   ██║  ██║███████╗██║  ██║
 ╚══╝╚══╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝
    ███████╗ ██████╗ ██████╗ ███████╗ ██████╗ █████╗ ███████╗████████╗
    ██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔════╝██╔══██╗██╔════╝╚══██╔══╝
    █████╗  ██║   ██║██████╔╝█████╗  ██║     ███████║███████╗   ██║   
    ██╔══╝  ██║   ██║██╔══██╗██╔══╝  ██║     ██╔══██║╚════██║   ██║   
    ██║     ╚██████╔╝██║  ██║███████╗╚██████╗██║  ██║███████║   ██║   
    ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝   
```

### 🌤️ Real-time Weather Forecasts — Daily · Hourly · Weekly

[![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![WeatherAPI](https://img.shields.io/badge/WeatherAPI.com-Live_Data-FFB347?style=for-the-badge&logo=cloud&logoColor=white)](https://www.weatherapi.com/)
[![httplib](https://img.shields.io/badge/httplib-v0.20.1-4CAF50?style=for-the-badge)](https://github.com/yhirose/cpp-httplib)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](LICENSE)

</div>

---

## 📖 About

**Weather Forecast System** is a full-stack C++ web application that fetches real-time weather data from [WeatherAPI.com](https://www.weatherapi.com/) and serves it through a clean, animated browser interface. Built with an HTTP server written in C++ using the header-only `httplib` library — no Node.js, no Python, pure C++.

---

## ✨ Features

| Feature | Description |
|---|---|
| 🌡️ **Daily Forecast** | Get weather for any specific date — temperature, condition, humidity & wind |
| ⏱️ **Hourly Forecast** | 24-hour breakdown for any day with per-hour conditions |
| 📅 **Weekly Forecast** | 7-day outlook at a glance |
| 🔍 **Search by City** | Search any city + country worldwide |
| 📜 **Search History** | Saves your last 20 searches locally |
| 🌙 **Day/Night Icons** | Dynamic weather icons based on time of day |
| 💾 **History Logging** | All searches logged to `weather_history.txt` |

---

## 🛠️ Tech Stack

```
Backend  →  C++17  +  httplib v0.20.1  (HTTP server)
API      →  WeatherAPI.com             (Real-time weather data)
JSON     →  nlohmann/json              (JSON parsing)
Frontend →  HTML5  +  CSS3  +  Vanilla JavaScript
Icons    →  Font Awesome 6
```

---

## 🚀 Getting Started

### Prerequisites

- **Windows** (10/11)
- **MinGW-w64 g++** (C++17 support) — [Install via MSYS2](https://www.msys2.org/)
- A free **WeatherAPI.com** API key — [Get one here](https://www.weatherapi.com/signup.aspx)

### 1. Clone the repo

```bash
git clone https://github.com/Ayeshanawaz1/WeatherForecastSystem.git
cd WeatherForecastSystem
```

### 2. Add your API key

Open `WeatherAPI.cpp` and replace the key on line 29:

```cpp
string apiKey = "YOUR_API_KEY_HERE";
```

### 3. Build

```bash
g++ -std=c++17 -DWIN32_LEAN_AND_MEAN -DNOMINMAX -w \
    -o WeatherForecastSystem.exe \
    Server.cpp WeatherAPI.cpp WeatherSystem.cpp \
    City.cpp Weather.cpp Forecast.cpp HistoryLogger.cpp \
    -lws2_32 -lcrypt32 -lwsock32
```

### 4. Run

```bash
.\WeatherForecastSystem.exe
```

### 5. Open in browser

```
http://localhost:8080
```

---

## 📁 Project Structure

```
WeatherForecastSystem/
├── Server.cpp           # HTTP server — routes & request handling
├── WeatherAPI.cpp       # Fetches data from WeatherAPI.com via httplib
├── WeatherSystem.cpp    # Orchestrates API calls + JSON parsing
├── Forecast.cpp         # Forecast model (weekly/daily/hourly)
├── Weather.cpp          # Weather data model
├── City.cpp             # City/country model
├── HistoryLogger.cpp    # Logs searches to weather_history.txt
├── httplib.h            # Header-only HTTP library (cpp-httplib v0.20.1)
├── json.hpp             # Header-only JSON library (nlohmann/json)
├── static/
│   ├── index.html       # Main SPA frontend
│   ├── styles.css       # All styling
│   └── script.js        # Frontend logic + API calls
└── .vscode/
    ├── tasks.json        # Ctrl+Shift+B build task
    └── launch.json       # F5 debug config
```

---

## 🔌 API Endpoints

| Method | Endpoint | Description |
|---|---|---|
| `GET` | `/` | Serves the frontend (`static/index.html`) |
| `GET` | `/api/weather?city=X&country=Y&type=daily&date=YYYY-MM-DD` | Daily forecast |
| `GET` | `/api/weather?city=X&country=Y&type=hourly&date=YYYY-MM-DD` | Hourly forecast |
| `GET` | `/api/weather?city=X&country=Y&type=weekly` | 7-day forecast |
| `GET` | `/api/history` | Returns search history log |
| `POST` | `/api/log` | Logs a search entry |

### Example Response (Daily)

```json
{
  "city": "Lahore",
  "country": "Pakistan",
  "date": "2026-09-19",
  "condition": "Sunny",
  "temperature": 31.5,
  "humidity": 38,
  "windSpeed": 12.2
}
```

---

## 🏗️ Architecture

```
Browser (Frontend)
      │  fetch() to localhost:8080/api/weather
      ▼
Server.cpp  (httplib HTTP server on port 8080)
      │  calls WeatherSystem::loadData()
      ▼
WeatherSystem.cpp
      │  calls WeatherAPI::fetchWeatherData()
      ▼
WeatherAPI.cpp  (httplib Client → api.weatherapi.com)
      │  returns raw JSON
      ▼
WeatherSystem.cpp  (nlohmann/json parsing)
      │  builds Forecast + Weather objects
      ▼
Server.cpp  (serializes to JSON → sends HTTP response)
      │
      ▼
Browser  (renders weather cards)
```

---

## 🌐 Deployment

> **Note:** This is a native Windows C++ application. It cannot be deployed to cloud platforms like Render or GitHub Pages directly. Below are your best options:

### Option A — Share the `.exe` (Simplest)
Build the `.exe` and share it. Anyone with Windows can run it locally.

### Option B — GitHub Releases (Recommended ⭐)
1. Build a Release version
2. Go to your repo → **Releases → Draft a new release**
3. Upload `WeatherForecastSystem.exe`
4. Users download & run — no install needed

### Option C — Run on a Windows VPS
Deploy to a Windows VPS (e.g., AWS EC2 Windows, Azure VM) and expose port 8080 publicly.

### Option D — Rewrite Backend in Node.js/Python + Deploy to Render
Convert `Server.cpp` → Express.js or FastAPI, then deploy the web frontend on **Render** or **Railway** for free.

---


## 👩‍💻 Authors

**Ayesha Nawaz** — University Project  
[![GitHub](https://img.shields.io/badge/GitHub-Ayeshanawaz1-181717?style=flat&logo=github)](https://github.com/Ayeshanawaz1)

**Muhammad Umar** - Univeristy Project
(https://github.com/Muhammad-UmarX)




---

<div align="center">
  <sub>Built with C++ · Powered by WeatherAPI.com</sub>
</div>
