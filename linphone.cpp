/**********************************************************\

  Auto-generated linphone.cpp

  This file contains the auto-generated main plugin object
  implementation for the linphone-js project

\**********************************************************/

#include "linphoneAPI.h"
#include "VideoWindowAPI.h"

#include "linphone.h"

// TO BE REMOVED WHEN NOT NEEDED ANYMORE
#include <typeinfo>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
/// @fn linphone::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void linphone::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
    
    printf("static init\n");
}

///////////////////////////////////////////////////////////////////////////////
/// @fn linphone::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void linphone::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
    printf("static de-init\n");
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  linphone constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
linphone::linphone()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  linphone destructor.
///////////////////////////////////////////////////////////////////////////////
linphone::~linphone()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

void linphone::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
}

void linphone::shutdown()
{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<linphone> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr linphone::createJSAPI()
{
    // m_host is the BrowserHost
    boost::optional<std::string> param;
    std::string type("main");
    if(param = this->getParam("pluginType")) type = *param;

    std::cout << "Type: " << type << std::endl;


    if(type == "main") {
        isMain = true; isVideo = false;
        return boost::make_shared<linphoneAPI>(FB::ptr_cast<linphone>(shared_from_this()), m_host);
    }
    else if(type == "video") {
        isMain = false; isVideo = true;
        return boost::make_shared<VideoWindowAPI>(FB::ptr_cast<linphone>(shared_from_this()), m_host);
    }
    else throw FB::script_error("Wrong type");
}


bool linphone::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool linphone::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool linphone::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}
bool linphone::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *win)
{
    // The window is attached; act appropriately
    printf("Window attached\n");
    std::cout << typeid(*evt).name() << ", " << typeid(*win).name() << std::endl;

    if(isMain) {
        // TODO: find out how to cast to linphoneAPIPtr
        linphoneAPIPtr api(FB::ptr_cast<linphoneAPI>(getRootJSAPI()));
        api->_fire_windowAttached(getNativeWindowId());
    }
    else if(isVideo) {

    }

    return false;
}

/**
 * Get native plugin window ID
 */
unsigned long linphone::getNativeWindowId(void) {
#if FB_X11
	FB::PluginWindowX11 *win = (FB::PluginWindowX11 *) GetWindow();
	return win ? win->getWindow() : NULL;
	
#elif FB_WIN
	FB::PluginWindowWin *win = (FB::PluginWindowWin *) GetWindow();
	return win->getHWND();

#elif FB_MAC
	FB::PluginWindowMac *win = (FB::PluginWindowMac *) GetWindow();
	return win->getWindowRef();

#else
	printf("getWindowId not supported, unknown platform\n");
	return 0;
	
#endif
}

bool linphone::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    printf("Window detached\n");

    if(isMain) {
        linphoneAPIPtr api(FB::ptr_cast<linphoneAPI>(getRootJSAPI()));
        api->_windiw_detached(getNativeWindowId());
    }
    else if(isVideo) {

    }

    return false;
}

bool linphone::draw(FB::RefreshEvent *evt, FB::PluginWindow*) {
    printf("Draw please\n");
}
