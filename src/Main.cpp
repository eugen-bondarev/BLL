#include "MNIST/MNISTHelper.h"
#include "Window/Window.h"
#include "AI/Network.h"
#include "AI/Random.h"
#include "AI/Math.h"
#include "AI/Util.h"

int main()
{
    try
    {
        AI::TrainingData trainingData {MNIST::Load(
            "C:/Users/azare/Documents/Dev/Cpp/BLL/dataset/test-images",
            "C:/Users/azare/Documents/Dev/Cpp/BLL/dataset/test-labels"
        )};
        
        AI::Random::Reset();

        AI::Network network({
            {784},
            {16},
            {16},
            {10}
        });

        const AI::Matrix output {network.Feedforward(trainingData[25].input)};
        const AI::Matrix desiredOutput {trainingData[25].output};

        LINE_OUT(output.ToString());
        LINE_OUT(AI::Util::FindGreatestIndex(output));
        
        Window window;
        while (window.IsRunning())
        {
            window.BeginFrame();
                ImGui::ShowDemoWindow();            
            window.EndFrame();
        }
    }
    catch (const std::runtime_error& error)
    {
        LINE_OUT("[Exception] " + std::string(error.what()));
    }

    return 0;
}