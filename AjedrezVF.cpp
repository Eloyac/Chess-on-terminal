#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

/**
 * * DECLARACION DEL STRUCT
*/

struct Piece
{
    string name;
    string form;
    int posX;
    int posY;
};


/**
 * * DECLARACION DE CONSTANTES
*/

const int NUM_PIECES = 32;
const int NUM_ROWS = 8;
const int NUM_COLS = 8;
string board[NUM_ROWS][NUM_COLS];

/**
 * * DECLARACION DE FUNCIONES
*/

void ganador(int turno);
void turnoYpeticion(int turno, string nombrePiezaMover, int actualX, int actualY, int newX, int newY);
bool fin(Piece pieces[]);
void imprimir();
void inicializar();
void inicializarPiezas(Piece pieces[]);
void rellenarTablero(Piece pieces[]);
void mover(string nombrePiezaMover, int actualX, int actualY, int newX, int newY, int cont, Piece pieces[], int turno);
void limpiar();
bool isValid(int newX, int newY, string nombrePiezaMover, int actualX, int actualY, Piece pieces[]);
void movement(string nombrePiezaMover, int actualX, int actualY, int newX, int newY, int auxX, int auxY, Piece pieces[]);
void barracarga();


main()
{

    Piece pieces[NUM_PIECES];

    SetConsoleOutputCP(CP_UTF8);

    barracarga();

    inicializarPiezas(pieces);

    inicializar();

    rellenarTablero(pieces);

    imprimir();

    string nombrePiezaMover;
    int actualX, actualY, newX, newY, auxX, auxY;
    int cont = 0;
    int turno = 0;

    do
    {
        
        if (turno % 2 == 0) // Hace que el jugador 1 empiece primero y luego cambie de jugador a cada turno
        {
            cout << endl
                 << "TURNO DEL JUGADOR 1" << endl
                 << endl;

            cout << "¿Que pieza quieres mover? " << endl;
            do
            {

                getline(cin, nombrePiezaMover);

            } while (!(nombrePiezaMover.find("White") != -1));
        }
        else
        {
            cout << endl
                 << "TURNO DEL JUGADOR 2" << endl
                 << endl;

            cout << "¿Que pieza quieres mover? " << endl;
            do
            {

                getline(cin, nombrePiezaMover);

            } while (!(nombrePiezaMover.find("Black") != -1));
        }

        cout << "Dime su posicion : " << endl
             << "Posicion X " << endl;
        cin >> actualX;
        cout << "Posicion Y " << endl;
        cin >> actualY;
        cout << "eliga el destino" << endl
             << "Meta la nueva x: " << endl;
        cin >> newX;
        cout << "Meta la nueva y: " << endl;
        cin >> newY;

        mover(nombrePiezaMover, actualX, actualY, newX, newY, cont, pieces, turno);

        // rellenarTablero(pieces);
        for (int i = 0; i < NUM_PIECES; i++)
        {
            int x = pieces[i].posX;
            int y = pieces[i].posY;
            board[x][y] = pieces[i].form;
        }

        imprimir();

        turno++;

    } while (fin(pieces) != false);

    ganador(turno);

    return 0;
}

// FUNCIONES

void inicializarPiezas(Piece pieces[])
{
    int indice = 0; // Indice de la pieza en el array

    // Inicializamos las piezas blancas 

    // White pawns
    for (int i = 0; i < 8; i++)
    {
        pieces[indice].name = "White Pawn";
        pieces[indice].form = "\u2659";
        pieces[indice].posX = 6;
        pieces[indice].posY = i;
        indice++;
    }

    // White rooks
    pieces[indice].name = "White Rook";
    pieces[indice].form = "\u2656";
    pieces[indice].posX = 7;
    pieces[indice].posY = 0;
    indice++;

    pieces[indice].name = "White Rook";
    pieces[indice].form = "\u2656";
    pieces[indice].posX = 7;
    pieces[indice].posY = 7;
    indice++;

    // White knights
    pieces[indice].name = "White Knight";
    pieces[indice].form = "\u2658";
    pieces[indice].posX = 7;
    pieces[indice].posY = 1;
    indice++;

    pieces[indice].name = "White Knight";
    pieces[indice].form = "\u2658";
    pieces[indice].posX = 7;
    pieces[indice].posY = 6;
    indice++;

    // White bishops
    pieces[indice].name = "White Bishop";
    pieces[indice].form = "\u2657";
    pieces[indice].posX = 7;
    pieces[indice].posY = 2;
    indice++;

    pieces[indice].name = "White Bishop";
    pieces[indice].form = "\u2657";
    pieces[indice].posX = 7;
    pieces[indice].posY = 5;
    indice++;

    // White queen
    pieces[indice].name = "White Queen";
    pieces[indice].form = "\u2655";
    pieces[indice].posX = 7;
    pieces[indice].posY = 3;
    indice++;

    // White king
    pieces[indice].name = "White King";
    pieces[indice].form = "\u2654";
    pieces[indice].posX = 7;
    pieces[indice].posY = 4;
    indice++;

    // Inicializamos las piezas negras 

    // Black pawns
    for (int i = 0; i < 8; i++)
    {
        pieces[indice].name = "Black Pawn";
        pieces[indice].form = "\u265F";
        pieces[indice].posX = 1;
        pieces[indice].posY = i;
        indice++;
    }

    // Black rooks
    pieces[indice].name = "Black Rook";
    pieces[indice].form = "\u265C";
    pieces[indice].posX = 0;
    pieces[indice].posY = 0;
    indice++;

    pieces[indice].name = "Black Rook";
    pieces[indice].form = "\u265C";
    pieces[indice].posX = 0;
    pieces[indice].posY = 7;
    indice++;

    // Black knights
    pieces[indice].name = "Black Knight";
    pieces[indice].form = "\u265E";
    pieces[indice].posX = 0;
    pieces[indice].posY = 1;
    indice++;

    pieces[indice].name = "Black Knight";
    pieces[indice].form = "\u265E";
    pieces[indice].posX = 0;
    pieces[indice].posY = 6;
    indice++;

    // Black bishops
    pieces[indice].name = "Black Bishop";
    pieces[indice].form = "\u265D";
    pieces[indice].posX = 0;
    pieces[indice].posY = 2;
    indice++;

    pieces[indice].name = "Black Bishop";
    pieces[indice].form = "\u265D";
    pieces[indice].posX = 0;
    pieces[indice].posY = 5;
    indice++;

    // Black queen
    pieces[indice].name = "Black Queen";
    pieces[indice].form = "\u265B";
    pieces[indice].posX = 0;
    pieces[indice].posY = 3;
    indice++;

    // Black king
    pieces[indice].name = "Black King";
    pieces[indice].form = "\u265A";
    pieces[indice].posX = 0;
    pieces[indice].posY = 4;
    indice++;
}

/**
 * * Inicializa las casillas  
*/

void inicializar()
{
    for (int i = 0; i < 8; i++)
    {

        if (i % 2 == 0)
        {
            for (int j = 0; j < 8; j++)
            {
                if (j % 2 == 0)
                {
                    board[i][j] = "\u26F6"; // Casillas blancas
                }
                else
                {
                    board[i][j] = "\u29C8"; // Casilla negra
                }
            }
        }
        else
        {
            for (int j = 0; j < 8; j++)
            {
                if (j % 2 == 0)
                {
                    board[i][j] = "\u29C8";
                }
                else
                {
                    board[i][j] = "\u26F6";
                }
            }
        }
    }
   
}

/**
 * * Sobreescribe las posiciones del tablero en las que se encuentran las piezas 
*/

void rellenarTablero(Piece pieces[])
{
    for (int i = 0; i < NUM_PIECES; i++)
    {
        int x = pieces[i].posX;
        int y = pieces[i].posY;
        board[x][y] = pieces[i].form;
    }
}

/**
 * * Imprime por pantalla el tablero
*/

void imprimir()
{
    int contador = 0;
    int cont = 0;
    cout << endl
         << "     NEGRAS   " << endl
         << endl;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 8)
            {
                cout << "";
            }
            else if (i == 9 && j == 8 || i == 8 && j == 8)
            {
                cout << "";
            }
            else if (i == 9)
            {
                cout << cont << " ";
                cont++;
            }
            else if (j == 8)
            {
                cout << " " << contador;
                contador++;
            }

            else
            {

                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << endl
         << "     BLANCAS   " << endl;
}

/**
 * * Comprueba el numero de reyes que hay y acaba el juego
*/

bool fin(Piece pieces[])
{
    int contadorRyes = 0;

    for (int i = 0; i < NUM_PIECES; i++)
    {
        if (pieces[i].name == "White King")
        {
            contadorRyes++;
        }
        else if (pieces[i].name == "Black King")
        {
            contadorRyes++;
        }
    }
    if (contadorRyes == 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * * Llama a la funcion de validacion y a la de movimiento
*/

void mover(string nombrePiezaMover, int actualX, int actualY, int newX, int newY, int cont, Piece pieces[], int turno)
{
    cont = 0;

    int auxX, auxY;

    if (isValid(newX, newY, nombrePiezaMover, actualX, actualY, pieces))
    {
        cout << "Movimineto valido " << endl;

        movement(nombrePiezaMover, actualX, actualY, newX, newY, auxX, auxY, pieces);
    }
    else
    {
        cout << "Movimiento no valido" << endl;
    }
}

/**
 * * Limpia la pantalla
*/

void limpiar()
{
    Sleep(100);
    system("cls");
}

/**
 * * Valida que los movimientos son correctos
*/

bool isValid(int newX, int newY, string nombrePiezaMover, int actualX, int actualY, Piece pieces[])
{
    int vertDistance = abs(newX - actualX);
    int horizDistance = abs(newY - actualY);

    if (nombrePiezaMover == "White Pawn")
    {
        // TODO: PEONES
        if (newX - actualX != -1)
        { // Peones blancos solo pueden moverse hacia arriba
            return false;
        }
        else if (newY - actualY != 0 && (newX - actualX) == -1)
        { // Peones solo pueden moverse hacia adelante en una sola columna
            return false;
        }
        else if (newY - actualY == 1 && newY - actualY == -1 && (newX - actualX) == -1)
        { // Peones solo pueden capturar en diagonal

            return false;
        }
        for (int i = 0; i < NUM_PIECES; i++)
        {
            if (pieces[i].posX == newX && pieces[i].posY == newY)
            {
                cout << "Movimiento inválido. Hay una pieza en esa posición." << endl;
                return false;
            }
            else
            {
                return true;
            }
        }
    }

    else if (nombrePiezaMover == "Black Pawn")
    {
        cout << "He entrado en el WhitePawn Checkers" << endl;
        if (newX - actualX != 1)
        { // Peones negros solo pueden moverse hacia abajo
            return false;
        }
        if (newY - actualY != 0 && (newX - actualX) == 1)
        { // Peones solo pueden moverse hacia adelante en una sola columna
            return false;
        }
        if (newY - actualY == 1 && newY - actualY == -1 && (newX - actualX) == 1)
        { // Peones solo pueden capturar en diagonal
            return false;
        }
        for (int i = 0; i < NUM_PIECES; i++)
        {
            if (pieces[i].posX == newX && pieces[i].posY == newY)
            {
                cout << "Movimiento inválido. Hay una pieza en esa posición." << endl;
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    // TODO: CABALLO
    else if (nombrePiezaMover.find("Knight") != -1)
    {
        if ((horizDistance == 2 && vertDistance == 1) || (horizDistance == 1 && vertDistance == 2))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // TODO: REY
    else if (nombrePiezaMover == "White King" || nombrePiezaMover == "Black King")
    {
        if (abs(actualX - newX) > 1 || abs(actualY - newY) > 1)
        {
            cout << "Movimiento inválido. El rey solo puede moverse a una casilla adyacente." << endl;
            return false;
        }
        for (int i = 0; i < NUM_PIECES; i++)
        {
            if (pieces[i].posX == newX && pieces[i].posY == newY)
            {
                cout << "Movimiento inválido. Hay una pieza en esa posición." << endl;
                return false;
            }
        }
    }

    // TODO: REINA

    else if (nombrePiezaMover == "White Queen" || nombrePiezaMover == "Black Queen")
    {
        if (actualX != newX && actualY != newY && abs(actualX - newX) != abs(actualY - newY))
        {
            return false;
        }
        int moveX = (newX - actualX) / abs(newX - actualX);
        int moveY = (newY - actualY) / abs(newY - actualY);
        int checkX = actualX + moveX;
        int checkY = actualY + moveY;

        while (checkX != newX || checkY != newY)
        {
            for (int i = 0; i < NUM_PIECES; i++)
            {
                if (pieces[i].posX == checkX && pieces[i].posY == checkY)
                {
                    cout << "Movimiento inválido. Hay una pieza en línea de movimiento." << endl;
                    return false;
                }
            }
            checkX += moveX;
            checkY += moveY;
        }
    }

    // TODO: ALFIL
    else if (nombrePiezaMover == "White Bishop" || nombrePiezaMover == "Black Bishop")
    {
        if (abs(actualX - newX) != abs(actualY - newY))
        {
            return false;
        }

        int moveX = (newX - actualX) / abs(newX - actualX);
        int moveY = (newY - actualY) / abs(newY - actualY);

        int checkX = actualX + moveX;
        int checkY = actualY + moveY;

        while (checkX != newX || checkY != newY)
        {
            for (int i = 0; i < NUM_PIECES; i++)
            {
                if (pieces[i].posX == checkX && pieces[i].posY == checkY)
                {
                    cout << "Movimiento inválido. Hay una pieza en línea de movimiento." << endl;
                    return false;
                }
            }
            checkX += moveX;
            checkY += moveY;
        }
    }

    // TODO: TORRE
    else if (nombrePiezaMover.find("Rook") != -1)
    {
        if ((horizDistance <= 8 && vertDistance == 0) || (horizDistance == 0 && vertDistance <= 8))
        {

            if (horizDistance == 0) // Comprueba parriba y abajo
            {
                if (actualX > newX)
                {
                    for (int i = actualX; i > newX; i--)
                    {
                        // cout << "--" << endl;
                        if (pieces[i].form != "\u26F6" || pieces[i].form != "\u29C8")
                        {
                            // cout << pieces[i].name << endl;
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                }
                else if (actualX < newX)
                {
                    for (int i = actualX; i < newX; i++)
                    {
                        // cout << "--" << endl;
                        if (pieces[i].form != "\u26F6" || pieces[i].form != "\u29C8")
                        {
                            // cout << pieces[i].name << endl;
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                }
            }
            else // Comprueba la los laos
            {
                if (actualY > newY)
                {
                    for (int i = actualY; i > newY; i--)
                    {
                        // cout << "--" << endl;
                        if (pieces[i].form != "\u26F6" || pieces[i].form != "\u29C8")
                        {
                            // cout << pieces[i].name << endl;
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                }
                else if (actualY < newY)
                {
                    for (int i = actualY; i < newY; i++)
                    {
                        // cout << "--" << endl;
                        if (pieces[i].form != "\u26F6" || pieces[i].form != "\u29C8")
                        {
                            // cout << pieces[i].name << endl;
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                }
            }
        }
        /*else
        {
            return true;
        }*/
    }
}

/**
 * * Realiza el movimiento sobreescribiendo la posicion de las piezas y volviendo su posicion inicial a la del tablero
*/
void movement(string nombrePiezaMover, int actualX, int actualY, int newX, int newY, int auxX, int auxY, Piece pieces[])
{
    int cont = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pieces[cont].name == nombrePiezaMover && pieces[cont].posX == actualX && pieces[cont].posY == actualY)
            {

                auxX = pieces[cont].posX;
                auxY = pieces[cont].posY;

                pieces[cont].posX = newX;
                pieces[cont].posY = newY;

                // TODO SI la pieza q me como es el rey se acaba

                if (auxX % 2 == 0)
                {
                    if (auxY % 2 == 0)
                    {
                        board[auxX][auxY] = "\u26F6";
                    }
                    else
                    {
                        board[auxX][auxY] = "\u29C8";
                    }
                }
                else
                {
                    if (auxY % 2 == 0)
                    {
                        board[auxX][auxY] = "\u29C8";
                    }
                    else
                    {
                        board[auxX][auxY] = "\u26F6";
                    }
                }

                board[newX][newY] = pieces[cont].form;
            }
            cont++;
        }
    }
}

/**
 * * Decide el ganador
*/
void ganador(int turno)
{
    if (turno % 2 == 0)
    {
        cout << "EL JUGADOR BLANCO HA GANADO" << endl;
    }
    else
    {

        cout << "EL JUGADOR NEGRO HA GANADO" << endl;
    }
}

/**
 * * Pinta una barra de carga
*/

void barracarga()
{
    // CREDITOS A ALE PORRO

    string caracter = "\u2654 ";
    int numcaract = 1, porcentaje = 0;
    cout << caracter;
    for (int i = 0; i < 50; i++)
    {
        cout << "Cargando \n";
        for (int j = 0; j < numcaract; j++)
        {
            cout << caracter;
        }
        numcaract++;
        cout << porcentaje << "% \n";
        if (i % 2 == 0)
        {
            porcentaje = porcentaje + 4;
        }
        Sleep(50);
        system("cls");
    }
}