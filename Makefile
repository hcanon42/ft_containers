##---------------------------------MAKEFILE-------------------------------------

#====================================OBJS=======================================
OBJS		=	${SRCS:.cpp=.o}
#-----
.cpp.o:
				$(CCPP) $(CPPFLAGS) -o $@ -c $<

#====================================SRCS=======================================
SRCS			=	main.cpp	\
					test/Number.cpp


#=============================FLAGS AND COMPILERS===============================
CCPP			=	clang++
CPPFLAGS		=	-g -Wall -Wextra -Werror -std=c++98 -I ./
NAME			=	ft_containers


#================================AVAILABLE RULES================================
#-----
$(NAME):	${OBJS}
		${CCPP} ${CPPFLAGS} -o ${NAME} ${OBJS}

#-----
all:		$(NAME)

#-----
clean:
		rm -f ${OBJS}

#-----
fclean:		clean
		rm -f ${NAME}

#-----
re:		fclean ${NAME}

#-----
.PHONY:		all clean fclean re
