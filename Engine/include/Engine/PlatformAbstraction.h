// PlatformAbstraction.h
#pragma once
#include <iostream>
#include <memory>
#include <string>

class PlatformLibrary {
  public:
    virtual ~PlatformLibrary() = default;

    virtual bool Load(const std::string &path) = 0;

    virtual void *GetFunction(const std::string &functionName) = 0;

    virtual void Unload() = 0;

    static std::unique_ptr<PlatformLibrary> Create();
};
