//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/EmmisiveFilterShader" {
Properties {
_MainTex ("Source", 2D) = "white" { }
}
SubShader {
 Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
 Pass {
  Name "Filter Emissive"
  Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
  ZWrite Off
  Cull Off
  GpuProgramID 52537
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
}
}
}