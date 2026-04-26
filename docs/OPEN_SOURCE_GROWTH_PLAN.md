# Open Source Growth Plan

This plan converts the repository review into a practical backlog for QtVoyager.

## Quick wins

- Add screenshots or GIFs showing the travel dashboard, search, sorting, charting, RFID flow, and plane animation.
- Add a Qt Test suite for search, sorting, average-cost calculation, and file/data loading.
- Add a GitHub Actions build that installs Qt and compiles the project.
- Add clang-format and clang-tidy configuration for consistent C++ style.
- Document sample data and expected folder structure.
- Add release packaging notes for Qt Installer Framework.

## Bugs and bad practices to watch

- Raw pointer ownership and QObject lifetime issues.
- Business logic coupled directly to UI widgets.
- Missing error handling for data files and RFID input.
- Chart calculations that are not independently testable.
- Platform-specific path assumptions.

## Star growth strategy

1. Add visual screenshots and a demo dataset.
2. Add a one-command build path for each supported platform.
3. Publish release artifacts so users can try the app quickly.
4. Add `good first issue` tasks for translations, sample data, and UI polish.
5. Share the project in Qt and C++ communities.

## Trending-library opportunities

- Use Polars in a companion analysis script for travel-cost analytics.
- Use MarkItDown-style export to generate Markdown itineraries or reports.
- Use AI-assisted chart recommendations for travel trends and cost summaries.

## Suggested next PRs

- Add `tests/` with Qt Test coverage for non-UI logic.
- Add `docs/ARCHITECTURE.md` explaining UI, data loading, and charting.
- Add a CI workflow that validates the build.
