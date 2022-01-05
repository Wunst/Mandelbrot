# A Mandelbrot zoom using OpenGL

## Controls
- Arrow keys: Move
- Return: Zoom in
- Backspace: Zoom out
- Escape: Quit

## Notes
- You can only zoom down to 32-bit floating-point precision
- Feel free to edit the fragment shader to change the colors or even make other fractals!
- The Makefile is written for a GNU environment, but you can change the variables to your compilers and flags

## How does it work?
Most of the work is done in the shader. The C code just creates an OpenGL context, loads the shader, and draws a shaded quad over the entire window.

