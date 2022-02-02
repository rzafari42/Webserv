# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simbarre <simbarre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 02:31:17 by simbarre          #+#    #+#              #
#    Updated: 2022/01/31 04:33:11 by simbarre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	server.cpp \
					conf/parsing/http_request_conf/parsing_http.cpp \
					conf/parsing/nginx_conf/ParserConf.cpp \
					Header/CGI_Handler.cpp \
					Header/HttpResponse.cpp \
					Header/utils.cpp

OBJS			=	$(SRCS:.cpp=.o)

HEADERS			=	Header/

CXX				=	clang++
RM				=	rm -f
CXXFLAGS		=	-Wall -Wextra -Werror -I $(HEADERS) -std=c++98

NAME			=	webserv

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

test: re
				./$(NAME) conf/conf_files/default00.conf
