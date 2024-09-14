// Define these on top of your file before any functions

#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define RESET "\033[0m"

// Usage: Specify the color and use RESET at the end of the line
cout << BLUE << " " << gameboard.getTileAtIndex(i).getPlayerID() << " " << RESET;

// Use RESET to revert back to the default terminal text color when done
cout << RESET << endl;