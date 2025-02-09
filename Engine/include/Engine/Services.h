#pragma once
#include "Engine/Core.h"
#include "Engine/IPlugin.h"

class Services: public Plugin::IServices {
  public:
    Services()          = default;
    virtual ~Services() = default;

    void  RegisterService(const std::string &name, void *service) override;
    void *GetService(const std::string &name) override;

    void  CreatePort(const std::string &name, void *port) override;
    void *GetPort(const std::string &name) override;

    void CreateConfigProperty(const std::string &name, void *configProperty) override;

  private:
    std::map<std::string, void *> m_services;
    std::map<std::string, void *> m_ports;
};
