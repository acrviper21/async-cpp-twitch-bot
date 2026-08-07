# async-cpp-twitch-bot
An asynchronous C++ Twitch bot engine designed for low latency event processing, built on Boost.Beast and OpenSSL. Currently implemnting synchronous foundational streams with plans for full asynchronous refactoring.

## Key Features

* Synchronous HTTP & WebSocket Streams: Utilizes Boost.Beast and Boost.Asio to manage both HTTPS REST requests and persistent WebSocket connections.
* SSL/TLS Encryption: Integrates OpenSSL to secure all data in transit across HTTPS and WSS endpoints.
* Twitch EventSub Integration: Automates session identification and sends authenticated HTTP POST requests using OAuth 2.0 headers to register chat subscriptions.
---
## Tech Stack
* Language: C++17
* Networking & I/O: Boost.Beast, Boost.Asio
* Security & Encryption: OpenSSL
* Data Parsing: Boost.json
* Build System: CMake (3.20+)
* Operating System: Linux
---
## Prerequisites
To build this project, you will need:
* C++ Compiler (supporting C++17 or higher)
* CMake (3.20+)
* Boost Libraries (System, Asio, Beast, JSON)
* OpenSSL (Development headers and SSL libraries)
---
## Build Instructions
1. **Clone the repository:**
```bash
git clone https://github.com/acrviper21/async-cpp-twitch-bot.git
cd async-cpp-twitch-bot
```

2. **Create a build directory:**
```bash
mkdir build && cd build
```

3. **Configure and build**
```bash
cmake .. && cmake --build .
cd src
```

---

## Usage

1. Create a `.env` file in the root directory with your credentials:
```env
TWITCH_CLIENT_ID=your_client_id_here
TWITCH_OAUTH_TOKEN=your_oauth_token_here
TWITCH_BROADCASTER_ID=your_broadcaster_id_here
```

2. Run the executable from the `build/src` directory:
   ./twitch_bot