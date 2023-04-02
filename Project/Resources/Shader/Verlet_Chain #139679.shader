//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Verlet/Chain" {
Properties {
_Chain1 ("_Chain1", 2D) = "white" { }
_Chain1Size ("Chain1 Size", Vector) = (1,1,1,1)
_Chain2 ("_Chain2", 2D) = "white" { }
_Chain2Size ("Chain2 Size", Vector) = (1,1,1,1)
_Length ("Size", Range(0, 3)) = 0.25
_Color ("Color", Color) = (1,1,1,1)
}
SubShader {
 Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  Cull Off
  GpuProgramID 11807
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PROCEDURAL_INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "PROCEDURAL_INSTANCING_ON" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}