#ifndef QTDEIKSTRAALGORYTHM_H
#define QTDEIKSTRAALGORYTHM_H

#include "qtdeikstraalgorythm_global.h"
#include <QVector>
class QTDEIKSTRAALGORYTHMSHARED_EXPORT QtDeikstraAlgorythm
{

public:
    QTDEIKSTRAALGORYTHMSHARED_EXPORT QVector<int> DeikstraAlgorythm(int VertexNum, QVector<int> EdgesArray,int Source);
};

#endif // QTDEIKSTRAALGORYTHM_H
