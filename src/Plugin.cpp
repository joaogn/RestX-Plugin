/*
 * SimData.c
 * 
 * This example demonstrates how to interact with X-Plane by reading and writing
 * data.  This example creates menus items that change the nav-1 radio frequency.
 * 
 */
#include "XPLM/XPLMPlugin.h"
#include "src/server/Server.h"
#include <cstdlib>
#include <thread>

using namespace std;

server::Server restService;

void StartRestService()
{
  restService.StartServer();
}

PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc)
{

  /* Provide our plugin's profile to the plugin system. */
  strcpy(outName, "RestXPlugin");
  strcpy(outSig, "xplanesdk.examples.restxplugin");
  strcpy(outDesc, "Rest Api plugin to Xplane, this can Get and Write DataRefs through Web.");

  thread StartServerThread(StartRestService);
  StartServerThread.detach();

  return 0;
}

PLUGIN_API void XPluginStop(void)
{
  restService.StopServer();
}

PLUGIN_API void XPluginDisable(void) {}

PLUGIN_API int XPluginEnable(void)
{
  return 1;
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho, int inMessage, void *inParam) {}