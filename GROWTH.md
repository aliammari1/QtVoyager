# Growing QtVoyager

A practical, honest playbook for getting QtVoyager in front of the people who'd
actually use it. QtVoyager is a **native Qt 5.15 desktop app** — there is no web
demo, so growth leans on **screenshots/GIFs, downloadable installers, and the Qt
community** rather than "click to try it live."

> One-line pitch to reuse everywhere:
> **"Qt desktop travel-management app with RFID check-in + cost analytics."**

---

## 1. Repo metadata (set on GitHub → do this first)

**About** (Settings → About, the box under the repo title):

> Qt 5.15 C++ desktop app for travel/flight management: RFID traveler check-in
> (Arduino serialport), QtCharts cost analytics, ODBC storage, PDF export.
> qmake + CMake. Downloadable Windows/macOS/Linux installers.

**Topics** (Settings → Topics — exact-match, drives discovery):

```
qt  cpp  desktop  rfid  qmake  cmake  qtcharts  odbc
```

Optional extras if you want more surface area: `qt5`, `serialport`, `arduino`,
`travel-management`, `cplusplus`, `gui`.

**Social preview image:** generate `assets/banner.png` from `BANNER.md` and set
it as Settings → Social preview, so links unfurl with the hero on
Reddit/X/forums (link cards convert far better than bare URLs).

---

## 2. Where to share (Qt-specific, highest signal first)

Desktop dev attention concentrates in a few high-quality places. Lead with the
**GUI screenshot/GIF + the download table**, not a wall of text.

- **r/Qt** — the most concentrated Qt audience on Reddit. Post a "Show & Tell"
  with a GIF of CRUD → charts → RFID lookup. Title angle:
  *"I built a Qt desktop travel app with Arduino RFID check-in + QtCharts cost
  analytics (source-available)."* Reply to every comment in the first hour.
- **Qt Forum — "Showcase / Show & Tell"** (forum.qt.io) — the canonical place to
  show finished Qt apps; threads here are evergreen and SEO-indexed. Same GIF +
  the download links + a short "how it's built" note (qmake+CMake, serialport,
  ODBC).
- **dev.to / Hashnode article:** *"Building a Qt + RFID desktop app: serialport,
  QtCharts, and ODBC in C++17."* Walk through the RFID serial reader, the
  parameterized SQL, and the qmake→CMake migration. Tag `qt`, `cpp`, `rfid`,
  `desktop`. Cross-post with a `canonical_url` back to your blog.
- **Hacker News (Show HN):** lower fit for a niche desktop CRUD app, but the
  **RFID-over-serial + provenance-signed installers** angle is the hook if you
  post. Tue–Thu ~13:00–16:00 UTC. Seed the first comment with the "why."
- **X / LinkedIn:** the GIF + the one-liner + the ⭐ link. Short.

Always include: the **GIF**, the **"⬇ Download for your OS"** table, the
**📖 Docs** link, and an explicit **⭐ star** ask.

---

## 3. Awesome-list / directory submissions (compounding, passive)

One accepted listing keeps sending traffic for free. Prepare a one-line entry
and open the PR:

- **awesome-qt** (`JesseTG/awesome-qt`) — submit under the apps/tools section.
  Suggested line:

  > **[QtVoyager](https://github.com/aliammari1/QtVoyager)** — Qt 5.15 desktop
  > travel-management app with Arduino RFID check-in, QtCharts cost analytics,
  > ODBC storage and PDF export (qmake + CMake; signed installers).

- **awesome-cpp** (`fffaraz/awesome-cpp`) — only if there's a fitting
  "applications" subsection; keep the line C++-framed.
- **OpenAlternative / opensource.builders** — if framed as a free, self-hostable
  alternative to commercial travel/booking-desk tooling.

Pass the list's `awesome-lint` rules (alphabetical order, trailing-period style)
before opening the PR so it merges cleanly.

---

## 4. The demo *is* the download (own the limitation)

A Qt binary can't run in a browser, so make that a feature, not an apology:

- Lead the README/posts with a **GUI screenshot + GIF** (the real demo).
- Point to the **Releases** page: Windows `.zip`, macOS `.dmg`, Linux
  `.AppImage` — already wired in `release.yml`.
- Installers carry **SLSA build provenance**; show the `gh attestation verify`
  one-liner as a trust signal (rare for hobby desktop apps).
- Host the **mkdocs-material docs on Cloudflare Pages** and link them as
  **📖 Docs** — state plainly that CF Pages hosts the docs only and cannot run a
  native Qt app.

---

## 5. Funding / commercial license

QtVoyager is **source-available** (`LicenseRef-Source-Available-1.0`): free for
personal/educational/non-commercial use; commercial use needs a license. Make
that path obvious and frictionless:

- Keep the **Ko-fi** button in the README for support **and** commercial-license
  inquiries: <https://ko-fi.com/aliammari>
- Add a short "Commercial use?" line in posts: *"Free for personal use; ping me
  on Ko-fi or email for a commercial license."*
- Direct contact: `ammari.ali.0001@gmail.com`.

---

## 6. Keep it alive (freshness compounds)

- Tag releases regularly — each tag rebuilds signed installers and refreshes the
  Releases page (the "demo").
- Commit the **banner + a real demo GIF** (`assets/images/demo.gif`); the README
  already has the slot.
- Once shipped, add the live **OpenSSF Scorecard** and **Codecov** badges to the
  posts — visible quality signals for a desktop project.
- Cross-link sibling repos (see the README "Related projects" footer) so each
  project makes the others discoverable.

---

### Quick checklist

- [ ] Set About + 8 topics + social-preview image on GitHub
- [ ] Generate `assets/banner.png` and a demo GIF
- [ ] Post Show & Tell on **r/Qt** and the **Qt Forum** (GIF + downloads)
- [ ] Publish the dev.to "Qt + RFID desktop app" article
- [ ] Open the **awesome-qt** submission PR
- [ ] Tag a release so signed installers are live
