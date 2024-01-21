/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concurrent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiman-m <maiman-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 08:01:50 by maiman-m          #+#    #+#             */
/*   Updated: 2024/01/21 11:32:05 by maiman-m         ###   ########.fr       */
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
    (void) cmds;
    (void) i;
    t_command	*cur;

    cur = *cmds;
    while (cur != NULL)
    {
        //fprintf(stderr, "%i / %i\n", cur->pos, cur->size);
        if (cur->pos != i)
        {
            /*
            //if (cur->read_end != -1 && cur->pos != 0)
            //if (cur->pos != 0)
            if (cur->read_end != -1)
            {
                print_inode(cur->read_end, cur->cmd, 'r');
                close_err(cur->read_end, cur->stat);
            }
            //if (cur->write_end != -1 && cur->pos != cur->size - 1) 
            //if (cur->pos != cur->size - 1) 
            if (cur->write_end != -1)
            {
                print_inode(cur->write_end, cur->cmd, 'w');
                close_err(cur->write_end, cur->stat);
            }
            */
            /*
            if (cur->pos == 0)
            {
                print_inode(cur->write_end, cur->cmd, 'w');
                close_err(cur->write_end, cur->stat);
            }
            else if (cur->pos == cur->size - 1)
            {
                print_inode(cur->read_end, cur->cmd, 'r');
                close_err(cur->read_end, cur->stat);
            }
            else
            {
                print_inode(cur->write_end, cur->cmd, 'w');
                close_err(cur->write_end, cur->stat);
                print_inode(cur->read_end, cur->cmd, 'r');
                close_err(cur->read_end, cur->stat);
            }
            */
            close_err(cur->write_end, cur->stat);
            close_err(cur->read_end, cur->stat);
        }
        cur = cur->next;
    }
}
