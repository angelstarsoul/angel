#include "Factory.hpp"
#include "FileConfigLoader.hpp"
#include "JsonTargetProvider.hpp"
#include "AnalyticalSolver.hpp"

IConfigLoader* createLoader(LoaderType type) {
    if (type == LoaderType::FILE) {
        return new FileConfigLoader();
    }
    return nullptr;
}

ITargetProvider* createProvider(ProviderType type, const std::string& targetsPath) {
    if (type == ProviderType::JSON) {
        return new JsonTargetProvider(targetsPath);
    }
    return nullptr;
}

IBallisticSolver* createSolver(SolverType type) {
    if (type == SolverType::ANALYTICAL) {
        return new AnalyticalSolver();
    }
    return nullptr;
}