//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/Aimline Shader" {
Properties {
_MainTex ("_MainTex", 2D) = "white" { }
_Color ("_Color", Color) = (0.7830189,0.7830189,0.7830189,1)
NoiseScale ("NoiseScale", Float) = 25
NoiseSpeed ("NoiseSpeed", Vector) = (-0.7,0,0,0)
Noise_Effect_Amount ("Noise Effect Amount", Float) = 1
_Sequence ("_Sequence", Float) = 0
}
SubShader {
 Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
 Pass {
  Name "Pass"
  Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
  Blend One One, One One
  ZWrite Off
  Cull Off
  GpuProgramID 30798
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
  Blend One One, One One
  Cull Off
  GpuProgramID 107253
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
  Blend One One, One One
  ColorMask 0 0
  Cull Off
  GpuProgramID 185001
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