mkdir -p gcc_output
cd src
g++ main.cpp applicationLoop.cpp CommandParser.cpp Enums.cpp ToyRobot.cpp Transform.cpp unitTests.cpp \
-o "..\gcc_output\toy-robot.exe" \
-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused \
-Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation \
-Wduplicated-cond -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion \
-Wformat=2 -Weffc++
cd ..