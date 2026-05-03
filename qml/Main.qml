import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import sort_visualizer

ApplicationWindow {
    width: 800
    height: 650
    visible: true
    title: "Визуализатор сортировки"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        // Заголовок
        Text {
            text: "Визуализатор алгоритмов сортировки"
            font.pixelSize: 20
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        // Выбор алгоритма и генерация
        RowLayout {
            ComboBox {
                id: algorithmSelector
                model: ["Пузырёк", "Быстрая", "Слияние"]
                onCurrentTextChanged: controller.selectAlgorithm(currentText)
            }

            RowLayout {
                Button {
                    text: "Сгенерировать"
                    onClicked: {
                        controller.stop()
                        arrayModel.generateRandom(sizeInput.value)
                    }
                }

                SpinBox {
                    id: sizeInput
                    from: 5
                    to: 30
                    value: 15
                    editable: true
                }
            }
        }

        // Кнопки управления
        RowLayout {
            Button {
                text: controller.isRunning && !controller.isPaused ? "Пауза" : "Старт"
                onClicked: {
                    if (controller.isRunning && !controller.isPaused) {
                        controller.pause()
                    } else {
                        controller.start()
                    }
                }
            }

            Button {
                text: "Сброс"
                onClicked: controller.stop()
            }

            Button {
                text: "◀ Шаг назад"
                onClicked: controller.previousStep()
            }

            Button {
                text: "Шаг вперёд ▶"
                onClicked: controller.nextStep()
            }
        }

        // Слайдер скорости
        RowLayout {
            Text { text: "Медленно" }
            Slider {
                from: 1000
                to: 10
                value: controller.speed
                onValueChanged: controller.setSpeed(Math.round(value))
                Layout.fillWidth: true
            }
            Text { text: "Быстро" }
            Text { text: Math.round(controller.speed) + " мс" }
        }

        // Прогресс
        ProgressBar {
            value: controller.totalSteps > 0 ?
                controller.currentStep / controller.totalSteps : 0
            Layout.fillWidth: true
        }

        Text {
            text: "Шаг " + controller.currentStep + " / " + controller.totalSteps
            Layout.alignment: Qt.AlignHCenter
        }

        // Визуализация
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Rectangle {
                anchors.fill: parent
                color: "#f5f5f5"
                radius: 8
            }

            Row {
                id: barsContainer
                anchors {
                    fill: parent
                    margins: 15
                    bottomMargin: 40
                }
                spacing: 3

                Repeater {
                    model: arrayModel.data
                    Rectangle {
                        width: arrayModel.size > 0 ?
                            (barsContainer.width - 3 * (arrayModel.size - 1)) / arrayModel.size : 0
                        height: arrayModel.size > 0 ?
                            (modelData / (arrayModel.size * 2.0)) * barsContainer.height : 0
                        color: {
                            if (controller.pivotIndex === index) {
                                return "#ffc060"
                            } else if (controller.activeIndexes.includes(index)) {
                                return "#ff6b6b"
                            } else {
                                return "#4ecdc4"
                            }
                        }
                        anchors.bottom: parent.bottom
                        radius: 2

                        Behavior on height {
                            NumberAnimation { duration: 150 }
                        }
                        Behavior on color {
                            ColorAnimation { duration: 100 }
                        }

                        Text {
                            anchors {
                                bottom: parent.top
                                bottomMargin: 4
                                horizontalCenter: parent.horizontalCenter
                            }
                            text: modelData
                            font.pixelSize: 10
                            color: "#333"
                        }
                    }
                }
            }
        }

        // Описание шага
        Rectangle {
            Layout.fillWidth: true
            height: 50
            color: "#e8e8e8"
            radius: 6

            Text {
                anchors.centerIn: parent
                text: controller.stepDescription || "Выберите алгоритм и нажмите Старт"
                font.pixelSize: 14
                color: "#333"
                wrapMode: Text.WordWrap
            }
        }
    }

    // Диалог завершения
    Dialog {
        id: finishDialog
        title: "Готово!"
        modal: true
        anchors.centerIn: parent

        ColumnLayout {
            Text {
                text: "Сортировка успешно завершена!"
                font.pixelSize: 16
            }
            Button {
                text: "ОК"
                onClicked: finishDialog.close()
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }

    Connections {
        target: controller
        function onSortingFinished() {
            finishDialog.open()
        }
    }

    Component.onCompleted: {
        arrayModel.generateRandom(15)
        controller.selectAlgorithm("Пузырёк")
    }
}
