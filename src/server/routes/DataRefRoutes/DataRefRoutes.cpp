#include "DataRefRoutes.h"

namespace routes
{
  void DataRefRoutes::Post(const shared_ptr<Session> session)
  {

    const auto request = session->get_request();

    int content_length = request->get_header("Content-Length", 0);

    session->fetch(content_length, [](const shared_ptr<Session> session, const Bytes &body) {
      int status = 200;
      json response;
      json bodyJson = json::parse((char *)body.data());
      char *end;
      bool validateError = false;

      for (auto &[key, value] : bodyJson.items())
      {
        json dataRefObject = json::object();
        json object;
        object[key] = value;

        if (!(object[key].find("value") != object[key].end()))
        {
          dataRefObject["error"] = "does not exist value";
        }
        else if (!(object[key].find("dataRef") != object[key].end()))
        {
          dataRefObject["error"] = "does not exist dataRef";
        }
        else if (!(object[key].find("ref") != object[key].end()))
        {
          dataRefObject["error"] = "does not exist ref";
        }
        else
        {

          string dataRefString = object[key]["dataRef"].get<string>();
          uint64_t ref = object[key]["ref"].get<uint64_t>();
          json newValue;

          newValue["newValue"] = *object[key].find("value");

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
            const bool dataRefWitrable = GetDataRefWitrable(ref);
            if (dataRefWitrable == false)
            {
              dataRefObject = GetDataRefValue(ref); //value
              dataRefObject["dataRef"] = dataRefString;
              dataRefObject["ref"] = ref;
              dataRefObject["writable"] = dataRefWitrable;
              dataRefObject["good"] = dataRefGood;
              dataRefObject["error"] = "this dataRef is not writable";
            }
            else
            {
              dataRefObject = SetDataRefValue(ref, newValue); //value and type error
              dataRefObject["dataRef"] = dataRefString;
              dataRefObject["ref"] = ref;
              dataRefObject["writable"] = dataRefWitrable;
              dataRefObject["good"] = dataRefGood;
            }
          }
        }

        if (dataRefObject.find("error") != dataRefObject.end())
        {
          status = 400;
        }
        response.push_back(dataRefObject);
      }

      string responseData = response.dump();
      const multimap<string, string> headers{
          {"Content-Length", to_string(responseData.length())},
          {"Content-Type", "application/json"},
          {"Connection", "close"}};

      session->close(status, responseData, headers);
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