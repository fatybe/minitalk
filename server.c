/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenjama <fbenjama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:31:01 by fbenjama          #+#    #+#             */
/*   Updated: 2025/03/22 02:59:18 by fbenjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// void ft_handler(int sig, siginfo_t *info, void *context)
// {
//     static char byte = 0;
//     static int i = 0;
//     ///int pid;
//     //pid = info->si_pid;
//     (void)context;

//     if (sig == SIGUSR1)
//         byte = (byte << 1) | 1;
//     else if (sig == SIGUSR2)
//         byte = (byte << 1) | 0;
//     i++;
//     if (i == 8)
//     {
//         write (1, &byte, 1);
//         i = 0;
//         byte = 0;
//     }
//     //kill(pid, SIGUSR1);
// }
void ft_handler(int sig, siginfo_t *info, void *context)
{
    if (sig == SIGUSR1)
    {
        write (1, "1", 1);
    }
    else if (sig == SIGUSR2)
    {
        write (1, "0", 1);
    }
}
int main(void)
{
    int pid;
    struct sigaction sa;
    pid = getpid();
    printf("%d\n",pid);
    
    sa.sa_sigaction = ft_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    write (1, "I'm here\n", 9);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
    {
        pause();
    }
}