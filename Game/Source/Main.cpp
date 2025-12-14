#include "Zeus.h"

#include "Animation/3D/ZAnimation.h"
#include "Animation/3D/ZAnimator.h"

#include "Gameplay/Demon.h"

class Game : public ZApplication
{
public:
    Game() 
    {
        Init();
        ZApplication::Update(z_Main,z_GameCamera);
    }

    ~Game()
    {

    }

    void Init()
    {
        //z_Levels.Add("Main", z_Main);

        z_Cube2 = z_Main.Create3DMeshEntity(ZTransform(Vec3(-7.5, 0, 0), Vec3(45, 0, 0)), ZCube(), ZShader("Zeus/Resource/Shaders/Lighting/TEADS.vert", "Zeus/Resource/Shaders/Lighting/TEADS.frag", {.Red = -1, .Green = -1, .Blue = -1}, "", {ZTexture("diffues0","Zeus/Resource/Textures/Wood.png")}, true));
        z_Cube2.AddComponent<ZBoxCollider>(ZBoxCollider(Vec3(0), Vec3(3.0)));

        z_Plane = z_Main.Create3DMeshEntity(ZTransform(Vec3(0, -5, 0)), ZPlane(), ZShader("Zeus/Resource/Shaders/Lighting/ADS.vert", "Zeus/Resource/Shaders/Lighting/ADS.frag", { .Red = 0.33, .Green = 0.33, .Blue = 0.33 }));
        z_Plane.AddComponent<ZBoxCollider>(ZBoxCollider(z_Plane.GetPosition(), Vec3(50, 1, 50)));
        z_Sphere = z_Main.Create3DMeshEntity(ZTransform(Vec3(-5.0, 0.0, 0.0), Vec3(0), Vec3(0.05f)), ZSphere(), ZShader("Zeus/Resource/Shaders/Lighting/ADS.vert", "Zeus/Resource/Shaders/Lighting/ADS.frag", { .Red = 1.0, .Green = 0.0, .Blue = 0.23 }));
        z_Sphere.AddComponent<ZBoxCollider>(ZBoxCollider(Vec3(-5.0, 0, 0.5), Vec3(1.0)));
        z_Cube = z_Main.Create3DMeshEntity(ZTransform(Vec3(0.0), Vec3(45, 0, 0)), ZCube(), ZShader("Zeus/Resource/Shaders/Lighting/ADS.vert", "Zeus/Resource/Shaders/Lighting/ADS.frag", { .Red = 0.0, .Green = 0.67, .Blue = 0.89 }));
        z_Cube.AddComponent<ZBoxCollider>(ZBoxCollider(Vec3(0), Vec3(3.0)));
        z_Ship = z_Main.Create3DMeshEntity(ZTransform(Vec3(5.0, 2, 0), Vec3(1.0)), ZModel("Zeus/Resource/Models/SpaceShip", "scene.gltf"), ZShader("Zeus/Resource/Shaders/Lighting/AssimpEADS.vert", "Zeus/Resource/Shaders/Lighting/AssimpEADS.frag", { .Red = -1, .Green = -1, .Blue = -1 }, "", {}, true));
        z_Ship.AddComponent<ZBoxCollider>(ZBoxCollider(Vec3(5.0, 2, 0), Vec3(5)));

        z_SkyboxEntity = z_Main.CreateEntity(ZTransform(Vec3(0)));
        z_SkyboxEntity.AddComponent<ZSkybox>(ZSkybox());

        z_TerrianEntity = z_Main.CreateEntity(ZTransform(Vec3(0)));
        z_TerrianEntity.AddComponent<ZTerrian>(ZTerrian("Zeus/Resource/Textures/iceland_heightmap.png",true));

        static_cast<ZEntity&>(z_Demon) = z_Main.Create3DMeshEntity(ZTransform(Vec3(-5.0, 2, 0), Vec3(0.0),Vec3(5)), ZModel("Zeus/Resource/Models/Demon", "Demon.dae"), ZShader("Zeus/Resource/Shaders/Animation/Animation.vert", "Zeus/Resource/Shaders/Animation/Animation.frag", { .Red = -1, .Green = -1, .Blue = -1 }, "", {}));
        z_Demon.AddComponent<ZBoxCollider>(ZBoxCollider(Vec3(5.0, 2, 0), Vec3(5)));
        z_Sprite = z_Main.CreateUiSpriteEntity(ZTransform(Vec3(10.0f, 540.0f, 0.0f), Vec3(270.0f, 0.0f, 0.0f), Vec3(50.0f, 50.0f, 0.0f)), ZSprite(), ZShader("Zeus/Resource/Shaders/Sprites/SpriteColored.vert", "Zeus/Resource/Shaders/Sprites/SpriteColored.frag"));
        z_Text = z_Main.CreateUiTextEntity(ZTransform(Vec3(400, 500, 0)), ZText("Hello World", 20, { .Red = 0.33, .Green = 0.67, .Blue = 0.89 }), ZShader("Zeus/Resource/Shaders/Texts/Text.vert", "Zeus/Resource/Shaders/Texts/Text.frag"));

        z_TerrianShader = ZTessellationShader("Zeus/Resource/Shaders/Terrian/Terrian.vert", "Zeus/Resource/Shaders/Terrian/Terrian.frag", "Zeus/Resource/Shaders/Terrian/Terrian.tcs", "Zeus/Resource/Shaders/Terrian/Terrian.tes");

        ZOutput.Load("Shoot", "Zeus/Resource/Sounds/Shoot.wav");

        z_FPSController = ZFPSController(z_GameCamera);

        ZRuntime.Add(z_FPSController);
        ZRuntime.Add(z_Demon);
    }

    ZLevel z_Main{};
    //LevelCache z_Levels{};

    ZCamera z_GameCamera = ZCamera(Vec3(0, 0, 10));

    ZFPSController z_FPSController{};

    ZEntity z_Sprite{};
    ZEntity z_Text{};

    ZEntity z_Ship{};
    Demon z_Demon{};
    ZEntity z_Cube{};
    ZEntity z_Cube2{};
    ZEntity z_Plane{};
    ZEntity z_Sphere{};

    ZEntity z_SkyboxEntity{};
    ZEntity z_TerrianEntity{};



    ZTessellationShader z_TerrianShader{};
    
};


ZApplication* CreateZApplication()
{
    return new Game();
}