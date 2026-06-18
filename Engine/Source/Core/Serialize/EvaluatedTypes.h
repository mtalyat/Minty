#pragma once

/**
 * @file EvaluatedTypes.h
 * @brief Header file defining evaluated types for the Minty engine.
 * @author Mitchell Talyat
 */

#include "Core/Math/Evaluate.h"
#include "Core/Serialize/Evaluator.h"

namespace Minty
{
    template<>
    struct Evaluator<Int8>
    {
        static Int8 evaluate(StringView const str)
        {
            return Math::evaluate<Int8>(str);
        }
    };

    template<>
    struct Evaluator<Int16>
    {
        static Int16 evaluate(StringView const str)
        {
            return Math::evaluate<Int16>(str);
        }
    };

    template<>
    struct Evaluator<Int32>
    {
        static Int32 evaluate(StringView const str)
        {
            return Math::evaluate<Int32>(str);
        }
    };

    template<>
    struct Evaluator<Int64>
    {
        static Int64 evaluate(StringView const str)
        {
            return Math::evaluate<Int64>(str);
        }
    };

    template<>
    struct Evaluator<UInt8>
    {
        static UInt8 evaluate(StringView const str)
        {
            return Math::evaluate<UInt8>(str);
        }
    };

    template<>
    struct Evaluator<UInt16>
    {
        static UInt16 evaluate(StringView const str)
        {
            return Math::evaluate<UInt16>(str);
        }
    };

    template<>
    struct Evaluator<UInt32>
    {
        static UInt32 evaluate(StringView const str)
        {
            return Math::evaluate<UInt32>(str);
        }
    };

    template<>
    struct Evaluator<UInt64>
    {
        static UInt64 evaluate(StringView const str)
        {
            return Math::evaluate<UInt64>(str);
        }
    };

    template<>
    struct Evaluator<Float32>
    {
        static Float32 evaluate(StringView const str)
        {
            return Math::evaluate<Float32>(str);
        }
    };

    template<>
    struct Evaluator<Float64>
    {
        static Float64 evaluate(StringView const str)
        {
            return Math::evaluate<Float64>(str);
        }
    };

    template<>
    struct Evaluator<Int2>
    {
        static Int2 evaluate(StringView const str)
        {
            return Math::evaluate<Int2>(str);
        }
    };

    template<>
    struct Evaluator<Int3>
    {
        static Int3 evaluate(StringView const str)
        {
            return Math::evaluate<Int3>(str);
        }
    };

    template<>
    struct Evaluator<Int4>
    {
        static Int4 evaluate(StringView const str)
        {
            return Math::evaluate<Int4>(str);
        }
    };

    template<>
    struct Evaluator<UInt2>
    {
        static UInt2 evaluate(StringView const str)
        {
            return Math::evaluate<UInt2>(str);
        }
    };

    template<>
    struct Evaluator<UInt3>
    {
        static UInt3 evaluate(StringView const str)
        {
            return Math::evaluate<UInt3>(str);
        }
    };

    template<>
    struct Evaluator<UInt4>
    {
        static UInt4 evaluate(StringView const str)
        {
            return Math::evaluate<UInt4>(str);
        }
    };

    template<>
    struct Evaluator<Float2>
    {
        static Float2 evaluate(StringView const str)
        {
            return Math::evaluate<Float2>(str);
        }
    };

    template<>
    struct Evaluator<Float3>
    {
        static Float3 evaluate(StringView const str)
        {
            return Math::evaluate<Float3>(str);
        }
    };

    template<>
    struct Evaluator<Float4>
    {
        static Float4 evaluate(StringView const str)
        {
            return Math::evaluate<Float4>(str);
        }
    };

    template<>
    struct Evaluator<WInt2>
    {
        static WInt2 evaluate(StringView const str)
        {
            return Math::evaluate<WInt2>(str);
        }
    };

    template<>
    struct Evaluator<WInt3>
    {
        static WInt3 evaluate(StringView const str)
        {
            return Math::evaluate<WInt3>(str);
        }
    };


    template<>
    struct Evaluator<WInt4>
    {
        static WInt4 evaluate(StringView const str)
        {
            return Math::evaluate<WInt4>(str);
        }
    };

    template<>
    struct Evaluator<WUInt2>
    {
        static WUInt2 evaluate(StringView const str)
        {
            return Math::evaluate<WUInt2>(str);
        }
    };

    template<>
    struct Evaluator<WUInt3>
    {
        static WUInt3 evaluate(StringView const str)
        {
            return Math::evaluate<WUInt3>(str);
        }
    };

    template<>
    struct Evaluator<WUInt4>
    {
        static WUInt4 evaluate(StringView const str)
        {
            return Math::evaluate<WUInt4>(str);
        }
    };

    template<>
    struct Evaluator<WFloat2>
    {
        static WFloat2 evaluate(StringView const str)
        {
            return Math::evaluate<WFloat2>(str);
        }
    };

    template<>
    struct Evaluator<WFloat3>
    {
        static WFloat3 evaluate(StringView const str)
        {
            return Math::evaluate<WFloat3>(str);
        }
    };

    template<>
    struct Evaluator<WFloat4>
    {
        static WFloat4 evaluate(StringView const str)
        {
            return Math::evaluate<WFloat4>(str);
        }
    };
}
