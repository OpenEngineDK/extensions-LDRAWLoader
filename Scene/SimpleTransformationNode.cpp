

#include <Scene/SimpleTransformationNode.h>

namespace OpenEngine {
    namespace Scene {


        SimpleTransformationNode::SimpleTransformationNode(const SimpleTransformationNode& node) : SceneNode(node) {
            transformationMatrix = node.transformationMatrix;
        }
        SimpleTransformationNode::SimpleTransformationNode() {
            
        }
        
        ISceneNode* SimpleTransformationNode::CloneSelf() {
            return new SimpleTransformationNode(*this);
        }

        void SimpleTransformationNode::Accept(ISceneNodeVisitor& v) {
            v.VisitSimpleTransformationNode(this);
        }

        SimpleTransformationNode::~SimpleTransformationNode() {}

        Matrix<4,4,float> SimpleTransformationNode::GetTransformationMatrix() {
            return transformationMatrix;
        }

    }
}
