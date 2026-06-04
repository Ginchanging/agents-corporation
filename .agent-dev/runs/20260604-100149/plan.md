# Implementation Plan: Add Project Introduction to README

## 1. Inspect Existing Files

- **`README.md`** — Read the full current content to understand what's already there and where to insert the new section without removing anything.
- **`main.cpp`** — Skim to understand what the project does (language, purpose, entry point).
- **`claude_headcmd`** / **`opencode_headcmd`** — Skim to understand the tool's role and usage patterns.
- **`task.yaml`** — Already read; no further action needed.

## 2. Synthesize Project Description

Based on the code review, draft a concise project introduction covering:

- What the project is (a local developer automation tool)
- Key components / commands it provides
- Target audience / use case

Keep it to 3–6 sentences or a short paragraph.

## 3. Edit README.md

- Open `README.md`.
- Insert a new `## About` (or `## Project Introduction`) section **after** any existing title/badge line but **before** any other existing content, so nothing is deleted.
- Paste the drafted description into that section.
- Verify the original content is fully intact below the new section.

### Example insertion point

```markdown
# Project Title        ← keep as-is

## About               ← NEW section inserted here
<project introduction paragraph>

<...existing content unchanged below...>
```

## 4. Verify Acceptance Criteria

| Criterion | How to check |
|---|---|
| README contains a project introduction | Read `README.md` and confirm the new section is present |
| Original content not deleted | Diff the file: every original line must still exist |
| Only `README.md` modified | `git diff --name-only` should show only `README.md` |
| No commit made | `git status` should show the file as modified but unstaged/uncommitted |

## 5. Do NOT Do

- Do not run `git add` or `git commit`.
- Do not modify any file other than `README.md`.
- Do not delete, reorder, or reformat existing README content.
