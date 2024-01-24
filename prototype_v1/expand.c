/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:08 by folim             #+#    #+#             */
/*   Updated: 2024/01/24 16:59:12 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	decide_quote(char c, bool *sq, bool *wq)
{
	if (c == 39 && !*sq && !*wq)
		*sq = true;
	else if (c == 34 && !*wq && !*sq)
		*wq = true;
}

static int	not_in_single(char *s)
{
	int		i;
	bool	sq;
	bool	wq;

	i = 0;
	sq = false;
	wq = false;
	while (s[i] != '\0')
	{
		if (s[i] == 39 || s[i] == 34)
			decide_quote(s[i], &sq, &wq);
		i++;
	}
	if ((!sq && wq) || (sq && wq) || (!sq && !wq))
		return (1);
	return (0);
}

static int	not_standalone_dollar(char *s)
{
	if (!ft_strcmp(s, "$") || !ft_strcmp(s, "\"$\""))
		return (0);
	return (1);
}

static void	expand_env_var(t_token **tokens, t_status *stat)
{
	int		len;
	char	**exp_key;
	char	**exp_value;
	t_token	*tmp;

	tmp = *tokens;
	exp_key = NULL;
	exp_value = NULL;
	while (tmp != NULL)
	{
		if (tmp->exp && ft_strcmp(tmp->token, "$?") != 0)
		{
			len = ft_strlen(tmp->token);
			exp_key = get_exp_key(tmp->token, len, stat);
			exp_value = get_exp_value(tmp->token, len, stat, exp_key);
			tmp->token = sub_exp(tmp->token, len, exp_key, exp_value);
		}
		else if (tmp->exp && !ft_strcmp(tmp->token, "$?"))
			tmp->token = ft_lltoa(stat->s_code);
                /*
                else if (ft_strchr(tmp->token, '$'))
		{
			expand_utils(&tmp->token, stat);
                        fprintf(stderr, "AFTER UTILS: %s\n", tmp->token);
                        (void) len;
                        (void) exp_key;
                        (void) exp_value;
                        (void) tmp->token;
		}
                */
		tmp = tmp->next;
	}
}

void	expansion(t_token **tokens, t_status *stat)
{
	t_token	*tmp;

	tmp = *tokens;
	(void) not_in_single;
	(void) not_standalone_dollar;
        (void) tmp;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->token, '$'))
		    if ((not_in_single(tmp->token) && not_standalone_dollar(tmp->token)) || !ft_strcmp(tmp->token, "$?"))		
                        tmp->exp = true;
		tmp = tmp->next;
	}
	expand_env_var(tokens, stat);
}
