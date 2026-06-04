I have enough context from the directory listing and git history. Here is the implementation plan:

---

## Implementation Plan: Add Project Introduction to README

### Context

- **Repository:** `Agents_corporation` — a local developer automation tool, likely a C++ agent runner (evidence: `main.cpp`, `claude_headcmd`, `opencode_headcmd` binaries).
- **Current state:** No `README.md` exists. The task requires one to be created (or updated if it exists by the time of execution).
- **Constraint:** Only modify `README.md`. Do not commit.

---

### Step 1 — Inspect existing files for content hints

Read the following to understand the project well enough to write an accurate introduction:

- `main.cpp` — reveals what the program does (entry point logic, flags, etc.)
- `claude_headcmd` / `opencode_headcmd` — names suggest these are agent head-command scripts or binaries for Claude and OpenCode backends
- `agent-dev/` directory — may contain configuration or sub-agent definitions
- `6a14f6d9-*.json` — may be a session/run artifact with useful metadata

---

### Step 2 — Determine if README.md already exists

```
ls README.md
```

- If it **exists**: read its current content fully before editing (do not delete anything).
- If it **does not exist**: create it from scratch.

---

### Step 3 — Write (or prepend) the project introduction

The introduction should cover:

1. **Project name / title** — `Agents Corporation`
2. **One-line description** — what it does (e.g., "A local developer automation harness that runs AI agents via configurable head-command adapters.")
3. **Key components** — brief bullet list of `main.cpp`, `claude_headcmd`, `opencode_headcmd`, and any agent definitions
4. **How it works** — high-level flow inferred from source

**If README already exists:** insert the introduction section *before* the existing content (or after the top-level `#` heading if one is present). Never remove any existing lines.

**If README does not exist:** create a new `README.md` with the introduction as the sole content.

Example structure:

```markdown
# Agents Corporation

Agents Corporation is a local developer automation tool that orchestrates AI agent workflows through pluggable head-command adapters (e.g., Claude, OpenCode).

## Overview

- **`main.cpp`** — Core entry point; parses task definitions and dispatches to the appropriate agent adapter.
- **`claude_headcmd`** — Head-command adapter for Claude-based agents.
- **`opencode_headcmd`** — Head-command adapter for OpenCode-based agents.
- **`agent-dev/`** — Agent development configurations and task definitions.

Tasks are described in YAML (e.g., `task.yaml`) and executed by the selected adapter, enabling automated code generation, review, and developer workflow automation from the command line.
```

*(Adjust the content based on what `main.cpp` actually reveals in Step 1.)*

---

### Step 4 — Verify acceptance criteria

Check both conditions manually before finishing:

| Criterion | Verification |
|---|---|
| README contains a project introduction | Read `README.md` and confirm a descriptive paragraph is present |
| Original content is preserved | Diff against any prior content to ensure nothing was removed |

---

### Files to touch

| File | Action |
|---|---|
| `README.md` | Create (if absent) or edit (if present) — **only this file** |

---

### What NOT to do

- Do not run `git add`, `git commit`, or `git push`.
- Do not modify `main.cpp`, `task.yaml`, or any other file.
- Do not delete or reformat existing README content if the file already exists.
