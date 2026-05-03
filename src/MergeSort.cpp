#include "MergeSort.h"

QVector<Step> MergeSort::execute(const QVector<int>& input) {
    QVector<Step> steps;
    QVector<int> array = input;
    if (!array.isEmpty()) {
        mergeSort(array, 0, array.size() - 1, steps);
    }
    return steps;
}

void MergeSort::mergeSort(QVector<int>& array, int left, int right, QVector<Step>& steps) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid, steps);
        mergeSort(array, mid + 1, right, steps);
        merge(array, left, mid, right, steps);
    }
}

void MergeSort::merge(QVector<int>& array, int left, int mid, int right, QVector<Step>& steps) {
    QVector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        Step step;
        step.index1 = i;
        step.index2 = j;
        step.description = QString("Сравниваем %1 и %2").arg(array[i]).arg(array[j]);

        if (array[i] <= array[j]) {
            temp.append(array[i]);
            step.description += " → берём левый";
            i++;
        } else {
            temp.append(array[j]);
            step.description += " → берём правый";
            j++;
        }

        QVector<int> displayArray = array;
        int ti = 0;
        for (int k = left; ti < temp.size(); ++k, ++ti) {
            displayArray[k] = temp[ti];
        }
        step.arrayState = displayArray;
        steps.append(step);
    }

    while (i <= mid) {
        Step step;
        step.index1 = i;
        step.index2 = i;
        step.description = QString("Добавляем оставшийся левый %1").arg(array[i]);
        temp.append(array[i]);
        i++;

        QVector<int> displayArray = array;
        int ti = 0;
        for (int k = left; ti < temp.size(); ++k, ++ti) {
            displayArray[k] = temp[ti];
        }
        step.arrayState = displayArray;
        steps.append(step);
    }

    while (j <= right) {
        Step step;
        step.index1 = j;
        step.index2 = j;
        step.description = QString("Добавляем оставшийся правый %1").arg(array[j]);
        temp.append(array[j]);
        j++;

        QVector<int> displayArray = array;
        int ti = 0;
        for (int k = left; ti < temp.size(); ++k, ++ti) {
            displayArray[k] = temp[ti];
        }
        step.arrayState = displayArray;
        steps.append(step);
    }

    for (int k = 0; k < temp.size(); ++k) {
        array[left + k] = temp[k];
    }
}
