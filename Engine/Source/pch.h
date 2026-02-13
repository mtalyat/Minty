#ifndef MINTY_PCH_H
#define MINTY_PCH_H

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "Minty/Core/Macro.h"

#include "Minty/Library/GLFW.h"
#ifndef MINTY_BULLET
#include "Minty/Library/Bullet.h"
#endif // MINTY_BULLET
#include "Minty/Library/EnTT.h"
#include "Minty/Library/GLM.h"
#ifdef MINTY_SOLOUD
#include "Minty/Library/SoLoud.h"
#endif // MINTY_SOLOUD
#ifdef MINTY_TRACE
#include "Minty/Library/Tracy.h"
#endif // MINTY_TRACE
#ifdef MINTY_VULKAN
#include "Minty/Library/Vulkan.h"
#endif // MINTY_VULKAN

#include "Minty/Core/Enum.h"
#include "Minty/Core/Format.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Array.h"
#include "Minty/Data/BufferContainer.h"
#include "Minty/Data/Cargo.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/ConstantContainer.h"
#include "Minty/Data/Container.h"
#include "Minty/Data/Dictionary.h"
#include "Minty/Data/DynamicContainer.h"
#include "Minty/Data/List.h"
#include "Minty/Data/ListContainer.h"
#include "Minty/Data/Lookup.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/MemoryContainer.h"
#include "Minty/Data/Object.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Queue.h"
#include "Minty/Data/Rect.h"
#include "Minty/Data/Scope.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Stack.h"
#include "Minty/Data/StaticContainer.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Transform.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/UITransform.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Variable.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Debug/Error.h"
#include "Minty/Log/Logger.h"
#include "Minty/Log/LoggerInfo.h"
#include "Minty/Log/LogLevel.h"
#include "Minty/Memory/Allocator.h"
#include "Minty/Memory/DebugAllocator.h"
#include "Minty/Memory/FrameAllocator.h"
#include "Minty/Memory/HeapAllocator.h"
#include "Minty/Memory/PersistentAllocator.h"
#include "Minty/Memory/MemoryManager.h"
#include "Minty/Memory/MemoryManagerInfo.h"
#include "Minty/Memory/MemoryPool.h"
#include "Minty/Memory/MemoryPoolInfo.h"
#include "Minty/Memory/MemoryStack.h"
#include "Minty/Memory/MemoryStackInfo.h"
#include "Minty/Memory/PersistentAllocator.h"
#include "Minty/Serialization/Node.h"
#include "Minty/Serialization/Parser.h"
#include "Minty/Serialization/ParsedTypes.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/SerializedTypes.h"
#include "Minty/Serialization/Serializer.h"
#include "Minty/Serialization/TextReader.h"
#include "Minty/Serialization/TextWriter.h"
#include "Minty/Serialization/Writer.h"

#endif //MINTY_PCH_H
