# Database / ODBC DSN setup

QtVoyager connects through the **Qt ODBC driver (`QODBC`)** by default. The
connection parameters are **never hardcoded** — they are resolved at runtime
in this order:

1. Environment variables
2. `QSettings` (organization `QtVoyager`, application `QtVoyager`)
3. Built-in defaults (driver `QODBC`; name/user/password empty)

## Configuration keys

| Setting    | Environment variable      | QSettings key  | Default |
|------------|---------------------------|----------------|---------|
| Driver     | `QTVOYAGER_DB_DRIVER`     | `db/driver`    | `QODBC` |
| DB / DSN   | `QTVOYAGER_DB_NAME`       | `db/name`      | *(empty)* |
| User       | `QTVOYAGER_DB_USER`       | `db/user`      | *(empty)* |
| Password   | `QTVOYAGER_DB_PASSWORD`   | `db/password`  | *(empty)* |

Copy [`.env.example`](https://github.com/aliammari1/QtVoyager/blob/main/.env.example)
and set values via your shell/launcher, or store them in QSettings. Never
commit a populated `.env`.

## Schema

The app expects two tables:

```sql
CREATE TABLE VOYAGES (
    FLIGHTREF VARCHAR(64),
    LIEUDEP   VARCHAR(64),
    LIEUARR   VARCHAR(64),
    DATEDEP   DATE,
    DATEARR   DATE,
    AIRLINE   VARCHAR(64),
    MONTANT   FLOAT,
    NBPER     INTEGER
);

CREATE TABLE VOYAGEURS (
    RFID_CARD VARCHAR(32),
    NAME      VARCHAR(128)
);
```

## Configuring an ODBC DSN

=== "Windows"

    Open *ODBC Data Source Administrator* -> *System DSN* -> *Add*, pick your
    driver (SQL Server / MySQL / PostgreSQL), and name the DSN. Set
    `QTVOYAGER_DB_NAME` to that DSN name.

=== "Linux / macOS"

    Edit `/etc/odbcinst.ini` (drivers) and `~/.odbc.ini` (DSNs), then point
    `QTVOYAGER_DB_NAME` at the DSN. Verify with `isql <DSN> <user> <pass>`.

## Switching to SQLite (for quick local runs)

```bash
export QTVOYAGER_DB_DRIVER=QSQLITE
export QTVOYAGER_DB_NAME=qtvoyager.db
```

This is also exactly what the test suite does (`:memory:`), so no production
DSN is needed to run tests.
