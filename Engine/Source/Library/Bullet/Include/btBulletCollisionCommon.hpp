/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  https://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BULLET_COLLISION_COMMON_H
#define BULLET_COLLISION_COMMON_H

///Common headerfile includes for Bullet Collision Detection

///Bullet's btCollisionWorld and btCollisionObject definitions
#include "BulletCollision/CollisionDispatch/btCollisionWorld.hpp"
#include "BulletCollision/CollisionDispatch/btCollisionObject.hpp"

///Collision Shapes
#include "BulletCollision/CollisionShapes/btBoxShape.hpp"
#include "BulletCollision/CollisionShapes/btSphereShape.hpp"
#include "BulletCollision/CollisionShapes/btCapsuleShape.hpp"
#include "BulletCollision/CollisionShapes/btCylinderShape.hpp"
#include "BulletCollision/CollisionShapes/btConeShape.hpp"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.hpp"
#include "BulletCollision/CollisionShapes/btConvexHullShape.hpp"
#include "BulletCollision/CollisionShapes/btTriangleMesh.hpp"
#include "BulletCollision/CollisionShapes/btConvexTriangleMeshShape.hpp"
#include "BulletCollision/CollisionShapes/btBvhTriangleMeshShape.hpp"
#include "BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.hpp"
#include "BulletCollision/CollisionShapes/btTriangleMeshShape.hpp"
#include "BulletCollision/CollisionShapes/btTriangleIndexVertexArray.hpp"
#include "BulletCollision/CollisionShapes/btCompoundShape.hpp"
#include "BulletCollision/CollisionShapes/btTetrahedronShape.hpp"
#include "BulletCollision/CollisionShapes/btEmptyShape.hpp"
#include "BulletCollision/CollisionShapes/btMultiSphereShape.hpp"
#include "BulletCollision/CollisionShapes/btUniformScalingShape.hpp"

///Narrowphase Collision Detector
#include "BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.hpp"

//#include "BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.hpp"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.hpp"

///Dispatching and generation of collision pairs (broadphase)
#include "BulletCollision/CollisionDispatch/btCollisionDispatcher.hpp"
#include "BulletCollision/BroadphaseCollision/btSimpleBroadphase.hpp"
#include "BulletCollision/BroadphaseCollision/btAxisSweep3.hpp"
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.hpp"

///Math library & Utils
#include "LinearMath/btQuaternion.hpp"
#include "LinearMath/btTransform.hpp"
#include "LinearMath/btDefaultMotionState.hpp"
#include "LinearMath/btQuickprof.hpp"
#include "LinearMath/btIDebugDraw.hpp"
#include "LinearMath/btSerializer.hpp"

#endif  //BULLET_COLLISION_COMMON_H
