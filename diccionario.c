

/*
    Título: Diccionario
    Nombre: Héctor Paredes Benavides
    Descripción: Creamos un programa para gestionar un diccionario de palabras de 3 letras mediante una tabla hash
    Fecha: 2/12/2022
*/

/* Instrucciones de Preprocesado */
// Inclusión de bibliotecas
#include <stdio.h>
#include <stdlib.h>

// Definición de constantes
#define HASH_MAP_SIZE 26
#define WORD_LENGTH 3

#define MAIN_MENU_MIN_OPTION 1
#define MAIN_MENU_MAX_OPTION 4

/* Declaraciones Globales */
// Estructuras
typedef struct HashMapLevel3_s{

    int key;
    char *value;
    int exists;

}HashMapLevel3_s;

typedef struct HashMapLevel2_s{

    int key;
    HashMapLevel3_s value[HASH_MAP_SIZE];

}HashMapLevel2_s;

typedef struct HashMapLevel1_s{

    int key;
    HashMapLevel2_s value[HASH_MAP_SIZE];

}HashMapLevel1_s;

// Enumeraciones
typedef enum MainMenuOptions_e{

    insert,
    search,
    delete,
    exitProgram

}MainMenuOptions_e;

// Funciones
// Funciones de la Tabla Hash
HashMapLevel1_s* initHashMap();
void freeHashMap(HashMapLevel1_s *hashMap);

int getHash(char character);

void insertValue(HashMapLevel1_s *hashMap, char *word, char *description);
char* getValue(HashMapLevel1_s *hashMap, char *word, int *exists);
void deleteValue(HashMapLevel1_s *hashMap, char *word);

// Funciones del diccionario
void insertNewWord(HashMapLevel1_s *hashMap);
void searchWord(HashMapLevel1_s *hashMap);
void deleteWord(HashMapLevel1_s *hashMap);

int checkWordExists(HashMapLevel1_s *hashMap, char *word);

// Funciones Auxiliares
void cleanBuffer();
char *readLine(int *lineLength);

/* Función Principal Main */
int main(int argc, char **argv){

    // Variables necesarias
    HashMapLevel1_s *hashMap;
    int executingMainMenu = 1;

    // Inicializamos la tabla hash a elementos vacíos
    hashMap = initHashMap();

    // (TODO) Importamos los datos del diccionario desde el fichero correspondiente 

    // Entramos en bucle para el menú del programa
    printf("Bienvenido al diccionario...\n");
    do{

        // Variables necesarias
        int choose = 0;
        MainMenuOptions_e chooseAsEnum = 0;
        int scanfError = 0;

        // Mostramos el menú principal y recogemos la selección del usuario
        do{

            printf("----- Menú Principal -----\n");
            printf("1.- Introducir palabra.\n");
            printf("2.- Buscar palabra.\n");
            printf("3.- Eliminar palabra.\n");
            printf("4.- Salir.\n");
            printf("Selección: ");

            scanfError = scanf("%d", &choose);
            cleanBuffer();

            if(scanfError == 0 || choose < MAIN_MENU_MIN_OPTION || choose > MAIN_MENU_MAX_OPTION)
                printf("ERROR: Ha ocurrido un error al introducir la selección.\n");

        }while(scanfError == 0 || choose < MAIN_MENU_MIN_OPTION || choose > MAIN_MENU_MAX_OPTION);

        // Interpretamos la selección del usuario
        chooseAsEnum = choose - 1;
        switch(chooseAsEnum){

            case insert:
                insertNewWord(hashMap);
                break;
            
            case search:
                searchWord(hashMap);
                break;
            
            case delete:
                deleteWord(hashMap);
                break;

            case exitProgram:
                printf("Finalizando el programa...\n");
                executingMainMenu = 0;
                break;

            default:
                printf("ERROR: Ha ocurrido un error al intentar interpretar la selección.");
                break;

        }

    }while(executingMainMenu);

    // Liberamos la memoria utilizada
    freeHashMap(hashMap);

    return 0;

}

/* Codificación de Funciones */
// initHashMap
HashMapLevel1_s* initHashMap(){

    // Variables necesarias
    HashMapLevel1_s *hashMap = NULL;

    // Reservamos la memoria para el hashmap
    hashMap = (HashMapLevel1_s*)malloc(HASH_MAP_SIZE * sizeof(HashMapLevel1_s));

    for(int i = 0; i < HASH_MAP_SIZE; i++){

        hashMap[i].key = i;

        for(int j = 0; j < HASH_MAP_SIZE; j++){

            hashMap[i].value[j].key = j;

            for(int k = 0; k < HASH_MAP_SIZE; k++){

                hashMap[i].value[j].value[k].key = k;
                hashMap[i].value[j].value[k].value = NULL;
                hashMap[i].value[j].value[k].exists = 0;

            }

        }

    }

    return hashMap;

}

// freeHashMap
void freeHashMap(HashMapLevel1_s *hashMap){

    // Liberamos la memoria utilizada para las descripciones
    for(int i = 0; i < HASH_MAP_SIZE; i++)
        for(int j = 0; j < HASH_MAP_SIZE; j++)
            for(int k = 0; k < HASH_MAP_SIZE; k++)
                if(hashMap[i].value[j].value[k].exists && hashMap[i].value[j].value[k].value != NULL)
                    free(hashMap[i].value[j].value[k].value);

    // Liberamos el hashmap
    free(hashMap);

}

// getHash
int getHash(char character){

    return (character - 'a');

}

// insertValue
void insertValue(HashMapLevel1_s *hashMap, char *word, char *description){

    // Obtenemos el hash de cada letra hasta que llegamos al 3 nivel, en el que introducimos la descripción y ponemos que existe
    hashMap[getHash(word[0])].value[getHash(word[1])].value[getHash(word[2])].value = description;
    hashMap[getHash(word[0])].value[getHash(word[1])].value[getHash(word[2])].exists = 1;

}

// getValue
char* getValue(HashMapLevel1_s *hashMap, char *word, int *exists){

    // Variables necesarias
    char *description = NULL;
    int wordExists = 0;

    // Obtenemos la información de la tabla hash (accedemos a ella de igual manera que en la función de inserción)
    description = hashMap[getHash(word[0])].value[getHash(word[1])].value[getHash(word[2])].value;
    wordExists = hashMap[getHash(word[0])].value[getHash(word[1])].value[getHash(word[2])].exists;

    // Devolvemos la información
    *exists = wordExists;
    return description;

}

// deleteValue
void deleteValue(HashMapLevel1_s *hashMap, char *word){

    // Variables necesarias
    char *descriptionRef = NULL;

    // Borramos el elemento de la tabla hash
    descriptionRef = hashMap[getHash(word[0])].value[getHash(word[1])].value[getHash(word[2])].value;
    hashMap[getHash(word[0])].value[getHash(word[1])].value[getHash(word[2])].value = NULL;
    hashMap[getHash(word[0])].value[getHash(word[1])].value[getHash(word[2])].exists = 0;

    // Liberamos la memoria utilizada por la descripción
    free(descriptionRef);

}

// insertNewWord
void insertNewWord(HashMapLevel1_s *hashMap){

    // Variables necesarias
    char *word = NULL;
    char *description = NULL;
    int wordLength = 0;
    int descriptionLength = 0;
    int wordExists = 0;

    // Obtenemos la palabra a introducir en la tabla hash
    printf("Introduzca la palabra que quiere añadir: ");
    word = readLine(&wordLength);

    // Comprobamos que nos haya introducido una palabra de 3 letras
    if(wordLength == WORD_LENGTH){

        // Comprobamos que la palabra no exista en nuestro diccionario
        wordExists = checkWordExists(hashMap, word);

        // Si la palabra no existe la introducimos, sino mostramos el error
        if(wordExists == 0){

            // Obtenemos la descripción de la palabra
            printf("Introduzca la descripción de la palabra: ");
            description = readLine(&descriptionLength);

            // Introducimos los datos en el HashMap
            insertValue(hashMap, word, description);
            
        }
        else
            printf("ERROR: La palabra introducida ya existe en el diccionario.\n");

    }
    else
        printf("ERROR: La palabra tiene que ser exactamente de %d letras.\n", WORD_LENGTH);
    
    // Liberamos la memoria utilizada
    free(word);

}

// searchWord
void searchWord(HashMapLevel1_s *hashMap){

    // Variables necesarias
    char *word = NULL;
    char *description = NULL;
    int wordLength = 0;
    int descriptionLength = 0;
    int wordExists = 0;

    // Obtenemos la palabra a buscar
    printf("Introduzca la palabra que quiere buscar: ");
    word = readLine(&wordLength);

    // Comprobamos que la palabra tenga 3 letras
    if(wordLength == WORD_LENGTH){

        // Obtenemos la descripción
        description = getValue(hashMap, word, &wordExists);

        // Comprobamos si la palabra existe
        if(wordExists)
            printf("Descripción de '%s': %s\n", word, description);
        else
            printf("ERROR: La palabra introducida no existe en el diccionario.\n");

    }
    else
        printf("ERROR: La palabra tiene que ser de %d letras.\n", WORD_LENGTH);

    // Liberamos la memoria utilizada
    free(word);

}

void deleteWord(HashMapLevel1_s *hashMap){

    // Variables necesarias
    char *word = NULL;
    int wordLength = 0;
    int wordExists = 0;

    // Obtenemos la palabra a elimiinar
    printf("Introduzca la palabra que quiere eliminar: ");
    word = readLine(&wordLength);

    // Comprobamos que la palabra tenga 3 letras
    if(wordLength == WORD_LENGTH){

        // Comprobamos que la palabra existe
        wordExists = checkWordExists(hashMap, word);

        if(wordExists)
            deleteValue(hashMap, word);
        else
            printf("ERROR: La palabra introducida no existe en el diccionario.\n");

    }
    else
        printf("ERROR: La palabra tiene que tener %d letras.\n", WORD_LENGTH);

    // Liberamos la memoria utilizada
    free(word);

}

// checkWordExists
int checkWordExists(HashMapLevel1_s *hashMap, char *word){

    // Variables necesarias
    int exists = 0;

    // Comprobamos si existe
    getValue(hashMap, word, &exists);

    // Devolvemos si existe
    return exists;

}

// cleanBuffer
void cleanBuffer(){
    while(getchar() != '\n'){}
}

// readLine
char *readLine(int *lineLength){

    // Variables necesarias
    char *line = NULL;
    int length = 0;
    char auxCharacter = '\0';

    // Inicializamos la linea
    line = (char*)malloc(sizeof(char));

    // Leemos lo que introduzca el usuario hasta que nos introduzca el intro
    while((auxCharacter = getchar()) != '\n'){

        line[length] = auxCharacter;
        length++;
        line = (char*)realloc(line, (length + 1) * sizeof(char));

    }

    // Cerramos la cadena
    line[length] = '\0';

    // Devolvemos los valores
    *lineLength = length;
    return line;

}
