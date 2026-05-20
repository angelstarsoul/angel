#pragma once
#include "IConfigLoader.hpp"
#include "ITargetProvider.hpp"
#include "IBallisticSolver.hpp"

enum class LoaderType { FILE };
enum class ProviderType { JSON };
enum class SolverType { ANALYTICAL };

IConfigLoader* createLoader(LoaderType type);
ITargetProvider* createProvider(ProviderType type, const std::string& targetsPath);
IBallisticSolver* createSolver(SolverType type);