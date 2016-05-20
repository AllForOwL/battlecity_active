#ifndef PARSING_H
#define PARSING_H

#include <QObject>

#include "constants.h"

class Parsing
{
public:
    Parsing();

    bool ParsTextFile(const QString &nameFile, int n_Map[CNT_ROWS_MAP][CNT_COLS_MAP], bool searchGoodWay);
};

#endif // PARSING_H
