/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:26:38 by hujeong           #+#    #+#             */
/*   Updated: 2023/03/07 21:18:30 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define SYNEND "minishell: syntax error: unexpected end of file\n"
# define SYNSING "minishell: unexpected EOF while looking for matching `''\n"
# define SYNDOUB "minishell: unexpected EOF while looking for matching `\"'\n"
# define SYNNEWL "minishell: syntax error near unexpected token `newline'\n"
# define SYNHERD "minishell: syntax error near unexpected token `<<'\n"
# define SYNIN "minishell: syntax error near unexpected token `<'\n"
# define SYNAPP "minishell: syntax error near unexpected token `>>'\n"
# define SYNOUT "minishell: syntax error near unexpected token `>'\n"
# define SYNPIP "minishell: syntax error near unexpected token `|'\n"

#endif