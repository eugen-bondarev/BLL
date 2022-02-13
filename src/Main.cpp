#include "MNIST/MNISTHelper.h"
#include "Window/Window.h"

#include "AI/Util/Random.h"
#include "AI/Util/Util.h"
#include "AI/Util/ImGuiMatrixRenderer.h"
#include "AI/Network.h"
#include "AI/Math.h"
#include "AI/Metrics.h"
#include "AI/Console.h"

#include <future>

int main()
{
    try
    {
        // Zufallszahlengenerator zurücksetzen, um bei jedem
        // Neustart neue Gewichtungen und Bias zu erzeugen.
        AI::Util::Random::Reset();

        // Der Datensatz, mit welchem das Netz getestet wird (enthält andere Samples).
        const AI::TrainingData testData{MNIST::Load(
            "dataset/test-images",
            "dataset/test-labels")};

        // Der Datensatz, mit welchem das Netz trainiert wird.
        const AI::TrainingData trainingData{MNIST::Load(
            "dataset/train-images",
            "dataset/train-labels")};

        AI::Network network({{784},
                             {16},
                             {16},
                             {10}});

        std::future<void> trainingFuture;

        Window window{1024, 768};

        AI::Matrix mat{784, 1};
        mat.setZero();

        while (window.IsRunning())
        {
            window.BeginFrame();

            AI::Console::ClearMessages();

            // ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
            ImVec2 v = ImGui::GetMainViewport()->Pos;
            ImVec2 s = ImGui::GetMainViewport()->Size;
            ImGui::SetNextWindowPos(v);
            ImGui::SetNextWindowSize(s);
            ImGui::Begin("Docking", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
                ImGui::DockSpace(ImGui::GetID("DockSpace"));
            ImGui::End();

            ImGui::Begin("Training");
            static int numEpochs = 30;
            ImGui::Text("Anzahl der Epochen");
            ImGui::InputInt("##numEpochs", &numEpochs);

            static int miniBatchSize = 20;
            ImGui::Text("Größe der Mini-Batches");
            ImGui::InputInt("##miniBatchSize", &miniBatchSize);

            static float eta = 3.f;
            ImGui::Text("Lernrate");
            ImGui::InputFloat("##eta", &eta);

            ImGui::Separator();
            
            if (!network.IsTrainingRunning() && ImGui::Button("Trainieren"))
            {
                trainingFuture = std::async(std::launch::async, [&]() { 
                    network.SGD(trainingData, numEpochs, miniBatchSize, eta, testData); 
                });
            }

            if (network.IsTrainingRunning())
            {
                if (ImGui::Button("Fertigstellen"))
                {
                    network.StopTraining();
                }
                ImGui::Text("Trainingsfortschritt:");
                ImGui::ProgressBar(network.GetCurrentSGDProgress());
                ImGui::Text("Aktuelle Epoche:");
                ImGui::ProgressBar(network.GetCurrentEpochProgress());
            }

            ImGui::End();

            ImGui::Begin("Zeichnen", nullptr, ImGuiWindowFlags_NoMove);

            {
                ImVec2 vMin = ImGui::GetWindowContentRegionMin();
                ImVec2 vMax = ImGui::GetWindowContentRegionMax();

                vMin.x += ImGui::GetWindowPos().x;
                vMin.y += ImGui::GetWindowPos().y;
                vMax.x += ImGui::GetWindowPos().x;
                vMax.y += ImGui::GetWindowPos().y;

                float mousePosInWindowX = ImGui::GetIO().MousePos.x - vMin.x;
                float mousePosInWindowY = ImGui::GetIO().MousePos.y - vMin.y;

                std::function<void(int j, int i, float val)> set = [&](int j, int i, float val)
                {
                    if (j < 28 && i < 28 && j >= 0 && i >= 0)
                    {
                        float &var = mat(j * 28 + i);
                        var += val;
                        if (var > 1.f)
                            var = 1.f;
                    }
                };

                if (mousePosInWindowX >= 0 && mousePosInWindowX < vMax.x)
                {
                    if (mousePosInWindowY >= 0 && mousePosInWindowY < vMax.y)
                    {
                        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
                        {
                            int i = mousePosInWindowX / 10;
                            int j = mousePosInWindowY / 10;
                            float factor = 1.f;

                            set(j, i, 1.f);
                            for (int x = -1; x <= 1; ++x)
                            {
                                set(j, i + x, 0.3f);
                            }
                            for (int y = -1; y <= 1; ++y)
                            {
                                set(j + y, i, 0.3f);
                            }
                        }
                    }
                }
            }

            ImGui::RenderMatrix(mat);
            ImGui::End();

            ImGui::Begin("Steuerung");
            static AI::Matrix res;
            static int right = 0;
            static int total = 0;
            if (ImGui::Button("Testen"))
            {
                res = network.Feedforward(mat);
                total++;
            }
            if (total != 0)
            {
                ImGui::SameLine();
                if (ImGui::Button("Zurücksetzen"))
                {
                    res.setZero();
                    right = 0;
                    total = 0;
                }
            }
            if (!res.isZero())
            {
                size_t greatestIndex = AI::Util::FindGreatestIndex(res);
                for (size_t i = 0; i < 10; ++i)
                {
                    float num = res(i, 0);
                    int color = 255 * num;
                    if (greatestIndex == i)
                    {
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
                        ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 255, 0, 255));
                    }
                    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(color, color, color, 255));
                    ImGui::Button(AI::StringFormat("%i %.3f", i, num).c_str());
                    if (greatestIndex == i)
                    {
                        ImGui::PopStyleVar();
                        ImGui::PopStyleColor();
                    }
                    ImGui::PopStyleColor();
                }

                if (ImGui::Button("Ja"))
                {
                    mat.setZero();
                    res.setZero();
                    right++;
                }
                ImGui::SameLine();
                if (ImGui::Button("Nein"))
                {
                    mat.setZero();
                    res.setZero();
                }
            }
            if (total != 0)
            {
                ImGui::Text("Genauigkeit: %.2f%%", right / static_cast<float>(total) * 100.f);
            }
            ImGui::End();

            ImGui::Begin("Samples");
            static int sample = 0;
            static AI::Matrix matrix = testData[sample].input;
            ImGui::RenderMatrix(matrix);
            if (ImGui::DragInt("Sample", &sample, 1.f, 0, testData.size() - 1))
            {
                matrix = testData[sample].input;
            }
            if (ImGui::Button("Test"))
            {
                res = network.Feedforward(matrix);
            }
            ImGui::End();

            ImGui::Begin("Konsole");
            for (int i = 0; i < AI::Console::GetMessages().size(); ++i)
            {
                ImGui::Text(AI::Console::GetMessages()[i].c_str());
            }
            ImGui::End();

            window.EndFrame();
        }

        trainingFuture.wait();
    }
    catch (const std::runtime_error &error)
    {
        LINE_OUT("[Exception] " + std::string{error.what()});
    }

    return 0;
}