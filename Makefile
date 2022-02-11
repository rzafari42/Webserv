SRCS			=	main.cpp \
					conf/parsing/http_request_conf/parsing_http.cpp \
					conf/parsing/nginx_conf/ParserConf.cpp \
					Header/CGI_Handler.cpp \
					Header/HttpResponse.cpp \
					Header/utils.cpp \
					core/HttpWorker.cpp

OBJS			=	$(SRCS:.cpp=.o)

HEADERS			=	Header/

CXX				=	g++
RM				=	rm -f
CXXFLAGS		=	-g3 -Wall -Wextra -Werror -I $(HEADERS) -std=c++98

NAME			=	webserv

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) ./autoindex.html

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

test: re
				./$(NAME) conf/conf_files/default00.conf

valgrind: re
				valgrind --leak-check=full --leak-check=full --trace-children=yes ./$(NAME) conf/conf_files/default00.conf
