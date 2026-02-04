#include "Error.h"

using namespace Minty;

static ErrorCode s_errorCode = ErrorCode::None;

// TODO: change this to use an array of messages instead of a switch statement
Char const *Minty::get_error_message(ErrorCode const code)
{
    switch (code)
    {
    case ErrorCode::None:
        return "No error.";

    case ErrorCode::NotImplemented:
        return "Functionality not implemented.";
    case ErrorCode::OperationFailed:
        return "Operation failed.";
    case ErrorCode::ConversionFailed:
        return "Conversion failed.";
    case ErrorCode::NotSupported:
        return "Operation not supported for this platform.";
    case ErrorCode::PlatformSpecific:
        return "Platform specific error. The corresponding library or platform should provide more details:";
    case ErrorCode::InvalidUserData:
        return "Invalid user data provided.";
    case ErrorCode::InfiniteLoop:
        return "Infinite loop detected.";

    case ErrorCode::Memory:
        return "Memory error.";
    case ErrorCode::Memory_AllocationFailed:
        return "Memory error. Memory allocation failed. The system may be out of memory.";
    case ErrorCode::Memory_DeallocationFailed:
        return "Memory error. Memory deallocation failed. Check for double free.";
    case ErrorCode::Memory_AllocatorNotInitialized:
        return "Memory error. Memory allocator not initialized.";
    case ErrorCode::Memory_AllocatorAlreadyInitialized:
        return "Memory error. Memory allocator already initialized.";
    case ErrorCode::Memory_NoSuitableAllocatorFound:
        return "Memory error. No suitable allocator found for requested size and alignment.";
    case ErrorCode::Memory_AllocatorMismatch:
        return "Memory error. Allocator mismatch for deallocation. You must deallocate memory using the same allocator that allocated it.";
    case ErrorCode::Memory_WeakLeakDetected:
        return "Memory error. Weak memory leak detected. Some pre-allocated memory was not freed before the allocator was destroyed.";
    case ErrorCode::Memory_StrongLeakDetected:
        return "Memory error. Strong memory leak detected. Some dynamically allocated memory was not freed.";
    case ErrorCode::Memory_InvalidPointer:
        return "Memory error. Invalid pointer provided for deallocation.";
    case ErrorCode::Memory_SizeMismatch:
        return "Memory error. Size mismatch for allocation or deallocation.";
    case ErrorCode::Memory_UnallowedSize:
        return "Memory error. The requested size is not allowed by the allocator.";

    case ErrorCode::Argument:
        return "Invalid argument error.";
    case ErrorCode::Argument_ExpectedNonZero:
        return "Invalid argument error. Expected non-zero value.";
    case ErrorCode::Argument_ExpectedNonNull:
        return "Invalid argument error. Expected non-null pointer.";
    case ErrorCode::Argument_ExpectedNull:
        return "Invalid argument error. Expected null pointer.";
    case ErrorCode::Argument_ExpectedNonEmpty:
        return "Invalid argument error. Expected non-empty value.";
    case ErrorCode::Argument_ExpectedEmpty:
        return "Invalid argument error. Expected empty value.";
    case ErrorCode::Argument_ExpectedNonDefault:
        return "Invalid argument error. Expected non-default (non-zero) value.";
    case ErrorCode::Argument_ExpectedAboveZero:
        return "Invalid argument error. Expected value greater than zero.";
    case ErrorCode::Argument_OutOfRange:
        return "Invalid argument error. Value is out of bounds.";
    case ErrorCode::Argument_ForeignPointer:
        return "Invalid argument error. Pointer does not belong to this object.";
    case ErrorCode::Argument_AlignmentMismatch:
        return "Invalid argument error. Pointer is not aligned to block size.";
    case ErrorCode::Argument_IncorrectOrder:
        return "Invalid argument error. Arguments are in the incorrect order.";
    case ErrorCode::Argument_KeyAlreadyExists:
        return "Invalid argument error. Key already exists in the collection.";
    case ErrorCode::Argument_KeyNotFound:
        return "Invalid argument error. Key not found in the collection.";
    case ErrorCode::Argument_InvalidFormat:
        return "Invalid argument error. Invalid format.";
    case ErrorCode::Argument_InvalidSize:
        return "Invalid argument error. Invalid size. The size is too large.";
    case ErrorCode::Argument_InvalidCount:
        return "Invalid argument error. Invalid count. The count is too large.";
    case ErrorCode::Argument_InvalidValue:
        return "Invalid argument error. Invalid value.";
    case ErrorCode::Argument_InvalidType:
        return "Invalid argument error. Invalid type.";
    case ErrorCode::Argument_InvalidState:
        return "Invalid argument error. The given argument's state is invalid for the requested operation.";
    case ErrorCode::Argument_DuplicateValue:
        return "Invalid argument error. Duplicate value found where unique value was expected.";

    case ErrorCode::Object:
        return "Object error.";
    case ErrorCode::Object_InvalidState:
        return "Object error. Invalid state for requested operation.";
    case ErrorCode::Object_InvalidOperation:
        return "Object error. Invalid operation for current state.";
    case ErrorCode::Object_AlreadyInitialized:
        return "Object error. Object is already initialized.";
    case ErrorCode::Object_NotInitialized:
        return "Object error. Object is not initialized.";
    case ErrorCode::Object_NeverDisposed:
        return "Object error. Object was never disposed before destruction.";
    case ErrorCode::Object_AlreadyRunning:
        return "Object error. Object is already running.";
    case ErrorCode::Object_NotRunning:
        return "Object error. Object is not running.";
    case ErrorCode::Object_EmptyContainer:
        return "Object error. Container is empty.";
    case ErrorCode::Object_FullContainer:
        return "Object error. Container is full.";
    case ErrorCode::Object_CreationFailed:
        return "Object error. Creation failed.";

    case ErrorCode::File:
        return "File error.";
    case ErrorCode::File_NotFound:
        return "File error. Not found.";
    case ErrorCode::File_NotAFile:
        return "File error. Not a file.";
    case ErrorCode::File_NotADirectory:
        return "File error. Not a directory.";
    case ErrorCode::File_AlreadyOpen:
        return "File error. Already open.";
    case ErrorCode::File_FailedToOpen:
        return "File error. Failed to open.";
    case ErrorCode::File_NotOpen:
        return "File error. Not open.";
    case ErrorCode::File_ReadWriteSyncMismatch:
        return "File error. Read/write sync mismatch.";
    case ErrorCode::File_FlagNotSupported:
        return "File error. Flag not supported.";
    case ErrorCode::File_PathTooLong:
        return "File error. Path too long.";
    case ErrorCode::File_EndOfFileReached:
        return "File error. End of file reached.";
    case ErrorCode::File_ReadFailed:
        return "File error. Read operation failed.";
    case ErrorCode::File_WriteFailed:
        return "File error. Write operation failed.";
    case ErrorCode::File_Empty:
        return "File error. File is empty.";

    case ErrorCode::Singleton:
        return "Singleton error.";
    case ErrorCode::Singleton_AlreadyExists:
        return "Singleton error. Instance already exists.";
    case ErrorCode::Singleton_DoesNotExist:
        return "Singleton error. Instance does not exist.";
    case ErrorCode::Singleton_DifferentObject:
        return "Singleton error. Different instance exists.";

    case ErrorCode::Library:
        return "Library error.";
    case ErrorCode::Library_InitializationFailed:
        return "Library error. Initialization failed.";
    case ErrorCode::Library_GLFW:
        return "Library error. GLFW error.";
    case ErrorCode::Library_Vulkan:
        return "Library error. Vulkan error.";
    case ErrorCode::Library_EnTT:
        return "Library error. EnTT error.";

    case ErrorCode::Serialization:
        return "Serialization error.";
    case ErrorCode::Serialization_InvalidFormat:
        return "Serialization error. Invalid format.";
    case ErrorCode::Serialization_InvalidValue:
        return "Serialization error. Invalid value.";
    case ErrorCode::Serialization_InvalidData:
        return "Serialization error. Invalid reader or writer user data.";
    case ErrorCode::Serialization_InvalidIndentation:
        return "Serialization error. Invalid indentation level. Ensure indentation levels are properly managed.";
    case ErrorCode::Serialization_UnexpectedEndOfData:
        return "Serialization error. Unexpected end of data.";
    case ErrorCode::Serialization_Failed:
        return "Serialization error. Operation failed.";
    case ErrorCode::Serialization_Write:
        return "Serialization error. Write operation failed.";
    case ErrorCode::Serialization_Read:
        return "Serialization error. Read operation failed.";
    case ErrorCode::Serialization_MissingKey:
        return "Serialization error. Missing key detected. A key was expected but not found in the data.";
    case ErrorCode::Serialization_InvalidBookmark:
        return "Serialization error. Invalid bookmark handle.";
    case ErrorCode::Serialization_InconsistentIndentation:
        return "Serialization error. Inconsistent indentation detected. Mixing of tabs and spaces is not allowed.";
    case ErrorCode::Serialization_UnsupportedType:
        return "Serialization error. Unsupported type encountered during serialization or deserialization. Ensure that the type has the proper serialization or parsing methods defined.";
    case ErrorCode::Serialization_IgnoredData:
        return "Serialization error. Ignored data detected. Some data in the stream was not read or processed.";
    case ErrorCode::Serialization_MissingValue:
        return "Serialization error. Missing value detected. A key was found without an associated value, when a value was expected.";

    case ErrorCode::Entity:
        return "Entity error.";
    case ErrorCode::Entity_NotValid:
        return "Entity error. Entity is not valid.";
    case ErrorCode::Entity_InvalidRelationship:
        return "Entity error. Invalid relationship.";
    case ErrorCode::Entity_CyclicRelationship:
        return "Entity error. Cyclic relationship detected.";
    case ErrorCode::Entity_MissingComponent:
        return "Entity error. Missing required component.";
    case ErrorCode::Entity_DuplicateComponent:
        return "Entity error. Duplicate component detected.";

    case ErrorCode::Component:
        return "Component error.";
    case ErrorCode::Component_NotRegistered:
        return "Component error. Component not registered.";
    case ErrorCode::Component_AlreadyRegistered:
        return "Component error. Component already registered.";
    case ErrorCode::Component_InvalidState:
        return "Component error. Component is in an invalid state for the requested operation.";
    case ErrorCode::Component_InvalidOperation:
        return "Component error. Invalid operation for the component type (component vs tag).";

    case ErrorCode::System:
        return "System error.";
    case ErrorCode::System_NotRegistered:
        return "System error. System not registered.";
    case ErrorCode::System_AlreadyRegistered:
        return "System error. System already registered.";

    case ErrorCode::Animation:
        return "Animation error.";
    case ErrorCode::Animation_NegativeTime:
        return "Animation error. Negative time value provided.";
    case ErrorCode::Animation_DuplicateTime:
        return "Animation error. Duplicate time value detected in animation steps.";
    case ErrorCode::Animation_DuplicateAction:
        return "Animation error. Duplicate action detected for the same entity/component in a single step.";
    case ErrorCode::Animation_IncorrectTimeOrder:
        return "Animation error. Animation steps are not in correct time order.";
    case ErrorCode::Animation_InvalidActionFormat:
        return "Animation error. Invalid action format.";
    case ErrorCode::Animation_InvalidActionType:
        return "Animation error. Invalid action type specified.";
    case ErrorCode::Animation_InvalidActionIndex:
        return "Animation error. Invalid action index referenced.";
    case ErrorCode::Animation_InvalidEntityIndex:
        return "Animation error. Invalid entity index referenced.";
    case ErrorCode::Animation_InvalidComponentIndex:
        return "Animation error. Invalid component index referenced.";
    case ErrorCode::Animation_InvalidVariableIndex:
        return "Animation error. Invalid variable index referenced.";
    case ErrorCode::Animation_InvalidValueIndex:
        return "Animation error. Invalid value index referenced.";
    case ErrorCode::Animation_EntityNotFound:
        return "Animation error. Entity not found.";
    case ErrorCode::Animation_ComponentNotFound:
        return "Animation error. Component not found.";
    case ErrorCode::Animation_NotEnoughActions:
        return "Animation error. Not enough actions provided for animation.";
    case ErrorCode::Animation_NotEnoughSteps:
        return "Animation error. Not enough steps provided for animation.";
    case ErrorCode::Animation_NotEnoughComponents:
        return "Animation error. Not enough components provided for animation.";
    case ErrorCode::Animation_InvalidVariableMode:
        return "Animation error. Invalid variable mode for animation. Check if the variable is marked as smooth or rigid correctly.";
    case ErrorCode::Animation_ScopedVariableNotFound:
        return "Animation error. Scoped variable not found in the provided scope. Check that the animator contains the correct scoped variable names.";

    case ErrorCode::Asset:
        return "Asset error.";
    case ErrorCode::Asset_InvalidFormat:
        return "Asset error. Invalid format or syntax.";
    case ErrorCode::Asset_InvalidConfiguration:
        return "Asset error. Invalid configuration.";
    case ErrorCode::Asset_UnknownType:
        return "Asset error. Unknown asset type.";
    case ErrorCode::Asset_MissingMeta:
        return "Asset error. Missing meta file.";
    case ErrorCode::Asset_MissingDependency:
        return "Asset error. Missing dependency asset. Make sure all dependencies are loaded previous to this asset.";
    case ErrorCode::Asset_InvalidDependencyType:
        return "Asset error. Invalid dependency type. The dependency asset type does not match the expected type.";
    case ErrorCode::Asset_AlreadyLoaded:
        return "Asset error. Asset is already loaded.";
    case ErrorCode::Asset_NotLoaded:
        return "Asset error. Asset is not loaded.";
    case ErrorCode::Asset_Busy:
        return "Asset error. Asset is busy and cannot perform the requested operation.";
    case ErrorCode::Asset_SavePathsNotEnabled:
        return "Asset error. Save paths are not enabled for this asset type.";
    case ErrorCode::Asset_LoadFailed:
        return "Asset error. Asset loading failed.";
    case ErrorCode::Asset_Shader_PushConstantLocation:
        return "Asset error. Shader push constant location not found.";
    case ErrorCode::Asset_Prefab_OverrideNotFound:
        return "Asset error. Prefab override not found.";
    case ErrorCode::Asset_Mesh_InvalidStride:
        return "Asset error. Mesh has an invalid vertex stride.";
    case ErrorCode::Asset_Font_CharNotFound:
        return "Asset error. Font character not found in the font variant.";

    case ErrorCode::UUID:
        return "UUID error.";
    case ErrorCode::UUID_Invalid:
        return "UUID error. Invalid UUID. Expected a non-zero UUID.";

    case ErrorCode::Render:
        return "Render error.";
    case ErrorCode::Render_AlreadyRenderingFrame:
        return "Render error. Already rendering a frame.";
        case ErrorCode::Render_AlreadyRenderingPass:
        return "Render error. Already rendering a pass.";
    case ErrorCode::Render_NotRenderingFrame:
        return "Render error. Not currently rendering a frame.";
    case ErrorCode::Render_NotRenderingPass:
        return "Render error. Not currently rendering a pass.";
    case ErrorCode::Render_NoSurface:
        return "Render error. No rendering surface available.";
    case ErrorCode::Render_UnsupportedFeature:
        return "Render error. Unsupported feature for current platform, configuration, or hardware.";
    case ErrorCode::Render_QueryFailed:
        return "Render error. Query operation failed.";
    case ErrorCode::Render_UnsupportedTransition:
        return "Render error. Unsupported resource transition.";
    case ErrorCode::Render_ShaderConfiguration:
        return "Render error. Shader configuration error. Missing or invalid shader bindings or inputs.";
    case ErrorCode::Render_FailedToLoadImage:
        return "Render error. Failed to load image for rendering.";

    case ErrorCode::Physics:
        return "Physics error.";

    case ErrorCode::Math:
        return "Math error.";
    case ErrorCode::Math_DivideByZero:
        return "Math error. Division by zero.";
    case ErrorCode::Math_InvalidToken:
        return "Math error. Invalid token in expression.";
    case ErrorCode::Math_MismatchedParentheses:
        return "Math error. Mismatched parentheses in expression.";
    case ErrorCode::Math_EvaluationFailed:
        return "Math error. Expression evaluation failed.";

    case ErrorCode::Scene:
        return "Scene error.";
    case ErrorCode::Scene_NoActiveScene:
        return "Scene error. No active scene set in the SceneManager.";
    case ErrorCode::Scene_TooManyListeners:
        return "Scene error. Too many listeners registered for the scene event.";
    case ErrorCode::Scene_MissingCamera:
        return "Scene error. Missing camera in the scene.";

    case ErrorCode::Threading:
        return "Threading error.";
    case ErrorCode::Threading_HandleAlreadyExists:
        return "Threading error. Thread handle already exists.";
    case ErrorCode::Threading_CyclicDependency:
        return "Threading error. Cyclic dependency detected between threads.";

    case ErrorCode::Audio:
        return "Audio error.";
    case ErrorCode::Audio_FailedToLoadClip:
        return "Audio error. Failed to load audio clip.";

    case ErrorCode::Window:
        return "Window error.";
    case ErrorCode::Window_CreationFailed:
        return "Window error. Window creation failed.";

    case ErrorCode::Layer:
        return "Layer error.";
    case ErrorCode::Layer_NotFound:
        return "Layer error. Layer not found.";

    case ErrorCode::CommandLine:
        return "Command line error.";
    case ErrorCode::CommandLine_NotEnoughArguments:
        return "Command line error. Not enough arguments provided for the specified parameter.";

    case ErrorCode::OS:
        return "System error.";
    case ErrorCode::OS_CopyFailed:
        return "System error. File or directory copy operation failed.";
    case ErrorCode::OS_MoveFailed:
        return "System error. File or directory move operation failed.";
    case ErrorCode::OS_EnvironmentVariableNotFound:
        return "System error. Environment variable not found.";
        
    case ErrorCode::Wrap:
        return "Wrap error.";
    case ErrorCode::Wrap_InvalidFormat:
        return "Wrap error. Invalid wrap format.";
    case ErrorCode::Wrap_EntryLimitReached:
        return "Wrap error. Entry limit reached. Cannot add more entries to the wrap.";
    case ErrorCode::Wrap_CompressionFailed:
        return "Wrap error. Compression failed.";
    case ErrorCode::Wrap_UncompressionFailed:
        return "Wrap error. Uncompression failed.";

    default:
        return "Unknown error.";
    }
}

ErrorCode Minty::get_error()
{
    return s_errorCode;
}

void Minty::set_error(ErrorCode const code)
{
    s_errorCode = code;
}