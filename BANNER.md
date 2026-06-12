# QtVoyager — Banner & Social Preview Spec

This file holds the single, ready-to-use image-generation prompt for the
QtVoyager brand banner. **TODO:** generate the image (e.g. via the `brandkit` /
`imagegen-frontend-web` skills or any text-to-image model), commit it as
`assets/banner.png` (and an optional `assets/banner@2x.png` hero), then set it as
the GitHub *Settings → Social preview*. The README already references
`assets/banner.png`.

## The prompt (copy/paste)

> A premium, flat vector technical banner for a Qt desktop application called
> **"QtVoyager"**, **1280×640**, no photo, no 3D, crisp SVG-style shapes.
> Background is a smooth diagonal **aviation gradient from deep navy `#051896`
> (top-left) to electric blue `#2D9CDB` (bottom-right)**, with a subtle indigo
> `#3F51B5` midtone — matching the app's in-app QSS background. A clean white
> **stylized airplane silhouette** flies along a **dotted great-circle flight-path
> arc** that sweeps across the banner (echoing the app's animated flight
> graphic). In the lower-right, a small **QtCharts-style donut/pie chart** in
> white and electric-blue segments suggests analytics. In the lower-left, a thin
> white-line **RFID / contactless glyph** (a card with radiating wave arcs) nods
> to the Arduino RFID check-in feature. The wordmark **"QtVoyager"** is set large
> in a clean geometric sans-serif (Outfit/Poppins style) in white, centered-left,
> with a lighter-weight tagline beneath it: *"Qt desktop travel management with
> RFID check-in."* Minimal, technical, confident — premium developer-tool feel,
> generous negative space, no clutter, no gradients on the text.

## Direction reference

- **Theme:** aviation navy → electric-blue gradient, matching the in-app QSS
  (`QColor(5, 24, 150)` graphics background; `Outfit` typeface).
- **Palette:** deep navy `#051896` → indigo `#3F51B5` → electric blue `#2D9CDB`;
  white plane, path, wordmark.
- **Motifs (all four):** vector plane silhouette, dotted flight-path arc,
  RFID/contactless glyph, QtCharts-style pie/donut chart.
- **Type:** `Outfit` (the app font) for the wordmark; lighter weight for the
  tagline.
- **Mood:** clean, technical, premium desktop software — not playful.

## Deliverables (commit to `assets/`)

| File | Size | Use |
|------|------|-----|
| `assets/banner.png` | 1280×640 | GitHub social preview + README hero |
| `assets/banner@2x.png` | 2560×1280 | optional retina hero |
| `assets/logo.svg` | square | wordmark / icon (reusable as app icon) |

Keep them as committed local SVG/PNG so they never rate-limit or 404.
