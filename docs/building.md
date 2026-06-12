# Building

QtVoyager builds with **Qt 5.15** and either **qmake** (original) or **CMake**
(Qt6-ready). Modules required: `widgets`, `sql` (with the ODBC driver),
`charts`, `serialport`, `printsupport`, `network`. C++17.

## Prerequisites

- Qt 5.15.2 with the **QtCharts** and **QtSerialPort** add-ons
- A C++17 compiler (GCC 9+, Clang 10+, or MSVC 2019+)
- For the ODBC driver: an ODBC manager (`unixODBC` on Linux/macOS; built in on
  Windows)

## CMake (recommended)

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

The binary is `build/GestionDeVoyages` (`.exe` on Windows).

## qmake (original)

```bash
qmake GestionDeVoyages.pro
make            # nmake / jom on Windows
```

## Running the tests

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --parallel
QT_QPA_PLATFORM=offscreen ctest --test-dir build --output-on-failure
```

Or with qmake:

```bash
cd tests
qmake tests.pro && make
QT_QPA_PLATFORM=offscreen ./tests
```

The tests use an **in-memory QSQLITE** database, so no ODBC DSN is needed.

## Per-OS notes

=== "Windows"

    Use the MSVC or MinGW Qt kit. Package a redistributable build with
    `windeployqt`. ODBC is available out of the box (configure a DSN in the
    *ODBC Data Source Administrator*).

=== "Linux"

    Install `qtcharts`, `qtserialport`, and `unixodbc` + the relevant ODBC
    driver. Package as an AppImage with `linuxdeployqt`. Add your user to the
    `dialout` group for serial-port (RFID) access.

=== "macOS"

    Install Qt via the online installer or Homebrew. Package with
    `macdeployqt`. Install `unixodbc` (e.g. via Homebrew) for the SQL driver.
