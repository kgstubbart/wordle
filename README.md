# Wordle

This is a simple implementation of the popular game *Wordle* written in C++. The player has six chances to guess a five-letter word, with each guess providing feedback on the correctness of the letters in the word.

## Features

- Random word selection from a list of five-letter words.
- Validation of guesses:
  - *Green* for correct letters in the correct position.
  - *Yellow* for correct letters in the wrong position.
  - *Red* for incorrect letters.
- Checks if the guessed word is valid (it must be a real word from the word list).
- Keeps track of previous guesses to avoid duplicates.
- Provides feedback after every guess, and reveals the correct word if the player doesn't guess it in time.

## Setup Instructions

1. Download or clone the repository.
2. Make sure the file `five_letter_words.txt` is present in the same directory as the executable. This text file should contain a list of five-letter words, each word on a new line.
3. Compile the C++ program using a C++ compiler:

   ```bash
   g++ -o wordle wordle.cpp
   ```

4. Run the program:

   ```bash
   ./wordle
   ```

## How to Play

1. The game will prompt you to input a five-letter word.
2. You will receive feedback for each guess:
   - **Green**: Correct letter in the correct position.
   - **Yellow**: Correct letter but in the wrong position.
   - **Red**: Incorrect letter.
3. Keep guessing until you find the correct word or run out of guesses (maximum of 6 tries).

## Example

```
Five Letter Word: apple
🟧🟧🟧🟧🟧
```

After six guesses, if the correct word isn't found, the program will reveal the word and let you try again next time!
