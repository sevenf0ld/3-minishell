/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: folim <folim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:47:12 by folim             #+#    #+#             */
/*   Updated: 2024/02/01 11:43:10 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*
   return 1 if absolute path
   return 0 if relative path
   return -1 on error
   return 2 if ./
*/
//n_builtins_3
static int check_path_type(char *path_str)
{
    /*
	if (!access(path_str, F_OK))
        {
                if (path_str[0] == '.' && path_str[1] == '/')
                    return (2);
		return (1);
        }
    */
        if (path_str[0] == '.' && path_str[1] == '/')
            return (2);
        else if (!access(path_str, F_OK))
            return (1);
	else if (path_str[0] == '/')
                return (-1);
	return (0);
}

static char	*join_and_free(char *to_free, char *to_concat)
{
	char	*end;

	end = ft_strjoin(to_free, to_concat);
	free(to_free);
	to_free = NULL;
	return (end);
}

//n_builtins
static char    *get_path_str(char *path, char *cmd)
{
    char    **env_path;
    char    *path_str;
    int     i;

    env_path = ft_split(path, ':');
    path_str = NULL;
    i = 0;
    while (env_path[i] != NULL)
    {
        path_str = ft_strjoin(env_path[i], "/");
        path_str = join_and_free(path_str, cmd);
        if (!access(path_str, F_OK))
            return (path_str);
        i++;
    }
    return (NULL);
}

static void execute_non_exe(t_command *c_node, t_mini *mi)
{
    /*
    int tmp_inre;
    int tmp_outre;
    int tmp_add;
    char    *buf;
    
    if (!access(c_node->cmd, X_OK))
    {
        tmp_inre = lim_err(c_node->cmd + 2, O_RDONLY, 0444, mi->stat);
        tmp_outre = lim_err("tmp_exe.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777, mi->stat);
        tmp_add = lim_err("tmp_exe.txt", O_CREAT | O_WRONLY | O_APPEND, 0666, mi->stat);
        write(tmp_outre, "#!/usr/bin/bash\n\n", ft_strlen("#!/usr/bin/bash\n\n"));
        buf = get_next_line(tmp_inre);
        while (buf != NULL)
        {
            write(tmp_add, buf, ft_strlen(buf));
            free(buf);
            buf = get_next_line(tmp_inre);
        }
        free(buf);
        //this will not work if we relaunch v1 and run non-builtins
        //free_2d_arr(c_node->args);
        //c_node->args = malloc(sizeof(char *) * 3);
        //c_node->args[0] = "bash";
        //c_node->args[1] = "tmp_exe.txt";
        //c_node->args[2] = NULL;
        //mini_exec(c_node, mi, NULL);
        //rename the file to the original but the original will have the shebang statement
        //pid_t tmp;
        //tmp = fork();
        //if (tmp == 0)
        //{
        //    char    **mv_tmp = malloc(sizeof(char *) * 4);
        //    mv_tmp[0] = "/usr/bin/mv";
        //    mv_tmp[1] = "tmp_exe.txt";
        //    mv_tmp[2] = c_node->cmd + 2;
        //    mv_tmp[3] = NULL;
        //    execve(mv_tmp[0], mv_tmp, NULL);
        //}
        //execute the new file. use this or use bash (refer to 126.c)
        //tmp = fork();
        //if (tmp == 0)
        //{
        //    char    **exe_tmp = malloc(sizeof(char *) * 2);
        //    exe_tmp[0] = c_node->cmd;
        //    exe_tmp[1] = NULL;
        //    execve(exe_tmp[0], exe_tmp, NULL);
        //}
    }
    */
    if (access(c_node->cmd + 2, F_OK) != 0)
    {
        ft_putstr_fd("minishell: ", 2);
        report_err(c_node->cmd, 1, mi->stat);
        mi->stat->s_code = 127;
        c_node->retval = mi->stat->s_code;
    }
    else if (access(c_node->cmd + 2, X_OK) != 0)
    {
        ft_putstr_fd("minishell: ", 2);
        report_err(c_node->cmd, 1, mi->stat);
        mi->stat->s_code = 126;
        c_node->retval = mi->stat->s_code;
    }
    else
        ft_putendl_fd("not required by the subject", STDERR_FILENO);
}

//n_builtins & n_builtins_1
static int execute_b_nb(t_command *c_node, t_mini *mi, char *path_str)
{
    char    *path;
    char    **envp;

    path = NULL;
    envp = malloc_err(sizeof(char *) * 2, mi->stat);
    envp[0] = ft_strjoin("TERM=", get_fvalue(mi->fix, "TERM"));
    envp[1] = NULL;
    if (c_node->builtin)
        return (mini_exec(c_node, mi, envp));
    if (!path_str)
    {
        path = get_fvalue(mi->fix, "PATH");
        if (!path)
            return (path_err(c_node, 1, mi->stat));
        path_str = get_path_str(path, c_node->cmd);
        if (!path_str || !ft_strlen(c_node->cmd) )
            return (path_err(c_node, 2, mi->stat));
    }
    c_node->args[0] = path_str;
    return (mini_exec(c_node, mi, envp));
}

//n_builtins
void    fork_exec(t_command *c_node, t_mini *mi)
{
    int     abs_rel_path;
    char     *path_str;

    if (!c_node->exec)
        return ;
    c_node->cmd = c_node->args[0];
    abs_rel_path = check_path_type(c_node->cmd);
    path_str = NULL;

    if (abs_rel_path == -1)
        path_err(c_node, 1, mi->stat);
    else if (abs_rel_path == 2)
        execute_non_exe(c_node, mi);
    else if (abs_rel_path == 1 || abs_rel_path == 0)
    {
        if (abs_rel_path == 1)
            path_str = c_node->cmd;
        execute_b_nb(c_node, mi, path_str);
    }
    /*
    if (abs_rel_path == 1)
        path_str = c_node->cmd;
    else if (abs_rel_path == 0)
        execute_b_nb(c_node, mi, path_str);
    else if (abs_rel_path == -1)
        return ;
    */
}

/*
//It checks if the cmd in t_command struct is an absolute path of a command or a command itself
//Check if the path_str is accessible using access() and returns (1), else if it has '/' character it prints "No such file or directory" and returns (-1). If it doesn't fulfil both conditions then the function returns (0)
int	n_builtins_3(char *path_str)
{
	if (!access(path_str, F_OK))
		return (1);
	else if (path_str[0] == '/')
	{
		printf("minishell: %s: No such file of directory\n", path_str);
		return (-1);
	}
	return (0);
}

//It uses fork() to split the process where the child process executes execve() and the parent process frees up the allocated memory
void	n_builtins_2(t_command **a, char **input, char *cmd, t_status *stat, t_command **cmds, t_pid *all_pid)
{
	t_command	*tmp;
        char    **envp = malloc(sizeof(char *) * 2);

	tmp = *a;
        envp[1] = NULL;
        envp[0] = ft_strjoin("TERM=", get_fvalue(tmp->env_var->fixed, "TERM"));
        all_pid->pid_c[tmp->pos] = fork();
	if (all_pid->pid_c[tmp->pos] == -1)
		return ;
	if (all_pid->pid_c[tmp->pos] == 0)
	{
                close_unused_ends(cmds, tmp->pos);
                redirect_command_io(*a);
		if (!tmp->builtin)
                {
			execve(input[0], input, envp);
		        stat->s_code = 127;
                }
                else if (!ft_strcmp(tmp->cmd, "echo"))
                    b_echo(tmp);
                else if (!ft_strcmp(tmp->cmd, "pwd"))
                    b_pwd(tmp, 'w');
                else if (!ft_strcmp(tmp->cmd, "cd") && tmp->size > 1)
                    b_cd(tmp);
                else if (!ft_strcmp(tmp->cmd, "env"))
                    b_env(tmp, &(tmp->env_var->fixed));
                else if (!ft_strcmp(tmp->cmd, "unset"))
                    b_unset(tmp, &(tmp->env_var->fixed));
                else if (!ft_strcmp(tmp->cmd, "export") && tmp->size > 1)
                    b_export(tmp, &(tmp->env_var->fixed));
                else if (!ft_strcmp(tmp->cmd, "exit") && tmp->size > 1)
                    b_exit(tmp);
                exit(EXIT_SUCCESS);
	}
}

//It malloc() enough memory for a 2D str array that stores the path_str, flags and argument with NULL terminator
void	n_builtins_1(t_command **a, char *path_str, t_status *stat, t_command **cmds, t_pid *all_pid)
{
	t_command	*tmp;

	tmp = *a;
        tmp->args[0] = path_str;
	n_builtins_2(a, tmp->args, tmp->cmd, stat, cmds, all_pid);
	return ;
}


void	n_builtins(t_command **a, t_status *stat, t_command **cmds, t_pid *all_pid)
{
	int			i;
	int			j;
	t_command	*tmp;
	char		**path;
	char		*path_str;

	tmp = *a;
        if (!tmp->exec)
            return ;
	i = 0;
	j = n_builtins_3(tmp->cmd);
	path = NULL;
	path_str = NULL;
	if (j == 1)
		path_str = tmp->cmd;
	else if (j == 0)
	{
		if (tmp->builtin)
                {
                        n_builtins_2(a, NULL, NULL, stat, cmds, all_pid);
			return ;
                }
		t_fixed	*ftmp;
		for (ftmp = tmp->env_var->fixed; ftmp != NULL; ftmp = ftmp->fnext)
		{
			if (!ft_strcmp("PATH", ftmp->fkey))
			{
				path = ft_split(ftmp->fvalue, ':');
				break ;
			}
		}
		if (ftmp == NULL)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(tmp->cmd, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			tmp->stat->s_code = 127;
			return ;
		}
		while (path[i])
		{
			path_str = ft_strjoin(path[i], "/");
			path_str = ft_strjoin(path_str, tmp->cmd);
			if (!access(path_str, F_OK))
				break ;
			i++;
		}
		if (!path[i])
		{
			printf("minishell: %s: command not found\n", tmp->cmd);
			tmp->stat->s_code = 127;
		}
	}
	else if (j == -1)
		return ;
	n_builtins_1(a, path_str, stat, cmds, all_pid);
	return ;
}
*/
