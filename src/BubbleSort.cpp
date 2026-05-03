#include "BubbleSort.h"
QVector<Step> BubbleSort::execute(const QVector<int>& input) {
    QVector<Step> steps;
    QVector<int> array = input;
    int n = array.size();

    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; ++j) {
            Step step;
            step.index1 = j;
            step.index2 = j + 1;
            step.description = QString("Сравниваем %1 и %2")
                                   .arg(array[j]).arg(array[j + 1]);

            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
                step.description += " → меняем местами";
            } else {
                step.description += " → порядок верный";
            }

            step.arrayState = array;
            steps.append(step);
        }

        if (!swapped) {
            break;
        }
    }

    return steps;
}
