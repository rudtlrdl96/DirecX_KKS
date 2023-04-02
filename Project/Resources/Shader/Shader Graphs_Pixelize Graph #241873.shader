//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/Pixelize Graph" {
Properties {
PixelSize ("PixelSize", Float) = 12
[ToggleUI] Use_Pixelize ("Use Pixelize", Float) = 0
Emission_Color ("Emission Color", Color) = (1,1,1,1)
Base_Color ("Base Color", Color) = (1,1,1,0)
AmbientColor ("AmbientColor", Color) = (0.2,0.2,0.2,0)
}
SubShader {
 Tags { "QUEUE" = "Geometry+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
 Pass {
  Name "Pass"
  Tags { "QUEUE" = "Geometry+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
  GpuProgramID 6983
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
 Pass {
  Name "ShadowCaster"
  Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Geometry+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
  GpuProgramID 105885
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
 Pass {
  Name "DepthOnly"
  Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "Geometry+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
  ColorMask 0 0
  GpuProgramID 193140
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
Fallback "Hidden/Shader Graph/FallbackError"
}