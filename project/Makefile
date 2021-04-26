# Makefile for the ELEC/XJEL3662 Mini-project
#
# If you use an SDK (e.g. Keil) you will not need this Makefile.
# However, a few people might compile by hand, which probably means 
# you are working on a Unix system such as Mac or Linux. In that 
# case, you may find this Makefile useful.

ccflags=-Wall
	# Tell the compiler to warn of anything that looks 
	# like a mistake.

# On the following line, everything after the colon is the name 
# of the final executable file (with extension .exe on Microsoft systems).
all: calculator test_calculator

calculator: main.o calculate_answer.o high_level_funcs.o \
		mid_level_funcs.o low_level_funcs_tiva.o
	cc main.o calculate_answer.o high_level_funcs.o \
		mid_level_funcs.o low_level_funcs_tiva.o \
		-lm -o calculator

main.o: main.c calculate_answer.h high_level_funcs.h \
		low_level_funcs_tiva.h
	cc -c $(ccflags) main.c -o main.o

calculate_answer.o: calculate_answer.c calculate_answer.h
	cc -c $(ccflags) calculate_answer.c -o calculate_answer.o

high_level_funcs.o: high_level_funcs.c high_level_funcs.h \
		mid_level_funcs.h low_level_funcs_tiva.h
	cc -c $(ccflags) high_level_funcs.c -o high_level_funcs.o

mid_level_funcs.o: mid_level_funcs.c mid_level_funcs.h \
		low_level_funcs_tiva.h
	cc -c $(ccflags) mid_level_funcs.c -o mid_level_funcs.o

low_level_funcs_tiva.o: low_level_funcs_tiva.c low_level_funcs_tiva.h
	cc -c $(ccflags) low_level_funcs_tiva.c -o low_level_funcs_tiva.o

# ---------------------------- test_calculator --------------------

test_calculator: test_calculator.o calculate_answer.o
	cc test_calculator.o calculate_answer.o -lm -o test_calculator

test_calculator.o: test_calculator.c calculate_answer.h
	cc -c $(ccflags) test_calculator.c -o test_calculator.o
	
