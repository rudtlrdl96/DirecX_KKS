//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Unlit/Hotel Boss Beam Shader" {
Properties {
_EdgeSmoothness ("Edge Smoothness", Float) = 100
_Thickness ("Thickness", Float) = 20
_Color ("Laser Color", Color) = (1,1,1,1)
_Sequence ("Sequence", Range(0, 1)) = 0
_BeamExpandRate ("Beam Expand Rate", Range(0, 5)) = 1
_NoiseFrequency ("Noise Frequency", Range(1, 100)) = 50
_NoiseLength ("Noise Length", Range(0.01, 1)) = 0.25
_NoiseIntensity ("Noise Intensity", Range(0, 0.1)) = 0.02
}
SubShader {
 Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
 Pass {
  Tags { "QUEUE" = "Transparent" "RenderType" = "Transparent" }
  Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
  ZWrite Off
  GpuProgramID 32974
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