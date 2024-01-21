/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concurrent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 08:01:50 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/21 21:35:21 by maiman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
static void print_inode(int fd, char *name, char mode) {
    struct stat info;
    if (fstat(fd, &info) != 0)
        fprintf(stderr,"fstat() error for %s %d: %s\n",name,fd,strerror(errno));
    else
    {
        if (mode == 'r')
            fprintf(stderr, "╳ The inode of %s (read_end) is %d\n", name, (int) info.st_ino);
        else
            fprintf(stderr, "╳ The inode of %s (write_end) is %d\n", name, (int) info.st_ino);
    }
}

void	close_unused_ends(t_command **cmds, int i)
{
    (void) print_inode;
    t_command	*cur;

    cur = *cmds;
    while (cur != NULL)
    {
        if (cur->pos != i)
        {
            if (cur->pos == 0)
            {
                //print_inode(cur->write_end, cur->cmd, 'w');
                close_err(cur->write_end, cur->stat);
                //print_inode(cur->write_end, cur->cmd, 'w');
            }
            else if (cur->pos == cur->size - 1)
            {
                //print_inode(cur->read_end, cur->cmd, 'r');
                close_err(cur->read_end, cur->stat);
                //print_inode(cur->read_end, cur->cmd, 'r');
            }
            else
            {
                //print_inode(cur->write_end, cur->cmd, 'w');
                close_err(cur->write_end, cur->stat);
                //print_inode(cur->read_end, cur->cmd, 'r');
                close_err(cur->read_end, cur->stat);
            }
        }
        cur = cur->next;
    }
}

void    last_close(t_pipe **pipes)
{
    t_pipe  *tmp;

    tmp = *pipes;
    while (tmp != NULL)
    {
        //make it safe
        close(tmp->pipe_fd[0]);
        close(tmp->pipe_fd[1]);
        tmp = tmp->next;
    }
}
