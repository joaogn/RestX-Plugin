#ifndef LIBERRORHANDLERROUTES_H
#define LIBERRORHANDLERROUTES_H

#include <nlohmann/json.hpp>
#include <cstdlib>
#include <stdexcept>
#include <restbed>

using namespace restbed;
using namespace std;
using json = nlohmann::json;

namespace routes
{
  class ErrorHandlerRoutes
  {
  public:
    static void ResourceError(const int, const exception &, const shared_ptr<Session> session);
    static void ServiceError(const int, const exception &, const shared_ptr<Session> session);
  };
} // namespace routes

#endif