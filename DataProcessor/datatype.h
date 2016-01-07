#ifndef DATATYPE
#define DATATYPE

    enum class DataType:char
    {
        unknown         = 'U',          // służy do inicjowania zmiennych analogicznie jak nullptr dla wskaźników

        configuration   = 'C',          // konfiguracja - obecnie przekazuje liczbe obrotów na zdjęcie dla arduino
        image           = 'I'           // zdjęcie
    };

#endif // DATATYPE

