SOURCES = $(wildcard $(C_REP)*.c)
OBJETS = $(SOURCES:.c=.o)
OBJETSC = $(patsubst $(C_REP)%.c, $(O_REP)%.o, $(SOURCES))


O_REP = obj/
E_REP = bin/
C_REP = src/
H_REP = include/
D_REP = dist/
IFLAGS = -I include -W -Wall
VPATH = $(H_REP)
vpath %.o $(E_REP)
vpath %.c $(C_REP)
vpath %.h $(H_REP)
vpath main $(O_REP)


main : $(OBJETS)
	gcc -g -o $@ $(OBJETSC)
	mkdir -p $(E_REP)
	mv $@ $(E_REP)
	@echo "\n ##################################################\n"
	@echo "            Compilation was successful :)"
	@echo "\n ##################################################\n"


%.o : %.c
	gcc -c $(IFLAGS) -o $@ $< 
	mkdir -p $(O_REP)
	mv $@ $(O_REP)


.PHONY : clean

	
clean:
	rm $(O_REP)* $(E_REP)*
	rmdir $(O_REP)
	rmdir $(E_REP)
	@echo "\n######## Directories obj/ et bin/ have been emptied and deleted ########\n"
	
docs:
	doxygen Doxyfile


dist: 
	@mkdir -p dist
	tar -l -cvf dist/Aki_Schmatzler_projet_SDA2.tar.xz src include makefile image Doxyfile compte_rendu.pdf
	@echo "\n ######## Archive created ########\n"
	

rmdist: 
		rm $(D_REP)*
		rmdir $(D_REP)
		@echo "\n########## Archive deleted ###########\n"
