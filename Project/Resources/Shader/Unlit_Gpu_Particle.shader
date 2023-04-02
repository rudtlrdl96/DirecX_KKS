//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Unlit/Gpu_Particle" {
Properties {
_MainTex ("Albedo (RGB)", 2D) = "white" { }
_Color ("Color", Color) = (1,1,1,1)
_Size ("Size", Vector) = (1,1,1,1)
}
SubShader {
 Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
  ZWrite Off
  Cull Off
  GpuProgramID 1909
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