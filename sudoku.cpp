#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>

class SudokuSolver {
private:
    std::vector<std::vector<int>> board;
    int stepCount;
    bool showSteps;
    
public:
    SudokuSolver(bool steps = true) : stepCount(0), showSteps(steps) {
        board.resize(9, std::vector<int>(9, 0));
    }
    
    // Input the Sudoku board
    void inputBoard() {
        std::cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
        std::cout << "Enter row by row, space-separated:\n\n";
        
        for (int i = 0; i < 9; i++) {
            std::cout << "Row " << (i + 1) << ": ";
            for (int j = 0; j < 9; j++) {
                std::cin >> board[i][j];
            }
        }
    }
    
    // Load a sample puzzle for testing
    void loadSamplePuzzle() {
        std::vector<std::vector<int>> sample = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        };
        board = sample;
    }
    
    // Display the current board state
    void displayBoard(const std::string& message = "") {
        if (!message.empty()) {
            std::cout << "\n" << message << "\n";
        }
        
        std::cout << "\n  ┌───────┬───────┬───────┐\n";
        for (int i = 0; i < 9; i++) {
            std::cout << "  │ ";
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    std::cout << "· ";
                } else {
                    std::cout << board[i][j] << " ";
                }
                if ((j + 1) % 3 == 0) std::cout << "│ ";
            }
            std::cout << "\n";
            if ((i + 1) % 3 == 0 && i != 8) {
                std::cout << "  ├───────┼───────┼───────┤\n";
            }
        }
        std::cout << "  └───────┴───────┴───────┘\n";
        
        if (showSteps && !message.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    
    // Check if placing num at board[row][col] is valid
    bool isValid(int row, int col, int num) {
        // Check row
        for (int j = 0; j < 9; j++) {
            if (board[row][j] == num) return false;
        }
        
        // Check column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == num) return false;
        }
        
        // Check 3x3 box
        int boxRow = (row / 3) * 3;
        int boxCol = (col / 3) * 3;
        for (int i = boxRow; i < boxRow + 3; i++) {
            for (int j = boxCol; j < boxCol + 3; j++) {
                if (board[i][j] == num) return false;
            }
        }
        
        return true;
    }
    
    // Find next empty cell
    bool findEmptyCell(int& row, int& col) {
        for (row = 0; row < 9; row++) {
            for (col = 0; col < 9; col++) {
                if (board[row][col] == 0) return true;
            }
        }
        return false;
    }
    
    // Backtracking algorithm to solve Sudoku
    bool solve() {
        int row, col;
        
        // Find next empty cell
        if (!findEmptyCell(row, col)) {
            return true; // No empty cells, puzzle solved
        }
        
        // Try numbers 1-9
        for (int num = 1; num <= 9; num++) {
            if (isValid(row, col, num)) {
                stepCount++;
                board[row][col] = num;
                
                if (showSteps) {
                    std::cout << "\nStep " << stepCount << ": Trying " << num 
                              << " at position (" << (row + 1) << "," << (col + 1) << ")";
                    displayBoard();
                }
                
                // Recursively solve
                if (solve()) {
                    return true;
                }
                
                // Backtrack
                board[row][col] = 0;
                if (showSteps) {
                    std::cout << "\nBacktracking: Removing " << num 
                              << " from position (" << (row + 1) << "," << (col + 1) << ")";
                    displayBoard();
                }
            }
        }
        
        return false; // No solution found
    }
    
    // Validate if the current board state is valid
    bool isValidBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != 0) {
                    int temp = board[i][j];
                    board[i][j] = 0;
                    if (!isValid(i, j, temp)) {
                        board[i][j] = temp;
                        return false;
                    }
                    board[i][j] = temp;
                }
            }
        }
        return true;
    }
    
    // Main solving function
    void solvePuzzle() {
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "           SUDOKU SOLVER\n";
        std::cout << std::string(50, '=') << "\n";
        
        displayBoard("Initial Puzzle:");
        
        if (!isValidBoard()) {
            std::cout << "\nError: Invalid puzzle! Please check your input.\n";
            return;
        }
        
        std::cout << "\nSolving using backtracking algorithm...\n";
        std::cout << "Press Enter to start solving...";
        std::cin.ignore();
        std::cin.get();
        
        auto start = std::chrono::high_resolution_clock::now();
        
        if (solve()) {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            
            std::cout << "\n" << std::string(50, '=') << "\n";
            std::cout << "          PUZZLE SOLVED!\n";
            std::cout << std::string(50, '=') << "\n";
            displayBoard("Final Solution:");
            std::cout << "\nSolved in " << stepCount << " steps\n";
            std::cout << "Time taken: " << duration.count() << " milliseconds\n";
        } else {
            std::cout << "\nNo solution exists for this puzzle!\n";
        }
    }
    
    // Toggle step display
    void toggleStepDisplay() {
        showSteps = !showSteps;
        std::cout << "Step display " << (showSteps ? "enabled" : "disabled") << "\n";
    }
};

int main() {
    SudokuSolver solver;
    int choice;
    
    while (true) {
        std::cout << "\n" << std::string(40, '=') << "\n";
        std::cout << "       SUDOKU SOLVER MENU\n";
        std::cout << std::string(40, '=') << "\n";
        std::cout << "1. Enter custom puzzle\n";
        std::cout << "2. Use sample puzzle\n";
        std::cout << "3. Toggle step display\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option (1-4): ";
        
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                solver.inputBoard();
                solver.solvePuzzle();
                break;
            case 2:
                solver.loadSamplePuzzle();
                solver.solvePuzzle();
                break;
            case 3:
                solver.toggleStepDisplay();
                break;
            case 4:
                std::cout << "\nThanks for using Sudoku Solver!\n";
                return 0;
            default:
                std::cout << "\nInvalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
