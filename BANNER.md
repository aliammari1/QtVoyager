# QtVoyager — Banner & Social Preview Spec

This file specifies the brand identity assets to render and commit under
`assets/`. **TODO:** generate the images (e.g. via the `brandkit` /
`imagegen-frontend-web` skills) and drop them in `assets/`, then wire them into
the README hero and GitHub Settings -> Social preview.

## Direction

- **Theme:** aviation navy gradient — matches the in-app QSS
  (`QColor(5, 24, 150)` graphics background; `Outfit` typeface).
- **Mood:** clean, technical, premium desktop software. Not playful.
- **Motifs:** a stylized plane silhouette tracing a dotted flight path (mirrors
  the in-app `graphics()` animation), subtle great-circle arc, faint ODBC/RFID
  data motif.
- **Palette:** deep navy `#051896` -> indigo `#3F51B5` gradient, white plane &
  path, a single accent (electric blue `#2D9CDB`).
- **Type:** `Outfit` (app font) for the wordmark "QtVoyager"; tagline in a
  lighter weight.
- **Tagline:** "Qt desktop travel management with RFID check-in."

## Deliverables (commit to `assets/`)

| File | Size | Use |
|------|------|-----|
| `assets/banner.png` | 1280×640 | GitHub social preview + README hero |
| `assets/logo.svg` | square | wordmark / icon (also reusable as app icon) |
| `assets/og.png` | 1200×630 | docs site / link previews |

Keep them as committed local SVG/PNG so they never rate-limit or 404.
