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
| 00011 | "Engine aborted. Failed to create game." | M_Engine.cpp | run() |
| 00012 | "Engine aborted. Failed to start game." | M_Engine.cpp | run() |
| 00013 | "Engine aborted. Failed to stop game." | M_Engine.cpp | run() |
| 00014 | "Engine aborted. Failed to destroy game." | M_Engine.cpp | run() |
| 00015 | "File not found at: ..." | M_File.cpp | file_readAllText() |
| 00016 | "File not found at: ..." | M_File.cpp | file_readAllLines() |
| 00017 | "File not found at: ..." | M_File.cpp | file_readAllCSV() |
| 00018 | "File was empty: ..." | M_File.cpp | file_readAllCSV() |
| 00019 | "Could not find input map '...'." | M_Input.cpp | select() |
| 00020 | "Failed to stop scene '...'." | M_SceneManager.cpp | load() |
| 00021 | "Failed to start scene '...'." | M_SceneManager.cpp | load() |
| 00022 | "No scene found for name '...'." | M_SceneManager.cpp | load() |
| 00023 | "Failed to fullscreen window." | M_Screen.cpp | Screen() |