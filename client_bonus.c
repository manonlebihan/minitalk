/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-biha <mle-biha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:52:47 by mle-biha          #+#    #+#             */
/*   Updated: 2023/02/13 11:25:11 by mle-biha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	Checks if all the char are digital (between 0 and 9)
	with the function ft_isdigit, if not it retruns 0.
*/
int	check_pid(char	*pid)
{
	int	i;

	i = 0;
	while (pid[i] != 0)
	{
		if (!ft_isdigit(pid[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
	Sends a char to a process identified by the pid passed as a parameter
	Uses the function "kill" to send two different signals, SIGUSR1 and SIGUSR2,
	to the target process depending on the binary representation of the char.
	Loops through each bit of the char and send either SIGUSR1 or SIGUSR2,
	then pause while waiting for a signal from the server,
	it then waits for 100 microseconds before moving on to the next bit.
	If the "kill" function returns an error,
	the function terminates the program with exit code EXIT_FAILURE.
*/
void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((1 & (c >> i)) == 0)
		{
			if (kill(pid, SIGUSR1) != 0)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2) != 0)
				exit(EXIT_FAILURE);
		}
		i++;
		pause();
	}
}

/*
	As long as the char where we are is not '\0',
	the function sends the char to the "send_char" function.
	When the while loop is over, it sends the char '\0' 
	to the "send_char" function.
*/
void	send_message(int pid, char *message)
{
	unsigned int	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\0');
}

/*
	If the signal received is SIGUSR2, ot divides the number of bits by 8,
	them checks if the nb of char is diffrent than 0, if so, it prints that the
	message was successfully sent to the server.
	If the nb of char is different than 0, if prints that something went wrong
	and exit with a failure. Then the nb of bits is back to 0.
	if the signal sent is not SIGUSR2, the nb of bits is being incremented.
	Then, it sleeps for 100 microseconds.
*/
void	signal_handler(int sig)
{
	static int	nb_bits = 0;
	int			nb_chars;

	if (sig == SIGUSR2)
	{
		nb_chars = nb_bits / 8;
		if (nb_chars != 0)
			ft_putstr_fd("Message sent to server !\n", 2);
		else
		{
			ft_putstr_fd("Something went wrong...\n", 2);
			exit(EXIT_FAILURE);
		}
		nb_bits = 0;
	}
	else
		nb_bits++;
	usleep(100);
}

/*
	Checks the number of arguments, if below three, something is missing
	Then checks the pid, if not valid, it returns an error.
	Then sends the message to the other process.
*/
int	main(int argc, char	*argv[])
{
	if (argc != 3)
	{
		ft_putendl_fd("usage: ./client [server-pid] [message]", 2);
		exit(EXIT_FAILURE);
	}
	if (!check_pid(argv[1]))
	{
		ft_putendl_fd("Invalid PID, PID should be a number", 2);
		exit(EXIT_FAILURE);
	}
	if (argv[2][0] == '\0')
	{
		ft_putendl_fd("Invalid message, message should not be empty", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
