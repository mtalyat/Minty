
#ifndef MINTY_H
#define MINTY_H

//		DLL
#include "M_Main.h"

//		Data Types
#include "M_Animation.h"
#include "M_Atlas.h"
#include "M_Click.h"
#include "M_Collision.h"
#include "M_Color.h"
#include "M_Direction.h"
#include "M_Event.h"
#include "M_Grid.h"
#include "M_Hitbox.h"
#include "M_Mask.h"
#include "M_Object.h"
#include "M_Pair.h"
#include "M_Palette.h"
#include "M_Point.h"
#include "M_PointF.h"
#include "M_Rect.h"
#include "M_RectF.h"
#include "M_Stopwatch.h"
#include "M_Time.h"

//		Data Structures
#include "M_PriorityQueue.h"

//		Helpers
#include "M_Debug.h"
#include "M_File.h"
#include "M_Line.h"
#include "M_Math.h"
#include "M_Packing.h"
#include "M_Parse.h"
#include "M_Path.h"
#include "M_Random.h"
#include "M_Resources.h"
#include "M_Text.h"

//		Engine
#include "M_Coroutine.h"
#include "M_Engine.h"
#include "M_EngineConfig.h"
#include "M_Game.h"
#include "M_Input.h"
#include "M_InputMap.h"
#include "M_Scene.h"
#include "M_SceneManager.h"
#include "M_Screen.h"
#include "M_Sprite.h"
#include "M_System.h"

//			Components
#include "M_C_Acceleration.h"
#include "M_C_Animator.h"
#include "M_C_Camera.h"
#include "M_C_Center.h"
#include "M_C_Clickable.h"
#include "M_C_Collider.h"
#include "M_C_DestroyTimer.h"
#include "M_C_MouseClick.h"
#include "M_C_MouseDown.h"
#include "M_C_MouseUp.h"
#include "M_C_Name.h"
#include "M_C_Position.h"
#include "M_C_Renderable.h"
#include "M_C_Renderer.h"
#include "M_C_Scale.h"
#include "M_C_Size.h"
#include "M_C_Target.h"
#include "M_C_UI.h"
#include "M_C_Velocity.h"
#include "M_C_Gravity.h"

//			Systems
#include "M_S_AnimationSystem.h"
#include "M_S_CollisionSystem.h"
#include "M_S_InputSystem.h"
#include "M_S_PhysicsSystem.h"
#include "M_S_RenderSystem.h"
#include "M_S_TargetSystem.h"
#include "M_S_UserInterfaceSystem.h"

//			Tags
#include "M_T_Destroy.h"
#include "M_T_NoDestroy.h"

//		Libraries
#include <SDL.h>
#include "entt.hpp"
#include "FastNoiseLite.h"

#endif
