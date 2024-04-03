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
- C++ compiler (compatible with C++11 or later)
- No external libraries are required


## Usage

To use OMAHACOMP, follow these steps:

### 1. Create an input file named `input.txt`:
#### - Input Format:
- HandA: Four cards for player A separated by hyphens.
- HandB: Four cards for player B separated by hyphens.
- Board: Five community cards separated by hyphens.
Example:
```bash
HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-6d Board:Ad-Kh-5s-2d-Qd
HandA:Qc-Jd-Td-3d HandB:Tc-Jc-8h-6d Board:Ad-Kh-Qs-2d-3c
HandA:Qh-4d-Tc-8s HandB:Qc-8c-7d-2h Board:Ad-As-3c-3d-5d
```

### 2. Compile and run the program.

####

### 3. The program will read the input from `input.txt` and generate an output file named `output.txt` with the winning hands for both high and low scenarios.
#### - Output Format:
- The program outputs the result of the comparison for both high and low hands. The result includes the hand rank and the winner.
####

## Example Output
```bash
HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
=> HandB wins Hi (3-of-a-Kind);   => HandB wins Lo (7652A)

HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-6d Board:Ad-Kh-5s-2d-Qd
=> HandA wins Hi (Flush);   => No hand qualified for Low

HandA:Qc-Jd-Td-3d HandB:Tc-Jc-8h-6d Board:Ad-Kh-Qs-2d-3c
=> Split pot Hi (Straight);   => HandB wins Lo (8632A)

HandA:Qh-4d-Tc-8s HandB:Qc-8c-7d-2h Board:Ad-As-3c-3d-5d
=> HandA wins Hi (One Pair);   => HandB wins Lo (7532A)
```

####

## The Algorithm

The solution follows an object-oriented approach, where the cards, hands, and board are represented as objects. The primary classes are `Card`, `Hand`, and `Board`. The `Card` class represents a single card with its rank and suit. The `Hand` class holds a collection of cards representing a player's hand. The `Board` class inherits from the `Hand` class and additionally maintains a set of hands corresponding to the players.

The algorithm for determining the winning hand is implemented in the `whoWinsHi` and `whoWinsLo` functions of the `Board` class. Here's a breakdown of how the algorithm works:

1. **High Hand Evaluation**:
   - The `whoWinsHi` function iterates over each hand in the board.
   - For each hand, it creates two arrays: `countRanksArr` to count the occurrences of each rank, and `countSuitsArr` to count the occurrences of each suit.
   - The function then checks for various hand combinations, such as Straight Flush, Four of a Kind, Full House, Flush, Straight, Three of a Kind, Two Pair, One Pair, and High Card, in descending order of rank.
   - It uses helper functions like `flush`, `fourKinds`, `fullHouse`, `straight`, `threeKinds`, and `twoPair` to determine if a hand satisfies the conditions for each combination.
   - If a hand satisfies a particular combination, its score is updated accordingly.
   - After evaluating both hands, the function compares their scores and determines the winner. If there's a tie, it calls the `fight` function to break the tie based on high cards and kickers.
   - The winning hand and its rank are returned as a string.

2. **Low Hand Evaluation**:
   - The `whoWinsLo` function iterates over each hand in the board.
   - For each hand, it creates a set `card` to store the unique ranks present in the hand and board, excluding ranks higher than 8 and duplicate ranks.
   - If the size of the set is less than 5 or if there are more than 2 cards with ranks higher than 8, the hand is disqualified for the low hand.
   - Otherwise, the function sorts the ranks in descending order, keeping only the 5 highest ranks.
   - The sorted ranks are then combined to form a number, which represents the score for the low hand.
   - After evaluating both hands, the function compares their scores and determines the winner for the low hand. If both hands are disqualified, it returns "No hand qualified for Low".

The algorithm makes use of helper functions like `getHighCard` and `getKicker` to determine the high card and kicker card in case of ties. Additionally, it utilizes data structures like vectors, sets, and maps to efficiently store and manipulate card data.
