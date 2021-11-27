#include "AI/Network.h"
#include "AI/Math.h"

#include "Window/Window.h"

int main()
{
    try
    {
        srand(time(nullptr));

        AI::Network network({
            {2},
            {4},
            {1}
        });

        const AI::Matrix input = 
        {
            {1.0f}, {0.8f}
        };

        const AI::Matrix output = network.Feedforward(input);

        LINE_OUT(output.ToString());
        
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
        LINE_OUT(error.what());
    }

    return 0;
}