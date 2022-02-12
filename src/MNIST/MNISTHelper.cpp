#include "MNISTHelper.h"

#include "mnist_reader_less.hpp"

namespace MNIST
{
    TrainingData Load(const Path& imagesPath, const Path& labelsPath)
    {
        const std::vector<std::vector<uint8_t>> images = mnist::read_mnist_image_file(imagesPath());
        const std::vector<uint8_t> labels = mnist::read_mnist_label_file(labelsPath());

        if (images.size() == 0)
        {
            throw std::runtime_error("File " + imagesPath() + " not found");
        }

        if (labels.size() == 0)
        {
            throw std::runtime_error("File " + labelsPath() + " not found");
        }

        TrainingData dataset;
        dataset.reserve(images.size());

        for (size_t i = 0; i < images.size(); ++i)
        {
            Matrix input{ images[i].size(), 1 };
            for (size_t j = 0; j < images[i].size(); ++j)
            {
                input(j) = images[i][j] / 255.f;
            }

            Matrix output = Matrix(10, 1);
            output.setZero();
            output(static_cast<int>(labels[i]), 0) = 1.f;

            dataset.push_back({ input, output });
        }

        return dataset;
    }
}