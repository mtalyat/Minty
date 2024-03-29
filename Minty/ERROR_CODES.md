# Error Codes

| Code | Error Message | File | Function |
| --- | --- | --- | --- |
| 00001 | "Failed to init SDL." | M_Engine.cpp | initialize() |
| 00002 | "Failed to init IMG." | M_Engine.cpp | initialize() |
| 00003 | "Failed to create window." | M_Screen.cpp | Screen() |
| 00004 | "Failed to create renderer." | M_Screen.cpp | Screen() |
| 00005 | "Failed to load icon." | M_Screen.cpp | Screen() |
| 00006 | "Failed to set logical render size." | M_Screen.cpp | Screen() |
| 00007 | "Could not load image at path '...'." | M_Resources.cpp | resources_load_image() |
| 00008 | "Failed to create image from resources at path: '...'." | M_Resources.cpp | resources_load_images() |
| 00009 | "Failed to create image from resources at path: '...'." | M_Resources.cpp | resources_load_all_images() |
| 00010 | "Engine aborted. No active scene." | M_Engine.cpp | run() |

| 00012 | "Engine aborted. Failed to start game." | M_Engine.cpp | run() |
| 00013 | "Engine aborted. Failed to stop game." | M_Engine.cpp | run() |

| 00015 | "File not found at: ..." | M_File.cpp | file_readAllText() |
| 00016 | "File not found at: ..." | M_File.cpp | file_readAllLines() |
| 00017 | "File not found at: ..." | M_File.cpp | file_readAllCSV() |
| 00018 | "File was empty: ..." | M_File.cpp | file_readAllCSV() |
| 00019 | "Could not find input map '...'." | M_Input.cpp | select() |
| 00020 | "Failed to unload scene '...'." | M_SceneManager.cpp | unload() |
| 00021 | "Failed to load scene '...'." | M_SceneManager.cpp | load() |
| 00022 | "No scene found for name '...'." | M_SceneManager.cpp | load() |
| 00023 | "Failed to fullscreen window." | M_Screen.cpp | Screen() |
| 00024 | "Failed to update active scene." | M_Engine.cpp | run() |
| 00025 | "Could not blit surface when slicing sprite." | M_Sprite.cpp | slice() |
| 00026 | "No camera has been instantiated in the Scene." | M_S_RenderSystem.cpp | update() |
| 00027 | "Could not lock surface." | M_ProceduralSprite.cpp | create() |
| 00028 | "Duplicate color in ProceduralSprite." | M_ProceduralSprite.cpp | ProceduralSprite() |
| 00029 | "No index found for given ID." | M_ProceduralSprite.cpp | generate() |
| 00030 | "Could not generate text sprite." | M_Text.cpp | apply() |
| 00031 | "Failed to create Canvas texture." | M_Canvas.cpp | Canvas() |
| 00032 | "Failed to lock Canvas." | M_Canvas.cpp | lock() |
| 00033 | "Failed to fixed update active scene." | M_Engine.cpp | run() |
| 00034 | "Could not blit surface when copying sprite." | M_Sprite.cpp | copy() |
| 00035 | "Failed to load music at path: '...'." | M_Resources.cpp | resources_load_music() |
| 00036 | "Failed to load sound at path: '...'." | M_Resources.cpp | resources_load_sound() |
| 00037 | "Music not found: '...'." | M_S_AudioSystem.cpp | playMusic() |
| 00038 | "Sound not found: '...'." | M_S_AudioSystem.cpp | playSound() |
| 00039 | "Failed to init AUDIO." | M_Engine.cpp | initialize() |
| 00040 | "Failed to init MIXER." | M_Engine.cpp | initialize() |