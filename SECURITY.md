# Security Policy

## Supported versions

QtVoyager is actively developed on the `main` branch. Security fixes are applied
to the latest release; please test against the most recent tag before reporting.

## Reporting a vulnerability

**Please do not open a public GitHub issue for security vulnerabilities.**

Report privately instead:

- Use GitHub's **[Report a vulnerability](https://github.com/aliammari1/QtVoyager/security/advisories/new)**
  (Security → Advisories) if enabled, **or**
- Email `ammari.ali.0001@gmail.com` with the subject `QtVoyager security`.

Please include: affected version / commit, OS and Qt version, reproduction
steps, and impact. We aim to acknowledge reports within a few days and will
coordinate a fix and disclosure timeline with you.

## Security posture

- **SQL is fully parameterized** (`QSqlQuery::prepare()` + bound values); a
  regression test covers SQL injection on the RFID and flight-ref lookups.
- **No hardcoded credentials** — database settings come from environment
  variables (`QTVOYAGER_DB_*`) or `QSettings`; the optional Anthropic AI key is
  read from `ANTHROPIC_API_KEY` / `QSettings` and is never committed.
- **CI scanning:** every push runs **gitleaks** (secret scanning) and **CodeQL**
  (static analysis), plus `clang-format` / `clang-tidy`.

See [`docs/security.md`](docs/security.md) for the full security model.
