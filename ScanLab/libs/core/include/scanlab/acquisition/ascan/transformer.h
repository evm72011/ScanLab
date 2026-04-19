#pragma once

#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace scanlab::acquisition::ascan {

class Transformer
{
public:
    Transformer() = default;

    template<typename T>
    static Transformer fromShared(std::shared_ptr<T> transformer)
    {
        Transformer result;
        result.transform_ =
            [transformer = std::move(transformer)](std::vector<float> input) {
                return transformer->transform(std::move(input));
            };
        return result;
    }

    [[nodiscard]]
    std::vector<float> transform(std::vector<float> input) const
    {
        if (!transform_) {
            return input;
        }

        return transform_(std::move(input));
    }

    [[nodiscard]]
    bool isValid() const
    {
        return static_cast<bool>(transform_);
    }

private:
    std::function<std::vector<float>(std::vector<float>)> transform_;
};

} // namespace scanlab::acquisition::ascan