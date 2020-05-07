#include "DataRefRoutes.h"

namespace routes
{

  void DataRefRoutes::Post(const shared_ptr<Session> session)
  {

    const auto request = session->get_request();

    const auto query = request->get_query_parameters();

    int content_length = request->get_header("Content-Length", 0);

    session->fetch(content_length - query.size(), [request](const shared_ptr<Session> session, const Bytes &body) {
      const auto request = session->get_request();

      bool debug = false;

      for (const auto query_parameter : request->get_query_parameters())
      {

        if (strcmp(query_parameter.first.c_str(), "debug") == 0)
        {

          if (strcasecmp("true", query_parameter.second.c_str()) == 0 || strcasecmp("1", query_parameter.second.c_str()) == 0)
          {

            debug = true;
          }
        }
      }

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
            if (debug)
            {
              dataRefObject["type"] = NULL;
              dataRefObject["writable"] = NULL;
              dataRefObject["good"] = dataRefGood;
            }
          }
          else
          {
            const bool dataRefWitrable = GetDataRefWitrable(ref);
            if (dataRefWitrable == false)
            {
              dataRefObject = GetDataRefValue(ref); //value
              dataRefObject["dataRef"] = dataRefString;
              dataRefObject["ref"] = ref;
              dataRefObject["error"] = "this dataRef is not writable";
              if (debug)
              {
                dataRefObject["type"] = GetDataRefType(ref);
                dataRefObject["writable"] = dataRefWitrable;
                dataRefObject["good"] = dataRefGood;
              }
            }
            else
            {
              dataRefObject = SetDataRefValue(ref, newValue); //value and type error
              dataRefObject["dataRef"] = dataRefString;
              dataRefObject["ref"] = ref;
              if (debug)
              {
                dataRefObject["type"] = GetDataRefType(ref);
                dataRefObject["writable"] = dataRefWitrable;
                dataRefObject["good"] = dataRefGood;
              }
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

      session->close(200, responseData, headers);
    });

    /*
    string responseData = test.dump();
    const multimap<string, string> headers{
        {"Content-Length", to_string(responseData.length())},
        {"Content-Type", "application/json"},
        {"Connection", "close"}};

    session->close(200, responseData, headers);
    */
  }

  void DataRefRoutes::Get(const shared_ptr<Session> session)
  {
    const auto request = session->get_request();
    bool debug = false;
    json response;
    json dataRefJson;
    for (const auto query_parameter : request->get_query_parameters())
    {
      if (strcmp(query_parameter.first.c_str(), "debug") == 0)
      {
        if (strcasecmp("true", query_parameter.second.c_str()) == 0 || strcasecmp("1", query_parameter.second.c_str()) == 0)
        {
          debug = true;
        }
      }
      else if (strcmp(query_parameter.first.c_str(), "dataRefs") == 0)
      {
        dataRefJson = json::parse(query_parameter.second.c_str());
      }
    }

    for (auto &[key, value] : dataRefJson.items())
    {
      json dataRefObject = json::object();

      const string dataRefString = key;

      // string to uint64_t
      char *end;
      uint64_t ref = value; //strtoull(value, &end, 10);

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
        if (debug)
        {
          dataRefObject["type"] = NULL;
          dataRefObject["writable"] = NULL;
          dataRefObject["good"] = dataRefGood;
        }
      }
      else
      {
        dataRefObject = GetDataRefValue(ref); //value
        dataRefObject["dataRef"] = dataRefString;
        dataRefObject["ref"] = ref;
        if (debug)
        {
          dataRefObject["type"] = GetDataRefType(ref);
          dataRefObject["writable"] = GetDataRefWitrable(ref);
          dataRefObject["good"] = dataRefGood;
        }
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