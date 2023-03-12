/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeongo <yeongo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 07:24:57 by yeongo            #+#    #+#             */
/*   Updated: 2023/02/26 09:46:18 by yeongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>

int		ft_isspace(int c);
int		ft_issign(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *str, int *result);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
void	ft_free(void **ptr);

#endif
