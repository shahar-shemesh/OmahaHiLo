# OmahaCOMP: Omaha Hi/Lo Poker Hand Evaluator

OmahaCOMP is a C++ program designed to determine the winning hand in Omaha Hi/Lo poker games. It evaluates both the high and low hands based on given inputs, following the rules and rankings specified in the task objective.

## Files

- `Board.cpp` and `Board.h`: Implementations and header file for the Board class, representing the community cards.
- `Card.cpp` and `Card.h`: Implementations and header file for the Card class, representing a single playing card.
- `Hand.cpp` and `Hand.h`: Implementations and header file for the Hand class, representing a player's hand.
- `input.txt`: Example input file containing test cases for the program.
- `main.cpp`: Main source file containing the program's entry point and logic for reading input, evaluating hands, and producing output.
- `output.txt`: Example output file containing the results of the test cases from `input.txt`.



## Requirements

- The source code.
- Brief descriptions of the algorithm.
- Fully debugged executable that runs on any Windows OS in plain DOS mode.



## Usage

To use OMAHACOMP, follow these steps:

1. **Clone the repository**: If you haven't already done so, clone this repository to your local machine using the following command:
```bash
git clone https://github.com/shahar-shemesh/OmahaHiLo
```

####

2. **Compile the source code**: Navigate to the root directory of the cloned repository and compile the source code using your preferred C++ compiler. For example:
```bash
g++ main.cpp -o omahacomp
```

This command assumes you have the GNU Compiler Collection (GCC) installed. Adjust the command accordingly if you're using a different compiler.

####

3. **Run the program**: Once the executable (`omahacomp`) is created, run the program with the following command:
```bash
./omahacomp input.txt output.txt
```


Replace `input.txt` with the path to your input file containing test cases, and `output.txt` with the desired name of the output file where the results will be saved.


#### - Input Format:
- HandA: Four cards for player A separated by hyphens.
- HandB: Four cards for player B separated by hyphens.
- Board: Five community cards separated by hyphens.
Example:
```bash
HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
```

#### - Output Format:
- The program outputs the result of the comparison for both high and low hands. The result includes the hand rank and the winner.
Example:
```bash
HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
=> HandB wins Hi (3-of-a-Kind); HandB wins Lo (7652A)
```
####

4. **View the results**: After running the program, open the output file (`output.txt`) to view the results of the test cases.


