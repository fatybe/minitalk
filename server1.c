/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenjama <fbenjama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:32:59 by fbenjama          #+#    #+#             */
/*   Updated: 2025/03/22 22:04:46 by fbenjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int binary_to_char(char *s)
{
    int n = 0;
    int i = 0;
    while (s[i])
    {
        n = (n * 2) + (s[i] - 48);
        i++;
    }
    return (n);
}
void handler(int sig, siginfo_t *info, void *context)
{
    static char s[8];
    static int i = 0;
    char c;
    static int pid;
    if (pid != info->si_pid)
    {
        i = 0;
    }
    if (i < 8)
    {
        if (sig == SIGUSR1)
            s[i] = '1';
        else if (sig == SIGUSR2)
            s[i] = '0';
        i++;
    }
    if (i == 8)
    {
        s[8] = '\0';
        c = (char)binary_to_char(s);
        write (1, &c, 1);
	    i = 0;
    }
    pid = info->si_pid;
    kill(pid, SIGUSR1);
}
// void handler(int sig, siginfo_t *info, void *context)
// {
//     int pid;
//     pid = info->si_pid;
//     if (sig == SIGUSR1)
//     {
//         write (1, "1", 1);
//     }
//     else if (sig == SIGUSR2)
//     {
//         write (1, "0", 1);
//     }
//     kill(pid, SIGUSR1);
// }
int main(void)
{
    int pid;
    struct sigaction sa;
    pid = getpid();
    printf("%d\n",pid);
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
    {
        pause();
    }
}
