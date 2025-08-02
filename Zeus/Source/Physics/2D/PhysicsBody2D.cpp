// PhysicsBody2D.cpp
#include "Core/CoreLibrary.h"
#include "PhysicsBody2D.h"

namespace {
    inline bool IsValidBody(b2BodyId id) {
        return b2Body_IsValid(id);
    }
}

PhysicsBody2D::PhysicsBody2D(PhysicsWorld2D& world, const BodyShape& body)
    : z_Body(body), z_World(&world)
{
    // Body definition
    z_BodyDef = b2DefaultBodyDef();
    z_BodyDef.type = z_Body.Type;
    z_BodyDef.position = b2Vec2(z_Body.X, z_Body.Y);
    z_BodyDef.angle = z_Body.Angle;
    z_BodyDef.fixedRotation = z_Body.FixedRotation;
    z_BodyDef.enableSleep = z_Body.CanSleep;
    z_BodyDef.gravityScale = z_Body.Gravity;
    z_BodyDef.isEnabled = z_Body.Enabled;
    z_BodyDef.linearDamping = z_Body.LinearDamping;
    z_BodyDef.angularDamping = z_Body.AngularDamping;
    z_BodyDef.isBullet = z_Body.Bullet;

    // Create body
    z_BodyId = b2CreateBody(z_World->GetId(), &z_BodyDef);
    if (!IsValidBody(z_BodyId)) {
        // Log or throw as per your engine's error policy
        CORE_LOG_ERROR("Failed to create b2Body");
        return;
    }

    // Create fixture(s)
    CreateShapes_();
}

PhysicsBody2D::~PhysicsBody2D() {
    Destroy();
}

PhysicsBody2D::PhysicsBody2D(PhysicsBody2D&& other) noexcept
    : z_Body(std::move(other.z_Body))
    , z_BodyDef(other.z_BodyDef)
    , z_BodyId(other.z_BodyId)
    , z_World(other.z_World)
{
    other.z_BodyId = b2_nullBodyId;
    other.z_World = nullptr;
}

PhysicsBody2D& PhysicsBody2D::operator=(PhysicsBody2D&& other) noexcept {
    if (this == &other) return *this;
    Destroy();
    z_Body = std::move(other.z_Body);
    z_BodyDef = other.z_BodyDef;
    z_BodyId = other.z_BodyId;
    z_World = other.z_World;
    other.z_BodyId = b2_nullBodyId;
    other.z_World = nullptr;
    return *this;
}

void PhysicsBody2D::CreateShapes_() {
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = z_Body.Material.density;
    shapeDef.friction = z_Body.Material.friction;
    shapeDef.restitution = z_Body.Material.restitution;
    shapeDef.isSensor = z_Body.IsSensor;

    // Collision filtering
    shapeDef.filter.categoryBits = z_Body.CategoryBits;
    shapeDef.filter.maskBits = z_Body.MaskBits;
    shapeDef.filter.groupIndex = z_Body.GroupIndex;

    switch (z_Body.Shape) {
        case ShapeType::Box: {
            // Note: b2MakeBox in v3 expects half-width/half-height. Your fields appear to be half-extents already.
            b2Polygon box = b2MakeBox(z_Body.Width, z_Body.Height);
            b2ShapeId shapeId = b2CreatePolygonShape(z_BodyId, &shapeDef, &box);
            if (!b2Shape_IsValid(shapeId)) {
                CORE_LOG_ERROR("Failed to create polygon shape");
            }
            break;
        }
        case ShapeType::Circle: {
            b2Circle circle{};
            circle.center = b2Vec2(0.0f, 0.0f);
            circle.radius = z_Body.Radius;
            b2ShapeId shapeId = b2CreateCircleShape(z_BodyId, &shapeDef, &circle);
            if (!b2Shape_IsValid(shapeId)) {
                CORE_LOG_ERROR("Failed to create circle shape");
            }
            break;
        }
        // Add other shape types here (polygons, capsules, chains)
        default:
            CORE_LOG_WARNING("Unsupported ShapeType, no fixtures created");
            break;
    }
}

void PhysicsBody2D::Destroy() {
    if (IsValidBody(z_BodyId)) {
        b2DestroyBody(z_BodyId);
        z_BodyId = b2_nullBodyId;
    }
}

bool PhysicsBody2D::IsValid() const {
    return IsValidBody(z_BodyId);
}

void PhysicsBody2D::SetAwake(bool awake) {
    if (!IsValid()) return;
    b2Body_SetAwake(z_BodyId, awake);
}

void PhysicsBody2D::Sleep(bool sleep) {
    // Box2D uses "awake" flag. To sleep, set awake=false.
    SetAwake(!sleep);
}

void PhysicsBody2D::ApplyForce(const b2Vec2& force, const b2Vec2& worldPoint, bool wake) {
    if (!IsValid()) return;
    b2Body_ApplyForce(z_BodyId, force, worldPoint, wake);
}

void PhysicsBody2D::ApplyForceToCenter(const b2Vec2& force, bool wake) {
    if (!IsValid()) return;
    b2Body_ApplyForceToCenter(z_BodyId, force, wake);
}

void PhysicsBody2D::ApplyLinearImpulse(const b2Vec2& impulse, const b2Vec2& worldPoint, bool wake) {
    if (!IsValid()) return;
    b2Body_ApplyLinearImpulse(z_BodyId, impulse, worldPoint, wake);
}

void PhysicsBody2D::ApplyLinearImpulseToCenter(const b2Vec2& impulse, bool wake) {
    if (!IsValid()) return;
    b2Body_ApplyLinearImpulseToCenter(z_BodyId, impulse, wake);
}
