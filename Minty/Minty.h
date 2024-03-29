
#ifndef MINTY_H
#define MINTY_H

//		DLL
#include "M_Main.h"

//		Abstract
#include "M_Saveable.h"

//		Data Structures
#include "M_PriorityQueue.h"

//		Data Types
#include "M_Animation.h"
#include "M_Atlas.h"
#include "M_Audio.h"
#include "M_Audio_Music.h"
#include "M_Audio_Sound.h"
#include "M_Brush.h"
#include "M_Brush_Solid.h"
#include "M_Brush_Sprite.h"
#include "M_Canvas.h"
#include "M_Collision.h"
#include "M_Color.h"
#include "M_Direction.h"
#include "M_Event.h"
#include "M_Font.h"
#include "M_Grid.h"
#include "M_Mask.h"
#include "M_MouseClickEvent.h"
#include "M_MouseMoveEvent.h"
#include "M_Object.h"
#include "M_Pair.h"
#include "M_Palette.h"
#include "M_Point.h"
#include "M_PointF.h"
#include "M_ProceduralSprite.h"
#include "M_Rect.h"
#include "M_RectF.h"
#include "M_Sprite.h"
#include "M_Stopwatch.h"
#include "M_Text.h"
#include "M_Time.h"

//		Helpers
#include "M_Debug.h"
#include "M_Direction.h"
#include "M_File.h"
#include "M_Line.h"
#include "M_Math.h"
#include "M_Packing.h"
#include "M_Parse.h"
#include "M_Path.h"
#include "M_Random.h"
#include "M_Resources.h"
#include "M_SaveLoad.h"
#include "M_Serialization.h"
#include "M_String.h"
#include "M_Templates.h"

//		Other
#include "M_Types.h"

//		Engine
#include "M_Coroutine.h"
#include "M_Engine.h"
#include "M_EngineConfig.h"
#include "M_Game.h"
#include "M_Input.h"
#include "M_InputMap.h"
#include "M_Renderer.h";
#include "M_Scene.h"
#include "M_SceneManager.h"
#include "M_Screen.h"
#include "M_System.h"

//			Components
#include "M_C_Acceleration.h"
#include "M_C_Animator.h"
#include "M_C_Camera.h"
#include "M_C_Center.h"
#include "M_C_Clickable.h"
#include "M_C_Collider.h"
#include "M_C_DestroyTimer.h"
#include "M_C_Follow.h"
#include "M_C_MouseClick.h"
#include "M_C_MouseDown.h"
#include "M_C_MouseEnter.h"
#include "M_C_MouseExit.h"
#include "M_C_MouseHover.h"
#include "M_C_MouseMove.h"
#include "M_C_MouseUp.h"
#include "M_C_Name.h"
#include "M_C_Position.h"
#include "M_C_Renderable.h"
#include "M_C_Scale.h"
#include "M_C_Selectable.h"
#include "M_C_Size.h"
#include "M_C_SpriteRenderer.h"
#include "M_C_Target.h"
#include "M_C_TextRenderer.h"
#include "M_C_UI.h"
#include "M_C_Velocity.h"
#include "M_C_Gravity.h"

//			Systems
#include "M_S_AnimationSystem.h"
#include "M_S_AudioSystem.h"
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
#include <SDL_ttf.h>
#include "entt.hpp"
#include "FastNoiseLite.h"

#endif
