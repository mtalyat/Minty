# Minty Engine

Minty is a modular C++23 game engine in active development, with a strong emphasis on clear boundaries between subsystems, data-driven content, and portable build tooling.

The current implementation already demonstrates a complete vertical slice of engine fundamentals: asset loading, window/event plumbing, render resource creation, audio playback, and ECS-oriented world foundations.

This is the latest iteration of the project. Each new iteration involves better design and practices, especially this one!

## What It Can Do Today

- Build as independent static-library layers with dependency-aware composition.
- Load typed engine resources from `.minty` asset definitions.
- Parse geometry data (including OBJ import path) into runtime-friendly vertex/index containers.
- Create and manage rendering resources (textures, shaders, pipelines, render passes, targets, surfaces).
- Create windows and process input/window events in a runtime loop.
- Create/play audio clips through the audio manager.
- Manage entities/components through an EnTT-backed ECS manager.
- Serialize and deserialize engine data through generic reader/writer pipelines.

In other words: the engine is past "hello world" and into a working systems-integration stage.

## Architecture At a Glance

Minty is organized as layered modules (for example: `Platform`, `Core`, `Resource`, `Window`, `Event`, `Input`, `Render`, `Audio`, `World`, `Scene`).

Each layer is compiled as an explicit unit, and top-level usage can be simplified through the single include facade (`Minty.h`) when desired.

### Core Design Patterns

1. Layered Architecture

	The engine is split into focused layers with intentional dependency direction.

	Why it helps:
- Keeps platform-specific concerns isolated.
- Reduces accidental coupling between high-level gameplay code and low-level systems.
- Makes large refactors safer because boundaries are explicit.

2. Manager-Oriented Subsystems + Handle-Based Lifetimes

	Subsystems like resources, rendering, audio, and windowing are exposed through manager classes and typed handles.

	Why it helps:
- Centralizes ownership/lifetime rules.
- Avoids raw pointer churn across subsystems.
- Creates clean integration points for tooling and diagnostics.

3. PIMPL for Runtime Backends

	Several managers hide implementation details behind `Impl` types.

	Why it helps:
- Keeps public headers stable while backend internals evolve.
- Reduces compile-time dependency spread.
- Makes backend swaps/experiments less disruptive.

4. ECS Foundation (EnTT)

	Entity/component operations are routed through `EntityManager` with EnTT as the storage/runtime backbone.

	Why it helps:
- Enables data-oriented iteration and composition over inheritance-heavy object trees.
- Scales feature growth by adding components/systems without rewriting base hierarchies.

5. Data-Driven Serialization via Templates + Concepts

	Generic `Reader`/`Writer` paths dispatch through `Serializer<T>` and `Parser<T>` specializations.

	Why it helps:
- New asset/component types plug in with predictable extension points.
- Serialization logic stays close to type definitions.
- Supports both structured object IO and primitive/string parsing flows.

6. Selective Singleton Access (Where Appropriate)

	Some globally unique services expose singleton access patterns.

	Why it helps:
- Enforces uniqueness where only one authoritative instance should exist.
- Simplifies integration in systems that need a globally coordinated registry.

## Typical Runtime Flow (Current Demo)

```mermaid
flowchart LR
	 A[Load .minty resources] --> B[Create AudioManager and play clip]
	 B --> C[Create WindowManager and window]
	 C --> D[Create RenderManager bound to window]
	 D --> E[Create render objects from resources]
	 E --> F[Process window/events loop]
```

## Build and Run

Prerequisites:

* CMake
* A C++23 capable compiler (Visual Studio works best)

From the repository:

1. Build the engine layers via `Engine/build_all.bat`.
2. Build the demo via `Demo/build.bat`.
3. Run the demo via `Demo/run.bat`.

The build setup uses CMake with configurable options for backend toggles (for example Vulkan/SoLoud compile definitions), output routing by configuration, and modular target assembly by layer.

## Current Maturity Snapshot

Minty currently shows strong architectural direction with practical subsystem integration already in place. Some areas are still being expanded (and a subset of serializers are explicitly marked as not yet implemented), but the foundational structure is intentionally designed to scale from prototype workflows into larger production-style pipelines.
