//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/Glitch" {
Properties {
_MainTex ("_MainTex", 2D) = "white" { }
_AlphaClipThreshold ("AlphaClipThreshold", Range(0, 1)) = 0.001
_Noise_Speed ("Noise Speed", Float) = 1
Noise_Threshold ("Noise Threshold", Range(0, 1)) = 0.3
_Noise_Distance ("Noise Distance", Range(0, 60)) = 0.1
Noise_Divider ("Noise Divider", Float) = 800
Color_Noise_Threshold ("Color Noise Threshold", Range(0, 1)) = 0.6
}
SubShader {
 Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
 Pass {
  Name "Pass"
  Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
  ZWrite Off
  GpuProgramID 41462
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SAMPLE_GI" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SAMPLE_GI" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "ShadowCaster"
  Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
  GpuProgramID 94025
Program "vp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SMOOTHNESS_TEXTURE_ALBEDO_CHANNEL_A" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_SMOOTHNESS_TEXTURE_ALBEDO_CHANNEL_A" }
"// shader disassembly not supported on DXBC"
}
}
}
 Pass {
  Name "DepthOnly"
  Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
  ColorMask 0 0
  GpuProgramID 187695
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