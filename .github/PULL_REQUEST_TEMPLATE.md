<!-- Thanks for contributing to QtVoyager! Please fill out the sections below. -->

## Summary

<!-- What does this PR change and why? Link related issues, e.g. "Closes #123". -->

## Type of change

- [ ] Bug fix
- [ ] New feature
- [ ] Documentation
- [ ] Refactor / cleanup
- [ ] Build / CI / tooling
- [ ] Security

## How was this tested?

<!-- Describe how you verified the change. -->

- [ ] Built with CMake (`cmake -S . -B build && cmake --build build`)
- [ ] Built with qmake (`qmake GestionDeVoyages.pro && make`)
- [ ] `ctest` passes (`QT_QPA_PLATFORM=offscreen ctest --test-dir build`)
- [ ] Manually exercised the affected UI / RFID / DB path

**OS / Qt version tested:** <!-- e.g. Windows 11 / Qt 5.15.2 -->

## Checklist

- [ ] My code follows the project's `.clang-format` / `.clang-tidy` style
- [ ] **All SQL is parameterized** (`prepare()` + `bindValue()`) — no string concatenation of user input
- [ ] **No hardcoded credentials, DSNs, or API keys** are committed
- [ ] I added/updated **QtTest** cases for behavior changes (esp. SQL & cost/profit math)
- [ ] I updated documentation (`docs/`, README) where relevant
- [ ] CI (3-OS build, tests, CodeQL, gitleaks, clang-format/tidy) is green
