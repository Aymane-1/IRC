# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aechafii <aechafii@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/09/05 21:48:02 by aechafii         ###   ########.fr        #
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
COMPONENTS_DIR := $(CONTROLLERS_DIR)/controllers

# Base variables
NAME := ircserv
MAIN := $(SRC_DIR)/main.cpp
REMOVE := rm -rf

MODULES := App Globals Client Server Command Channel CommandWorker
MODULES := $(addprefix $(MODULES_DIR)/, $(addsuffix .hpp, $(MODULES)))

CONTROLLERS := App Client Server Command Channel CommandWorker
CONTROLLERS := $(addprefix $(CONTROLLERS_DIR)/, $(addsuffix .cpp, $(CONTROLLERS)))

COMPONENTS	:= pass nick user privmsg join invite pong
COMPONENTS	:= $(addprefix $(COMPONENTS_DIR)/, $(addsuffix .cpp, $(COMPONENTS)))

SRC := $(CONTROLLERS) $(COMPONENTS)

BUILD := $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.cpp=.o)))


all: $(NAME) signature

$(NAME): $(MAIN) $(MODULES) $(BUILD)
	@echo "\t$(YELLOW)Compiling $(GREEN)$(NAME) $(CYAN)executable file...$(WHITE)"
	@$(CPP) $(CFLAGS) $(C98) $(MAIN) $(BUILD) -o $(NAME)

$(BUILD_DIR)/%.o: $(CONTROLLERS_DIR)/%.cpp $(MODULES)
	@echo "\t$(YELLOW)Compiling $(GREEN)$(notdir $<) $(CYAN)object file...$(WHITE)"
	@mkdir -p $(BUILD_DIR)
	@$(CPP) $(CFLAGS) $(C98) -c $< -o $@

$(BUILD_DIR)/%.o: $(CONTROLLERS_DIR)/*/%.cpp $(MODULES)
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