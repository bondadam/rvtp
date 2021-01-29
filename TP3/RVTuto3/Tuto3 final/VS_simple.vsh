attribute highp vec3 rv_Position;
attribute highp vec3 rv_Color;
uniform   highp mat4 u_ModelViewProjectionMatrix;
uniform   highp float u_opacity;
uniform   highp vec4 u_color;
varying   highp vec4 outColor;

void main(void)
{
    gl_Position = u_ModelViewProjectionMatrix * vec4(rv_Position,1);
    outColor = vec4(rv_Color * u_color.rgb, u_opacity);
}
