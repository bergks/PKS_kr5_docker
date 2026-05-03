#include "SortingController.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "MergeSort.h"

SortingController* SortingController::s_instance = nullptr;

SortingController& SortingController::instance() {
    return *s_instance;
}
SortingController::SortingController(ArrayModel* model, QObject* parent)
    : QObject(parent), m_model(model)
{
    Q_ASSERT(s_instance == nullptr);
    s_instance = this;

    connect(&m_timer, &QTimer::timeout, this, &SortingController::onTimerTick);
}
void SortingController::setSpeed(int speed) {
    if (m_speed != speed) {
        m_speed = speed;
        emit speedChanged();
        if (m_isRunning && !m_isPaused) {
            m_timer.setInterval(m_speed);
        }
    }
}

void SortingController::selectAlgorithm(const QString& name) {
    m_timer.stop();
    m_isRunning = false;
    m_isPaused = false;

    if (name == "Пузырёк") {
        m_strategy = std::make_unique<BubbleSort>();
    } else if (name == "Быстрая") {
        m_strategy = std::make_unique<QuickSort>();
    } else if (name == "Слияние") {
        m_strategy = std::make_unique<MergeSort>();
    } else {
        return;
    }

    m_algorithmName = name;
    emit currentAlgorithmChanged();

    m_steps = m_strategy->execute(m_model->data());
    m_currentStep = 0;
    emit totalStepsChanged();
    emit currentStepChanged();

    m_isRunning = false;
    m_isPaused = false;
    emit isRunningChanged();
    emit isPausedChanged();
}
void SortingController::start() {
    if (m_isRunning && m_isPaused) {
        m_isPaused = false;
        emit isPausedChanged();
        m_timer.start(m_speed);
    } else if (!m_isRunning) {
        if (m_strategy) {
            m_steps = m_strategy->execute(m_model->data());
            m_currentStep = 0;
            emit totalStepsChanged();
            emit currentStepChanged();
        }

        m_isRunning = true;
        m_isPaused = false;
        emit isRunningChanged();
        emit isPausedChanged();
        m_timer.setInterval(m_speed);
        m_timer.start();
    }
}
void SortingController::pause() {
    if (m_isRunning && !m_isPaused) {
        m_isPaused = true;
        emit isPausedChanged();
        m_timer.stop();
    }
}

void SortingController::stop() {
    m_timer.stop();
    m_isRunning = false;
    m_isPaused = false;
    m_currentStep = 0;
    m_pivotIndex = -1;
    m_steps.clear();
    m_activeIndexes.clear();
    m_stepDescription = QString();

    emit isRunningChanged();
    emit isPausedChanged();
    emit currentStepChanged();
    emit totalStepsChanged();
    emit activeIndexesChanged();
    emit stepDescriptionChanged();

    m_model->reset();
}

void SortingController::nextStep() {
    // Если анимация идёт — просто ставим на паузу, без выполнения шага
    if (m_isRunning && !m_isPaused) {
        pause();
        return;
    }
    // Если шаги ещё не рассчитаны — рассчитываем
    if (m_steps.isEmpty() && m_strategy) {
        m_steps = m_strategy->execute(m_model->data());
        m_currentStep = 0;
        emit totalStepsChanged();
        emit currentStepChanged();
    }

    if (m_currentStep < m_steps.size()) {
        executeStep(m_steps[m_currentStep]);
        m_currentStep++;
        emit currentStepChanged();

        if (m_currentStep >= m_steps.size()) {
            m_isRunning = false;
            emit isRunningChanged();
            emit sortingFinished();
        }
    }
}
void SortingController::previousStep() {
    if (m_isRunning && !m_isPaused) {
        pause();
        return;
    }

    if (m_currentStep > 1) {
        m_currentStep -= 2;
        executeStep(m_steps[m_currentStep]);
        m_currentStep++;
        emit currentStepChanged();
    } else if (m_currentStep == 1) {
        m_currentStep = 0;
        m_model->reset();
        m_activeIndexes.clear();
        m_stepDescription = "";
        emit currentStepChanged();
        emit activeIndexesChanged();
        emit stepDescriptionChanged();
    }
}
void SortingController::onTimerTick() {
    if (m_currentStep < m_steps.size()) {
        executeStep(m_steps[m_currentStep]);
        m_currentStep++;
        emit currentStepChanged();
    } else {
        m_timer.stop();
        m_isRunning = false;
        emit isRunningChanged();
        emit sortingFinished();
    }
}

void SortingController::executeStep(const Step& step) {
    m_model->setArray(step.arrayState);
    m_activeIndexes = {step.index1, step.index2};
    m_pivotIndex = step.pivotIndex;
    m_stepDescription = step.description;
    emit activeIndexesChanged();
    emit stepDescriptionChanged();
}
void SortingController::resetToStart() {
    m_currentStep = 0;
    m_model->reset();
    m_activeIndexes.clear();
    m_stepDescription = "";
    m_pivotIndex = -1;
    emit currentStepChanged();
    emit activeIndexesChanged();
    emit stepDescriptionChanged();
}
