
#ifndef MINTY_H
#define MINTY_H

//		DLL
#include "M_Main.h"

//		Data Types
#include "M_Color.h"
#include "M_Direction.h"
#include "M_Event.h"
#include "M_Mask.h"
#include "M_Object.h"
#include "M_Pair.h"
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
#include "M_Game.h"
#include "M_Input.h"
#include "M_InputMap.h"
#include "M_Scene.h"
#include "M_SceneManager.h"
#include "M_Screen.h"
#include "M_Sprite.h"

//			Components
#include "M_C_Acceleration.h"
#include "M_C_Camera.h"
#include "M_C_Child.h"
#include "M_C_Parent.h"
#include "M_C_Position.h"
#include "M_C_Scale.h"
#include "M_C_Size.h"
#include "M_C_SpriteRenderer.h"
#include "M_C_Velocity.h"

//			Tags
#include "M_T_Destroy.h"
#include "M_T_Gravity.h"
#include "M_T_NoDestroy.h"

//		Libraries
#include <SDL.h>
#include "entt.hpp"
#include "FastNoiseLite.h"

#endif
