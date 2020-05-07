
#ifndef LIBSERVER_H
#define LIBSERVER_H

#include <nlohmann/json.hpp>
#include <cstdlib>
#include <restbed>
#include "src/server/routes/DataRefRoutes/DataRefRoutes.h"
#include "src/server/routes/ErrorHandlerRoutes/ErrorHandlerRoutes.h"

using namespace routes;
using namespace restbed;

namespace server
{
  class Server
  {
    Service service;
    DataRefRoutes dataRefRoutes;
    ErrorHandlerRoutes errorHandlerRoutes;

  public:
    void StartServer();
    void StopServer();
  };

} // namespace server

#endif