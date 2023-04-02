//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/CopyDepth" {
Properties {
}
SubShader {
 Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
 Pass {
  Name "CopyDepth"
  Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
  ColorMask 0 0
  ZTest Always
  GpuProgramID 53695
Program "vp" {
SubProgram "d3d11 " {
Keywords { "_DEPTH_NO_MSAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_DEPTH_MSAA_2" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_DEPTH_MSAA_4" }
"// shader disassembly not supported on DXBC"
}
}
Program "fp" {
SubProgram "d3d11 " {
Keywords { "_DEPTH_NO_MSAA" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_DEPTH_MSAA_2" }
"// shader disassembly not supported on DXBC"
}
SubProgram "d3d11 " {
Keywords { "_DEPTH_MSAA_4" }
"// shader disassembly not supported on DXBC"
}
}
}
}
}