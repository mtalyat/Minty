Minty Game Engine
======
A basic C++ ECS game engine for pixel-based games, developed by Mitchell Talyat/BigMintyMitch (hence, Minty Game Engine).

NOTE: THIS PROJECT HAS BEEN ARCHIVED. It has been replaced with the more advanced version of the engine, using Vulkan: [https://github.com/mtalyat/Minty-Engine](https://github.com/mtalyat/Minty-Engine).

# Features

* A basic game engine design, all written in C++.
* Uses an Entity-Component-System design, to ensure efficient iteration of all objects within the game.
* Many common classes and structs provided, such as Rect.
* Based on SDL2, so it will have the same portability as SDL2.

# Motivation

The main motivation for this project is to create an efficient game engine for a pixel-based game I am working on, that is meant to simulate many moving pixels at the same time, simular to many falling sand simulations that have been created in the past. In order to do that, I felt it was easiest to create an engine from scratch, so that I had full control over the data and where the code could be improved upon, compared to using a generic game engine, which might not be efficient enough for what I have in mind.

# Libraries

The Minty game engine takes advantage of the following libraries:

* [SDL2](https://www.libsdl.org/)
* [EnTT](https://github.com/skypjack/entt)
* [FastNoiseLite](https://github.com/Auburn/FastNoiseLite)
* [json](https://github.com/nlohmann/json)

# Notes

This library will constantly be updated, changed, and improved by me until I believe it is in a state that will no longer require large changes. As this is still heavily in development, it is possible that I will remove or change entire chunks of code as time goes on, to suit my needs. Not to mention, I am always learning, and may change things as I discover new and better ways of doing things.

A guide to using the engine will be added to this repository once the engine is more functional and more stable.
