
attribute highp vec3  rv_Position;
attribute highp vec3  rv_Color;
uniform   highp mat4  u_ModelViewProjectionMatrix;
uniform   highp float u_strength;
uniform   highp vec3  u_filter_color;
varying   highp vec3  outColor;

void main(void)
{
    gl_Position = u_ModelViewProjectionMatrix * vec4(rv_Position,1);
    vec3 new_color = mix(rv_Color, u_filter_color, u_strength);
    outColor = new_color;
}
