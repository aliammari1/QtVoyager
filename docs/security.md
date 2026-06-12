# Security

## Parameterized SQL everywhere

All database access uses `QSqlQuery::prepare()` + `bindValue()`. Two queries
that previously concatenated untrusted input were fixed:

- **RFID lookup** (`mainwindow.cpp`, `update_label()`): the card serial read
  from the Arduino was concatenated into a `SELECT ... WHERE RFID_CARD = '...'`.
  A cloned/crafted card could inject SQL. Now bound as `:rfid`.
- **Flight-ref search** (`gestionVoyages/voyage.cpp`, `searchByFlightRef()`):
  the reference was concatenated into the `WHERE` clause. Now bound as `:ref`.

A regression test feeds the classic `' OR '1'='1` payload and asserts it
matches **zero** rows (see `tests/tst_voyage.cpp`).

## No hardcoded credentials

`config/connection.cpp` no longer contains a database name, user, or password.
Credentials resolve from environment variables, then `QSettings`, then empty
defaults (see [Database setup](database.md)). A **gitleaks** scan with custom
rules (`.gitleaks.toml`) fails CI if a literal is passed to
`setUserName`/`setPassword`.

## Opt-in AI feature

The "flight insights" feature (`ai/flightinsights.cpp`) is **strictly opt-in**:
it never calls the network unless the user supplies their own Anthropic API key
(via `ANTHROPIC_API_KEY` or QSettings `ai/anthropic_api_key`). With no key it
fails gracefully. Only aggregated, anonymized summary text is sent.

## Reporting

See [`SECURITY.md`](https://github.com/aliammari1/QtVoyager/blob/main/SECURITY.md)
for the disclosure policy.
