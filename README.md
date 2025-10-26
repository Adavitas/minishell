Minishell Tracker:
# 🐚 Minishell – 42 Project Checklist

A small shell implementation that mimics Bash behavior.  
This checklist helps track development progress and main project milestones.

---

## ⚙️ 0. Setup

- [ ] Create `Makefile` with proper flags (`-Wall -Wextra -Werror`)
- [ ] Organize project structure:
  - `includes/`
  - `src/` (`lexer/`, `parser/`, `executor/`, `builtins/`, etc.)
  - `libft/`
- [ ] Link Readline: `-lreadline`
- [ ] Implement first loop with `readline()` and `add_history()`
- [ ] Disable Readline’s default signal handling

---

## 💬 1. Input & Prompt

- [ ] Display custom prompt (e.g. `minishell$ `)
- [ ] Handle empty inputs
- [ ] Handle `Ctrl+D` (EOF)
- [ ] Add valid commands to history
- [ ] Free allocated memory each loop
- [ ] Check for memory leaks (`valgrind`)

---

## 🚨 2. Signal Handling

- [ ] Handle `SIGINT` (Ctrl+C):
  - Print newline
  - Redisplay prompt
  - Don’t exit minishell
- [ ] Ignore `SIGQUIT` (Ctrl+\)
- [ ] Restore default behavior in child processes
- [ ] Use `rl_on_new_line()`, `rl_replace_line()`, and `rl_redisplay()`

---

## 🧩 3. Lexer (Tokenization)

- [ ] Split input into tokens (commands, arguments, operators)
- [ ] Handle quotes (`'`, `"`)
- [ ] Detect pipes (`|`) and redirections (`<`, `>`, `<<`, `>>`)
- [ ] Manage token types
- [ ] Handle syntax errors (like `||`, `>>>`)
- [ ] Skip whitespace outside quotes

---

## 🧠 4. Parser

- [ ] Group tokens into commands
- [ ] Store command name, arguments, redirections
- [ ] Build structures (linked list or AST)
- [ ] Expand environment variables (`$VAR`, `$?`)
- [ ] Handle heredocs (`<<`)
- [ ] Detect missing files or invalid syntax

---

## 🌱 5. Environment Management

- [ ] Duplicate environment (`envp`) into custom structure
- [ ] Implement built-ins:
  - [ ] `env`
  - [ ] `export`
  - [ ] `unset`
- [ ] Manage variable expansion (`$HOME`, `$USER`, `$?`)
- [ ] Update environment dynamically

---

## ⚙️ 6. Execution

- [ ] Identify built-ins:
  - [ ] `echo`
  - [ ] `cd`
  - [ ] `pwd`
  - [ ] `export`
  - [ ] `unset`
  - [ ] `env`
  - [ ] `exit`
- [ ] Run built-ins in parent process when needed
- [ ] Implement `fork()` + `execve()` for external commands
- [ ] Search executable via `PATH`
- [ ] Handle return codes and errors

---

## 🔁 7. Pipes & Redirections

- [ ] Implement input/output redirections:
  - [ ] `>` → truncate
  - [ ] `>>` → append
  - [ ] `<` → input
  - [ ] `<<` → heredoc
- [ ] Manage file descriptors with `dup2()`
- [ ] Chain multiple pipes (`cmd1 | cmd2 | cmd3`)
- [ ] Handle errors (permissions, file not found)
- [ ] Clean up all file descriptors

---

## 🧹 8. Cleanup & Exit

- [ ] Free all allocated memory
- [ ] Clear history (`rl_clear_history()`)
- [ ] Remove heredoc temp files
- [ ] Exit gracefully with correct status

---

## 🧪 9. Testing

- [ ] Compare behavior with Bash for:
  - [ ] Simple commands
  - [ ] Pipes
  - [ ] Redirections
  - [ ] Built-ins
  - [ ] Quotes
  - [ ] `$VAR` expansions
  - [ ] Signal handling (Ctrl+C, Ctrl+D)
- [ ] Run `valgrind` → no leaks

---

## ⭐ 10. Bonus (Optional)

- [ ] Logical operators (`&&`, `||`)
- [ ] Wildcards (`*`)
- [ ] Subshells (`( )`)
- [ ] Advanced error messages

---

## 📊 Summary Flow

---

### 🧠 Tips

- Always test against **/bin/bash** for expected behavior.
- Handle **memory management early**.
- Use **`valgrind`** and **`gdb`** during development.
- Keep functions **modular and single-purpose**.
- Commit regularly and tag working stages (lexer, parser, executor, etc.).

