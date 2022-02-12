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

        Window window{ 1024, 768 };

        AI::Matrix mat{ 784, 1 };
        mat.setZero();

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

        while (window.IsRunning()) {
            window.BeginFrame();

                if (false) {
                    ImGui::Begin("Samples");
                    static int sample = 0;
                    static AI::Matrix matrix = testData[sample].input;
                        ImGui::RenderMatrix(matrix);
                        if (ImGui::DragInt("Sample", &sample, 1.f, 0, testData.size() - 1)) {
                            matrix = testData[sample].input;
                        }
                        if (ImGui::Button("Test")) {
                            LINE_OUT(AI::Util::FindGreatestIndex(network.Feedforward(matrix)));
                        }
                    ImGui::End();
                }

                ImGui::Begin("Draw", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

                    {
                        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
                        ImVec2 vMax = ImGui::GetWindowContentRegionMax();

                        vMin.x += ImGui::GetWindowPos().x;
                        vMin.y += ImGui::GetWindowPos().y;
                        vMax.x += ImGui::GetWindowPos().x;
                        vMax.y += ImGui::GetWindowPos().y;

                        float mousePosInWindowX = ImGui::GetIO().MousePos.x - vMin.x;
                        float mousePosInWindowY = ImGui::GetIO().MousePos.y - vMin.y;

                        std::function<void(int j, int i, float val)> set = [&](int j, int i, float val) {
                            if (j < 28 && i < 28 && j >= 0 && i >= 0) {
                                float& var = mat(j * 28 + i);
                                var += val;
                                if (var > 1.f) var = 1.f;
                            }
                        };

                        if (mousePosInWindowX >= 0 && mousePosInWindowX < vMax.x) {
                            if (mousePosInWindowY >= 0 && mousePosInWindowY < vMax.y) {                                
                                if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsWindowHovered()) {
                                    int i = mousePosInWindowX / 10;
                                    int j = mousePosInWindowY / 10;
                                    float factor = 1.f;

                                    set(j, i, 1.f);
                                    for (int x = -1; x <= 1; ++x) {
                                        set(j, i + x, 0.3f);
                                    }
                                    for (int y = -1; y <= 1; ++y) {
                                        set(j + y, i, 0.3f);
                                    }
                                }
                            }
                        }
                    }

                    ImGui::RenderMatrix(mat);
                ImGui::End();

                ImGui::Begin("Control panel");
                static int res = -1;
                static int right = 0;
                static int total = 0;
                if (ImGui::Button("Test")) {
                    res = AI::Util::FindGreatestIndex(network.Feedforward(mat));
                    total++;
                }
                if (res != -1) {
                    ImGui::SameLine();
                    if (ImGui::Button("Reset")) {
                        res = -1;
                        right = 0;
                        total = 0;
                    }
                }
                if (res != -1) {
                    ImGui::Text("%i?", res);
                    if (ImGui::Button("Ja")) {
                        mat.setZero();
                        right++;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Nein")) {
                        mat.setZero();
                    }
                    ImGui::Text("Accuracy: %.2f", right / static_cast<float>(total) * 100.f);
                }
                ImGui::End();

            window.EndFrame();
        }
    }
    catch (const std::runtime_error& error)
    {
        LINE_OUT("[Exception] " + std::string{ error.what() });
    }

    return 0;
}