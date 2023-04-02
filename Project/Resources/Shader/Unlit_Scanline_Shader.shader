//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Unlit/Scanline_Shader" {
Properties {
_MainTex ("Texture", 2D) = "white" { }
_ScanlineSpeed ("Scanline Speed", Float) = 1
_SlimlineDensity ("Slimline Density", Float) = 1
_MinIntensity ("Min Intensity", Float) = 1
_ScanlineIntensity ("Scanline Intenstiy", Float) = 1
_DistortionScale ("Distortion Scale", Float) = 1
_DistortionSpeed ("Distortion speed", Float) = 1
_DistortionStrength ("Distortion strength", Float) = 1
}
SubShader {
 Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZTest Off
  ZWrite Off
  GpuProgramID 2375
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