//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Custom/RenderFeature/Screen Mask" {
Properties {
_MainTex ("Texture", 2D) = "white" { }
}
SubShader {
 Tags { "RenderType" = "Opaque" }
 Pass {
  Name "Draw TO Mask Map"
  Tags { "RenderType" = "Opaque" }
  GpuProgramID 55505
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
  Name "Draw ScreenTex"
  Tags { "RenderType" = "Opaque" }
  GpuProgramID 97526
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