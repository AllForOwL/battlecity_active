#ifndef ALGORITHMLI_H
#define ALGORITHMLI_H

#include <QVector>
#include "parsing.h"
#include "constants.h"

struct point
{
    int x;
    int y;
    int index;
};

class algorithmLI
{
public:
    algorithmLI();

public:
    QString PATH_TO_MAP_FOR_LEVEL;
    int _begin_x;
    int _begin_y;
    int _end_x;
    int _end_y;
    int begin_x_Three_Four_Bot;
    int begin_y_Three_Four_Bot;
    int end_x_Three_Four_Bot;
    int end_y_Three_Four_Bot;

    QString _nameBot;
    int n_map[CNT_ROWS_MAP][CNT_COLS_MAP];
    QVector<point> vectorPassableElement; // проходимые елементы
    QVector<point> vectorFoundWay;        // найденный путь

    Parsing *p_ReadFromFile;              // обьект для чтения файла с картой

    bool SearchWay(int x, int y, int end_x, int end_y); // находить кратчайшый путь
    bool AuditSearchWay(int x_begin, int y_begin, int x_end, int y_end);
    bool PassableElement(int x, int y);
    bool PassableElementMoreThree(int i, int _i);
    bool PassableElementLessThree(int i, int _i);
    void SetPathToMap(const QString& pathToFile);
};

#endif // ALGORITHMLI_H
