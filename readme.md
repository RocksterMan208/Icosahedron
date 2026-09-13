# This is an implementation of using icosahedrons for generating sphere meshes.
### This is done through subdividing a base icosahedron a set number of times and then uploading the finished mesh to OpenGL for rendering

# Compilation
Compilation is handled through CMmake, but the following libraries are still required:
- glfw3
- glm
- OpenGL (typically handled through the installation of mesa on linux filesystems)

### To compile:
You can compile with these following commands.</br>
```
cmake -S . -B build && cmake --build
```
Then you can run the executable outputted from CMake.
```
./gl
```
> [!NOTE]
> CMake can be ran through Visual Studio Code or some other IDEs that have the extension installed.
