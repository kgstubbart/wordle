#include <string>
using std::string;

#include <iostream>
using std::cout, std::cerr, std::endl, std::cin;

#include <vector>
using std::vector;

#include <algorithm>
using std::find;

#include <cctype>
using std::tolower;

#include <fstream>
using std::ifstream, std::getline;

#include <random>
using std::random_device, std::mt19937, std::uniform_int_distribution;


string get_secret_word() {
    ifstream file("five_letter_words.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file for reading: five_letter_words.txt" << endl;
        return "";
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 5756);
    int random_line = dis(gen);

    int line = 0;
    string secret_word;
    while (line <= random_line) {
        getline(file, secret_word);
        ++line;
    }

    file.close();
    return secret_word;
}


bool word_not_real(const string& possible_word) {
    ifstream file("five_letter_words.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file for reading: five_letter_words.txt" << endl;
        return "";
    }
    string word_file;
    bool not_found_word = true;
    while (file >> word_file) {
        if (word_file == possible_word) {
            not_found_word = false;
            break;
        }
    }
    file.close();
    return not_found_word;
}


string make_lowercase(const string& in_word) {
    string lower_word = in_word;
    for (char& letter : lower_word) {
        letter = tolower(letter);
    }
    return lower_word;
}


bool check_word(const string& answer, const string& guess) {
    if (guess == answer) {
        cout << "\033[1;32m" << guess << "\033[0m" << endl;
        return true;
    }
    string correctness = "-----";
    bool used_tracker[5] = {false, false, false, false, false};
    for (int i = 0; i < 5; ++i) {
        if (answer[i] == guess[i]) {
            correctness[i] = '*';
            used_tracker[i] = true;
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (correctness[i] == '-') {
            for (int j = 0; j < 5; ++j) {
                if (!used_tracker[j] && answer[j] == guess[i]) {
                    correctness[i] = '!';
                    used_tracker[j] = true;
                    break;
                }
            }
        }
    }

    for (int k = 0; k < 5; ++k) {
        if (correctness[k] == '*') {
            cout << "\033[1;32m" << guess[k] << "\033[0m";
        }
        else if (correctness[k] == '!') {
            cout << "\033[1;33m" << guess[k] << "\033[0m";
        }
        else {
            cout << "\033[1;31m" << guess[k] << "\033[0m";
        }
    }
    cout << endl;
    return false;
}


bool guess_word(const string& secret_wordle) {
    vector<string> guessed_words;
    int guess_count = 0;
    while (guess_count < 6) {
        string word_guess;
        cout << "Five Letter Word: ";
        cin >> word_guess;
        string fixed_guess = make_lowercase(word_guess);

        if (fixed_guess.length() > 5) {
            cout << fixed_guess << " is longer than 5 letters!" << endl;
        }
        else if (fixed_guess.length() < 5) {
            cout << fixed_guess << " is shorter than 5 letters!" << endl;
        }
        else if (word_not_real(fixed_guess)) {
            cout << fixed_guess << " is not a word!" << endl;
        }
        else if(find(guessed_words.begin(), guessed_words.end(), fixed_guess) != guessed_words.end()) {
            cout << "You already guessed " << fixed_guess << "! Try another." << endl;
        }
        else {
            ++guess_count;
            guessed_words.push_back(fixed_guess);

            if (check_word(secret_wordle, fixed_guess)) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    string wordle_word = get_secret_word();
    if (guess_word(wordle_word)) {
        cout << "Well done!" << endl;
    }
    else {
        cout << "Almost! The wordle is: " << wordle_word << ". You've got this next time!" << endl;
    }
    return 0;
}
