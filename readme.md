# This is an implementation of using icosahedrons for generating sphere meshes.
### This is done through subdividing a base icosahedron a set number of times and then uploading the finished mesh to OpenGL for rendering.

<img width="1916" height="1069" alt="image" src="https://github.com/user-attachments/assets/2a3f7946-3a94-491c-b44a-dda497fc5d6c" />

<img width="1912" height="1074" alt="image" src="https://github.com/user-attachments/assets/73caeecf-9a42-4b16-8232-cdca26f5d09b" />


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
