# QtVoyager

A Qt 5.15 C++ desktop application for managing travel/flight data, with
ODBC database storage, Qt Charts analytics, and an Arduino-based RFID reader
for traveler check-in.

> Banner: see [`BANNER.md`](https://github.com/aliammari1/QtVoyager/blob/main/BANNER.md)
> for the aviation navy-gradient hero spec (TODO: render and commit to `assets/`).

## Features

- Create, read, update, delete flight records (`VOYAGES` table)
- Search and sorting across all fields
- Average cost between two locations and total profit analytics
- Qt Charts visualizations
- RFID card lookup of travelers via a serial-connected Arduino reader
- Opt-in AI "flight insights" over aggregated booking data (Anthropic API,
  user-supplied key)

## Quick links

- [Building per OS](building.md)
- [Database / ODBC DSN setup](database.md)
- [Arduino / RFID wiring](rfid.md)
- [Security model](security.md)

## License

QtVoyager is **source-available** under a Commercial Use License
(`LicenseRef-Source-Available-1.0`). Personal, educational and non-commercial
use is free; commercial use requires a license. See `LICENSE`.
