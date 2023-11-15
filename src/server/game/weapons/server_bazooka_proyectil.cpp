//
// Created by xguss on 14/11/23.
//

#include "server_bazooka_proyectil.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "bazooka_proyectil_info.h"

BazookaProyectil::BazookaProyectil(b2World* world, b2Vec2& pos, float angle) :
        dragConstant(.3),
        GameObject() {

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 510);

    b2PolygonShape polygonShape;
    b2Vec2 vertices[4];
    vertices[0].Set(-.5f, -0);
    vertices[1].Set(0, -0.2f);
    vertices[2].Set(0.2, 0);
    vertices[3].Set(0, 0.2f);

    polygonShape.Set(vertices, 4);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 1;

    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    body = world->CreateBody(&bodyDef);

    body->CreateFixture( &fixtureDef );
    body->SetAngularDamping( 1);
    body->SetBullet(true);

    body->SetAwake(true);
    body->SetAngularVelocity(0);
    body->SetTransform( pos, angle);
    body->SetLinearVelocity( body->GetWorldVector( b2Vec2(1 * 12,0)));
}

void BazookaProyectil::update(b2World& world) {

    b2Vec2 flightDirection = body->GetLinearVelocity();
    float flightSpeed = flightDirection.Normalize();//normalizes and returns length
    b2Vec2 pointingDirection = body->GetWorldVector( b2Vec2( 1, 0 ) );
    float dot = b2Dot( flightDirection, pointingDirection );

    float dragForceMagnitude = (1 - fabs(dot)) * flightSpeed * flightSpeed * dragConstant * body->GetMass();

    b2Vec2 arrowTailPosition = body->GetWorldPoint( b2Vec2( -0.5, 0 ) );

    body->ApplyForce( dragForceMagnitude * -flightDirection, arrowTailPosition, true);
}



std::unique_ptr<GameObjectInfo> BazookaProyectil::get_status() const {
    return std::make_unique<BazookaProyectilInfo>(*this);
}
ObjectType BazookaProyectil::get_id() const {
    return PROYECTIL;
}
