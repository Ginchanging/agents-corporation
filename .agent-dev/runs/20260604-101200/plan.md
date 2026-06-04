No `README.md` exists yet. The plan below accounts for that.

---

# Implementation Plan: Add Project Introduction to README

## Context

- **Working directory:** `/Users/liu./Documents/Workshop/Agents_corporation/Agents_corporation/Agents_corporation/`
- **Current state:** No `README.md` exists. Project files include `main.cpp`, `claude_headcmd`, `opencode_headcmd`, and `task.yaml`.
- **Constraint:** Only modify `README.md`; do not commit.

---

## Files to Inspect First

| File | Purpose |
|---|---|
| `main.cpp` | Understand what the program does so the introduction is accurate |
| `claude_headcmd` | Likely a shell script/config — reveals how Claude is invoked |
| `opencode_headcmd` | Similar, for OpenCode — reveals secondary tooling |
| `task.yaml` | Reference for project goals and terminology |

---

## Implementation Steps

### Step 1 — Understand the project

Read `main.cpp`, `claude_headcmd`, and `opencode_headcmd` to determine:
- What the program does
- Key features or entry points
- Any dependencies or usage patterns

### Step 2 — Check if README.md exists

```
ls README.md
```

Since no `README.md` was found in the directory listing, the file must be **created from scratch**.

### Step 3 — Write README.md

Create `README.md` with the following structure, preserving any existing content if the file does appear (the acceptance criterion says "do not delete original content"):

```markdown
# Agents Corporation

## 项目介绍

[One paragraph describing what the project does, derived from reading main.cpp and the headcmd files. Should cover: what the tool is, its purpose, and how it works at a high level.]

[Any existing content that was already in the file goes below, unchanged.]
```

The introduction should:
- State the project's purpose in plain language
- Mention that it is a local developer automation tool
- Reference key components (e.g., Claude and OpenCode integrations, if confirmed by reading the source)
- Be written in the same language as the rest of the repo (Chinese, based on `task.yaml`)

### Step 4 — Verify acceptance criteria

1. Confirm `README.md` contains a project introduction paragraph.
2. Confirm no original content was removed (if the file previously existed).
3. Confirm no other files were modified (`git diff --name-only` should show only `README.md` or be empty if the file is untracked).
4. Confirm there is no new commit (`git log --oneline -1` should still show `647d40d First`).

---

## Tests / Verification Commands

```bash
# 1. Confirm only README.md is modified or newly created
git status

# 2. Confirm no commit was made
git log --oneline -1   # should still be: 647d40d First

# 3. Confirm introduction text is present
grep -c "介绍\|Introduction\|项目" README.md   # should be >= 1

# 4. Confirm file is non-empty and well-formed
wc -l README.md        # should be > 0
```

---

## Notes

- If `main.cpp` cannot be read (permission issue), write the introduction based on the project name (`Agents_corporation`) and the `task.yaml` background description.
- Do not add a trailing newline-only file or placeholder text — the introduction must be substantive.
- Keep the tone technical but concise (2–4 sentences is sufficient for the introduction paragraph).
