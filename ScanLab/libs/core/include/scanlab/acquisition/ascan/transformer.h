#pragma once

#include <concepts>
#include <functional>
#include <memory>
#include <span>
#include <utility>
#include <vector>

namespace scanlab::acquisition::ascan {

template<typename T>
concept VectorTransformer =
    requires(T& transformer, std::vector<float>& samples) {
        { transformer.transform(samples) } -> std::same_as<void>;
    };

template<typename T>
concept SpanTransformer =
    requires(T& transformer, std::span<float> samples) {
        { transformer.transform(samples) } -> std::same_as<void>;
    };

class Transformer
{
public:
    Transformer() = default;

    template<typename T>
        requires VectorTransformer<T>
    static Transformer fromShared(std::shared_ptr<T> transformer)
    {
        Transformer result;
        result.transform_ =
            [transformer = std::move(transformer)](std::vector<float>& samples) {
                transformer->transform(samples);
            };

        return result;
    }

    template<typename T>
        requires (!VectorTransformer<T> && SpanTransformer<T>)
    static Transformer fromShared(std::shared_ptr<T> transformer)
    {
        Transformer result;
        result.transform_ =
            [transformer = std::move(transformer)](std::vector<float>& samples) {
                transformer->transform(std::span<float>{samples});
            };

        return result;
    }

    void transform(std::vector<float>& samples) const
    {
        if (!transform_) {
            return;
        }

        transform_(samples);
    }

    [[nodiscard]]
    bool isValid() const
    {
        return static_cast<bool>(transform_);
    }

private:
    std::function<void(std::vector<float>&)> transform_;
};

} // namespace scanlab::acquisition::ascan