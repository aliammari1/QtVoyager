# Contributing to QtVoyager

Thanks for your interest in QtVoyager — a Qt 5.15 / C++17 desktop application for
travel management with ODBC storage, Qt Charts analytics, and Arduino-based RFID
check-in. Contributions of all kinds are welcome: bug fixes, features, docs, and
tests.

> **License note:** QtVoyager is **source-available** (not OSS) under a
> Commercial Use License (`LicenseRef-Source-Available-1.0`). By submitting a
> contribution you agree it may be distributed under that license. For
> commercial-use licensing, contact `ammari.ali.0001@gmail.com` or support via
> [Ko-fi](https://ko-fi.com/aliammari).

## Getting set up

You need **Qt 5.15.2** with the `qtcharts` and `qtserialport` add-ons, a C++17
compiler (GCC 9+, Clang 10+, or MSVC 2019+), and an ODBC manager (`unixODBC` on
Linux/macOS; built in on Windows). See [`docs/building.md`](docs/building.md) for
full per-OS instructions.

```bash
# Clone and build with CMake (recommended; Qt6-ready)
git clone https://github.com/aliammari1/QtVoyager.git
cd QtVoyager
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build --parallel

# Run the test suite (offscreen, in-memory SQLite — no DSN needed)
QT_QPA_PLATFORM=offscreen ctest --test-dir build --output-on-failure
```

The original **qmake** build is also supported:
`qmake GestionDeVoyages.pro && make`. CI verifies both.

For a quick local run without a real ODBC database, use SQLite via env vars
(copy `.env.example`):

```bash
export QTVOYAGER_DB_DRIVER=QSQLITE
export QTVOYAGER_DB_NAME=qtvoyager.db
```

## Coding conventions

- **C++17**, Qt idioms. Format with the repo's `.clang-format` and lint with
  `.clang-tidy` before committing (`pre-commit` is configured —
  `pre-commit install`).
- **Parameterized SQL only.** Never build a query by string-concatenating user
  input. Use `QSqlQuery::prepare()` + `bindValue()` / `addBindValue()`. This is a
  hard requirement — there is a SQL-injection regression test covering the RFID
  and flight-ref lookups, and new query paths must follow the same pattern.

  ```cpp
  // Good
  QSqlQuery q;
  q.prepare("SELECT * FROM VOYAGEURS WHERE RFID = :rfid");
  q.bindValue(":rfid", cardId);
  q.exec();

  // Never do this
  q.exec("SELECT * FROM VOYAGEURS WHERE RFID = '" + cardId + "'");
  ```

- **No hardcoded credentials.** Database connection settings come from
  environment variables (`QTVOYAGER_DB_*`) or `QSettings` — see `connection.cpp`
  and `.env.example`. Do not commit DSNs, passwords, host names, or API keys.
  CI runs **gitleaks** and will fail the build on a leaked secret.
- **AI feature:** the Anthropic "flight insights" stub is opt-in and reads the
  key from `ANTHROPIC_API_KEY` / `QSettings`; keep it disabled-by-default and
  never embed a key.
- Add or update **QtTest** cases under `tests/` for behavior changes,
  especially anything touching SQL or the cost/profit math.

## How to contribute

1. Fork the repo and create a feature branch (`feat/...` or `fix/...`).
2. Make focused changes; keep commits clear and conventional
   (`feat:`, `fix:`, `docs:`, `test:`, `security:`).
3. Run `clang-format`, `clang-tidy`, and the test suite locally.
4. Push and open a pull request using the template. Link any related issue.
5. CI (3-OS build matrix, tests, CodeQL, gitleaks, clang-format/tidy) must pass.

## Reporting bugs & requesting features

Open a GitHub issue. For bugs, include your OS, Qt version, build system
(qmake/CMake), and steps to reproduce. For security issues, see
[`SECURITY.md`](SECURITY.md) — please do **not** open a public issue for
vulnerabilities.

No contribution is too small — a typo fix or a doc clarification is genuinely
appreciated.
