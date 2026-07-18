#pragma once

/**
 * @file Error.h
 * @brief Header file for error handling utilities.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @brief Enumeration of error codes used throughout the engine.
     */
    enum class ErrorCodeEnum : UInt
    {
        None = 0,
        NotImplemented,
        OperationFailed,
        ConversionFailed,
        NotSupported,
        PlatformSpecific,
        InvalidUserData,
        InfiniteLoop,

        Memory = 100,
        Memory_AllocationFailed,
        Memory_DeallocationFailed,
        Memory_AllocatorNotInitialized,
        Memory_AllocatorAlreadyInitialized,
        Memory_NoSuitableAllocatorFound,
        Memory_AllocatorMismatch,
        Memory_WeakLeakDetected,
        Memory_StrongLeakDetected,
        Memory_InvalidPointer,
        Memory_SizeMismatch,
        Memory_UnallowedSize,
        
        Argument = 200,
        Argument_ExpectedNonZero,
        Argument_ExpectedZero,
        Argument_ExpectedNonNull,
        Argument_ExpectedNull,
        Argument_ExpectedNonEmpty,
        Argument_ExpectedEmpty,
        Argument_ExpectedNonDefault,
        Argument_ExpectedAboveZero,
        Argument_ExpectedDefined,
        Argument_OutOfRange,
        Argument_ForeignPointer,
        Argument_AlignmentMismatch,
        Argument_IncorrectOrder,
        Argument_KeyAlreadyExists,
        Argument_KeyNotFound,
        Argument_InvalidFormat,
        Argument_InvalidSize,
        Argument_InvalidCount,
        Argument_InvalidValue,
        Argument_InvalidType,
        Argument_InvalidState,
        Argument_InvalidIndex,
        Argument_InvalidHandle,
        Argument_DuplicateValue,
        
        Object = 300,
        Object_InvalidState,
        Object_InvalidOperation,
        Object_AlreadyInitialized,
        Object_NotInitialized,
        Object_NeverDisposed,
        Object_AlreadyRunning,
        Object_NotRunning,
        Object_EmptyContainer,
        Object_FullContainer,
        Object_CreationFailed,
        Object_AlreadyRegistered,
        Object_NotRegistered,
        Object_TypeMismatch,

        File = 400,
        File_NotFound,
        File_NotAFile,
        File_NotADirectory,
        File_AlreadyOpen,
        File_FailedToOpen,
        File_NotOpen,
        File_ReadWriteSyncMismatch,
        File_FlagNotSupported,
        File_PathTooLong,
        File_EndOfFileReached,
        File_ReadFailed,
        File_WriteFailed,
        File_Empty,

        Singleton = 500,
        Singleton_AlreadyExists,
        Singleton_DoesNotExist,
        Singleton_DifferentObject,

        Library = 600,
        Library_InitializationFailed,
        Library_GLFW,
        Library_Vulkan,
        Library_EnTT,

        Serialization = 700,
        Serialization_InvalidFormat,
        Serialization_InvalidKey,
        Serialization_InvalidValue,
        Serialization_InvalidData,
        Serialization_InvalidIndentation,
        Serialization_UnexpectedEndOfData,
        Serialization_Failed,
        Serialization_Write,
        Serialization_Read,
        Serialization_MissingKey,
        Serialization_InvalidBookmark,
        Serialization_InconsistentIndentation,
        Serialization_UnsupportedType,
        Serialization_IgnoredData,
        Serialization_MissingValue,

        Entity = 800,
        Entity_NotValid,
        Entity_InvalidRelationship,
        Entity_CyclicRelationship,
        Entity_MissingComponent,
        Entity_DuplicateComponent,

        Component = 900,
        Component_NotRegistered,
        Component_AlreadyRegistered,
        Component_InvalidState,
        Component_InvalidOperation,

        System = 1000,
        System_NotRegistered,
        System_AlreadyRegistered,

        Animation = 1100,
        Animation_NegativeTime,
        Animation_DuplicateTime,
        Animation_DuplicateAction,
        Animation_IncorrectTimeOrder,
        Animation_InvalidActionFormat,
        Animation_InvalidActionType,
        Animation_InvalidActionIndex,
        Animation_InvalidEntityIndex,
        Animation_InvalidComponentIndex,
        Animation_InvalidVariableIndex,
        Animation_InvalidValueIndex,
        Animation_EntityNotFound,
        Animation_ComponentNotFound,
        Animation_NotEnoughActions,
        Animation_NotEnoughSteps,
        Animation_NotEnoughComponents,
        Animation_InvalidVariableMode,
        Animation_ScopedVariableNotFound,

        Resource = 1200,
        Resource_InvalidFormat,
        Resource_InvalidConfiguration,
        Resource_UnknownType,
        Resource_MissingMeta,
        Resource_MissingDependency,
        Resource_InvalidDependencyType,
        Resource_AlreadyLoaded,
        Resource_NotLoaded,
        Resource_Busy,
        Resource_SavePathsNotEnabled,
        Resource_LoadFailed,
        Resource_Shader_PushConstantLocation,
        Resource_Prefab_OverrideNotFound,
        Resource_Mesh_InvalidStride,
        Resource_Font_CharNotFound,
        Resource_NotRegistered,
        Resource_AlreadyRegistered,

        UUID = 1300,
        UUID_Invalid,

        Render = 1400,
        Render_AlreadyRenderingFrame,
        Render_AlreadyRenderingPass,
        Render_NotRenderingFrame,
        Render_NotRenderingPass,
        Render_NoSurface,
        Render_UnsupportedFeature,
        Render_QueryFailed,
        Render_UnsupportedTransition,
        Render_ShaderConfiguration,
        Render_FailedToLoadImage,
        Render_FailedToRender,
        Render_InvalidBind,

        Physics = 1500,
        Physics_InSimulation,
        Physics_NotInSimulation,
        Physics_RigidbodyRequiresCollider,

        Math = 1600,
        Math_DivideByZero,
        Math_InvalidToken,
        Math_MismatchedParentheses,
        Math_EvaluationFailed,

        Scene = 1700,
        Scene_NoActiveScene,
        Scene_TooManyListeners,
        Scene_MissingCamera,

        Threading = 1800,
        Threading_HandleAlreadyExists,
        Threading_CyclicDependency,

        Audio = 1900,
        Audio_FailedToLoadClip,

        Window = 2000,
        Window_CreationFailed,

        Layer = 2100,
        Layer_NotFound,
        Layer_AlreadyExists,
        Layer_Protected,
        Layer_MaxLayersReached,

        CommandLine = 2200,
        CommandLine_NotEnoughArguments,

        OS = 2300,
        OS_CopyFailed,
        OS_MoveFailed,
        OS_EnvironmentVariableNotFound,

        Wrap = 2400,
        Wrap_InvalidFormat,
        Wrap_EntryLimitReached,
        Wrap_CompressionFailed,
        Wrap_UncompressionFailed,

        Application = 2500,
        Application_WindowNotInitialized,
        Application_MemoryManagerNotInitialized,
        Application_JobManagerNotInitialized,
        Application_AudioManagerNotInitialized,
        Application_LayerManagerNotInitialized,
        Application_PhysicsManagerNotInitialized,
        Application_ResourceManagerNotInitialized,
        Application_InputManagerNotInitialized,
        Application_RenderManagerNotInitialized,
        Application_SceneManagerNotInitialized,
        Application_TimeControllerNotInitialized,

        Unknown = ~0U
    };

    /**
     * @brief Get the error message corresponding to the given error code.
     * @param code The error code.
     */
    Char const* get_error_message(ErrorCodeEnum const code);

    /**
     * @brief Get the current error code.
     */
    ErrorCodeEnum get_error();

    /**
     * @brief Set the current error code.
     * @param code The error code to set.
     */
    void set_error(ErrorCodeEnum const code);
}