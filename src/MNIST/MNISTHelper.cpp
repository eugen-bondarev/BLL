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

        TrainingData dataset(images.size());

        for (size_t i = 0; i < images.size(); ++i)
        {
            Vec<Num> input(images[i].size());
            for (size_t j = 0; j < images[i].size(); ++j)
            {
                input[j] = images[i][j] / 255.0f;
            }

            Eigen::Map<Matrix> m(input.data(), input.size(), 1);
            dataset[i].input = Matrix(m);

            dataset[i].output = Matrix(10, 1);
            dataset[i].output.setZero();
            dataset[i].output(static_cast<int>(labels[i]), 0) = 1.0f;
        }

        return dataset;
    }
}