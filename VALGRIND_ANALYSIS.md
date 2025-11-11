# Valgrind Memory Leak Analysis - Minishell Project

## Overview
This document identifies potential memory leaks and issues that need to be fixed for Valgrind clean execution.

---

## 🔴 CRITICAL ISSUES - Must Fix

### 1. **Quote Token Memory Leak in handle_functions.c**
**Location:** `lex_analysis/handle_functions.c`

**Problem:**
```c
// Line 22: store_quote() stores the original pointer without duplicating
q->value = str;  // ❌ LEAK: 'str' is freed elsewhere but 'q->value' still points to it
```

**Issue:** 
- In `make_main_token_single()` and `make_main_token_double()`, `single_quote`/`double_quote` is passed to `store_quote()`
- The quote token stores the raw pointer without duplicating
- Later in `free_quote_chain()`, we free `q->value` which might be the same pointer as `token->value`
- This causes a **double free** issue

**Fix Required:**
```c
// In store_quote():
q->value = ft_strdup(str);  // ✅ Duplicate the string
if (!q->value)
{
    free(q);
    return NULL;
}
```

---

### 2. **Error Handling Memory Leaks**
**Location:** Multiple files

**Problem:**
When functions return NULL on error, previously allocated memory is not always freed.

**Examples:**

**File: `lex_analysis/handle_functions.c`**
```c
// Line 36-41: If store_quote fails, 'single_quote' is not freed
quote_str = store_quote(single_quote, SINGLE_QUOTE);
if(!quote_str)
{
    free(token);
    return NULL;  // ❌ 'single_quote' leaks
}
```

**File: `syntax_analysis/ast_nodes.c`**
```c
// Line 64: If malloc fails, we don't clean up
arr = store_avs(tokens);
if(!arr)
{
    free(cmd_node);  // ✅ Good
    return(NULL);    // ✅ But tokens were already consumed
}
```

**Fix Required:**
Add proper cleanup in all error paths.

---

### 3. **Readline Memory Not Freed on NULL**
**Location:** `main.c`

**Problem:**
```c
line = readline("minishell$ ");
if (!handle_input(line))
    break ;  // ❌ If line is NULL, we break without freeing
if (*line)
{
    add_history(line);
    last_status = process_line(line, env, last_status);
}
free(line);  // ❌ Never reached if line was NULL
```

**Fix Required:**
```c
line = readline("minishell$ ");
if (!line)
{
    printf("exit\n");
    break;  // ✅ OK, line is NULL, nothing to free
}
if (*line)
{
    add_history(line);
    last_status = process_line(line, env, last_status);
}
free(line);
```

---

### 4. **AST Parsing - Token Leak on Error**
**Location:** `syntax_analysis/parsers.c`, `syntax_analysis/syntax_analysis.c`

**Problem:**
```c
// In parse_pipeline():
left = parse_command(tokens);
if(!left)
    return (NULL);  // ❌ Tokens were consumed but AST not built
```

**Issue:** When parsing fails midway, tokens are already consumed but AST nodes may leak.

**Fix Required:**
Ensure all allocated AST nodes are freed on error before returning NULL.

---

### 5. **Environment Array Not Updated**
**Location:** `src/env/env_utils.c`

**Problem:**
```c
void set_env_value(t_env *env, char *key, char *value)
{
    // ... updates env->vars linked list
    // ❌ But env->envp_array is NOT updated!
    // This causes a stale array to exist
}
```

**Fix Required:**
```c
void set_env_value(t_env *env, char *key, char *value)
{
    // ... existing code ...
    
    // Update the array
    if (env->envp_array)
        free_array(env->envp_array);
    env->envp_array = env_to_array(env);
}
```

---

## 🟡 MODERATE ISSUES - Should Fix

### 6. **File Descriptor Leaks**
**Location:** `src/executor/heredoc.c`, `src/executor/redir_files.c`

**Problem:**
- File descriptors opened in child processes may not be closed properly
- In error cases, FDs are not always closed

**Example:**
```c
// heredoc.c
fd = open_heredoc_tmp();
// If read_heredoc_lines fails, fd might not be closed
```

**Fix Required:**
Ensure all file descriptors are closed in error paths.

---

### 7. **Global Variable g_signal_received**
**Location:** Signal handling

**Problem:**
Global variables can cause issues with Valgrind if not properly initialized.

**Fix Required:**
Ensure `g_signal_received` is initialized to 0 at program start.

---

## 🟢 MINOR ISSUES - Nice to Have

### 8. **Readline History Leaks**
**Location:** `main.c`

**Problem:**
```c
rl_clear_history();  // ✅ Good, but...
```

**Note:** Readline's internal structures may still report "still reachable" in Valgrind. This is usually acceptable but can be suppressed.

**Suppression File Example:**
```
{
   readline_leak
   Memcheck:Leak
   ...
   fun:readline
}
```

---

### 9. **Split Function Memory**
**Location:** Throughout (anywhere ft_split is used)

**Issue:** When ft_split is used, need to ensure the entire array is freed with free_array().

**Currently:** Seems to be handled correctly with free_array() utility function.

---

## 📋 CHECKLIST FOR VALGRIND CLEAN

### Must Complete:
- [ ] Fix double-free in quote token handling (store_quote)
- [ ] Add cleanup for 'single_quote'/'double_quote' in error paths
- [ ] Fix readline NULL handling in main loop
- [ ] Ensure AST nodes are freed on parse errors
- [ ] Update envp_array when environment changes

### Should Complete:
- [ ] Add proper FD cleanup in all error paths
- [ ] Review all malloc/strdup calls for matching free calls
- [ ] Ensure tokens are properly freed after use

### Testing Commands:
```bash
# Basic test
echo "ls" | valgrind --leak-check=full --show-leak-kinds=all ./minishell

# More complex test
echo "ls | grep minishell" | valgrind --leak-check=full ./minishell

# With suppression file (for readline)
valgrind --leak-check=full --suppressions=readline.supp ./minishell
```

---

## 🔧 SPECIFIC CODE FIXES NEEDED

### Fix 1: lex_analysis/handle_functions.c
```c
t_quote_token *store_quote(char *str, t_quote_type qtype)
{
    t_quote_token *q;

    q = malloc(sizeof(t_quote_token));
    if(!q)
        return NULL;
    q->value = ft_strdup(str);  // ✅ FIX: Duplicate instead of assign
    if (!q->value)               // ✅ FIX: Check allocation
    {
        free(q);
        return NULL;
    }
    q->qtype = qtype;
    q->next = NULL;
    return(q);
}
```

### Fix 2: lex_analysis/handle_functions.c (handle_single_quotes)
```c
int handle_single_quotes(t_token **token_list, char *input)
{
    // ... existing code ...
    token = make_main_token_single(single_quote);
    if(!token)
    {
        free(single_quote);  // ✅ FIX: Free on error
        return(0);
    }
    // ... rest of code ...
}
```

### Fix 3: main.c
```c
while (1)
{
    line = readline("minishell$ ");
    if (!line)  // ✅ FIX: Check NULL first
    {
        printf("exit\n");
        break;
    }
    if (*line)
    {
        add_history(line);
        last_status = process_line(line, env, last_status);
    }
    free(line);  // ✅ Now safe to free
}
```

---

## 📊 SUMMARY

**Total Issues Found:** 9
- Critical: 5
- Moderate: 2  
- Minor: 2

**Estimated Time to Fix:** 2-3 hours

**Priority Order:**
1. Fix quote token double-free (CRITICAL)
2. Fix readline NULL handling (CRITICAL)
3. Add error path cleanup (CRITICAL)
4. Update envp_array properly (CRITICAL)
5. Fix file descriptor leaks (MODERATE)
6. Test with Valgrind (VERIFY)

---

**Last Updated:** November 11, 2025
**Analyzed By:** AI Assistant
**Project:** 42 Minishell
