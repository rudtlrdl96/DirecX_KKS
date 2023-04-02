//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/Tornado" {
Properties {
_CircularMotionSize ("Circular Motion Size", Float) = 0.4
_CircularMotionSpeed ("Circular Motion Speed", Float) = 3
_CircularMotionFrequency ("Circular Motion Frequency", Float) = 2
_WaveSize ("Wave Size", Float) = 0.1
_WaveSpeed ("Wave Speed", Float) = 0.3
_WaveFrequency ("Wave Frequency", Float) = 18
_NoiseTexture ("Noise Texture", 2D) = "white" { }
_NoiseScrollSpeed ("Noise Scroll Speed x2 XY/ZW", Vector) = (0.1,-0.5,-0.1,-1)
_StormSpeed ("Storm Speed", Range(0, 1)) = 0.5
[ToggleUI] _Fresnel ("Fresnel", Float) = 0
Cut_Off_Value ("Cut Off Value", Float) = 5
PixelSize ("PixelSize", Float) = 12
}
SubShader {
 Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
 Pass {
  Name "Pass"
  Tags { "QUEUE" = "Transparent+0" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
  ZWrite Off
  Cull Off
  GpuProgramID 44122
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
  Cull Off
  GpuProgramID 105389
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
  Cull Off
  GpuProgramID 172202
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