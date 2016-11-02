/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef _BspLevelManager_H__
#define _BspLevelManager_H__

#include "OgreBspPrerequisites.h"
#include "OgreResourceManager.h"
#include "OgreSingleton.h"

namespace Ogre {
    /** \addtogroup Plugins
    *  @{
    */
    /** \addtogroup BSPSceneManager
    *  @{
    */
    /** Manages the locating and loading of BSP-based indoor levels.
    Like other ResourceManager specialisations it manages the location and loading
    of a specific type of resource, in this case files containing Binary
    Space Partition (BSP) based level files e.g. Quake3 levels.
    However, note that unlike other ResourceManager implementations,
    only 1 BspLevel resource is allowed to be loaded at one time. Loading
    another automatically unloads the currently loaded level if any.
    */
    class BspResourceManager : public ResourceManager, public Singleton<BspResourceManager>
    {
    public:
        BspResourceManager();
        ~BspResourceManager();

        /** Loads a BSP-based level from the named file.
            Currently only supports loading of Quake3 .bsp files.
        */
        ResourcePtr load(const String& name, 
            const String& group, bool isManual = false, 
            ManualResourceLoader* loader = 0, const NameValuePairList* loadParams = 0,
            bool backgroundThread = false);

        /** Loads a BSP-based level from a stream.
            Currently only supports loading of Quake3 .bsp files.
        */
        ResourcePtr load(DataStreamPtr& stream, const String& group);

        /** Override standard Singleton retrieval.
        @remarks
        Why do we do this? Well, it's because the Singleton
        implementation is in a .h file, which means it gets compiled
        into anybody who includes it. This is needed for the
        Singleton template to work, but we actually only want it
        compiled into the implementation of the class based on the
        Singleton, not all of them. If we don't change this, we get
        link errors when trying to use the Singleton-based class from
        an outside dll.
        @par
        This method just delegates to the template version anyway,
        but the implementation stays in this single compilation unit,
        preventing link errors.
        */
        static BspResourceManager& getSingleton(void);
        /** Override standard Singleton retrieval.
        @remarks
        Why do we do this? Well, it's because the Singleton
        implementation is in a .h file, which means it gets compiled
        into anybody who includes it. This is needed for the
        Singleton template to work, but we actually only want it
        compiled into the implementation of the class based on the
        Singleton, not all of them. If we don't change this, we get
        link errors when trying to use the Singleton-based class from
        an outside dll.
        @par
        This method just delegates to the template version anyway,
        but the implementation stays in this single compilation unit,
        preventing link errors.
        */
        static BspResourceManager* getSingletonPtr(void);


    protected:
        /** @copydoc ResourceManager::createImpl. */
        Resource* createImpl(const String& name, ResourceHandle handle, 
            const String& group, bool isManual, ManualResourceLoader* loader, 
            const NameValuePairList* createParams);

        // Singleton managed by this class
        Quake3ShaderManager *mShaderMgr;

    };
    /** @} */
    /** @} */
}

#endif
