.SILENT:

#--------------------------------------------------------------------------------------------------
COMPILER = g++
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
SRC = src/
HPP = headers/
OBJ = obj/
LIB = myLib/
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
INCLUDE_FLAGS = -I$(LIB) -I$(HPP)
SANITAZER     = -fsanitize=address
SFML_FLAGS    = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

FLAGS		  = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations \
			    -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wfloat-equal          \
			    -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd  \
				-Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel     \
				-Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override            \
				-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros              \
				-Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector        \
				$(INCLUDE_FLAGS)                                                                                                             \
				$(SANITAZER)
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
STACK_OBJ = $(OBJ)stack.o $(OBJ)myLib.o $(OBJ)main.o
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
run: stk

run_: stk
	./structStack.out
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
clean: 
	rm -f $(OBJ)*
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
stk: $(STACK_OBJ)
	$(COMPILER) $^ -o structStack.out $(FLAGS)
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
$(OBJ)%.o : $(SRC)%.cpp
	$(COMPILER) $(FLAGS) -c $< -o $@

$(OBJ)%.o : $(LIB)%.cpp		
	$(COMPILER) $(FLAGS) -c $< -o $@
#--------------------------------------------------------------------------------------------------
