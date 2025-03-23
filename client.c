/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenjama <fbenjama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:07:59 by fbenjama          #+#    #+#             */
/*   Updated: 2025/03/23 02:26:45 by fbenjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
volatile int k = 1;

int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;   
}
int ft_atoi(char *s)
{
    int i = 0;
    int res = 0;
    int sign = 1;
    while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
        i++;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-')
            sign *= -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
    {
        res = (res * 10) + (s[i] - '0');
        i++;
    }
    return (sign * res);
}
void    convert_to_binary(int pid, char v)
{
    int  i =7;
    int bit;
    
    while (i >= 0)
    {
        bit = (v >> i) & 1;
        if (bit == 1)
        {
            kill(pid, SIGUSR1);
        }
        else if (bit == 0)
        {
           kill(pid, SIGUSR2);
                 //printf("Error SIGUSR2\n");
             //printf("bit %d sent successfuly\n", bit);
         }
        while (k == 1)
            usleep(100);
        k = 1;
        i--;
    }
    
}
void    ft_handler(int sig)
{
    k = 0;
}
int main(int c, char **v)
{
    int i = 0;
    int j = 0;
    int pid;
    signal(SIGUSR1, ft_handler);
    if (c == 3)
    {
        while (v[1][j])
        {
            if (is_digit(v[1][j]) == 0)
                return (0);
            j++;
        }
        pid = ft_atoi(v[1]);
        while (v[2][i])
        {
            convert_to_binary(pid, v[2][i]);
            i++;
        }
    }
}
