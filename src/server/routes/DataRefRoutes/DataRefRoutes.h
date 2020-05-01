#ifndef LIBDATAREFROUTES_H
#define LIBDATAREFROUTES_H

#include "XPLM/XPLMDataAccess.h"
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <restbed>
#include "src/lib/DataManipulator/DataManipulator.h"

using namespace manipulator;
using namespace restbed;
using namespace std;
using json = nlohmann::json;

namespace routes
{
  class DataRefRoutes
  {
  public:
    static void Get(const shared_ptr<Session> session);
    static void Post(const shared_ptr<Session> session);
  };
} // namespace routes

#endif