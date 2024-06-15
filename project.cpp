#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

class SnakeGame {
private:
    int tailXPosition;
    int tailYPosition;
    int foodXPosition;
    int foodYPosition;
    int snakeSize;
    int score;
    char UserInput;
    char direction;
    int snakeBodySegments[128][2];
    int length = 15;  // Update the length to your desired value
    int width = 30;   // Update the width to your desired value
    string player;

public:

    void thePlayer(const string a){
        this->player = a;

    }
    SnakeGame() {
        tailXPosition = 11;
        tailYPosition = 4;
        foodXPosition = 0;
        foodYPosition = 0;
        snakeSize = 3;
        score = 0;
        UserInput = '\0';
        direction = 'a';

        for (int i = 0; i < 128; i++) {
            snakeBodySegments[i][0] = 0;
            snakeBodySegments[i][1] = 0;
        }
        snakeBodySegments[0][0] = 8;
        snakeBodySegments[0][1] = 4;
        snakeBodySegments[1][0] = 9;
        snakeBodySegments[1][1] = 4;
        snakeBodySegments[2][0] = 10;
        snakeBodySegments[2][1] = 4;
    }


    void AddSegment() {
        snakeBodySegments[snakeSize][0] = tailXPosition;
        snakeBodySegments[snakeSize][1] = tailYPosition;
        snakeSize++;
    }

    int InSnake(int x, int y) {
        for (int i = 1; i < snakeSize; i++) {
            if (snakeBodySegments[i][0] == x && snakeBodySegments[i][1] == y) {
                return 1;
            }
        }
        return 0;
    }

    void MoveSnake(int x, int y) {
        tailXPosition = snakeBodySegments[snakeSize - 1][0];
        tailYPosition = snakeBodySegments[snakeSize - 1][1];

        for (int i = snakeSize - 1; i > 0; i--) {
            snakeBodySegments[i][0] = snakeBodySegments[i - 1][0];
            snakeBodySegments[i][1] = snakeBodySegments[i - 1][1];
        }

        snakeBodySegments[0][0] += x;
        snakeBodySegments[0][1] += y;

        UserInput = '\0';
    }

    void Move() {
        if (UserInput == 'w' && direction != 's') {
            MoveSnake(0, -1);
            direction = 'w';
        } else if (UserInput == 'a' && direction != 'd') {
            MoveSnake(-1, 0);
            direction = 'a';
        } else if (UserInput == 's' && direction != 'w') {
            MoveSnake(0, 1);
            direction = 's';
        } else if (UserInput == 'd' && direction != 'a') {
            MoveSnake(1, 0);
            direction = 'd';
        } else {
            UserInput = direction;
            Move();
        }
    }

    void NewFood() {
        int x, y;
        int attempts = 0;

        while (attempts < 100) {
            x = rand() % (width - 2) + 1;
            y = rand() % (length - 2) + 1;

            if (!InSnake(x, y) && snakeBodySegments[0][0] != x && snakeBodySegments[0][1] != y) {
                foodXPosition = x;
                foodYPosition = y;
                return;
            }
            attempts++;
        }
    }




void Draw() {
    // Get the console handle for Windows-specific functions
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the cursor position to (0,0) to minimize flickering
    COORD cursorPos;/*COORD is a structure that represents a pair of X and Y coordinates.
    In this case, it will be used to specify the new cursor position on the console screen.*/
    cursorPos.X = 0;
    cursorPos.Y = 0;
    SetConsoleCursorPosition(consoleHandle, cursorPos);

    // Use a single buffer to store the updated game screen
    string buffer;

    // Append the player name and score to the buffer
    buffer += "\033[35m+---------------------------+\n";
    buffer += "\033[35m| Player Name:        " + player + "|\n";
    buffer += "\033[35m+---------------------------+\n";
    buffer += "\033[35m+-----------------+\n";
    buffer += "\033[35m| Score:        " + to_string(score) + " |\n";
    buffer += "\033[35m+-----------------+\n";

    // Loop through the game grid and update the buffer accordingly
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == length - 1 || x == 0 || x == width - 1) {
                buffer += "\033[36m[]\033[0m"; // Cyan color for boundary
            } else if (x == snakeBodySegments[0][0] && y == snakeBodySegments[0][1]) {
                buffer += "\033[32m()\033[0m"; // Green color for snake head
            } else if (InSnake(x, y)) {
                buffer += "\033[34m[]\033[0m"; // Blue color for snake body
            } else if (x == foodXPosition && y == foodYPosition) {
                buffer += "\033[31m()\033[0m"; // Red color for food
            } else {
                buffer += "  ";
            }
        }
        buffer += "\n";
    }

    // Output the buffered content directly without clearing the console
    cout << buffer;
}




    void End() {
        cout << "\n\nGame Over! Press any key to exit...";
        _getch();
        exit(0);
    }

    void HitTest() {
        if (foodXPosition == snakeBodySegments[0][0] && foodYPosition == snakeBodySegments[0][1]) {
            score++;
            AddSegment();
            NewFood();
        } else if (snakeBodySegments[0][1] == 0 || snakeBodySegments[0][1] == length - 1 || snakeBodySegments[0][0] == 0 || snakeBodySegments[0][0] == width - 1) {
            End();
        } else if (InSnake(snakeBodySegments[0][0], snakeBodySegments[0][1])) {
            End();
        }
    }

    void Run() {
        while (true) {
            Sleep(150);
            if (_kbhit()) {
                UserInput = _getch();
            }
            Move();
            Draw();
            HitTest();
        }
    }
};

int main() {

    cout << "\033[32m   /#################################################################################################################\033[32m\\" << endl;
    cout << "\033[32m  /################################################################################################\033[35m###################\033[32m\\" << endl;
    cout << "  \033[32m##            _______  _        _______  _______  _______  _______      _________ _______       #\033[35m# 1-Zohaib Khalid #\033[32m#"<< endl;
    cout << "  \033[32m##  |\\     /|(  ____ \\( \\      (  ____ \\(  ___  )(       )(  ____ \\     \\__   __/(  ___  )      #\033[35m# 2-Rameen Amir   #\033[32m#" << endl;
    cout << "  \033[32m##  | )   ( || (    \\/| (      | (    \\/| (   ) || () () || (    \\/        ) (   | (   ) |      #\033[35m# 3-Iqra Fatima   #\033[32m#" << endl;
    cout << "  \033[32m##  | | _ | || (__    | |      | |      | |   | || || || || (__            | |   | |   | |      #\033[35m# 4-Khurram Ihsan #\033[32m#" << endl;
    cout << "  \033[32m##  | |( )| ||  __)   | |      | |      | |   | || |(_)| ||  __)           | |   | |   | |      #\033[35m# 5-Romaisa Zia   #\033[32m#" << endl;
    cout << "  \033[32m##  | || || || (      | |      | |      | |   | || |   | || (              | |   | |   | |      #\033[35m###################\033[32m#" << endl;
    cout << "  \033[32m##  | () () || (____/\\| (____/\\| (____/\\| (___) || )   ( || (____/\\        | |   | (___) |      #\033[32m###################\033[32m#" << endl;
    cout << "  \033[32m##  (_______)(_______/(_______/(_______/(_______)|/     \\|(_______/        )_(   (_______)      \t\t     ##" << endl;
    cout << "  \033[32m##                                                                                                                 ##\n";
    cout << "  \033[32m##    \033[31m_____      __      _     ____      __   ___    _____         _____      ____       __    __      _____       \033[32m##" << endl;
    cout << "  \033[32m##   \033[31m/ ____\\    /  \\    / )   (    )    () ) / __)  / ___/        / ___ \\    (    )      \\ \\  / /     / ___/       \033[32m##" << endl;
    cout << "  \033[32m##  \033[31m( (___     / /\\ \\  / /    / /\\ \\    ( (_/ /    ( (__         / /   \\_)   / /\\ \\      () \\/ ()    ( (__         \033[32m##" << endl;
    cout << "  \033[32m##   \033[31m\\___ \\    ) ) ) ) ) )   ( (__) )   ()   (      ) __)       ( (  ____   ( (__) )     / _  _ \\     ) __)        \033[32m##" << endl;
    cout << "  \033[32m##       \033[31m) )  ( ( ( ( ( (     )    (    () /\\ \\    ( (          ( ( (__  )   )    (     / / \\/ \\ \\   ( (           \033[32m##" << endl;
    cout << "  \033[32m##   \033[31m___/ /   / /  \\ \\/ /    /  /\\  \\   ( (  \\ \\    \\ \\___       \\ \\__/ /   /  /\\  \\   /_/      \\_\\   \\ \\___       \033[32m##" << endl;
    cout << "  \033[32m##  \033[31m/____/   (_/    \\__/    /__(  )__\\  ()_)  \\_\\    \\____\\       \\____/   /__(  )__\\ (/          \\)   \\____\\      \033[32m##" << endl;
    cout << "  \033[32m##                                                                                                                 ##" << endl;
    cout << "  \033[32m\\###################################################################################################################/" << endl;
    cout << "   \033[32m\\#################################################################################################################/\n" << endl;

    Sleep(5000);
    system ("cls");

    string name;
    cout << "            ____" << endl;
    cout << "\033[32m      _,.-'`_ o `;__,                \033[33m ____   _  _    ____          _  _      _    \n";
    cout << "\033[32m       _.-'` '---'  '                \033[33m|  _ \\ (_)| |  |  _ \\        (_)| |    | |\n";
    cout << "\033[32m                    ____             \033[33m| |_) | _ | |_ | |_) | _   _  _ | |  __| |\n";
    cout << "\033[32m                 .'`_ o `;__,        \033[33m|  _ < | || __||  _ < | | | || || | / _` | / _ \\| '__|\n";
    cout << "\033[32m       .       .'.'` '---'`  '       \033[33m| |_) || || |_ | |_) || |_| || || || (_| ||  __/| |   \n";
    cout << "\033[32m       .`-...-'.'                    \033[33m|____/ |_| \\__||____/  \\__,_||_||_| \\__,_| \\___||_|   \n";
    cout << "\033[32m        `-...-'                      \033[33m _____                    _               _    _     \n";
    cout << "\033[32m                        _,.--.       \033[33m|  __ \\                  | |             | |  (_) \n";
    cout << "\033[32m    --..,_           .'`__ o  `;__   \033[33m| |__) | _ __   ___    __| | _   _   ___ | |_  _   ___   _ __   ___\n";
    cout << "\033[32m       `'.'.       .'.'`  '---'`  '  \033[33m|  ___/ | '__| / _ \\  / _` || | | | / __|| __|| | / _ \\ | '_ \\ / __|\n";
    cout << "\033[32m          '.`-...-'.'                \033[33m| |     | |   | (_) || (_| || |_| || (__ | |_ | || (_) || | | |\\__ \\\n";
    cout << "\033[32m            `-...-'                  \033[33m|_|     |_|    \\___/  \\__,_| \\__,_| \\___| \\__||_| \\___/ |_| |_|\\___/\n";
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "\033[33m+-------------------+\n";
    cout << "\033[33m| Enter Your Name:  |\n";
    cout << "\033[33m+-------------------+\n";
    getline(cin,name);
    system("cls");


    SnakeGame game;

    game.thePlayer(name);

    game.NewFood();  // Generate initial food

    game.Run();

    return 0;
}
