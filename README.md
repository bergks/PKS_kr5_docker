# Sort Visualizer

Визуализатор алгоритмов сортировки с графическим интерфейсом на Qt6 QML. Поддерживает пошаговую демонстрацию, навигацию по шагам и несколько алгоритмов сортировки.

## Алгоритмы

- **Bubble Sort** (Пузырёк) — сравниваем соседние элементы и меняем их местами
- **Quick Sort** (Быстрая) — выбираем опорный элемент и разделяем массив
- **Merge Sort** (Слияние) — делим массив на части и объединяем их обратно

## Стек

- **C++17** — основной язык
- **Qt 6** — GUI и QML
- **CMake** — система сборки
- **Catch2** — unit-тестирование
- **Docker** — контейнеризация

## Структура проекта
```
├── src/ # Исходный код
│ ├── SortingStrategy.h # Интерфейс стратегий сортировки
│ ├── BubbleSort.h/cpp # Пузырьковая сортировка
│ ├── QuickSort.h/cpp # Быстрая сортировка
│ ├── MergeSort.h/cpp # Сортировка слиянием
│ ├── ArrayModel.h/cpp # Модель данных массива
│ ├── SortingController.h/cpp # Контроллер сортировки
│ └── main.cpp # Точка входа
├── qml/
│ └── Main.qml # GUI интерфейс
├── tests/
│ ├── test_sorting.cpp # Unit-тесты (Catch2)
│ ├── scenario1.cpp # Сценарий: демонстрация всех алгоритмов
│ ├── scenario2.cpp # Сценарий: интерактивный режим
│ └── CMakeLists.txt
├── Dockerfile
├── entrypoint.sh
└── README.md
```

## Сборка и запуск

### Локально

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/appsort_visualizer
```

### Docker
```
# Сборка образа
docker build -t sort-visualizer .

# Запуск тестов
docker run --rm sort-visualizer tests

# Запуск GUI (Linux)
docker run --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix --net=host sort-visualizer gui

# Запуск GUI (Windows, требуется VcXsrv)
docker run --rm -e DISPLAY=host.docker.internal:0 sort-visualizer gui
```

## Тестирование
Проект использует Catch2 для unit-тестирования. Покрыты:
- Краевые случаи (пустой массив, один элемент, одинаковые значения)
- Инварианты сортировки (корректность результата, сохранение элементов)
- Контроллер (выбор алгоритма, пошаговая навигация, сброс)
- Сценарий полного workflow

```
# Локально
./build/tests/test_sorting

# В Docker
docker run --rm sort-visualizer tests
```

