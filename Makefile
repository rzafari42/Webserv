SRCS			=	main.cpp \
					http/parsing_http.cpp \
					conf/ParserConf.cpp \
					cgi/CGI_Handler.cpp \
					http/HttpResponse.cpp \
					core/HttpWorker.cpp

OBJS			=	$(SRCS:.cpp=.o)

HEADERS			=	./

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
				./$(NAME) conf_files/default00.conf

valgrind: re
				valgrind --leak-check=full --leak-check=full --trace-children=yes ./$(NAME) conf/conf_files/default00.conf
SRCS			=	main.cpp \
					http/parsing_http.cpp \
					conf/ParserConf.cpp \
					cgi/CGI_Handler.cpp \
					http/HttpResponse.cpp \
					core/HttpWorker.cpp

OBJS			=	$(SRCS:.cpp=.o)

HEADERS			=	./

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
				./$(NAME) conf_files/default00.conf

valgrind: re
				valgrind --leak-check=full --leak-check=full --trace-children=yes ./$(NAME) conf/conf_files/default00.conf

