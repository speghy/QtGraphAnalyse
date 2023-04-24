#include "qtdeikstraalgorythm.h"


QTDEIKSTRAALGORYTHMSHARED_EXPORT QVector<int> QtDeikstraAlgorythm::DeikstraAlgorythm(int VertexNum, QVector<int> EdgesArray, int Source)
{
        int MaximalUnreachableLength= 100000;
        int MinimalNumbersIndex;
        int MinimalNumber;
        QVector<int> MinimalPaths(VertexNum,MaximalUnreachableLength);  // значения обозначают минимальный найденный путь до вершины
        QVector<bool> VisitedPaths(VertexNum,true);                     // значения обозначают,нужно ли отработать алгоритму в данной вершине
        EdgesArray.resize(VertexNum*VertexNum);
        MinimalPaths[Source]= 0;
       do
       {
            MinimalNumbersIndex = MaximalUnreachableLength;
            MinimalNumber = MaximalUnreachableLength;
            for (int i = 0;i<VertexNum;i++)
            {
                if((VisitedPaths[i]==true)&&(MinimalPaths[i]<MinimalNumber)) // Если алгоритм не отработал в вершине и вес меньше текущего минимального
                {
                    MinimalNumber = MinimalPaths[i];
                    MinimalNumbersIndex = i;
                }
            }
            // Добавляем найденный минимальный вес
            // к текущему весу вершины
            // и сравниваем с текущим минимальным весом вершины
            if(MinimalNumbersIndex!=MaximalUnreachableLength)
            {
                for(int i = 0;i<VertexNum;i++)
                {
                    if(EdgesArray[MinimalNumbersIndex*VertexNum + i]>0)
                    {
                        int VariableToAddEdgeInValue = MinimalNumber + EdgesArray[MinimalNumbersIndex*VertexNum + i];
                        if(VariableToAddEdgeInValue<MinimalPaths[i])
                        {
                            MinimalPaths[i]=VariableToAddEdgeInValue;
                        }

                    }
                }
                VisitedPaths[MinimalNumbersIndex]=0;
            }

       }
       while(MinimalNumbersIndex<MaximalUnreachableLength);
       return MinimalPaths;
}
