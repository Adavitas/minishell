#ifndef AST_TYPES_H
# define AST_TYPES_H

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
}	t_node_type;

typedef struct s_redir	t_redir;
typedef struct s_env	t_env;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	t_redir				*redirs;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

int		execute_ast(t_ast_node *ast, t_env *env);
void	free_ast(t_ast_node *ast);

#endif
