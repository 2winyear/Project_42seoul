NAME=fixed
CXX=c++
CXXFLAGS=-Wall -Wextra -Werror -std=c++98 -pedantic
SRCS_NAME=main.cpp \
		Fixed.cpp
INCFALGS=-I.
OBJS_NAME= $(SRCS_NAME:.cpp=.o)
OBJS_DIR= ./objs

OBJS= $(addprefix $(OBJS_DIR)/, $(OBJS_NAME))

all: $(NAME)

$(OBJS_DIR)/%.o: ./%.cpp
	@mkdir -p $(OBJS_DIR) 
	$(CXX) $(CXXFLAGS) $(INCFALGS) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCFALGS) $(OBJS) -o $(NAME)

clean:
	rm -rf ./objs

fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHONEY: clean fclean re all