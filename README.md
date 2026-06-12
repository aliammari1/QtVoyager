# QtVoyager

> **Qt desktop travel-management app with RFID check-in + cost analytics.**

<!-- Banner: render assets/banner.png per BANNER.md, then this hero shows it. -->
![QtVoyager](assets/banner.png)

<p align="center">
  <a href="https://github.com/aliammari1/QtVoyager/releases"><b>⬇ Download for your OS</b></a> ·
  <a href="https://github.com/aliammari1/QtVoyager"><b>📖 Docs</b></a> ·
  <a href="https://github.com/aliammari1/QtVoyager/stargazers"><b>⭐ Star this repo</b></a>
</p>

A Qt 5.15 C++ desktop application for managing travel/flight records, with
ODBC storage, Qt Charts analytics, PDF export, and **RFID traveler check-in**
over an Arduino serial reader. **If it's useful, a ⭐ helps a lot.**

[![CI](https://github.com/aliammari1/QtVoyager/actions/workflows/ci.yml/badge.svg)](https://github.com/aliammari1/QtVoyager/actions/workflows/ci.yml)
[![Release](https://github.com/aliammari1/QtVoyager/actions/workflows/release.yml/badge.svg)](https://github.com/aliammari1/QtVoyager/releases)
[![Docs](https://github.com/aliammari1/QtVoyager/actions/workflows/docs.yml/badge.svg)](https://github.com/aliammari1/QtVoyager/actions/workflows/docs.yml)
[![codecov](https://codecov.io/gh/aliammari1/QtVoyager/branch/main/graph/badge.svg)](https://codecov.io/gh/aliammari1/QtVoyager)
[![OpenSSF Scorecard](https://api.scorecard.dev/projects/github.com/aliammari1/QtVoyager/badge)](https://scorecard.dev/viewer/?uri=github.com/aliammari1/QtVoyager)
[![License: Source-Available](https://img.shields.io/badge/license-Source--Available-blue)](LICENSE)
![Qt](https://img.shields.io/badge/Qt-5.15-41cd52?logo=qt)
![C++17](https://img.shields.io/badge/C%2B%2B-17-00599c?logo=cplusplus)
![Platforms](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-555)

## Screenshots

> Desktop GUI — flight CRUD, analytics, and RFID check-in.

![QtVoyager main window](assets/images/preview.png)

<!-- TODO: record a short screen capture of CRUD + charts + RFID lookup and
     commit it as assets/images/demo.gif, then this line will render it. -->
<!-- ![QtVoyager demo](assets/images/demo.gif) -->

## Download

QtVoyager is a **native desktop app** — grab a packaged installer for your OS
from the [**Releases**](https://github.com/aliammari1/QtVoyager/releases) page
(built automatically on each tagged release):

| OS | Artifact | Built with |
|----|----------|-----------|
| Windows | `QtVoyager-windows.zip` (portable, Qt DLLs bundled) | `windeployqt` |
| macOS | `QtVoyager-macos.dmg` | `macdeployqt` |
| Linux | `QtVoyager-linux.AppImage` | `linuxdeployqt` |

Every installer ships with **SLSA build provenance** (signed via
`actions/attest-build-provenance`). Verify a download came from this repo's CI:

```bash
gh attestation verify QtVoyager-windows.zip -R aliammari1/QtVoyager
```

Prefer to build from source? See [Quickstart](#quickstart) below.

> **Note on the demo:** because this is a Qt desktop binary, there is no live web
> demo — the demo *is* the downloadable installer above plus the screenshots and
> GIF. The [documentation site](https://github.com/aliammari1/QtVoyager) is built
> with **mkdocs-material** and deployed to **Cloudflare Pages** (Pages hosts the
> docs only; it cannot run a native Qt application).

## Features

- Full CRUD over flight records (`VOYAGES`)
- Search and multi-field sorting
- Average cost between two locations and total-profit analytics
- Qt Charts visualizations and animated flight graphic
- RFID card lookup of travelers (`VOYAGEURS`) via a serial Arduino reader
- Opt-in AI **flight insights** over aggregated bookings (Anthropic API,
  user-supplied key — disabled with no key)

## Tech stack

Qt 5.15 (`widgets`, `sql`/ODBC, `charts`, `serialport`, `printsupport`,
`network`), C++17. Builds with **qmake** *or* **CMake** (Qt6-ready).

## Quickstart

```bash
git clone https://github.com/aliammari1/QtVoyager.git
cd QtVoyager
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
# binary: build/GestionDeVoyages
```

qmake also works: `qmake GestionDeVoyages.pro && make`.

**Prerequisites:** Qt 5.15.2 with the `qtcharts` and `qtserialport` add-ons, a
C++17 compiler, and an ODBC manager.

| OS | Get Qt + deps | Build & run |
|----|---------------|-------------|
| **Windows** | Qt online installer (MSVC/MinGW kit); ODBC is built in | `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build`, then run `build\GestionDeVoyages.exe` |
| **macOS** | `brew install qt@5 unixodbc` (or Qt installer) | `cmake -S . -B build && cmake --build build`, then `open build/GestionDeVoyages.app` |
| **Linux** | `qtcharts`, `qtserialport`, `unixodbc` from your package manager; add user to `dialout` for serial RFID | `cmake -S . -B build && cmake --build build && ./build/GestionDeVoyages` |

Configure the database via environment variables (no credentials are
hardcoded) — copy `.env.example` and set `QTVOYAGER_DB_*`. For a quick local
run with SQLite:

```bash
export QTVOYAGER_DB_DRIVER=QSQLITE
export QTVOYAGER_DB_NAME=qtvoyager.db
```

See the [docs](docs/index.md) for full ODBC/DSN setup, Arduino/RFID wiring, and
per-OS build notes.

## Tests

```bash
cmake -S . -B build -DBUILD_TESTING=ON && cmake --build build --parallel
QT_QPA_PLATFORM=offscreen ctest --test-dir build --output-on-failure
```

Tests run against an **in-memory QSQLITE** database (no DSN needed) and cover
CRUD, cost/profit math, and a SQL-injection regression for the RFID and
flight-ref lookups.

## Security

Database access is fully parameterized and credentials are externalized to
env/`QSettings`. CI runs **gitleaks**, **CodeQL**, and clang-format/clang-tidy.
See [`docs/security.md`](docs/security.md) and [`SECURITY.md`](SECURITY.md).

## Engineering decisions

- **Source-available, not OSS:** the owner monetizes a commercial license via
  Ko-fi; the SPDX id `LicenseRef-Source-Available-1.0` makes GitHub recognize
  the chip while keeping the code portfolio-visible.
- **qmake kept, CMake added:** CMake is the path to Qt 6 and cleaner CI, but the
  original qmake build is preserved and CI verifies both.
- **Cloudflare Pages for docs only:** the app is a native desktop binary
  shipped via GitHub Releases; only the mkdocs site deploys to CF Pages.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) and the
[ROADMAP](ROADMAP.md). Issues and PRs welcome.

## Support / commercial license

Personal, educational, and non-commercial use is free. If you use QtVoyager
commercially, please obtain a commercial license:

[![Ko-fi](https://img.shields.io/badge/Ko--fi-support%20%2F%20commercial%20license-FF5E5B?logo=ko-fi&logoColor=white)](https://ko-fi.com/aliammari)

Support development or buy a commercial license via
[**Ko-fi**](https://ko-fi.com/aliammari), or email
`ammari.ali.0001@gmail.com`.

## License

Source-available under a **Commercial Use License**
(`LicenseRef-Source-Available-1.0`). Personal, educational, and non-commercial
use is free; commercial use requires a license — contact
`ammari.ali.0001@gmail.com`. See [`LICENSE`](LICENSE).

## Related projects

Part of [@aliammari1](https://github.com/aliammari1)'s portfolio — other
desktop / systems work you might like:

- [rakcha](https://github.com/aliammari1/rakcha) — polyglot cinema platform
  (JavaFX + Symfony + Flutter) with `jpackage` installers
- [Gold-Rush](https://github.com/aliammari1/Gold-Rush) — a 2D platformer in
  pure C/SDL that plays in the browser via WASM
- See the [profile hub](https://github.com/aliammari1) for the full ecosystem.

See [GROWTH.md](GROWTH.md) for how this project is shared and grown.

---

**Topics:** `qt` · `cpp` · `desktop` · `rfid` · `qmake` · `cmake` · `qtcharts` · `odbc`
<!-- Set these as GitHub repo topics in Settings for discoverability. -->
**Share it:** post a *Show & Tell* on the Qt Forum and a "Qt + RFID desktop app"
note on dev.to to drive traffic.
