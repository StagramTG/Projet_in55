#include "Model.h"

IN::Model::Model(std::string file)
{
    // Load Model file with assimp
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file, 
        aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    
    // Extract all meshes and build them
    for(size_t i = 0; i < scene->mNumMeshes; ++i)
    {
		aiMaterial* material = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];

        // Create mesh and push in vector
        Mesh m = createMeshes(scene->mMeshes[i], material);
        meshes.push_back(m);
    }

    // Free memory
    importer.FreeScene();
}

IN::Model::~Model()
{

}

void IN::Model::render()
{

}

IN::Mesh IN::Model::createMeshes(aiMesh* mesh, aiMaterial* material)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    // Extract data in vector of Vertex
    for(size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;

        aiVector3D pos = mesh->mVertices[i];
        vertex.position = glm::vec3(pos.x, pos.y, pos.z);

        if(mesh->HasNormals())
        {
            aiVector3D nor = mesh->mNormals[i];
            vertex.normal = glm::vec3(nor.x, nor.y, nor.z);
        }

        if(mesh->HasTextureCoords(0))
        {
            aiVector3D tex = mesh->mTextureCoords[0][i];
            vertex.uv = glm::vec2(tex.x, tex.y);
        }

        // Push the vertex in vector
        vertices.push_back(vertex);
    }

    // Extract indices
    for(size_t y = 0; y < mesh->mNumFaces; ++y)
    {
        indices.push_back(mesh->mFaces[y].mIndices[0]);
        indices.push_back(mesh->mFaces[y].mIndices[1]);
        indices.push_back(mesh->mFaces[y].mIndices[2]);
    }

    // Extract textures
    if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {

    }

    // Create the mesh
    Mesh newMesh;
    newMesh.create(vertices, indices, std::vector<Texture>());
}