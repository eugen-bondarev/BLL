#include "MNIST/MNISTHelper.h"
#include "Window/Window.h"

#include "AI/Util/Random.h"
#include "AI/Util/Util.h"
#include "AI/Util/ImGuiMatrixRenderer.h"
#include "AI/Network.h"
#include "AI/Math.h"
#include "AI/Metrics.h"

#include <iostream>

#define LO(x) std::cout << x << '\n'

int main()
{
    // std::vector<float> vals = { 1, 2, 3, 4, 5, 6 };
    // Eigen::Map<AI::Matrix> m{vals.data(), 3, 2};
    // AI::Matrix mat{m};
    // AI::Matrix m1{mat.unaryExpr([](float x) { return x * 2; })};
    // LO(mat);
    // LO(m1);

    // return 0;

    try
    {
        AI_PROFILER_BEGIN("BLL");

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

        for (size_t l = 0; l < 30; ++l) {
            // Stochastisches Gradientenabstiegsverfahren (Training).
            network.SGD(trainingData, 20, 1, 3.0f);

            // Tests werden nach dem Training durchgeführt.
            const size_t numTests{ 1000 };
            size_t rightPredictions{ 0 };

            for (size_t i = 0; i < numTests; ++i)
            {
                // Zufälliges Sample aus dem Testdatensatz:
                const AI::TrainingSample& randomSample{ testData[rand() % testData.size()] };

                // Die Prognose unseres Netzes:
                const AI::Matrix output{ network.Feedforward(randomSample.input) };
                const size_t prediction{ AI::Util::FindGreatestIndex(output) };

                // Die gewünschte Prognose:
                const size_t rightAnswer{ AI::Util::FindGreatestIndex(randomSample.output) };

                // Wenn die Prognose des Netzes der gewünschten Prognose entspricht,
                // das Resultat als korrekt bezeichnen.
                if (prediction == rightAnswer)
                {
                    rightPredictions++;
                }
            }

            LINE_OUT(AI::StringFormat("Epoche #%i", l));
            LINE_OUT(AI::StringFormat("Genauigkeit: %.1f%%", static_cast<float>(rightPredictions) / numTests * 100.f));
        }

        AI_PROFILER_END();
    }
    catch (const std::runtime_error& error)
    {
        LINE_OUT("[Exception] " + std::string{ error.what() });
    }

    return 0;
}