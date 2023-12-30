#include "minishell.h"

t_token	*get_redir(char *prompt, int i, char *redire_type)
{
	t_token	*res;
	int		j;
	int		ind;
	char	*ret;
	int		start;

	j = i + strlen(redire_type);
	ind = 0;
	while (prompt[j] && iswhitespace(prompt[j]))
		j++;
	start = j;
	while (prompt[j] && !iswhitespace(prompt[j]))
		j++;
	ret = ft_calloc(j - start + 1, sizeof (char));
	ret = ft_strncpy(ret, &prompt[start], j - start);
	res = ft_calloc(1, sizeof(t_token));
	res->type = REDIR;// TDOO
	res->argv = ret;
	ft_strcpy(&prompt[i], &prompt[j]);
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
					tmp.next = tmp2;
				else
					tmp  = tmp2;
			}
		}
	}
	return (res);
}