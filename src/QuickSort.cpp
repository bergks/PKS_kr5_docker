#include "QuickSort.h"
#include <algorithm>

QVector<Step> QuickSort::execute(const QVector<int>& input) {
    QVector<Step> steps;
    QVector<int> array = input;
    if (!array.isEmpty()) {
        quickSort(array, 0, array.size() - 1, steps);
    }
    return steps;
}

void QuickSort::quickSort(QVector<int>& array, int low, int high, QVector<Step>& steps) {
    if (low < high) {
        int pi = partition(array, low, high, steps);
        quickSort(array, low, pi - 1, steps);
        quickSort(array, pi + 1, high, steps);
    }
}
int QuickSort::partition(QVector<int>& array, int low, int high, QVector<Step>& steps) {
    int pivot = array[high];
    int i = low - 1;
    int pivotPos = high;

    for (int j = low; j < high; ++j) {
        Step step;
        step.pivotIndex = pivotPos;
        step.description = QString("Сравниваем %1 с опорным %2")
                               .arg(array[j]).arg(pivot);

        if (array[j] < pivot) {
            i++;
            if (i != j) {
                // Своп: array[i] и array[j]
                step.index1 = i;
                step.index2 = j;
                step.description += QString(" → меняем %1 и %2").arg(array[i]).arg(array[j]);
            } else {
                step.index1 = j;
                step.index2 = j;
                step.description += " → оставляем на месте";
            }
            std::swap(array[i], array[j]);
        } else {
            step.index1 = j;
            step.index2 = high;
            step.description += " → оставляем справа";
        }

        step.arrayState = array;
        steps.append(step);
    }

    std::swap(array[i + 1], array[high]);
    pivotPos = i + 1;

    Step finalStep;
    finalStep.index1 = i + 1;
    finalStep.index2 = high;
    finalStep.pivotIndex = pivotPos;
    finalStep.description = QString("Ставим опорный %1 на позицию %2").arg(pivot).arg(array[high]);
    finalStep.arrayState = array;
    steps.append(finalStep);

    return i + 1;
}
