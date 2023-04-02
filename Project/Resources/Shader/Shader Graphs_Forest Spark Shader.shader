//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/Forest Spark Shader" {
Properties {
_AlphaClipThreshold ("AlphaClipThreshold", Float) = 0.01
Color_3013A882 ("Color", Color) = (0,0,0,0)
Texture2D_4D935D6E ("MainTex", 2D) = "white" { }
}
SubShader {
 Tags { "QUEUE" = "Geometry+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
 Pass {
  Name "Pass"
  Tags { "QUEUE" = "Geometry+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
  GpuProgramID 2510
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
  GpuProgramID 108265
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
  GpuProgramID 168437
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