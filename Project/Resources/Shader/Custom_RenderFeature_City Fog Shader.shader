//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Custom/RenderFeature/City Fog Shader" {
Properties {
_MainTex ("Texture", 2D) = "white" { }
_CloudTex ("Cloud Texture", 2D) = "white" { }
_FrontFogOffset ("Front Fog Offset", Vector) = (1,1,0,0)
}
SubShader {
 Tags { "RenderType" = "Opaque" }
 Pass {
  Tags { "RenderType" = "Opaque" }
  GpuProgramID 45746
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