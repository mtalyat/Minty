#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"

namespace Minty
{
#pragma region Audio

	constexpr Float DEFAULT_AUDIO_ATTENUATION_ROLL_OFF = 1.0f;
	constexpr Float DEFAULT_AUDIO_MAX_DISTANCE = 100.0f;
	constexpr Float DEFAULT_AUDIO_MIN_DISTANCE = 1.0f;
	constexpr Float DEFAULT_AUDIO_VOLUME = 1.0f;

#pragma endregion

#pragma region Assets

	constexpr Size DEFAULT_ASSET_SPRITE_SHADER = 0xdef000000000000b;
	constexpr Size DEFAULT_ASSET_SPRITE_MATERIAL_TEMPLATE = 0xdef000000000000f;
	constexpr Size DEFAULT_ASSET_TEXT_SHADER = 0xdef000000000000c;
	constexpr Size DEFAULT_ASSET_TEXT_MATERIAL_TEMPLATE = 0xdef0000000000010;
	constexpr Size DEFAULT_ASSET_UI_MATERIAL_TEMPLATE = 0xdef0000000000011;
	constexpr Size DEFAULT_ASSET_TEXTURE = 0xdef0000000000000;

#pragma endregion

#pragma region Color

	constexpr Size COLOR_SHAMT_R = 0;
	constexpr Size COLOR_SHAMT_G = 8;
	constexpr Size COLOR_SHAMT_B = 16;
	constexpr Size COLOR_SHAMT_A = 24;

#pragma endregion

#pragma region Defaults

	/// <summary>
	/// The default capacity that collections used, if not explicitly given one.
	/// </summary>
	constexpr Size DEFAULT_COLLECTION_SIZE = 16;

	/// <summary>
	/// The default threshold for rehashing a hashed collection.
	/// </summary>
	constexpr Float DEFAULT_COLLECTION_REHASH_THRESHOLD = 0.75f;

	/// <summary>
	/// The default width of a Canvas.
	/// </summary>
	constexpr Int DEFAULT_CANVAS_RESOLUTION_X = 1920;

	/// <summary>
	/// The default height of a Canvas.
	/// </summary>
	constexpr Int DEFAULT_CANVAS_RESOLUTION_Y = 1080;

#pragma endregion

#pragma region Extensions

	constexpr Char const* EXTENSION_MINTY = ".minty";

	constexpr Char const* EXTENSION_ANIMATION = ".ani.minty";
	constexpr Char const* EXTENSION_ANIMATOR = ".anr.minty";
	constexpr Char const* EXTENSION_CONTEXT = EXTENSION_MINTY;
	constexpr Char const* EXTENSION_AUDIO_CLIP_WAV = ".wav";
	constexpr Char const* EXTENSION_AUDIO_CLIP_MP3 = ".mp3";
	constexpr Char const* EXTENSION_BITMAP = ".bmp";
	constexpr Char const* EXTENSION_CAMERA = ".cam.minty";
	constexpr Char const* EXTENSION_CSV = ".csv";
	constexpr Char const* EXTENSION_FONT = ".fnt.minty";
	constexpr Char const* EXTENSION_FONT_VARIANT = ".fnt";
	constexpr Char const* EXTENSION_JPEG = ".jpeg";
	constexpr Char const* EXTENSION_JPG = ".jpg";
	constexpr Char const* EXTENSION_MATERIAL = ".mat.minty";
	constexpr Char const* EXTENSION_MATERIAL_TEMPLATE = ".mtp.minty";
	constexpr Char const* EXTENSION_MESH_OBJECT = ".obj";
	constexpr Char const* EXTENSION_META = ".meta";
	constexpr Char const* EXTENSION_PNG = ".png";
	constexpr Char const* EXTENSION_RENDER_PASS = ".rpa.minty";
	constexpr Char const* EXTENSION_RENDER_TARGET = ".rta.minty";
	constexpr Char const* EXTENSION_SCENE = ".sce.minty";
	constexpr Char const* EXTENSION_SCRIPT = ".cs";
	constexpr Char const* EXTENSION_SHADER = ".sha.minty";
	constexpr Char const* EXTENSION_SHADER_CODE = ".glsl";
	constexpr Char const* EXTENSION_SHADER_CODE_FRAGMENT = ".frag";
	constexpr Char const* EXTENSION_SHADER_CODE_VERTEX = ".vert";
	constexpr Char const* EXTENSION_SHADER_MODULE = ".spv";
	constexpr Char const* EXTENSION_SPRITE = ".spr.minty";
	constexpr Char const* EXTENSION_TEXT = ".txt";
	constexpr Char const* EXTENSION_WRAP = ".wrap";

#pragma endregion

#pragma region Handle

	constexpr Handle INVALID_HANDLE = UINT_MAX;

#pragma endregion

#pragma region Indexing

	/// <summary>
	/// Represents an invalid index.
	/// </summary>
	constexpr Size INVALID_INDEX = -1;

#pragma endregion

#pragma region Input

	/// <summary>
	/// The threshold for a joystick to be considered non-zero.
	/// </summary>
	constexpr Float JOYSTICK_DEADZONE = 0.1f;

#pragma endregion

#pragma region Layer

	/// <summary>
	/// No Layers.
	/// </summary>
	constexpr Layer LAYER_NONE = 0;

	/// <summary>
	/// All Layers.
	/// </summary>
	constexpr Layer LAYER_ALL = ~0;

	/// <summary>
	/// The Default Layer.
	/// </summary>
	constexpr Layer LAYER_DEFAULT = 1;

	/// <summary>
	/// The maximum number of Layers that can be used in the engine.
	/// </summary>
	constexpr Layer LAYER_COUNT = 32;

#pragma endregion

#pragma region Minty

	constexpr Char const* MINTY_NAME = "Minty";
	constexpr UInt MINTY_VERSION_MAJOR = 0;
	constexpr UInt MINTY_VERSION_MINOR = 1;
	constexpr UInt MINTY_VERSION_PATCH = 0;
	constexpr UInt MINTY_VERSION = MINTY_MAKE_VERSION(MINTY_VERSION_MAJOR, MINTY_VERSION_MINOR, MINTY_VERSION_PATCH);

#pragma endregion

#pragma region Physics

	constexpr Float DEFAULT_PHYSICS_GRAVITY = -9.81f;
	constexpr Float DEFAULT_PHYSICS_TIME_STEP = 1.0f / 60.0f;
	constexpr Float DEFAULT_PHYSICS_RAYCAST_DISTANCE = 1000.0f;

#pragma endregion

#pragma region Render

	constexpr Size FRAMES_PER_FLIGHT = 2;

#pragma endregion

#pragma region Time

	constexpr TimeElapsed ONE_NANOSECOND = 1ll;
	constexpr TimeElapsed ONE_MICROSECOND = ONE_NANOSECOND * 1000ll;
	constexpr TimeElapsed ONE_MILLISECOND = ONE_MICROSECOND * 1000ll;
	constexpr TimeElapsed ONE_SECOND = ONE_MILLISECOND * 1000ll;
	constexpr TimeElapsed ONE_MINUTE = ONE_SECOND * 60ll;
	constexpr TimeElapsed ONE_HOUR = ONE_MINUTE * 60ll;

#pragma endregion

#pragma region Text

	constexpr Char const* TEXT_EMPTY = "";
	constexpr Char const* TEXT_WHITESPACE = " \n\r\t\v\b\f";
	constexpr Char const* TEXT_OPEN = "([{<\"";
	constexpr Char const* TEXT_CLOSE = ")]}>\"";

#pragma endregion

#pragma region Units of Measurement

	/// <summary>
	/// The number of bytes in a byte.
	/// </summary>
	constexpr Size B = sizeof(Byte);

	/// <summary>
	/// The number of bytes in a kilobyte.
	/// </summary>
	constexpr Size KB = 1024 * B;

	/// <summary>
	/// The number of bytes in a megabyte.
	/// </summary>
	constexpr Size MB = 1024 * KB;

	/// <summary>
	/// The number of bytes in a gigabyte.
	/// </summary>
	constexpr Size GB = 1024 * MB;

#pragma endregion

#pragma region UUID

	constexpr ID INVALID_ID = 0;

#pragma endregion

#pragma region Wrap

	/// <summary>
	/// The first bytes in any Wrap file.
	/// </summary>
	constexpr Char const* WRAP_MAGIC = "WRAP";

	/// <summary>
	/// The number of magic bytes in a Wrap file.
	/// </summary>
	constexpr Size WRAP_MAGIC_SIZE = 4;

	/// <summary>
	/// The maximum size of a Wrap header path.
	/// </summary>
	constexpr Size const WRAP_HEADER_PATH_SIZE = 100;

	/// <summary>
	/// The maximum size of a Wrap header name.
	/// </summary>
	constexpr Size const WRAP_HEADER_NAME_SIZE = 50;

	/// <summary>
	/// The maximum size of a Wrap entry path.
	/// </summary>
	constexpr Size const WRAP_ENTRY_PATH_SIZE = 255;

	/// <summary>
	/// The current Wrap version.
	/// </summary>
	constexpr uint16_t const WRAP_VERSION = 0;

#pragma endregion
}