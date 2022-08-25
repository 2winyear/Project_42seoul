/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex00.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:46:52 by seseo             #+#    #+#             */
/*   Updated: 2022/08/24 01:40:53 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "default.h"
#include "ex00.h"
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    char *a = "DefUAlt String";
    char b[20] = {0};
    char *c;
    int *iptr;

    for (int i = 0; a[i]; i++) {
        b[i] = a[i];
    }

    c = malloc(sizeof(int) + 1);

    iptr = (int *)(c + 8000000000);
    *iptr = 42;

    b[3] = 'a';
    b[4] = 'u';

    // a[3] = 'a'; // bus err
    // a[4] = 'u'; // bus err
    
    printf("string a: %s\n", a);
    printf("string b: %s\n", b);
    printf("%ld\n", sizeof(a));

    // DEFAULT_STR[3] = 'a';

    printf("%c\n", DEFAULT_STR[3]);

    print_default_str();

    return (0);
}


void print_default_str(void){
    printf("%s\n", DEFAULT_STR);
}