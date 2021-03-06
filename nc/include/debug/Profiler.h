#pragma once

/** @note __PRETTY_FUNCTION__ is not portable and source_location does not produce
 *  a sufficiently unique name(in gcc at least). When the cross-platform reckoning
 *  comes, we'll have to do some fiddling here. */

#ifdef NC_EDITOR_ENABLED
    #define NC_PROFILE_BEGIN(filter); \
        static const auto NC_FUNCTION_ID = nc::debug::profiler::Register(__PRETTY_FUNCTION__, filter); \
        nc::debug::profiler::Push(NC_FUNCTION_ID);
    #define NC_PROFILE_END(); \
        nc::debug::profiler::Pop();
#else
    #define NC_PROFILE_BEGIN(filter);
    #define NC_PROFILE_END();
#endif

namespace nc::debug::profiler
{
    enum class Filter : unsigned
    {
        All = 0u,
        Logic = 1u,
        Physics = 2u,
        Rendering = 3u,
        User = 4u
    };
}

/* Internal Use */
#ifdef NC_EDITOR_ENABLED
#include "time/NcTime.h"
#include <array>
#include <string>
#include <unordered_map>

namespace nc::debug::profiler
{
    struct FunctionMetrics;

    using FuncId = uint32_t;
    using ProfileData = std::unordered_map<FuncId, FunctionMetrics>;

    FuncId Register(const char* name, Filter filter);
    void Push(FuncId id);
    void Pop();
    ProfileData& GetData();
    void UpdateHistory(FunctionMetrics* metrics);
    void Reset(FunctionMetrics* metrics);
    std::tuple<float, float> ComputeAverages(FunctionMetrics const* metrics);
    const char* ToCString(Filter filter);


    struct FunctionMetrics
    {
        FunctionMetrics(std::string name, Filter profileFilter);

        static constexpr unsigned historySize = 64u;
        std::string functionName;
        std::array<float, historySize> callHistory;
        std::array<float, historySize> timeHistory;
        time::Timer timer;
        unsigned callCount;
        float execTime;
        Filter filter;
        bool active;
    };
} // end namespace nc::debug
#endif