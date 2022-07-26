# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasselin <gasselin@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 13:45:23 by gasselin          #+#    #+#              #
#    Updated: 2022/07/26 13:54:49 by gasselin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@chmod 777 ./run_tests.sh && ./run_tests.sh

clean:
	@rm -f tests/err.log
	@rm -rf tests/output
	@rm -rf tests/diff
	@rm -rf tests/logs

.PHONY: re clean