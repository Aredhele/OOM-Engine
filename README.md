# Floppy-Bug
<a href="https://aredhele.itch.io/floppy-bug">Floppy-Bug</a> is a game created for the Floppy game jam with the OOM-Engine, a custom game engine realized for the occasion.

The game was created by :
* <a href="https://darennkeller.wordpress.com/">Darenn Keller</a> - Game designer
* <a href="https://vincentcalisto.com/">Vincent Stehly--Calisto</a> - Engine/Gameplay programmer
* <a href="https://www.artstation.com/thomaslukegarcia">Thomas Garcia</a> - 3D/2D Game Artist
* <a href="demeyaurelien.wixsite.com/aureliendemey">Aurélien Demey</a> - Game Sound Designer / Composer

The game won the design and the quality prices and the second place in gameplay :

<p align="center">
  <img src="https://image.noelshack.com/fichiers/2018/34/1/1534761613-e1.png" width="729" height="181" />
</p>

# OOM-Engine
1.44 MB 3D game engine made in C++17 with OpenGL holding in a floppy disk. The engine fits in
440 KB only and was made for the <a href="https://itch.io/jam/floppyjam">**Floppy game jam**</a>
in approximately 15 days.

Third party libraries :
* Glew
* Glfw
* Glm
* DirectX (Direct Sound)
* <a href="https://github.com/RandyGaul/qu3e">qu3e</a>
* <a href="https://github.com/xiph/ogg">ogg</a>
* <a href="https://github.com/xiph/vorbis">vorbis</a>

The project is under CMake 3.2 and is compatible (tested) with Microsoft
Visual Studio 2017 (CMake support). The engine is no more compatible with GCC
since DirectX headers have missing definitions.

You can find <a href="https://www.youtube.com/watch?v=wQ5CTL_yWNIs">here</a> the teaser
of the project and <a href="https://www.youtube.com/watch?v=B6xjwc-0cTM">here</a> a video of all
engine features.

**Scene example preview**

<p align="center">
  <a href="http://zupimages.net/viewer.php?id=18/34/7r0q.gif"><img src="https://zupimages.net/up/18/34/7r0q.gif" alt="" /></a>
</p>

### Features

#### General
* Full entity-component pattern
* Game objects
* A complete SDK

#### Rendering
* Post-processing
    * Post-processing stack
    * Vignette
    * Depth of field
    * Fog
    * FXAA

* Renderer
    * MeshRenderer
    * TextRenderer
    * SpriteRenderer

* Lighting
    * Directional light
    * Point light

* Debug
    * Gizmos (Box, Cone, lights etc.)
    * Lines
    * Rays

#### Audio
* DirectX (Direct Sound)
    * Wav file loading
    * 3D Audio listener
    * 3D Audio source
    * Support of WAV files
    * Support of OGG files

### Physics
* Integration of qu3e
    * Box collider
    * Rigid body
    * Ray cast

## Usage

Code
```cpp
#include "SDK/SDK.hpp"

int main(int argc, char** argv)
{
    Sdk::Debug::EnableGizmo(EGizmo::Axis);
    Sdk::Debug::EnableGizmo(EGizmo::Grid);
    Sdk::Debug::EnableGizmo(EGizmo::Transform);
    Sdk::Debug::EnableGizmo(EGizmo::AllColliders);

    Sdk::GameObject::CreateFreeCamera();
    Sdk::GameObject::CreateDirectionalLight();

    // Import a mesh
    Sdk::Import::ImportMesh("Resources/Mesh/Mesh_Cube.obj");

    // Create the ground
    auto* p_ground_go   = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
    auto* p_ground_body = p_ground_go->AddComponent<CRigidBody>();
    auto* p_ground_box  = p_ground_go->AddComponent<CBoxCollider>();

    // The ground is a static body
    p_ground_body->SetBodyType(CRigidBody::EBodyType::Static);

    return 0;
}
```
