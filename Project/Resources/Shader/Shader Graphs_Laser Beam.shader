//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/Laser Beam" {
Properties {
_MainTex ("_MainTex", 2D) = "white" { }
_AlphaClipThreshold ("AlphaClipThreshold", Float) = 0.001
_Bright_Color ("Bright Color", Color) = (0.504717,0.9104583,1,0)
_Blink_Speed ("Blink Speed", Float) = 2
_Blink_Intenity ("Blink_Intensity", Float) = 0.2
}
SubShader {
 Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
 Pass {
  Name "Pass"
  Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
  ZWrite Off
  GpuProgramID 34017
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
  Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
  GpuProgramID 76812
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
  Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
  ColorMask 0 0
  GpuProgramID 163222
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