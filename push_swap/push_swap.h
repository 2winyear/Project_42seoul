/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 13:50:27 by seungyel          #+#    #+#             */
/*   Updated: 2021/09/09 09:22:15 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
#include <unistd.h>

t_stack* create_stack_with_arg(int argc, char *argv[]);

typedef struct  s_stack
{
    struct s_stack *next;
    struct s_stack *prev;
    int content;
}               t_stack;

typedef struct  s_stack
{
    t_stack *a;
    t_stack *b;
    int visualizer;
}               t_push_swap;

#endif
