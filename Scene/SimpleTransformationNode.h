// Transformation node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SIMPLE_TRANSFORMATION_NODE_H_
#define _SIMPLE_TRANSFORMATION_NODE_H_

#include <Scene/SceneNode.h>
#include <Scene/ISceneNodeVisitor.h>

#include <Math/Vector.h>
#include <Math/Matrix.h>

namespace OpenEngine {
namespace Scene {

using OpenEngine::Math::Vector;
using OpenEngine::Math::Matrix;


    class SimpleTransformationNode : public SceneNode {

        OE_SCENE_NODE(SimpleTransformationNode, SceneNode)

private:


protected:


    ISceneNode* CloneSelf();

public:

    Matrix<4,4,float> transformationMatrix;
    
    // constructor / destructor
    SimpleTransformationNode();
    SimpleTransformationNode(const SimpleTransformationNode&);
    virtual ~SimpleTransformationNode();


    Matrix<4,4,float> GetTransformationMatrix();


};

} // NS Scene
} // NS OpenEngine


#endif // _SIMPLE_TRANSFORMATION_NODE_H_
