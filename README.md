# Toy Robot Coding Challenge

Technical assessment challenge for job interview process

## Build and Run with GCC/G++

### Pre-requisites
For the above to work correctly, the GCC compilers must be in your system `PATH`

### Build
Open a shell in the root of the cloned project and run the following

```bash
./build.sh
```

This will output the executable binary to ./gcc_output

### Run 
To run the program with standard user keyboard input:
```bash
./gcc_output/toy-robot.exe
```

To run the program's unit test suite
```bash
./gcc_output/toy-robot.exe -run-unit-tests
```

To run the program with external file input
```bash
./gcc_output/toy-robot.exe -file ./file_data/sample_data.txt
```


## Build and Run with Microsoft Visual Studio

This solution/project was created with Visual Studio 2019. This has not been tested with other versions of Visual Studio

-  Open adamh-iress-toy-robot.sln
- Build (CTRL+SHIFT+B)
- Run (F5)

By default the project has been configured to run without unit tests or from external file. To try these command line switches, open the project properties Configuration `Properties->Debugging->Command Arguments` and use the following flags
- `-run-unit-tests`
- `-file ./file_data/sample_data.txt`

## Message
My main aim for this challenge, was to build a testable, correct and simple (in terms of readability and algorithm complexity) implementation of the requirements of the Toy Robot Code Challenge. All warnings from [CPP Best Practices](https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md#compilers) have been turned on for both MSVC and G++ builds to demonstrate code cleanliness. Unit tests along with a minimal unit test framework have been added to demonstrate correctness. 

Classes and structs have been implemented where I felt they made sense, but I have not tried to shoehorn the entire design into object oriented patterns. 

I have tried to demonstrate a flexible design by allowing the unit tests, file input and `std::cin` options within the same executable via optional command line flags. 

## Feedback
Please get in touch with me at `hulbert dot adam at gmail dot com` for feedback on this submission