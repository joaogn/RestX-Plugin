// DataManipulator.cpp

#include "DataManipulator.h"
#include <sstream>

namespace manipulator
{
  uint64_t GetDataRefReference(string data_ref)
  {
    XPLMRef gDataRef = XPLMFindDataRef(data_ref.c_str());
    return (uint64_t)gDataRef;
  }

  bool GetDataRefWitrable(uint64_t ref)
  {
    return XPLMCanWriteDataRef((XPLMDataRef)ref);
  }

  bool GetDataRefGood(uint64_t ref)
  {
    return XPLMIsDataRefGood((XPLMDataRef)ref);
  }

  string GetDataRefType(uint64_t ref)
  {
    XPLMDataTypeID gDataRefType = XPLMGetDataRefTypes((XPLMDataRef)ref);

    switch (gDataRefType)
    {
    case xplmType_Int:
      return "Int";
    case xplmType_Float:
      return "Float";
    case xplmType_Double:
      return "Double";
    case xplmType_FloatArray:
      return "Float";
    case xplmType_IntArray:
      return "IntArray";
    case xplmType_Data:
      return "Data";
    default:
      return "Unknow";
    }
  }

  json GetDataRefValue(uint64_t ref)
  {
    XPLMRef gDataRef = (XPLMDataRef)ref;
    XPLMDataTypeID gDataRefType = XPLMGetDataRefTypes(gDataRef);

    json response;
    if (gDataRefType == xplmType_Int)
    {
      response["value"] = ReadDataRefInt(gDataRef);
      response["type"] = "int";
    }
    else if (gDataRefType == xplmType_Float)
    {
      response["value"] = ReadDataRefFloat(gDataRef);
      response["type"] = "float";
    }
    else if (gDataRefType == xplmType_Double)
    {
      response["value"] = ReadDataRefDouble(gDataRef);
      response["type"] = "double";
    }
    else if (gDataRefType == xplmType_FloatArray)
    {
      response["value"] = ReadDataRefFloatArray(gDataRef);
      response["type"] = "Float Array";
    }
    else if (gDataRefType == xplmType_IntArray)
    {
      response["value"] = ReadDataRefIntArray(gDataRef);
      response["type"] = "Int Array";
    }
    else if (gDataRefType == xplmType_Data)
    {

      response["value"] = ReadDataRefByteArray(gDataRef);
      response["type"] = "Byte Array";
    }
    else
    {
      response["type"] = "Other";
      int sizeFLT = XPLMGetDatavf(gDataRef, nullptr, 0, 0);
      if (sizeFLT > 0)
      {
        response["value"] = ReadDataRefFloatArray(gDataRef);
      }
      else
      {
        int sizeBTY = XPLMGetDatab(gDataRef, nullptr, 0, 0);
        if (sizeBTY > 0)
        {
          response["value"] = ReadDataRefByteArray(gDataRef);
        }
        else
        {
          response["value"] = ReadDataRefDouble(gDataRef);
        }
      }
    }
    return response;
  }

  json SetDataRefValue(uint64_t ref, json newValue)
  {
    XPLMRef gDataRef = (XPLMDataRef)ref;
    XPLMDataTypeID gDataRefType = XPLMGetDataRefTypes(gDataRef);

    json response;
    if (gDataRefType == xplmType_Int)
    {
      return WriteDataRefInt(gDataRef, newValue);
    }
    else if (gDataRefType == xplmType_Float)
    {
      return WriteDataRefFloat(gDataRef, newValue);
    }
    else if (gDataRefType == xplmType_Double)
    {
      return WriteDataRefDouble(gDataRef, newValue);
    }
    else if (gDataRefType == xplmType_FloatArray)
    {
      return WriteDataRefFloatArray(gDataRef, newValue);
    }
    else if (gDataRefType == xplmType_IntArray)
    {
      return WriteDataRefIntArray(gDataRef, newValue);
    }
    else if (gDataRefType == xplmType_Data)
    {
      return WriteDataRefByteArray(gDataRef, newValue);
    }
    else
    {

      json responseInt = WriteDataRefInt(gDataRef, newValue);
      if ((responseInt.find("error") != responseInt.end()))
      {
        return responseInt;
      }
      else
      {
        json responseFloat = WriteDataRefFloat(gDataRef, newValue);
        if ((responseFloat.find("error") != responseFloat.end()))
        {
          return responseFloat;
        }
        else
        {
          json responseDouble = WriteDataRefDouble(gDataRef, newValue);
          if ((responseDouble.find("error") != responseDouble.end()))
          {
            return responseDouble;
          }
          else
          {
            json responseFloatArray = WriteDataRefFloatArray(gDataRef, newValue);
            if ((responseFloatArray.find("error") != responseFloatArray.end()))
            {
              return responseFloatArray;
            }
            else
            {
              json responseIntArray = WriteDataRefIntArray(gDataRef, newValue);
              if ((responseIntArray.find("error") != responseIntArray.end()))
              {
                return responseIntArray;
              }
              else
              {
                json responseByteArray = WriteDataRefByteArray(gDataRef, newValue);
                if ((responseByteArray.find("error") != responseByteArray.end()))
                {
                  return responseByteArray;
                }
                else
                {
                  json response;
                  response["error"] = "the type for the value was not found";
                  return response;
                }
              }
            }
          }
        }
      }
    }
  }

  int ReadDataRefInt(XPLMRef gDataRef)
  {
    return XPLMGetDatai(gDataRef);
  }

  float ReadDataRefFloat(XPLMRef gDataRef)
  {
    return XPLMGetDataf(gDataRef);
  }

  double ReadDataRefDouble(XPLMRef gDataRef)
  {
    return XPLMGetDatad(gDataRef);
  }

  vector<int> ReadDataRefIntArray(XPLMRef gDataRef)
  {
    int size = XPLMGetDatavi(gDataRef, nullptr, 0, 0);
    static vector<int> value;
    value.resize(size);
    XPLMGetDatavi(gDataRef, value.data(), 0, size);

    return value;
  }

  vector<float> ReadDataRefFloatArray(XPLMRef gDataRef)
  {
    int size = XPLMGetDatavf(gDataRef, nullptr, 0, 0);
    static vector<float> value;
    value.resize(size);
    XPLMGetDatavf(gDataRef, value.data(), 0, size);

    return value;
  }

  string ReadDataRefByteArray(XPLMRef gDataRef)
  {
    int size = XPLMGetDatab(gDataRef, nullptr, 0, 0);
    static vector<uint8_t> value;
    value.resize(size);
    XPLMGetDatab(gDataRef, value.data(), 0, size);
    string resultStr;
    for (const uint8_t byte : value)
    {
      if (0 != byte && isprint(byte))
      {
        resultStr.push_back(byte);
      }
    }
    return resultStr;
  }

  json WriteDataRefInt(XPLMRef gDataRef, json newValue)
  {
    json response;
    try
    {
      int value = newValue["newValue"].get<int>();
      XPLMSetDatai(gDataRef, value);
      response["value"] = value;
    }
    catch (json::exception &e)
    {
      response["error"] = e.what();
    }
    return response;
  }

  json WriteDataRefFloat(XPLMRef gDataRef, json newValue)
  {
    json response;
    try
    {
      float value = newValue["newValue"].get<float>();
      XPLMSetDataf(gDataRef, value);
      response["value"] = value;
    }
    catch (json::exception &e)
    {
      response["error"] = e.what();
    }
    return response;
  }

  json WriteDataRefDouble(XPLMRef gDataRef, json newValue)
  {
    json response;
    try
    {
      double value = newValue["newValue"].get<double>();
      XPLMSetDatad(gDataRef, newValue);
      response["value"] = value;
    }
    catch (json::exception &e)
    {
      response["error"] = e.what();
    }
    return response;
  }

  json WriteDataRefIntArray(XPLMRef gDataRef, json newValue)
  {
    json response;
    try
    {
      vector<int> vectorValue = newValue["newValue"].get<vector<int>>();
      int sizeINT = XPLMGetDatavi(gDataRef, nullptr, 0, 0);
      if (sizeINT == vectorValue.size())
      {
        int *value = &vectorValue[0];
        XPLMSetDatavi(gDataRef, value, 0, sizeINT);
        response["value"] = vectorValue;
      }
      else
      {
        response["error"] = "array values are not the same size as your dataRef";
      }
    }
    catch (json::exception &e)
    {
      response["error"] = e.what();
    }
    return response;
  }

  json WriteDataRefFloatArray(XPLMRef gDataRef, json newValue)
  {
    json response;
    try
    {
      vector<float> vectorValue = newValue["newValue"].get<vector<float>>();
      int sizeFLT = XPLMGetDatavf(gDataRef, nullptr, 0, 0);
      if (sizeFLT == vectorValue.size())
      {
        float *value = &vectorValue[0];
        XPLMSetDatavf(gDataRef, value, 0, sizeFLT);
        response["value"] = vectorValue;
      }
      else
      {
        vectorValue = ReadDataRefFloatArray(gDataRef);
        response["error"] = "array values are not the same size as your dataRef";
      }
    }
    catch (json::exception &e)
    {
      response["error"] = e.what();
    }
    return response;
  }

  json WriteDataRefByteArray(XPLMRef gDataRef, json newValue)
  {
    json response;
    try
    {
      string valueStr = newValue["newValue"].get<string>();
      XPLMSetDatab(gDataRef, reinterpret_cast<void *>(const_cast<char *>(valueStr.c_str())), 0, static_cast<int>(valueStr.size() + 1));
      response["value"] = ReadDataRefByteArray(gDataRef);
    }
    catch (json::exception &e)
    {
      response["error"] = e.what();
    }
    return response;
  }

} // namespace manipulator