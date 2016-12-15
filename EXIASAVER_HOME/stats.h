typedef struct Input Input;
struct Input{
    char date[11];
    char heure[11];
    char type[6];
    char parametre[20]; //le nom de nos fichier ne depassera pas les 20 caractere et les dimensions non plus
};
void ReadStats(Input input[]);
void triDate(Input input[]);
void triHeure(Input input[]);
void printStats(Input input[]);
void Counter(Input input[]);