# QtVoyager

A Qt 5.15 C++ desktop application for managing travel/flight records, with
ODBC storage, Qt Charts analytics, PDF export, and **RFID traveler check-in**
over an Arduino serial reader.

<!-- TODO: render and commit assets/banner.png per BANNER.md, then embed it here. -->
<!-- ![QtVoyager](assets/banner.png) -->

![Preview](assets/images/preview.png)

[![CI](https://github.com/aliammari1/QtVoyager/actions/workflows/ci.yml/badge.svg)](https://github.com/aliammari1/QtVoyager/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/aliammari1/QtVoyager/branch/main/graph/badge.svg)](https://codecov.io/gh/aliammari1/QtVoyager)
[![License: Source-Available](https://img.shields.io/badge/license-Source--Available-blue)](LICENSE)
![Qt](https://img.shields.io/badge/Qt-5.15-41cd52?logo=qt)
![C++17](https://img.shields.io/badge/C%2B%2B-17-00599c?logo=cplusplus)

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

Configure the database via environment variables (no credentials are
hardcoded) — copy `.env.example` and set `QTVOYAGER_DB_*`. For a quick local
run with SQLite:

```bash
export QTVOYAGER_DB_DRIVER=QSQLITE
export QTVOYAGER_DB_NAME=qtvoyager.db
```

See the [docs](docs/index.md) for ODBC/DSN setup, Arduino/RFID wiring, and
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

## License

Source-available under a **Commercial Use License**
(`LicenseRef-Source-Available-1.0`). Personal, educational, and non-commercial
use is free; commercial use requires a license — contact
`ammari.ali.0001@gmail.com`. See [`LICENSE`](LICENSE).
