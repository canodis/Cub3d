/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtosun <rtosun@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:49:06 by ecayir            #+#    #+#             */
/*   Updated: 2022/10/11 16:53:27 by rtosun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_strrev(char *str)
{
	int		len;
	int		i;
	char	tmp;

	len = 0;
	i = 0;
	while (str[len])
		len++;
	len -= 1;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
	return (str);
}

int	ft_len_hex(unsigned int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

char	*double_str_join(char **str)
{
	int		idx;
	char	*res;

	res = malloc(1);
	idx = 0;
	while (*(str + idx))
	{
		res = ft_strjoin(res, *(str + idx));
		idx++;
	}
	return (res);
}

char	*convert(int res, char *value)
{
	char		*hexvalue;
	long long	temp_decimal;
	char		*hex;
	int			index;
	int			rem;

	index = 0;
	hexvalue = malloc(sizeof(char) * 17);
	ft_strlcpy(hexvalue, "0123456789ABCDEF\0", 17);
	temp_decimal = res;
	hex = malloc(sizeof(char) * ft_len_hex(res) + 1);
	while (temp_decimal != 0)
	{
		rem = temp_decimal % 16;
		hex[index] = hexvalue[rem];
		temp_decimal /= 16;
		index++;
	}
	hex[index] = '\0';
	ft_strrev(hex);
	free(hexvalue);
	free(value);
	return (hex);
}

int	get_color(char *str)
{
	char	**double_array;
	int		len;
	char	*str_result;
	int		result;

	len = -1;
	double_array = ft_split(str, ',');
	while (double_array[len])
		len++;
	while (--len >= 0)
		double_array[len] = convert(ft_atoi(double_array[len]),
				double_array[len]);
	str_result = double_str_join(double_array);
	result = (ft_atoi_base(str_result));
	free(str_result);
	free_2d_array(double_array);
	return (result);
}
