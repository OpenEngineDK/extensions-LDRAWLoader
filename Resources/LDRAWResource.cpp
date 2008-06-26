#include <Resources/LDRAWResource.h>
#include <Resources/File.h>
#include <Logging/Logger.h>

#include <Scene/SceneNode.h>
#include <Scene/GeometryNode.h>
#include <Scene/TransformationNode.h>
#include <Scene/SimpleTransformationNode.h>

#include <Resources/DirectoryManager.h>

using namespace std;
using namespace OpenEngine::Scene;

namespace OpenEngine {
namespace Resources {

    LDRAWPlugin::LDRAWPlugin() {
        this->AddExtension("dat");
    }

    IModelResourcePtr LDRAWPlugin::CreateResource(string file) {
        return IModelResourcePtr(new LDRAWResource(file));
    }


    LDRAWResource::LDRAWResource(string file) : file(file) {}

    LDRAWResource::~LDRAWResource() {}

    void LDRAWResource::Load() {
        
        faces = new FaceSet();
        node = new SceneNode();
        char buffer[256];
        
        ifstream* in = File::Open(file);

        while(!in->eof()) {
            in->getline(buffer, 256);
            
            switch (buffer[0]) {
                
            case '1':
                {
                    //logger.info << "Subfile: " << buffer << logger.end;
                char fstring[255];
                Matrix<4,4,float> matrix;
                matrix[3][3] = 1.0;
                matrix[0][3] = 1.0;
                matrix[1][3] = 1.0;
                matrix[2][3] = 1.0;
                int color;
                
                sscanf(buffer, "1 %i %f %f %f %f %f %f %f %f %f %f %f %f %s",
                       &color,
                       &matrix(3,0),&matrix(3,1),&matrix(3,2),
                       &matrix(0,0),&matrix(1,0),&matrix(2,0),
                       &matrix(0,1),&matrix(1,1),&matrix(2,1),
                       &matrix(0,2),&matrix(1,2),&matrix(2,2),
                       fstring
                       );


                string filestring = string(fstring);
                
                while(string::size_type loc = filestring.find('\\',0) != string::npos) {
                    filestring[loc] = '/';
                }
                
                //logger.info << "Matrix: " << matrix << logger.end;
                //logger.info << "File: " << filestring << logger.end;

                SimpleTransformationNode* tnode = new SimpleTransformationNode();
                tnode->transformationMatrix = matrix;
                // Move the transformation

                LDRAWResource* subres = new LDRAWResource(DirectoryManager::FindFileInPath(filestring));
                subres->Load();

                tnode->AddNode(subres->GetSceneNode());

                subres->Unload();

                node->AddNode(tnode);

                }
                break;
            case '2':
                // ignore this line...
                break;
            case '3':
                {

                    //logger.info << "Face: " << buffer << logger.end;
                    int color;
                    Vector<3,float> p1,p2,p3;
                    sscanf(buffer,"3 %i %f %f %f %f %f %f %f %f %f",
                           &color,
                           &p1[0],&p1[1],&p1[2],
                           &p2[0],&p2[1],&p2[2],
                           &p3[0],&p3[1],&p3[2]
                           );
                    FacePtr f = FacePtr(new Face(p1,p2,p3));
                    faces->Add(f);
                    //logger.info << f->ToString() << logger.end;
                }
                break;
            case '4':
                {
                Vector<3,float> p1,p2,p3,p4;
                int color;
                sscanf(buffer,"4 %i %f %f %f %f %f %f %f %f %f %f %f %f",
                       &color,
                       &p1[0], &p1[1], &p1[2],
                       &p2[0], &p2[1], &p2[2],
                       &p3[0], &p3[1], &p3[2],
                       &p4[0], &p4[1], &p4[2]);

                //logger.info << "Quad" << logger.end;

                FacePtr f1 = FacePtr(new Face(p1,p2,p3));
                FacePtr f2 = FacePtr(new Face(p3,p4,p1));
                f1->colr[0] = Vector<4,float>(1,0,0,1);
                f1->colr[1] = Vector<4,float>(1,0,0,1);
                f1->colr[2] = Vector<4,float>(1,0,0,1);

                faces->Add(f1);
                faces->Add(f2);

                }
                break;
            case '5':
                // ignore lines for now
                break;
            case '\0':
            case '0':
                // Comment, ignore!
                //logger.info << "Comment: " << buffer << logger.end;
                break;
            default:
                logger.info << "Other: " << buffer << logger.end;
            }

        }
        
        node->AddNode(new GeometryNode(faces));

    }
   

    void LDRAWResource::Unload() {
        node = NULL;
        faces = NULL;
    }

    
    ISceneNode* LDRAWResource::GetSceneNode() {
        return node;
    }

    
}
}
