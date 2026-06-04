# Agents Corporation

Agents Corporation is a local developer automation tool that orchestrates a two-stage AI agent pipeline: Claude generates an implementation plan from a task definition, then OpenCode executes that plan against your codebase.

## How It Works

1. A task is described in a YAML file (e.g., `task.yaml`).
2. `main.cpp` reads the task, passes it along with a planning prompt (`claude_headcmd`) to Claude, which produces a step-by-step plan.
3. The plan is combined with an execution prompt (`opencode_headcmd`) and fed to OpenCode, which makes the actual code changes.

## Key Files

- **`main.cpp`** — Entry point. Parses CLI args, manages the run pipeline, and writes intermediate artifacts to `.agent-dev/runs/<timestamp>/`.
- **`claude_headcmd`** — System prompt for the planning agent (Claude).
- **`opencode_headcmd`** — System prompt for the execution agent (OpenCode).
- **`task.yaml`** — Task definition that drives the pipeline.

## Usage

```
./agent-dev run task.yaml
```
### 1. 配置项目（生成构建文件）
cmake -S . -B build

### 2. 编译
cmake --build build

### 3. 运行
./build/agent-dev run task.yaml

Each run creates a timestamped directory under `.agent-dev/runs/` containing the prompts, plan output, and execution logs.
