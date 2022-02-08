#include "MNIST/MNISTHelper.h"
#include "Window/Window.h"

#include "AI/Util/Random.h"
#include "AI/Util/Util.h"
#include "AI/Util/ImGuiMatrixRenderer.h"
#include "AI/Network.h"
#include "AI/Math.h"
#include "AI/Metrics.h"

int main()
{
    try
    {
        // Zufallszahlengenerator zurücksetzen, um bei jedem 
        // Neustart neue Gewichtungen und Bias zu erzeugen.
        AI::Util::Random::Reset();

        // Der Datensatz, mit welchem das Netz getestet wird (enthält andere Samples).
        const AI::TrainingData testData{ MNIST::Load(
            "dataset/test-images",
            "dataset/test-labels"
        ) };

        // Der Datensatz, mit welchem das Netz trainiert wird.
        const AI::TrainingData trainingData{ MNIST::Load(
            "dataset/train-images",
            "dataset/train-labels"
        ) };

        AI::Network network({
            { 784 },
            { 16 },
            { 16 },
            { 10 }
        });

        network.SGD(trainingData, 30, 20, 3.0f, testData);
    }
    catch (const std::runtime_error& error)
    {
        LINE_OUT("[Exception] " + std::string{ error.what() });
    }

    return 0;
}