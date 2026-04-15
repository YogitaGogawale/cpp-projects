#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Function to display the game menu
void displayMenu() {
    cout << "\n=================================\n";
    cout << "   NUMBER GUESSING GAME\n";
    cout << "=================================\n";
    cout << "1. Play Game\n";
    cout << "2. View High Scores\n";
    cout << "3. Exit\n";
    cout << "=================================\n";
    cout << "Enter your choice: ";
}

// Function to save high score to file
void saveHighScore(const string& playerName, int attempts) {
    ofstream file("highscores.txt", ios::app);
    if (file.is_open()) {
        file << playerName << "," << attempts << endl;
        file.close();
    } else {
        cout << "Unable to save high score.\n";
    }
}

// Function to display high scores from file
void viewHighScores() {
    ifstream file("highscores.txt");
    cout << "\n=================================\n";
    cout << "       HIGH SCORES\n";
    cout << "=================================\n";
    
    if (file.is_open()) {
        string line;
        bool hasScores = false;
        
        while (getline(file, line)) {
            hasScores = true;
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string name = line.substr(0, commaPos);
                string attempts = line.substr(commaPos + 1);
                cout << name << " - " << attempts << " attempts\n";
            }
        }
        
        if (!hasScores) {
            cout << "No high scores yet. Be the first!\n";
        }
        
        file.close();
    } else {
        cout << "No high scores yet. Be the first!\n";
    }
    cout << "=================================\n";
}

// Function to play the guessing game
void playGame() {
    string playerName;
    cout << "\nEnter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, playerName);
    
    // Generate random number between 1 and 100
    int secretNumber = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    
    cout << "\nI'm thinking of a number between 1 and 100.\n";
    cout << "Can you guess it?\n\n";
    
    // Game loop
    while (true) {
        cout << "Enter your guess: ";
        
        // Input validation
        if (!(cin >> guess)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        attempts++;
        
        if (guess < secretNumber) {
            cout << "Too low! Try again.\n\n";
        } else if (guess > secretNumber) {
            cout << "Too high! Try again.\n\n";
        } else {
            cout << "\n🎉 Congratulations, " << playerName << "! 🎉\n";
            cout << "You guessed the number in " << attempts << " attempts!\n";
            
            // Save the score
            saveHighScore(playerName, attempts);
            break;
        }
    }
}

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    int choice;
    
    cout << "Welcome to the Number Guessing Game!\n";
    
    // Main game loop
    while (true) {
        displayMenu();
        
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                viewHighScores();
                break;
            case 3:
                cout << "\nThanks for playing! Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please select 1, 2, or 3.\n";
        }
    }
    
    return 0;
}
