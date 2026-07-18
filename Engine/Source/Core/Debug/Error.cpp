#include "pch.hpp"
#include "Error.hpp"

using namespace Minty;

static ErrorCodeEnum s_errorCode = ErrorCodeEnum::None;

Char const *Minty::get_error_message(ErrorCodeEnum const code)
{
    // NOTE: Do not use an array here, to avoid mismatch errors due to new ones being added and the array not being updated.
    // It is an error message, it does not need to be fast.
    switch (code)
    {
    case ErrorCodeEnum::None:
        return "No error.";

    case ErrorCodeEnum::NotImplemented:
        return "Functionality not implemented.";
    case ErrorCodeEnum::OperationFailed:
        return "Operation failed.";
    case ErrorCodeEnum::ConversionFailed:
        return "Conversion failed.";
    case ErrorCodeEnum::NotSupported:
        return "Operation not supported for this platform.";
    case ErrorCodeEnum::PlatformSpecific:
        return "Platform specific error. The corresponding library or platform should provide more details:";
    case ErrorCodeEnum::InvalidUserData:
        return "Invalid user data provided.";
    case ErrorCodeEnum::InfiniteLoop:
        return "Infinite loop detected.";

    case ErrorCodeEnum::Memory:
        return "Memory error.";
    case ErrorCodeEnum::Memory_AllocationFailed:
        return "Memory error. Memory allocation failed. The system may be out of memory.";
    case ErrorCodeEnum::Memory_DeallocationFailed:
        return "Memory error. Memory deallocation failed. Check for double free.";
    case ErrorCodeEnum::Memory_AllocatorNotInitialized:
        return "Memory error. Memory allocator not initialized.";
    case ErrorCodeEnum::Memory_AllocatorAlreadyInitialized:
        return "Memory error. Memory allocator already initialized.";
    case ErrorCodeEnum::Memory_NoSuitableAllocatorFound:
        return "Memory error. No suitable allocator found for requested size and alignment.";
    case ErrorCodeEnum::Memory_AllocatorMismatch:
        return "Memory error. Allocator mismatch for deallocation. You must deallocate memory using the same allocator that allocated it.";
    case ErrorCodeEnum::Memory_WeakLeakDetected:
        return "Memory error. Weak memory leak detected. Some pre-allocated memory was not freed before the allocator was destroyed.";
    case ErrorCodeEnum::Memory_StrongLeakDetected:
        return "Memory error. Strong memory leak detected. Some dynamically allocated memory was not freed.";
    case ErrorCodeEnum::Memory_InvalidPointer:
        return "Memory error. Invalid pointer provided for deallocation.";
    case ErrorCodeEnum::Memory_SizeMismatch:
        return "Memory error. Size mismatch for allocation or deallocation.";
    case ErrorCodeEnum::Memory_UnallowedSize:
        return "Memory error. The requested size is not allowed by the allocator.";

    case ErrorCodeEnum::Argument:
        return "Invalid argument error.";
    case ErrorCodeEnum::Argument_ExpectedNonZero:
        return "Invalid argument error. Expected non-zero value.";
    case ErrorCodeEnum::Argument_ExpectedZero:
        return "Invalid argument error. Expected zero value.";
    case ErrorCodeEnum::Argument_ExpectedNonNull:
        return "Invalid argument error. Expected non-null pointer.";
    case ErrorCodeEnum::Argument_ExpectedNull:
        return "Invalid argument error. Expected null pointer.";
    case ErrorCodeEnum::Argument_ExpectedNonEmpty:
        return "Invalid argument error. Expected non-empty value.";
    case ErrorCodeEnum::Argument_ExpectedEmpty:
        return "Invalid argument error. Expected empty value.";
    case ErrorCodeEnum::Argument_ExpectedNonDefault:
        return "Invalid argument error. Expected non-default (non-zero) value.";
    case ErrorCodeEnum::Argument_ExpectedAboveZero:
        return "Invalid argument error. Expected value greater than zero.";
    case ErrorCodeEnum::Argument_OutOfRange:
        return "Invalid argument error. Value is out of bounds.";
    case ErrorCodeEnum::Argument_ForeignPointer:
        return "Invalid argument error. Pointer does not belong to this object.";
    case ErrorCodeEnum::Argument_AlignmentMismatch:
        return "Invalid argument error. Pointer is not aligned to block size.";
    case ErrorCodeEnum::Argument_IncorrectOrder:
        return "Invalid argument error. Arguments are in the incorrect order.";
    case ErrorCodeEnum::Argument_KeyAlreadyExists:
        return "Invalid argument error. Key already exists in the collection.";
    case ErrorCodeEnum::Argument_KeyNotFound:
        return "Invalid argument error. Key not found in the collection.";
    case ErrorCodeEnum::Argument_InvalidFormat:
        return "Invalid argument error. Invalid format.";
    case ErrorCodeEnum::Argument_InvalidSize:
        return "Invalid argument error. Invalid size. The size is too large.";
    case ErrorCodeEnum::Argument_InvalidCount:
        return "Invalid argument error. Invalid count. The count is too large.";
    case ErrorCodeEnum::Argument_InvalidValue:
        return "Invalid argument error. Invalid value.";
    case ErrorCodeEnum::Argument_InvalidType:
        return "Invalid argument error. Invalid type.";
    case ErrorCodeEnum::Argument_InvalidState:
        return "Invalid argument error. The given argument's state is invalid for the requested operation.";
    case ErrorCodeEnum::Argument_InvalidIndex:
        return "Invalid argument error. Invalid index.";
    case ErrorCodeEnum::Argument_InvalidHandle:
        return "Invalid argument error. Invalid handle.";
    case ErrorCodeEnum::Argument_DuplicateValue:
        return "Invalid argument error. Duplicate value found where unique value was expected.";
    case ErrorCodeEnum::Argument_ExpectedDefined:
        return "Invalid argument error. Expected a defined value.";

    case ErrorCodeEnum::Object:
        return "Object error.";
    case ErrorCodeEnum::Object_InvalidState:
        return "Object error. Invalid state for requested operation.";
    case ErrorCodeEnum::Object_InvalidOperation:
        return "Object error. Invalid operation for current state.";
    case ErrorCodeEnum::Object_AlreadyInitialized:
        return "Object error. Object is already initialized.";
    case ErrorCodeEnum::Object_NotInitialized:
        return "Object error. Object is not initialized.";
    case ErrorCodeEnum::Object_NeverDisposed:
        return "Object error. Object was never disposed before destruction.";
    case ErrorCodeEnum::Object_AlreadyRunning:
        return "Object error. Object is already running.";
    case ErrorCodeEnum::Object_NotRunning:
        return "Object error. Object is not running.";
    case ErrorCodeEnum::Object_EmptyContainer:
        return "Object error. Container is empty.";
    case ErrorCodeEnum::Object_FullContainer:
        return "Object error. Container is full.";
    case ErrorCodeEnum::Object_CreationFailed:
        return "Object error. Creation failed.";
    case ErrorCodeEnum::Object_AlreadyRegistered:
        return "Object error. Object already registered.";
    case ErrorCodeEnum::Object_NotRegistered:
        return "Object error. Object not registered.";
    case ErrorCodeEnum::Object_TypeMismatch:
        return "Object error. Object type mismatch. The object is not of the expected type for this operation.";

    case ErrorCodeEnum::File:
        return "File error.";
    case ErrorCodeEnum::File_NotFound:
        return "File error. Not found.";
    case ErrorCodeEnum::File_NotAFile:
        return "File error. Not a file.";
    case ErrorCodeEnum::File_NotADirectory:
        return "File error. Not a directory.";
    case ErrorCodeEnum::File_AlreadyOpen:
        return "File error. Already open.";
    case ErrorCodeEnum::File_FailedToOpen:
        return "File error. Failed to open.";
    case ErrorCodeEnum::File_NotOpen:
        return "File error. Not open.";
    case ErrorCodeEnum::File_ReadWriteSyncMismatch:
        return "File error. Read/write sync mismatch.";
    case ErrorCodeEnum::File_FlagNotSupported:
        return "File error. Flag not supported.";
    case ErrorCodeEnum::File_PathTooLong:
        return "File error. Path too long.";
    case ErrorCodeEnum::File_EndOfFileReached:
        return "File error. End of file reached.";
    case ErrorCodeEnum::File_ReadFailed:
        return "File error. Read operation failed.";
    case ErrorCodeEnum::File_WriteFailed:
        return "File error. Write operation failed.";
    case ErrorCodeEnum::File_Empty:
        return "File error. File is empty.";

    case ErrorCodeEnum::Singleton:
        return "Singleton error.";
    case ErrorCodeEnum::Singleton_AlreadyExists:
        return "Singleton error. Instance already exists.";
    case ErrorCodeEnum::Singleton_DoesNotExist:
        return "Singleton error. Instance does not exist.";
    case ErrorCodeEnum::Singleton_DifferentObject:
        return "Singleton error. Different instance exists. It may have been corrupted, or another instance was created unexpectedly.";

    case ErrorCodeEnum::Library:
        return "Library error.";
    case ErrorCodeEnum::Library_InitializationFailed:
        return "Library error. Initialization failed.";
    case ErrorCodeEnum::Library_GLFW:
        return "Library error. GLFW error.";
    case ErrorCodeEnum::Library_Vulkan:
        return "Library error. Vulkan error.";
    case ErrorCodeEnum::Library_EnTT:
        return "Library error. EnTT error.";

    case ErrorCodeEnum::Serialization:
        return "Serialization error.";
    case ErrorCodeEnum::Serialization_InvalidFormat:
        return "Serialization error. Invalid format.";
    case ErrorCodeEnum::Serialization_InvalidValue:
        return "Serialization error. Invalid value.";
    case ErrorCodeEnum::Serialization_InvalidData:
        return "Serialization error. Invalid reader or writer user data.";
    case ErrorCodeEnum::Serialization_InvalidIndentation:
        return "Serialization error. Invalid indentation level. Ensure indentation levels are properly managed.";
    case ErrorCodeEnum::Serialization_UnexpectedEndOfData:
        return "Serialization error. Unexpected end of data.";
    case ErrorCodeEnum::Serialization_Failed:
        return "Serialization error. Operation failed.";
    case ErrorCodeEnum::Serialization_Write:
        return "Serialization error. Write operation failed.";
    case ErrorCodeEnum::Serialization_Read:
        return "Serialization error. Read operation failed.";
    case ErrorCodeEnum::Serialization_MissingKey:
        return "Serialization error. Missing key detected. A key was expected but not found in the data.";
    case ErrorCodeEnum::Serialization_InvalidBookmark:
        return "Serialization error. Invalid bookmark handle.";
    case ErrorCodeEnum::Serialization_InconsistentIndentation:
        return "Serialization error. Inconsistent indentation detected. Mixing of tabs and spaces is not allowed.";
    case ErrorCodeEnum::Serialization_UnsupportedType:
        return "Serialization error. Unsupported type encountered during serialization or deserialization. Ensure that the type has the proper serialization or parsing methods defined.";
    case ErrorCodeEnum::Serialization_IgnoredData:
        return "Serialization error. Ignored data detected. Some data in the stream was not read or processed.";
    case ErrorCodeEnum::Serialization_MissingValue:
        return "Serialization error. Missing value detected. A key was found without an associated value, when a value was expected.";

    case ErrorCodeEnum::Entity:
        return "Entity error.";
    case ErrorCodeEnum::Entity_NotValid:
        return "Entity error. Entity is not valid.";
    case ErrorCodeEnum::Entity_InvalidRelationship:
        return "Entity error. Invalid relationship.";
    case ErrorCodeEnum::Entity_CyclicRelationship:
        return "Entity error. Cyclic relationship detected.";
    case ErrorCodeEnum::Entity_MissingComponent:
        return "Entity error. Missing required component.";
    case ErrorCodeEnum::Entity_DuplicateComponent:
        return "Entity error. Duplicate component detected.";

    case ErrorCodeEnum::Component:
        return "Component error.";
    case ErrorCodeEnum::Component_NotRegistered:
        return "Component error. Component not registered.";
    case ErrorCodeEnum::Component_AlreadyRegistered:
        return "Component error. Component already registered.";
    case ErrorCodeEnum::Component_InvalidState:
        return "Component error. Component is in an invalid state for the requested operation.";
    case ErrorCodeEnum::Component_InvalidOperation:
        return "Component error. Invalid operation for the component type (component vs tag).";

    case ErrorCodeEnum::System:
        return "System error.";
    case ErrorCodeEnum::System_NotRegistered:
        return "System error. System not registered.";
    case ErrorCodeEnum::System_AlreadyRegistered:
        return "System error. System already registered.";

    case ErrorCodeEnum::Animation:
        return "Animation error.";
    case ErrorCodeEnum::Animation_NegativeTime:
        return "Animation error. Negative time value provided.";
    case ErrorCodeEnum::Animation_DuplicateTime:
        return "Animation error. Duplicate time value detected in animation steps.";
    case ErrorCodeEnum::Animation_DuplicateAction:
        return "Animation error. Duplicate action detected for the same entity/component in a single step.";
    case ErrorCodeEnum::Animation_IncorrectTimeOrder:
        return "Animation error. Animation steps are not in correct time order.";
    case ErrorCodeEnum::Animation_InvalidActionFormat:
        return "Animation error. Invalid action format.";
    case ErrorCodeEnum::Animation_InvalidActionType:
        return "Animation error. Invalid action type specified.";
    case ErrorCodeEnum::Animation_InvalidActionIndex:
        return "Animation error. Invalid action index referenced.";
    case ErrorCodeEnum::Animation_InvalidEntityIndex:
        return "Animation error. Invalid entity index referenced.";
    case ErrorCodeEnum::Animation_InvalidComponentIndex:
        return "Animation error. Invalid component index referenced.";
    case ErrorCodeEnum::Animation_InvalidVariableIndex:
        return "Animation error. Invalid variable index referenced.";
    case ErrorCodeEnum::Animation_InvalidValueIndex:
        return "Animation error. Invalid value index referenced.";
    case ErrorCodeEnum::Animation_EntityNotFound:
        return "Animation error. Entity not found.";
    case ErrorCodeEnum::Animation_ComponentNotFound:
        return "Animation error. Component not found.";
    case ErrorCodeEnum::Animation_NotEnoughActions:
        return "Animation error. Not enough actions provided for animation.";
    case ErrorCodeEnum::Animation_NotEnoughSteps:
        return "Animation error. Not enough steps provided for animation.";
    case ErrorCodeEnum::Animation_NotEnoughComponents:
        return "Animation error. Not enough components provided for animation.";
    case ErrorCodeEnum::Animation_InvalidVariableMode:
        return "Animation error. Invalid variable mode for animation. Check if the variable is marked as smooth or rigid correctly.";
    case ErrorCodeEnum::Animation_ScopedVariableNotFound:
        return "Animation error. Scoped variable not found in the provided scope. Check that the animator contains the correct scoped variable names.";

    case ErrorCodeEnum::Resource:
        return "Resource error.";
    case ErrorCodeEnum::Resource_InvalidFormat:
        return "Resource error. Invalid format or syntax.";
    case ErrorCodeEnum::Resource_InvalidConfiguration:
        return "Resource error. Invalid configuration.";
    case ErrorCodeEnum::Resource_UnknownType:
        return "Resource error. Unknown asset type.";
    case ErrorCodeEnum::Resource_MissingMeta:
        return "Resource error. Missing meta file.";
    case ErrorCodeEnum::Resource_MissingDependency:
        return "Resource error. Missing dependency asset. Make sure all dependencies are loaded previous to this asset.";
    case ErrorCodeEnum::Resource_InvalidDependencyType:
        return "Resource error. Invalid dependency type. The dependency asset type does not match the expected type.";
    case ErrorCodeEnum::Resource_AlreadyLoaded:
        return "Resource error. Resource is already loaded.";
    case ErrorCodeEnum::Resource_NotLoaded:
        return "Resource error. Resource is not loaded.";
    case ErrorCodeEnum::Resource_Busy:
        return "Resource error. Resource is busy and cannot perform the requested operation.";
    case ErrorCodeEnum::Resource_SavePathsNotEnabled:
        return "Resource error. Save paths are not enabled for this asset type.";
    case ErrorCodeEnum::Resource_LoadFailed:
        return "Resource error. Resource loading failed.";
    case ErrorCodeEnum::Resource_Shader_PushConstantLocation:
        return "Resource error. Shader push constant location not found.";
    case ErrorCodeEnum::Resource_Prefab_OverrideNotFound:
        return "Resource error. Prefab override not found.";
    case ErrorCodeEnum::Resource_Mesh_InvalidStride:
        return "Resource error. Mesh has an invalid vertex stride.";
    case ErrorCodeEnum::Resource_Font_CharNotFound:
        return "Resource error. Font character not found in the font variant.";
    case ErrorCodeEnum::Resource_NotRegistered:
        return "Resource error. Resource not registered in the ResourceManager.";
    case ErrorCodeEnum::Resource_AlreadyRegistered:
        return "Resource error. Resource already registered in the ResourceManager.";

    case ErrorCodeEnum::UUID:
        return "UUID error.";
    case ErrorCodeEnum::UUID_Invalid:
        return "UUID error. Invalid UUID. Expected a non-zero UUID.";

    case ErrorCodeEnum::Render:
        return "Render error.";
    case ErrorCodeEnum::Render_AlreadyRenderingFrame:
        return "Render error. Already rendering a frame.";
        case ErrorCodeEnum::Render_AlreadyRenderingPass:
        return "Render error. Already rendering a pass.";
    case ErrorCodeEnum::Render_NotRenderingFrame:
        return "Render error. Not currently rendering a frame.";
    case ErrorCodeEnum::Render_NotRenderingPass:
        return "Render error. Not currently rendering a pass.";
    case ErrorCodeEnum::Render_NoSurface:
        return "Render error. No rendering surface available.";
    case ErrorCodeEnum::Render_UnsupportedFeature:
        return "Render error. Unsupported feature for current platform, configuration, or hardware.";
    case ErrorCodeEnum::Render_QueryFailed:
        return "Render error. Query operation failed.";
    case ErrorCodeEnum::Render_UnsupportedTransition:
        return "Render error. Unsupported resource transition.";
    case ErrorCodeEnum::Render_ShaderConfiguration:
        return "Render error. Shader configuration error. Missing or invalid shader bindings or inputs.";
    case ErrorCodeEnum::Render_FailedToLoadImage:
        return "Render error. Failed to load image for rendering.";

    case ErrorCodeEnum::Physics:
        return "Physics error.";
    case ErrorCodeEnum::Physics_InSimulation:
        return "Physics error. Entity is in the physics simulation.";
    case ErrorCodeEnum::Physics_NotInSimulation:
        return "Physics error. Entity is not in the physics simulation.";
    case ErrorCodeEnum::Physics_RigidbodyRequiresCollider:
        return "Physics error. Rigidbodies require a collider to be registered first. Register a collider for this entity before registering a rigidbody.";

    case ErrorCodeEnum::Math:
        return "Math error.";
    case ErrorCodeEnum::Math_DivideByZero:
        return "Math error. Division by zero.";
    case ErrorCodeEnum::Math_InvalidToken:
        return "Math error. Invalid token in expression.";
    case ErrorCodeEnum::Math_MismatchedParentheses:
        return "Math error. Mismatched parentheses in expression.";
    case ErrorCodeEnum::Math_EvaluationFailed:
        return "Math error. Expression evaluation failed.";

    case ErrorCodeEnum::Scene:
        return "Scene error.";
    case ErrorCodeEnum::Scene_NoActiveScene:
        return "Scene error. No active scene set in the SceneManager.";
    case ErrorCodeEnum::Scene_TooManyListeners:
        return "Scene error. Too many listeners registered for the scene event.";
    case ErrorCodeEnum::Scene_MissingCamera:
        return "Scene error. Missing camera in the scene.";

    case ErrorCodeEnum::Threading:
        return "Threading error.";
    case ErrorCodeEnum::Threading_HandleAlreadyExists:
        return "Threading error. Thread handle already exists.";
    case ErrorCodeEnum::Threading_CyclicDependency:
        return "Threading error. Cyclic dependency detected between threads.";

    case ErrorCodeEnum::Audio:
        return "Audio error.";
    case ErrorCodeEnum::Audio_FailedToLoadClip:
        return "Audio error. Failed to load audio clip.";

    case ErrorCodeEnum::Window:
        return "Window error.";
    case ErrorCodeEnum::Window_CreationFailed:
        return "Window error. Window creation failed.";

    case ErrorCodeEnum::Layer:
        return "Layer error.";
    case ErrorCodeEnum::Layer_NotFound:
        return "Layer error. Layer not found.";

    case ErrorCodeEnum::CommandLine:
        return "Command line error.";
    case ErrorCodeEnum::CommandLine_NotEnoughArguments:
        return "Command line error. Not enough arguments provided for the specified parameter.";

    case ErrorCodeEnum::OS:
        return "System error.";
    case ErrorCodeEnum::OS_CopyFailed:
        return "System error. File or directory copy operation failed.";
    case ErrorCodeEnum::OS_MoveFailed:
        return "System error. File or directory move operation failed.";
    case ErrorCodeEnum::OS_EnvironmentVariableNotFound:
        return "System error. Environment variable not found.";
        
    case ErrorCodeEnum::Wrap:
        return "Wrap error.";
    case ErrorCodeEnum::Wrap_InvalidFormat:
        return "Wrap error. Invalid wrap format.";
    case ErrorCodeEnum::Wrap_EntryLimitReached:
        return "Wrap error. Entry limit reached. Cannot add more entries to the wrap.";
    case ErrorCodeEnum::Wrap_CompressionFailed:
        return "Wrap error. Compression failed.";
    case ErrorCodeEnum::Wrap_UncompressionFailed:
        return "Wrap error. Uncompression failed.";

    default:
        return "Unknown error.";
    }
}

ErrorCodeEnum Minty::get_error()
{
    return s_errorCode;
}

void Minty::set_error(ErrorCodeEnum const code)
{
    s_errorCode = code;
}