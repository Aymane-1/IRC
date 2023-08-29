# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sel-kham <sel-kham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/15 03:50:33 by sel-kham          #+#    #+#              #
#    Updated: 2023/08/29 22:22:09 by sel-kham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colrs
RED := \033[0;31m
WHITE := \033[0;37m
GREEN := \033[0;32m
BLUE := \033[0;34m
YELLOW := \033[0;33m
CYAN := \033[0;36m
BBLACK := \033[1;30m

# Compiling
CPP := c++

# Flags
CFLAGS := -Wall -Wextra -Werror 
C98 := -std=c++98

# Directories
SRC_DIR := src
BUILD_DIR := build

# Subdirectories
MODULES_DIR := $(SRC_DIR)/modules
HELPERS_DIR := $(SRC_DIR)/helpers
CONTROLLERS_DIR := $(SRC_DIR)/controllers

# Base variables
NAME := ircserv
MAIN := $(SRC_DIR)/main.cpp
REMOVE := rm -rf

MODULES := App Globals Client Server Command Channel
MODULES := $(addprefix $(MODULES_DIR)/, $(addsuffix .hpp, $(MODULES)))

CONTROLLERS := App Client Server Command Channel
CONTROLLERS := $(addprefix $(CONTROLLERS_DIR)/, $(addsuffix .cpp, $(CONTROLLERS)))

SRC := $(CONTROLLERS)

BUILD := $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.cpp=.o)))


all: $(NAME) signature

$(NAME): $(MAIN) $(MODULES) $(BUILD)
	@echo "\t$(YELLOW)Compiling $(GREEN)$(NAME) $(CYAN)executable file...$(WHITE)"
	@$(CPP) $(CFLAGS) $(C98) $(MAIN) $(BUILD) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/*/%.cpp $(MODULES)
	@echo "\t$(YELLOW)Compiling $(GREEN)$(notdir $<) $(CYAN)object file...$(WHITE)"
	@mkdir -p $(BUILD_DIR)
	@$(CPP) $(CFLAGS) $(C98) -c $< -o $@

clean:
	@echo "\t$(RED)Removing $(CYAN)object files...$(WHITE)"
	@$(REMOVE) $(BUILD_DIR)

fclean: clean
	@echo "\t$(RED)Removing $(CYAN)executable file $(GREEN)$(NAME)...$(WHITE)"
	@$(REMOVE) $(NAME)

re: fclean all

signature:
	@echo
	@echo
	@echo "\t\t$(CYAN)██╗██████╗░░█████╗░  ░██████╗███████╗██████╗░██╗░░░██╗███████╗██████╗░$(WHITE)"
	@echo "\t\t$(CYAN)██║██╔══██╗██╔══██╗  ██╔════╝██╔════╝██╔══██╗██║░░░██║██╔════╝██╔══██╗$(WHITE)"
	@echo "\t\t$(CYAN)██║██████╔╝██║░░╚═╝  ╚█████╗░█████╗░░██████╔╝╚██╗░██╔╝█████╗░░██████╔╝$(WHITE)"
	@echo "\t\t$(CYAN)██║██╔══██╗██║░░██╗  ░╚═══██╗██╔══╝░░██╔══██╗░╚████╔╝░██╔══╝░░██╔══██╗$(WHITE)"
	@echo "\t\t$(CYAN)██║██║░░██║╚█████╔╝  ██████╔╝███████╗██║░░██║░░╚██╔╝░░███████╗██║░░██║$(WHITE)"
	@echo "\t\t$(CYAN)╚═╝╚═╝░░╚═╝░╚════╝░  ╚═════╝░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝$(WHITE)"
	@echo
	@echo "\t\t\t$(YELLOW)* $(GREEN)Soufiane $(YELLOW):\t $(CYAN)https://github.com/MGS15$(WHITE)"
	@echo "\t\t\t$(YELLOW)* $(GREEN)Aeymne   $(YELLOW):\t $(CYAN)https://github.com/Aymane-1$(WHITE)"
	@echo "\t\t\t$(YELLOW)* $(GREEN)Mahmoud  $(YELLOW):\t $(CYAN)https://github.com/7ach7ouch101$(WHITE)"
	@echo

.PHONY: all clean fclean re signature