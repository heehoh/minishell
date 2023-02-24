/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hujeong <hujeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:20:44 by hujeong           #+#    #+#             */
/*   Updated: 2023/02/23 19:25:51 by hujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

int main() {
    char* input;
    while (1) {
        input = readline("minishell $> ");
        printf("You entered: %s\n", input);
		add_history(input);
        //rl_on_new_line();  // 입력중인 줄의 시작으로 커서 이동
		free(input);
    }
    return 0;
}
