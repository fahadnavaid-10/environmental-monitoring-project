# 🚀 Environmental Monitoring Project
A compact, low-level environmental monitoring prototype that fetches live weather data for a configured city, generates human-readable reports, and raises desktop alerts. Built for edge/host machines and field operators who need a lightweight, dependency-minimal system to monitor temperature, humidity, and weather conditions and generate archival reports.

---

### 🛠️ Tech Stack & System Architecture
- **Core Languages & Frameworks:** C (glibc, POSIX), Bash (process orchestration)
- **Tools & Ecosystem:** gcc / Makefile, libcurl (HTTP client), cJSON (JSON parsing), bc (numeric comparisons), notify-send (desktop notifications)
- **Why this stack?** C + shell provides minimal runtime overhead and direct system integration for resource-constrained or embedded-like deployments while using battle-tested libraries (libcurl, cJSON) for robust I/O and parsing.

---

### 📊 Repository Insights & Performance Metrics
<p align="left">
  <img src="https://github-readme-stats.vercel.app/api?username=fahadnavaid-10&show_icons=true&theme=tokyonight&count_private=true" height="150" alt="GitHub Stats" />
  <img src="https://github-readme-stats.vercel.app/api/top-langs/?username=fahadnavaid-10&layout=compact&theme=tokyonight" height="150" alt="Top Languages" />
</p>

---

### 📂 Repository File Structure
```text
├── .vscode/                 # Editor settings for local development
├── Makefile                 # Build recipe (gcc linking with -lcurl -lcjson)
├── main                     # Compiled ELF binary (artifact, not source)
├── main.c                   # Entry point: calls retrieveEnvironmentalData("Karachi")
├── data_processing.c        # Fetches weather JSON via libcurl, parses with cJSON, triggers alerts + processing script
├── data_processing.h        # WeatherData struct and function prototypes
├── alert.c                  # Desktop notification helpers using notify-send (temperature alert)
├── alert.h                  # Alert function prototypes
├── process_data.sh          # Bash script: formats & appends human-readable report to report.txt and sends notifications
├── report.txt               # Example generated reports (append-only log of processed data)
