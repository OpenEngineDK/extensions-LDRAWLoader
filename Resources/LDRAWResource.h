#ifndef _LDRAW_RESOURCE_H_
#define _LDRAW_RESOURCE_H_

#include <Resources/IModelResource.h>
#include <Resources/IResourcePlugin.h>

#include <Geometry/FaceSet.h>

namespace OpenEngine {
namespace Resources {

    using namespace OpenEngine::Geometry;
    


/** 
 * LDRAW-model resource plug-in.
 * @class LDRAWPlugin LDRAWResource.h "LDRAWResource.h"
 */ 
    class LDRAWPlugin : public IResourcePlugin<IModelResource> {
    public:
        LDRAWPlugin();
        IModelResourcePtr CreateResource(string file);
        
    };

    /**
     * LDRAW-model resource
     * @class LDRAWResource LDRAWResource.h "LDRAWResource.h"
     */
    class LDRAWResource : public IModelResource {
    private:
        string file;
        FaceSet* faces;
        ISceneNode* node;
    public:
        LDRAWResource(string file);
        ~LDRAWResource();
        void Load();
        void Unload();
        
        ISceneNode* GetSceneNode();
    };


}
}

#endif
