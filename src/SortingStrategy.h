#ifndef SORTINGSTRATEGY_H
#define SORTINGSTRATEGY_H

#include <QVector>
#include <QString>

struct Step {
    QVector<int> arrayState;
    int index1;
    int index2;
    int pivotIndex;
    QString description;
};

class SortingStrategy {
public:
    virtual ~SortingStrategy() = default;
    virtual QString name() const = 0;
    virtual QVector<Step> execute(const QVector<int>& array) = 0;
};

#endif
