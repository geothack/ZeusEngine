// PhysicsBody2D.h
#pragma once
#include "Core/CoreLibrary.h"
#include "PhysicsWorld2D.h"
#include <box2d/box2d.h>

enum class ShapeType { Box, Circle /*, Polygon, Capsule, etc. */ };

struct Material2D {
    float density = 1.0f;
    float friction = 0.3f;
    float restitution = 0.0f;
};

struct BodyShape {
    // Body setup
    b2BodyType Type = b2_dynamicBody;
    float X = 0.0f;
    float Y = 0.0f;
    float Angle = 0.0f;            // new: initial rotation (radians)
    bool FixedRotation = false;
    bool CanSleep = true;
    float Gravity = 1.0f;          // gravity scale
    bool Enabled = true;
    float LinearDamping = 0.0f;    // new
    float AngularDamping = 0.0f;   // new
    bool Bullet = false;           // new: continuous collision

    // Shape setup
    ShapeType Shape = ShapeType::Box;
    float Width = 0.5f;            // box half-width
    float Height = 0.5f;           // box half-height
    float Radius = 0.5f;           // for circles

    // Material
    Material2D Material{};
    uint16_t CategoryBits = 0x0001;     // new: collision filtering
    uint16_t MaskBits = 0xFFFF;
    int16_t GroupIndex = 0;

    // Sensor
    bool IsSensor = false;
};

class PhysicsBody2D {
public:
    PhysicsBody2D(PhysicsWorld2D& world, const BodyShape& body);
    ~PhysicsBody2D();

    PhysicsBody2D(const PhysicsBody2D&) = delete;
    PhysicsBody2D& operator=(const PhysicsBody2D&) = delete;
    PhysicsBody2D(PhysicsBody2D&& other) noexcept;
    PhysicsBody2D& operator=(PhysicsBody2D&& other) noexcept;

    void Destroy();

    // State
    void SetAwake(bool awake);
    void Sleep(bool sleep); // convenience
    bool IsValid() const;

    // Forces/velocities (wrappers)
    void ApplyForce(const b2Vec2& force, const b2Vec2& worldPoint, bool wake = true);
    void ApplyForceToCenter(const b2Vec2& force, bool wake = true);
    void ApplyLinearImpulse(const b2Vec2& impulse, const b2Vec2& worldPoint, bool wake = true);
    void ApplyLinearImpulseToCenter(const b2Vec2& impulse, bool wake = true);

    // Access
    b2BodyId GetId() const { return z_BodyId; }

private:
    void CreateShapes_();

private:
    BodyShape z_Body;
    b2BodyDef z_BodyDef{};
    b2BodyId z_BodyId{ b2_nullBodyId };
    PhysicsWorld2D* z_World = nullptr;
};
