#include "color.h"

// Regular text
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define CYN "\e[0;36m"

void COLOR_RED() { printf(RED); }
void COLOR_GREEN() { printf(GRN); };
void COLOR_YELLOW() { printf(YEL); }
void COLOR_BLUE() { printf(BLU); };
void COLOR_CYAN() { printf(CYN); }

// Regular bold text
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BCYN "\e[1;36m"

void COLOR_RED_BOLD() { printf(BRED); }
void COLOR_GREEN_BOLD() { printf(BGRN); }
void COLOR_YELLOW_BOLD() { printf(BYEL); }
void COLOR_BLUE_BOLD() { printf(BBLU); }
void COLOR_CYAN_BOLD() { printf(BCYN); }

// Regular underline text
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UCYN "\e[4;36m"

void COLOR_RED_UNDERLINE() { printf(URED); }
void COLOR_GREEN_UNDERLINE() { printf(UGRN); }
void COLOR_YELLOW_UNDERLINE() { printf(UYEL); }
void COLOR_BLUE_UNDERLINE() { printf(UBLU); }
void COLOR_CYAN_UNDERLINE() { printf(UCYN); }

// Reset Color
#define RESET "\e[0m"

void COLOR_RESET() { printf(RESET); }