CXX=g++
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic
EXECUTABLE = PInc
DOTO = .main.o .setup.o .position.o .interpreter.o .Commands.o .motor.o .line_move.o

all: $(DOTO)
	$(CXX) $(CXXFLAGS) $^ -o $(EXECUTABLE)

.main.o: main.cpp position.h enums.h Aux_Data.h
	$(CXX) $(CXXFLAGS) -c $< -o .main.o

.setup.o: setup.cpp setup.h Aux_Data.h
	$(CXX) $(CXXFLAGS) -c $< -o .setup.o

.position.o: position.cpp position.h Aux_Data.h
	$(CXX) $(CXXFLAGS) -c $< -o .position.o

.interpreter.o: interpreter.cpp interpreter.h setup.h position.h Commands.h Aux_Data.h motor.h
	$(CXX) $(CXXFLAGS) -c $< -o .interpreter.o

.Commands.o: Commands.cpp Commands.h Aux_Data.h motor.h
	$(CXX) $(CXXFLAGS) -c $< -o .Commands.o

.line_move.o: linear_move_command.cpp Commands.h Aux_Data.h motor.h
	$(CXX) $(CXXFLAGS) -c $< -o .line_move.o

.motor.o: motor.cpp motor.h
	$(CXX) $(CXXFLAGS) -c $< -o .motor.o

clean:
	rm -f $(EXECUTABLE) $(DOTO)
