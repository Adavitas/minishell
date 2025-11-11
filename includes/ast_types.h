#ifndef AST_TYPES_H
# define AST_TYPES_H

# include "parser.h"

/* Forward declaration */
typedef struct s_env	t_env;

/* AST execution prototypes */
int		execute_ast(t_ast *ast, t_env *env);

#endif
