# trace-engine

Trace Engine is a hobbiest project focused on creating a proof of concept for smoothest and easist asset pipeline for game development. I'm not interested in working on the latest graphics features, or the most advanced abstraction layers, or support for multiple platforms. Those things can come later after we've built the best pipeline.

* Tools
- Blender
- V8 JavaScript Engine

* Work

1. Setup Project
+ VS Code Project for Windows
+ Makefile Setup
+ Create Window
+ Initialize Device Context
+ Setup Hardcoded Camera, Viewport
+ Draw Triangle with Hardcoded Color Vertecies
2. Simple Rendering 
- Shade Triangle with Material
- Simple Scene
- Single Directional Light
- Model with Meshes
- Replace Triangle with Model, 1 Cubes + 1 Trangle for Meshes
3. Info
- Seperate Console Window (Std In/Out)
- Seperate Debug Window (Std Err)
4. Console Commands
- Select Object by Name
- Set Material Property
- Select Camera by Name
- Set Camera Property
- Select Viewport by Name
- Set Viewport Property
6. V8 JS Engine (JSON Support)
- Load Properties From File Command 
- Load Scene From File Command


Notes --

I had to change the rpcndr.h file in CYGWIN to update the verion to 500, I assume because of the October update.