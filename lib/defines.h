#ifndef DEFINES_H
#define DEFINES_H

///Rozmiary map
#define ROZ_X 50
#define ROZ_Y 20

///Definicja podlogi
#define P00 '.'

///Definicja muru, kranca mapy
#define M00 '='

///Rozdzielczosc ekranu klienta
#define RES 15 // TYLKO NIEPARZYSTA

/// Port dla klienta i serwera
#define PORT 8866

/// Adres tylko potrzebny klientowi
#define ADDRESS "127.0.0.1"

/// Bufor dla rozdzielczosci 'ekranu' klienta
#define BUFF_IO 226 // RES^2 + 1

#endif // DEFINES_H
