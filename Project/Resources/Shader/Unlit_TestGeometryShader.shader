//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Unlit/TestGeometryShader" {
Properties {
_MainTex ("Texture", 2D) = "white" { }
_TessEdge ("Tess Edge", Float) = 2
_Distortion ("Distortion", Range(0, 0.12)) = 1
_Sequence ("Sequence", Range(0, 3)) = 0
}
SubShader {
 LOD 100
 Tags { "RenderType" = "Opaque" }
 Pass {
  LOD 100
  Tags { "RenderType" = "Opaque" }
  GpuProgramID 3949
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
Program "hp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
Program "dp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
}
}
}
}