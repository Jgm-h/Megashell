#include "minishell.h"
#include "parser.h"

/*TODO:
 * 	- [ ] match type for redir type (ft_strncmp)
 * */
t_token	*get_redir(char *prompt, int i, char *redire_type)
{
	t_token	*res;
	int		j;
	char	*ret;
	int		start;

	j = i + strlen(redire_type);
	while (prompt[j] && iswhitespace(prompt[j]))
		j++;
	start = j;
	while (prompt[j] && !iswhitespace(prompt[j]))
		j++;
	ret = ft_calloc(j - start + 1, sizeof (char));
	ft_strlcpy(ret, &prompt[start], j - start);
	res = ft_calloc(1, sizeof(t_token));
	res->type = IN_REDIR;
	res->argv = ret;
	ft_strlcpy(&prompt[i], &prompt[j], ft_strlen(&prompt[j]));
	return (res);
}

t_token	*redir(char *prompt)
{
	t_token 	*res;
	t_token 	*tmp;
	t_token 	*tmp2;
	int			i;
	static char	*strings[] = { "<<", ">>", ">", "<" };

	res = 0;
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] ==  '"' || prompt[i] == '\'')
			i = skip_quotes(prompt, i);
		while (++i < 4)
		{
			if (ft_strncmp(&prompt[i], strings[i], strlen(strings[i])) == 0)
			{
				tmp2 = get_redir(prompt, i, strings[i]);
				if (res == 0)
					res = tmp2;
				if (tmp)
					tmp->right = tmp2;
				else
					tmp  = tmp2;
			}
		}
	}
	return (res);
}