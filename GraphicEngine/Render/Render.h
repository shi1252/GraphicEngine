#pragma once
class BaseGeometry;
class Vertex;

void DrawCall(BaseGeometry* mesh);
Vertex VertexShader(Vertex v);
//DWORD FragmentShader(Frag f);