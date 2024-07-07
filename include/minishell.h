#ifndef MINISHELL_H
# define MINISHELL_H

# include "dlink_list.h"
# include "ft_printf.h"
# include "libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "stdlib.h"
# include "string.h"
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_minishell
{
	t_list			*env;
	char			*line;
	int				pipe_count;
	t_dlinked_list	*tokenizer;
}					t_minishell;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define ERR_TITLE "minishell: "
# define SYNTAX_ERR "syntax error near unexpected token"

int					parser(t_minishell *minishell);
int					quote_handler(t_minishell *minishell, int pipe_i, int sign);
void				lexer(t_minishell *minishell);
void				parse_env(t_minishell *minishell, char **env);

void				export(t_minishell *minishell, char *key, char *value);
void				print_env(t_minishell *minishell);
t_list	*search_env(t_minishell *minishell, char *key);
void				get_pwd();
void 				*del(void *content);
void				unset(t_minishell *mini, char *key);
#endif
