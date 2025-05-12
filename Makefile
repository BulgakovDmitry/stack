Compiler = g++

SRC = src/
H = headers/
OBJ = obj/
M = myLib/

Flags	 = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations \
		   -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wfloat-equal          \
		   -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd  \
		   -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel     \
		   -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override            \
		   -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros              \
		   -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector        \
		   -fsanitize=address  
#SFML_FLAGS -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

#----------------------------------------------------------------------------------
stk: $(OBJ)stack.o $(OBJ)myLib.o $(OBJ)main.o
	$(Compiler) $(OBJ)stack.o $(OBJ)myLib.o $(OBJ)main.o -o structStack.out $(Flags)
#----------------------------------------------------------------------------------

#----------------------------------------------------------------------------------
$(OBJ)stack.o: $(SRC)stack.cpp
	$(Compiler) -c $(SRC)stack.cpp -o $(OBJ)stack.o $(Flags)
#----------------------------------------------------------------------------------
$(OBJ)main.o: $(SRC)main.cpp
	$(Compiler) -c $(SRC)main.cpp -o $(OBJ)main.o $(Flags)
#----------------------------------------------------------------------------------
$(OBJ)myLib.o: $(M)myLib.cpp		
	$(Compiler) -c $(M)myLib.cpp -o $(OBJ)myLib.o $(Flags)
#----------------------------------------------------------------------------------

run: stk

#----------------------------------------------------------------------------------
clean: 
	rm -f $(OBJ)*
#----------------------------------------------------------------------------------