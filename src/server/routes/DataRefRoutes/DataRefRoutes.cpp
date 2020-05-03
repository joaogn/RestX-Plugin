#include "DataRefRoutes.h"

namespace routes
{
  void DataRefRoutes::Post(const shared_ptr<Session> session)
  {

    const auto request = session->get_request();

    int content_length = request->get_header("Content-Length", 0);

    session->fetch(content_length, [](const shared_ptr<Session> session, const Bytes &body) {
      session->close(OK, "Hello, World!", {{"Content-Length", "13"}});
    });
  }

  void DataRefRoutes::Get(const shared_ptr<Session> session)
  {
    const auto request = session->get_request();

    json response;
    for (const auto query_parameter : request->get_query_parameters())
    {
      json dataRefObject = json::object();

      const string dataRefString = query_parameter.first;

      // string to uint64_t
      char *end;
      uint64_t ref = strtoull(query_parameter.second.c_str(), &end, 10);

      if (GetDataRefGood(ref) == false)
      {
        ref = GetDataRefReference(dataRefString);
      }

      const bool dataRefGood = GetDataRefGood(ref);

      if (dataRefGood == false)
      {
        dataRefObject["value"] = NULL;
        dataRefObject["dataRef"] = dataRefString;
        dataRefObject["ref"] = NULL;
        dataRefObject["writable"] = NULL;
        dataRefObject["good"] = dataRefGood;
      }
      else
      {
        dataRefObject = GetDataRefValue(ref); //value
        dataRefObject["dataRef"] = dataRefString;
        dataRefObject["ref"] = ref;
        dataRefObject["writable"] = GetDataRefWitrable(ref);
        dataRefObject["good"] = dataRefGood;
      }
      response.push_back(dataRefObject);
    }

    string responseData = response.dump();
    const multimap<string, string> headers{
        {"Content-Length", to_string(responseData.length())},
        {"Content-Type", "application/json"},
        {"Connection", "close"}};

    session->close(OK, responseData, headers);
  }
} // namespace routes